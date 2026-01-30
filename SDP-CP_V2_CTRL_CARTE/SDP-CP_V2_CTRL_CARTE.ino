
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                               Définition des librairies et initialisation 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Activation/ Desactivation de certaines propriétés
// -----------------------------------------------------------------------------------------------------------
// #define ENABLE_AFFICHAGE                                   // Activer la communication avecl'écran

#define ENABLE_XPORT                                           //  Active l'initialisation du XPORT
// #define ENABLE_GPIO_EXP                                        // Active la configuation de l'extendeur de bus 
#define ENABLE_CONV_TRMS                                       // Active la communication avec le convertisseur (STM32)
// #define ENABLE_SPI                                             // Active la communicaiton avec le bus SPI

#define TEST_EN_COURS                                          // Utilisé dans la phase de développement

// ===========================================================================================================
// Librairies Arduino (téléchargée)
// ===========================================================================================================
#include <Arduino.h> 
#include <WiFi.h>                     // Permet la gestion du Wifi 
#include <ModbusRTU.h>                // Permet la gestion de la communication MODBUS 
#include <Adafruit_GFX.h>             // Permet la gestion de l'écran
#include <Adafruit_ST7789.h>          // Permet la gestion de l'écran
#include <SPI.h>                      // Permet la gestion du SPI 
#include <plcLib.h>                   // Permet la gestion de fonctions ladder
#include <EEPROM.h>                   // Permet la gestion de la mémoire EEPROM 
#include <HardwareSerial.h>           // Permet la gestion de l'UART 
#include <ArduinoJson.h>
#include <SD.h>                       // Permet la gestion de la communication avec la carte SD
#include <ETH.h>        // LAN8720
#include "esp_log.h"
// ===========================================================================================================
// Librairies de gestion OTA
// ===========================================================================================================
  #include <ESPmDNS.h>
  #include <WiFiUdp.h>
  #include <ArduinoOTA.h>
  
  #include <WebServer.h>

  WebServer server_SDP(80);    // Serveur web qui nous permettra d'accéder aux paramètres de l'ESP32 via l'interface graphique

  
  typedef enum {
    WAIT_TRIGGER,
    SEND_LOW,
    WAIT_LOW,
    SEND_HIGH,
    ENTRER_MODE_SETUP,
    CONFIG_IP_0,
    CONFIG_IP_1,
    CONFIG_IP_2,
    CONFIG_IP_3,
    CONFIG_IP_4,
    GATEWAY_IP,
    NETMASK_IP,
    TELNET_PWD,
    CONFIG_FIN,
    SAUVEGARDE,
    REINIT_CONFIG,
    TERMINE
  } EtatConfig;

  EtatConfig etat = WAIT_TRIGGER;
  TickType_t chrono;

  char result ;
  String txt;

    // Buffers pour chaque partie de l'IP
  char part0[4] = {0}, part1[4] = {0}, part2[4] = {0}, part3[4] = {0};

  int ip0, ip1, ip2, ip3;

  char c[5];

  

  const char* filename = "/donnees.bin";

// ===========================================================================================================
// Librairies personnalisé (développée par SREM)
// ===========================================================================================================
#include "definition_banque.h"           // Permet de gérer les différents registres Modbus 
#include "Banque_EEPROM.h"               // Permet de gérer la mémoire EEPROM
#include "Myfunctions.h"                 // Permet l'interaction avec l'écran et l'expandeur de bus
#include "variables_globales.h"          // Déclaration des variables globales utilisées
#include "variables_globales_basic.h"          // Déclaration des variables globales utilisées
#include <gestion_registres.h>           // Permet la gestion des différents registres
#include "perso.h"
// ===========================================================================================================
// Déclaration des éléments de communication ()
// ===========================================================================================================

HardwareSerial ModBus_Uart(1);   // Liaison UART ( XPORT <--> ESP32  ) [Communication filaire TX,RX]

ModbusRTU mb;                    // Liaison Modbus (ESP32 <--> PC)  [Communication via câble Ethernet]



int incre = 0;

// =============================================================================================================================
// Initilisation écran
// =============================================================================================================================
uint16_t counter = 0;
uint16_t temps = 0;

// Instances de la librairies permettant de gérer la communication avec l'écran :
Adafruit_ST7789 tft = Adafruit_ST7789(CS1_PIN, DC_PIN,-1);                //  Permet d'utiliser les SPI défini dans SPI.begin


uint8_t i = 0;


F_Trig ESP32_boot_falling;  // Permet de détecter le front montant pour l'activation du point d'accès wifi de l'ESP32


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                            Gestion mutlitâche
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/* On utilise un système multitâche pour gérer les différents étapes du process, allant de la reception des
 * mesures, le traitement et l'envoi des commandes ainsi que l'affichage */

// ===============================================================================================================================
// Task Handles : Ce sont des références à chaque tâche, permettant de les manipuler après leur création
// ===============================================================================================================================
TaskHandle_t TaskReceptionTRMSHandler;     // Reception des trames mesures (Convertisseur --> ESP32)
TaskHandle_t TaskComGUIHandler;            // Traitement des trames de mesures et gestion des cycles
TaskHandle_t TaskComEcranHandler;          // Gestion de l'écran
TaskHandle_t TaskModbusHandler;            // Gestion de la communication Modbus  
TaskHandle_t TaskEmissionTRMSHandler;      // Emission des commandes  (ESP32 --> COnvertisseur)
TaskHandle_t TaskBASICHandler;             // Gestion programme langage Basic

TaskHandle_t TaskWifiHandler;
TaskHandle_t TaskOTAHandler;
TaskHandle_t TaskSDcardHandler;

TaskHandle_t TaskSchedulerHandler;
// =====================================================================================
// Fonctions 
// =====================================================================================
void LECTURE_XPORT(){
    for (int i = 0; i < 400; i++){
      // Serial.print(char(ModBus_Uart.read()));
    ModBus_Uart.read();
    }
}

void SEND_ENTER_XPORT(){
      ModBus_Uart.print(char(13));
}

void LECTURE_XPORT_ALL(){
    for (int i = 0; i < 4500; i++){
      // Serial.print(char(ModBus_Uart.read()));
      ModBus_Uart.read();
    }
}



// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                            Initialisation des configurations 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/* Ci-après, sera initialisé les différents paramètres par défauts                                          */
// ===========================================================================================================
void setup() {

  spiMutex = xSemaphoreCreateMutex();

// -------------------------------------------------------------------------------------
// Initialisation de l'UART 
// -------------------------------------------------------------------------------------
  Serial.begin(576000);   // Utilisé pour la communication avec le convertisseur   //576000
// -------------------------------------------------------------------------------------
// Initialisation de l'ADC de l'ESP32 (utilisé pour les sondes de température)
// -------------------------------------------------------------------------------------
  analogReadResolution(12); // Values range from 0 to 4095

  analogSetAttenuation(ADC_11db); // Enables full voltage range
// -------------------------------------------------------------------------------------
// Définition du statut du mode TEST 
// @brief : Permet de modifier manuellement des sorties analogiques via le configurateur
// -------------------------------------------------------------------------------------
  *MODE_TEST = 0;         // Si *MODE_TEST == 0  => Fonctionnement normal 

// --------------------------------------------------------------------------------------
// Initialisation du port ethernet
// --------------------------------------------------------------------------------------
   /* // Events Ethernet
    WiFi.onEvent(WiFiEvent);*/

    // Activation OSC
    pinMode(ESP32_EN_OSC, OUTPUT);
    digitalWrite(ESP32_EN_OSC, HIGH);
    delay(50);

    // LED
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    // RESET PHY
    pinMode(ETH_RST, OUTPUT);
    digitalWrite(ETH_RST, LOW);
    delay(100);
    digitalWrite(ETH_RST, HIGH);
    delay(100);

   /* // Init ETHERNET 
    bool eth_ok = false;
    for (int i = 0; i < 5 && !eth_ok; i++) {
        eth_ok = ETH.begin(ETH_PHY_ADDR, ETH_POWER_PIN, ETH_PHY_MDC, ETH_PHY_MDIO, ETH_PHY_TYPE, ETH_CLK_MODE);
        delay(500);
    }*/

    WiFi.softAP(ssid, password);
    mqttBroker.begin();



// --------------------------------------------------------------------------------------
// Configuration des entrées et sorties de l'ESP32
// -------------------------------------------------------------------------------------
pinMode(34,INPUT); // Pin ESP32_BOOT, si mis à 1 => activation du point d'accès WiFi
pinMode(CS2_PIN, OUTPUT);
pinMode(CS1_PIN, OUTPUT);
pinMode(MOSI_PIN, OUTPUT);
pinMode(SCLK_PIN, OUTPUT);
pinMode(MISO_PIN, INPUT);
// -------------------------------------------------------------------------------------
// Configuration de la communication Modbus 
// -------------------------------------------------------------------------------------
  #ifdef ENABLE_XPORT
    Configuration_COM_Modbus(ModBus_Uart,mb);  // GPIO 16 , 17
  #endif
// -------------------------------------------------------------------------------------  
  *MODE = 0; // Initialisation du MODE CP : défini le mode de fonctionnement (ex : *MODE = 0 => BO 000 , *MODE = 7 => BO 111 , *MODE = 8 => BF 000) 
  *MODE_SUP = 0;

  *INITIALISE = 0; 
// -----------------------------------------------------------------------------------------------------------------
// Initialisation du bus SPI
// -----------------------------------------------------------------------------------------------------------------
#ifdef ENABLE_SPI
  SPI.begin(SCLK_PIN, MISO_PIN, MOSI_PIN);
#endif 
// -----------------------------------------------------------------------------------------------------------------
// Initialisation de l'extendeur de bus
// -----------------------------------------------------------------------------------------------------------------
  #ifdef ENABLE_GPIO_EXP
    pinMode(CS3_PIN, OUTPUT);
    digitalWrite(CS3_PIN, HIGH); // Activation de l'extendeur de bus

    // writeRegister(0x05,0b00111110,MCPaddr,cs3Pin,spi);  //Registre IOCON

    // Initialisation du MCP23S08 : toutes les broches en sortie

    	digitalWrite(CS3_PIN, LOW);              // Sélectionner le MCP23S08
      SPI.transfer(MCP23S08_ADDR);            // Envoyer l'adresse avec le bit d'écriture
      SPI.transfer(0x00);                      // Envoyer le registre � �écrire
      SPI.transfer(0x00);                    // Envoyer la valeur
      digitalWrite(CS3_PIN, HIGH);             // D�s�lectionner le MCP23S08

    // Mettre toutes les broches à 1 (GPIO)

      digitalWrite(CS3_PIN, LOW);              // Sélectionner le MCP23S08
      SPI.transfer(MCP23S08_ADDR);            // Envoyer l'adresse avec le bit d'écriture
      SPI.transfer(0x09);                      // Envoyer le registre � �écrire
      SPI.transfer(0xFF);                    // Envoyer la valeur
      digitalWrite(CS3_PIN, HIGH);             // D�s�lectionner le MCP23S08

  #endif

 
// -----------------------------------------------------------------------------------------------------------------
// Ré-initialisation des registres utilisées pour les sorties ana/TOR et entrées TOR 
// -----------------------------------------------------------------------------------------------------------------
  *Sortie_analogique_V1 = 0;
  *Sortie_analogique_V2 = 0;
  *Sortie_analogique_V3 = 0;
  // *Sortie_analogique_V4 = 6500;  // PWM à 50%
  *Sortie_analogique_V4 = 0;
  

  *TOR_S1 = 0;
  *TOR_S2 = 0;
  *TOR_S3 = 0;
  *TOR_S4 = 0;
  
  *TOR_E1 = 0;
  *TOR_E2 = 0;
  *TOR_E3 = 0;
  *TOR_E4 = 0;

 *TOR_S1_MODBUS = 0;
 *TOR_S2_MODBUS = 0;
 *TOR_S3_MODBUS = 0; 
 *TOR_S4_MODBUS = 0;
// -----------------------------------------------------------------------------------------------------------------
// Acquittement des défauts 
// -----------------------------------------------------------------------------------------------------------------
  in(1); // Si utilisation de WMOV, on doit obligatoirement utiliser in(1) 
  DWMOV(0,WM(),0*16);      // WM0, WM1      (source, destination, indice de destination)
  in(1);
  WMOV(0,WM(),2*16);       // WM2           (source, destination, indice de destination)

// -----------------------------------------------------------------------------------------------------------------
// Initialisation (WM_CONF_DYN_E_MODBUS  = 0)
// -----------------------------------------------------------------------------------------------------------------
  in(1);
  WMOV(0,WM(),11*16);      // (source, destination, indice de destination)  // Fonction : Conversion n°0 sur entrée ana n°0   et accès à la banque 0 (banque de régulation)
  in(1);
  WMOV(0,WP(),6*16);
// -----------------------------------------------------------------------------------------------------------------

  initVariablesTemperature();

  *REPOS_4s_GT = 0;

  
// -----------------------------------------------------------------------------------------------------------
// Core 0 
// -----------------------------------------------------------------------------------------------------------
#ifdef ENABLE_CONV_TRMS

  // Create the tasks
    xTaskCreatePinnedToCore(
      TaskReceptionTRMS,          // Function to implement the task
      "Task Reception TRMS",       // Name of the task
      4096,          // Stack size in words
      NULL,           // Task input parameter
      3,              // Priority of the task
      &TaskReceptionTRMSHandler,  // Task handle.
      0);             // Core where the task should run

    xTaskCreatePinnedToCore(
      TaskComGUI,          // Function to implement the task
      "Task Com GUI",       // Name of the taskSD.begin(
      2048,          // Stack size in words
      NULL,           // Task input parameter
      2,              // Priority of the task
      &TaskComGUIHandler,  // Task handle.
      0);             // Core where the task should run

      xTaskCreatePinnedToCore(
      TaskEmissionTRMS,          // Function to implement the task
      "Task Emission TRMS",       // Name of the task
      2048,          // Stack size in words
      NULL,           // Task input parameter
      1,              // Priority of the task
      &TaskEmissionTRMSHandler,  // Task handle.
      0);             // Core where the task should run

  #endif
    
 // ============================================================================================================

      xTaskCreatePinnedToCore(
      app_scheduler, /* Function to implement the task */
      "Task scheduling", /* Name of the task */
      2048,  /* Stack size in words */
      NULL,  /* Task input parameter */
      4,  /* Priority of the task */
      &TaskSchedulerHandler,  /* Task handle. */
      1); /* Core where the task should run */  

}
// =============================================================================================================
// Main loop
// =============================================================================================================
void loop() {
      
}
// =============================================================================================================
  





