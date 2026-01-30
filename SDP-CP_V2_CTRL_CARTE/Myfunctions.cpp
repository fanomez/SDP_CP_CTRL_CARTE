#include "MyFunctions.h"

// ----------------------------------------------------------------------------------------
// Fonction pour écrire dans un registre du MCP23S08
// ----------------------------------------------------------------------------------------
void writeRegister(uint8_t reg, uint8_t value, uint8_t MCP_addr, uint8_t csPin, SPIClass& spi) {
	digitalWrite(csPin, LOW);              // Sélectionner le MCP23S08
	spi.transfer(MCP_addr);            // Envoyer l'adresse avec le bit d'écriture
	spi.transfer(reg);                      // Envoyer le registre � �écrire
	spi.transfer(value);                    // Envoyer la valeur
	digitalWrite(csPin, HIGH);             // D�s�lectionner le MCP23S08
}
// ----------------------------------------------------------------------------------------
// Fonction pour lire un registre du MCP23S08
// ----------------------------------------------------------------------------------------
uint8_t readRegister(uint8_t reg, uint8_t MCP_addr, uint8_t csPin, SPIClass& spi) {
	uint8_t value;
	digitalWrite(csPin, LOW);              // S�lectionner le MCP23S08
	spi.transfer(MCP_addr | 0x01);     // Envoyer l'adresse avec le bit de lecture
	spi.transfer(reg);                      // Envoyer le registre � lire
	value = spi.transfer(0x00);             // Lire la valeur
	digitalWrite(csPin, HIGH);             // D�s�lectionner le MCP23S08
	return value;
}

// ==================================================================================================================================================
// Init extendeur de BUS
// ==================================================================================================================================================
void Configuration_GPIO_EXP(SPIClass& spi,uint8_t clkPin,uint8_t misoPin,uint8_t mosiPin,uint8_t cs3Pin,uint8_t ethRst,uint8_t MCPaddr){

  // ==============================================================
  // Initialisation Extendeur GPIO
  // ==============================================================
    // spi.begin(clkPin,misoPin,mosiPin,cs3Pin);
    // delay(2000);

    // Configurer la broche CS en sortie
    pinMode(ethRst, OUTPUT); 
    digitalWrite(ethRst, HIGH); // Activation de l'extendeur de bus
    pinMode(cs3Pin, OUTPUT);
    digitalWrite(cs3Pin, HIGH); // Activation de l'extendeur de bus

    // writeRegister(0x05,0b00111110,MCPaddr,cs3Pin,spi);  //Registre IOCON

    // Initialisation du MCP23S08 : toutes les broches en sortie
    writeRegister(0x00, 0x00,MCPaddr,cs3Pin,spi); // Registre IODIR : toutes les broches en sortie

    // Mettre toutes les broches à 1 (GPIO)
    writeRegister(0x09, 0xFF,MCPaddr,cs3Pin,spi); // Registre GPIO : mettre toutes les broches à 1



}
// ----------------------------------------------------------------------------------------
// Gestion écran
// ----------------------------------------------------------------------------------------
// Color definitions
  const uint16_t Display_Color_Black = 0x0000;
  const uint16_t Display_Color_White = 0xFFFF;
  const uint16_t Display_Color_Blue = 0x01FF; // Jaune


void initEcran(Adafruit_ST7789& tft, uint16_t* counter,uint16_t* temps) {
    tft.init(240, 320);
    // Initialisation logicielle de l'écran

    tft.setRotation(1);
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(10); // Adjust text size as needed
    tft.setCursor(5, 5);

            // Print initial counter and time values
    printFormattedCounter(tft, counter, 5, 5);
    printFormattedTime(tft,  temps, 5, 100);
}


void printFormattedCounter(Adafruit_ST7789& tft, uint16_t* number, int x, int y) {
    char buffer[6]; // Buffer to hold the formatted number
    sprintf(buffer, "%05d", *number); // Format the number with three digits
    tft.setCursor(x, y);
    tft.print(buffer); // Print the formatted number
}

void printFormattedTime(Adafruit_ST7789& tft, uint16_t* number, int x, int y) {
    char buffer[6]; // Buffer to hold the formatted number
    sprintf(buffer, "%05d", *number); // Format the number with three digits
    tft.setCursor(x, y);
    tft.print(buffer); // Print the formatted number
}

void updateFormattedCounter(Adafruit_ST7789& tft, uint16_t* oldNumber, uint16_t* newNumber, int x, int y) {
    char oldBuffer[6], newBuffer[6];
    sprintf(oldBuffer, "%05u", *oldNumber); // Format the old number with three digits
    sprintf(newBuffer, "%05u", *newNumber); // Format the new number with three digits

    for (int i = 0; i < 5; i++) {
            // Erase the old digit       
            tft.fillRect(x + (i * 60), y,  60, 80, ST77XX_BLACK);

            // Draw the new digit
            tft.setCursor(x + (i * 60), y);
            tft.setTextColor(ST77XX_RED);
            tft.print(newBuffer[i]);
    }
}

void updateFormattedTime(Adafruit_ST7789& tft, uint16_t* oldNumber, uint16_t* newNumber, int x, int y) {
    char oldBuffer[6], newBuffer[6];
    sprintf(oldBuffer, "%05u", *oldNumber); // Format the old number with three digits
    sprintf(newBuffer, "%05u", *newNumber); // Format the new number with three digits

    for (int i = 0; i < 5; i++) {
        if (oldBuffer[i] != newBuffer[i]) {
            // Erase the old digit
            
            tft.fillRect(x + (i * 60), y, 60, 80, ST77XX_BLACK);

            // Draw the new digit
            tft.setCursor(x + (i * 60), y);
            tft.setTextColor(ST77XX_RED);
            tft.print(newBuffer[i]);
        }


        // =================================================================================
    }
}
// =============================================================================================
// COMMUNICATION GUI 
// =============================================================================================
// Fonction pour extraire les valeurs à partir du deuxième caractère
// *********************************************************************
void parseStringFromSecondChar(const char* input, void* values, uint8_t* count, int isFloat) {
    // Commencer à lire à partir du deuxième caractère
    const char* current = input + 1;
    char tempBuffer[20]; // Buffer temporaire pour extraire les valeurs
    int index = 0;
    *count = 0; // Compteur de valeurs extraites

    // Parcourir la chaîne à partir du deuxième caractère
    while (*current != '\0') {
        if (*current == ',') {
            // Lorsqu'on rencontre une virgule, convertir le buffer en nombre
            if (index > 0) {
                tempBuffer[index] = '\0';

                if (isFloat) {
                    ((float*)values)[*count] = atof(tempBuffer); // Ajouter une valeur flottante
                }
                else {
                    ((int*)values)[*count] = atoi(tempBuffer);   // Ajouter une valeur entière
                }

                (*count)++; // Incrémenter le compteur
                index = 0; // Réinitialiser le buffer
            }
        }
        else {
            // Ajouter le caractère au buffer temporaire pour construire un nombre
            tempBuffer[index++] = *current;
        }

        current++; // Passer au caractère suivant
    }

    // Ajouter la dernière valeur si présente
    if (index > 0) {
        tempBuffer[index] = '\0';

        if (isFloat) {
            ((float*)values)[*count] = atof(tempBuffer); // Ajouter une valeur flottante
        }
        else {
            ((int*)values)[*count] = atoi(tempBuffer);   // Ajouter une valeur entière
        }

        (*count)++;
    }
}
// *********************************************************************
// Extraction de valeurs séparées par des virgules
// *********************************************************************
uint16_t extractValues(char* start, uint16_t values[], char delimiter) {
    uint16_t count = 0;
    char* token = strtok(start, &delimiter);  // Divise par les virgules
    while (token != NULL) {
        values[count++] = atoi(token);  // Convertit chaque sous-chaîne en entier
        token = strtok(NULL, ",");  // Poursuit le découpage
    }
    return count;  // Retourne le nombre de valeurs extraites
}
// *********************************************************************
// Fonction pour combiner les valeurs de bits en une variable de 8 bits
// *********************************************************************
uint8_t combineBits(void* bitValues, uint8_t numBits, uint8_t valueType) {
    uint8_t result = 0;

    for (uint8_t i = 0; i < numBits; i++) {
        uint16_t intValue;

        // Vérifier le type de données (flottant ou entier)
        if (valueType == 1) { // Si 'f', c'est un tableau de float
            float* floatValues = (float*)bitValues;
            intValue = (uint16_t)floatValues[i];  // Caster en entier
        }
        else if (valueType == 0) { // Si 'i', c'est un tableau d'entiers
            intValue = ((uint16_t*)bitValues)[i];
        }
        else {
            printf("Type non supporté\n");
            return 0;
        }

        // Si la valeur entière est 1, on positionne le bit correspondant
        if (intValue == 1) {
            result |= (1 << i);  // Positionne le bit i à 1
        }
    }

    return result;
}
// ************************************************************************************************
// Fonction pour convertir un flottant en un tableau d'octets hexadécimaux (32 bits IEEE 754)
// ************************************************************************************************
void float_to_hex_array(float float_value, uint8_t byte_array[4]) {

  // Exemple : 6 => 0x 40 C0 00 00
    // Interpréter l'adresse du flottant comme un entier 32 bits
    uint32_t hex_value = *(uint32_t*)&float_value;

    // Diviser la valeur hexadécimale en 4 octets de 8 bits
    for (int i = 0; i < 4; i++) {
        byte_array[3 - i] = (hex_value >> (8 * i)) & 0xFF;  // MSB First
    }
}
// ************************************************************************************************

// ==================================================================================================================================================
// COnfiguration COM Modbus 
// ==================================================================================================================================================
void Configuration_COM_Modbus(HardwareSerial& ModBus_Uart, ModbusRTU& mb){

    ModBus_Uart.begin(115200,SERIAL_8N1,16,17);  // Initialisation XPORT/MODBUS  (16 : RX ; 17 : TX)
    // Initialisation communication modbus
    mb.begin(&ModBus_Uart);
    mb.slave(1);

}
// ==================================================================================================================================================
