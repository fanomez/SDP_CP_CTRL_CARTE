#pragma once


// =======================================================================================================
// Données de la machine 
// =======================================================================================================
const char *ssid = "SDP_CP_V2_CONTROLE_CARTE";    
const char *password = "SREM_012026";
const char *version = "1.0.3";
const char *machine = "CH4X";
const char *date = "22/01/25";
// =======================================================================================================
// Serveur TCP WiFi 
// =======================================================================================================
WiFiServer mqttBroker(1883); // serveur TCP
WiFiClient clientMQTT;
// =======================================================================================================
// Configuration ETHERNET
// =======================================================================================================
#define ETH_CLK_MODE    ETH_CLOCK_GPIO0_IN
#define ETH_PHY_MDC     23
#define ETH_PHY_MDIO    18
#define ETH_PHY_ADDR    1
#define ETH_PHY_TYPE    ETH_PHY_LAN8720
#define ETH_POWER_PIN   -1
#define ETH_RST         5

#define ESP32_EN_OSC    33
#define LED_PIN         15  // Active LOW


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                         VARIABLES GLOBALES
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static bool eth_connected = false;
static bool eth_server_started = false;

// TCP serveur Ethernet LAN8720
WiFiServer tcpServer(5000);



// =======================================================================================================



// definitions de constantes

#define TPS_SEUIL_BO_DEMAG 500
#define TPS_PROB_PUISSANCE 2051
#define TPS_SUP_ARRET_C1_SIMULTANE 26
#define TPS_PRE_SEUIL 500

// Rampes(2)

#define TPS_RAMPES_MONTEES_BO 105
#define TPS_FILTRE_STABILITE 78   // 3*26 ms

bool rampe1;
bool rampe2;
bool rampe3;

// ================================================================
// Trame de communication entre STM32 et ESP32
// ================================================================
uint8_t frame_rcv[500] = {0};
uint8_t frame_snd[500] = {0};
uint8_t frame_tmp[5] = {0};

uint8_t en_tete[2]={0}; 

uint8_t len = 0;

// ----------------------------------------------------------------
// Variables contenant les mesures
// ----------------------------------------------------------------
uint16_t I_eff[7]={0};
uint16_t I_crete[7]={0};
uint16_t I_moy[7]={0};
uint16_t I_min[7]={0};
uint16_t I_max[7]={0};

uint8_t emission = 0;
uint8_t balayage = 0;
uint8_t reception = 1;

uint16_t crc ;      // Calculé
uint16_t RX_crc ;   // reçu

#define RX_Mesures_ID 0x01
#define RX_Horodatage_ID 0x02
// Identifiant des trames de transmission 
#define Config_ID 0x10
#define Commandes_ID 0x11
#define Horodotage_ID 0x12
#define Commandes_unitaire_ID 0x13
#define Commande_Offset_ID 0x14


uint8_t TX_ID; 

char etat_cmd = ' ' ;  // Empêche l'envoi d'une nouvelle tant que la temporisation est en cours
char buf[100];

uint16_t nb_commandes_envoyee = 0;
uint16_t nb_retour_commandes = 0;



// ================================================================
// Trame de communication avec interface graphique 
// ================================================================
  // Tableaux pour stocker les valeurs après A et T
    uint16_t valuesA[10], valuesT[10], valuesD[10];
    uint16_t numValuesA = 0, numValuesT = 0, numValuesD = 0;
// ================================================================

// =================================================================================================================================================================
// Gestion de front 
// =================================================================================================================================================================
R_Trig depart_cycle;

R_Trig arret_cycle;  // fait par moi

R_Trig SO_3;

R_Trig tor_E1;
R_Trig tor_E2;
R_Trig tor_E3;
R_Trig tor_E4;

R_Trig front_Montant_ACY;
// =================================================================================================================================================================
// Timers
// =================================================================================================================================================================
unsigned long Timer0 = 0;
unsigned long Timer1 = 0;
unsigned long Timer2 = 0;
unsigned long Timer3 = 0;
unsigned long Timer4 = 0;
unsigned long Timer5 = 0;
unsigned long Timer6 = 0;
unsigned long Timer7 = 0;
unsigned long Timer8 = 0;
unsigned long Timer9 = 0;
unsigned long Timer10 = 0;
unsigned long Timer11 = 0;
unsigned long Timer12 = 0;
unsigned long Timer13 = 0;
unsigned long Timer14 = 0;
unsigned long Timer15 = 0;
unsigned long Timer16 = 0;
unsigned long Timer17 = 0;
unsigned long Timer18 = 0;
unsigned long Timer19 = 0;
unsigned long Timer20 = 0;
unsigned long Timer21 = 0;
unsigned long Timer22 = 0;
unsigned long Timer23 = 0;
unsigned long Timer24 = 0;
unsigned long Timer25 = 0;
unsigned long Timer26 = 0;
unsigned long Timer27 = 0;
unsigned long Timer28 = 0;
unsigned long Timer29 = 0;
unsigned long Timer30 = 0;
unsigned long Timer31 = 0;
unsigned long Timer32 = 0;
unsigned long Timer33 = 0;
unsigned long Timer34 = 0;
unsigned long Timer35 = 0;
unsigned long Timer36 = 0;
unsigned long Timer37 = 0;
unsigned long Timer38 = 0;
unsigned long Timer39 = 0;
unsigned long Timer40 = 0;
unsigned long Timer41 = 0;
unsigned long Timer42 = 0;
unsigned long Timer43 = 0;
unsigned long Timer44 = 0;
unsigned long Timer45 = 0;
unsigned long Timer46 = 0;
unsigned long Timer47 = 0;
unsigned long Timer48 = 0;
unsigned long Timer49 = 0;
unsigned long Timer50 = 0;
unsigned long Timer51 = 0;
unsigned long Timer52 = 0;
unsigned long Timer53 = 0;
unsigned long Timer54 = 0;
unsigned long Timer55 = 0;
unsigned long Timer56 = 0;
unsigned long Timer57 = 0;
unsigned long Timer58 = 0;
unsigned long Timer59 = 0;
unsigned long Timer90 = 0;
unsigned long Timer91 = 0 ;
unsigned long Timer92 = 0;
unsigned long Timer93 = 0;
unsigned long Timer94 = 0;
unsigned long Timer95 = 0;
unsigned long Timer96 = 0;
unsigned long Timer97 = 0;


unsigned long Timer98 = 0;
unsigned long Timer99 = 0;

unsigned long Timer105 = 0;

unsigned long TimerOffsetDyn = 0;

unsigned long TimerSD = 0;   // Debug facteur thermique 

unsigned long TimerFth_C1[4];

unsigned long TimerFth_C2[4];

unsigned long TimerFth_C3[4];

unsigned long TimerG3 = 0;    // Debug G3 [Test en cours]

unsigned long Timer201 = 0;    //
unsigned long Timer203 = 0;    //  
unsigned long Timer209 = 0;    //  
unsigned long Timer207 = 0;    //  
unsigned long Timer208 = 0;    //  
unsigned long Timer210 = 0;    //  
unsigned long Timer211 = 0;    //  
unsigned long Timer212 = 0;    //  
unsigned long Timer213 = 0;    //  
unsigned long Timer214 = 0;    //  
unsigned long Timer215 = 0;    //  
unsigned long Timer217 = 0;    //  
unsigned long Timer219 = 0;    //  
unsigned long Timer221 = 0;    //  
unsigned long Timer225 = 0;    //
unsigned long Timer227 = 0;    //

unsigned long Timer223 = 0;    //  
unsigned long Timer230 = 0;    //  
unsigned long Timer232 = 0;    //  
unsigned long Timer233 = 0;    //  
unsigned long Timer234 = 0;    //  
unsigned long Timer235 = 0;    //  
unsigned long Timer236 = 0;    //  
unsigned long Timer237 = 0;    //  
unsigned long Timer239 = 0;    //  
unsigned long Timer242 = 0;    //  
unsigned long Timer243 = 0;    //  
unsigned long Timer245 = 0;    //  
unsigned long Timer246 = 0;    //  
unsigned long Timer248 = 0;    //  
unsigned long Timer256 = 0;    //  

unsigned long Timer290 = 0;    //  
unsigned long Timer291 = 0;    //  

unsigned long Timer294 = 0;    //  
unsigned long Timer295 = 0;    //  

unsigned long Timer_timeout_cycle_3 = 0;

unsigned long TimerWifiSAT = 0;

unsigned long Temps_ecoule_C_consigne_temps_C1 = 0;
unsigned long Temps_ecoule_C_consigne_temps_C2 = 0;
unsigned long Temps_ecoule_C_consigne_temps_C3 = 0;



bool lastBit = false;
unsigned long lastChangeTime = 0;
bool currentBit; // Lecture du bit Modbus 
unsigned long now;

const unsigned long BIT_DE_VIE_TIMEOUT = 2000; // ms (≈ 3 × 622 ms)

enum EtatBitDeVie {
  BIT_VIE_OK = 0,
  BIT_VIE_BLOQUE_0 = 1,
  BIT_VIE_BLOQUE_1 = 2
};

EtatBitDeVie etatBit = BIT_VIE_OK;

uint8_t recalcul_fth_C1[4] = {0,0,0,0};
uint8_t recalcul_fth_C2[4] = {0,0,0,0};
uint8_t recalcul_fth_C3[4] = {0,0,0,0};


float pourc[3][16];

// =================================================================================================================================================================
// Initilisation des étapes du grafcet
// =================================================================================================================================================================
// grafcet 0 à l'état 0
uint8_t  S0=0;
// grafcet 1 à l'état 0
uint8_t  S1=0;
// grafcet 2 à l'état 0
uint8_t  S2=0;

// grafcet 3 à l'état 0
uint8_t  S3=0;

uint8_t BSPEC1 = 0;
uint8_t BSPEC2 = 0;
uint8_t BSPEC3 = 0;

uint32_t  tps1=0;
uint32_t  tps2=0;
uint32_t  tps3=0;

uint8_t Int_periodique = 1; 
// =================================================================================================================================================================
// variables globales
uint32_t WM20 = 0;
uint32_t WM21 = 0;
uint32_t WM22 = 0;
uint32_t WM23 = 0;

uint32_t DWM20 = 0;
uint32_t DWM22 = 0;
uint32_t cmd_precedente_1 = 0;  // Correspond à WM24 dans le ladder
uint32_t cmd_precedente_2 = 0;  // Correspond à WM26 dans le ladder
uint32_t cmd_precedente_3 = 0;  // Correspond à WM26 dans le ladder


uint16_t Sortie_1_Old = 0;     // Correspond à WM28 dans le ladder
uint16_t Sortie_2_Old = 0;     // Correspond à WM29 dans le ladder
uint16_t Sortie_3_Old = 0;     // Correspond à WM29 dans le ladder

uint16_t Sortie_1_Old_t1 = 0;     // Correspond à WM14 dans le ladder
uint16_t Sortie_1_Old_t2 = 0;     // Correspond à WM15 dans le ladder
uint16_t Sortie_1_Old_t3 = 0;     // Correspond à WM16 dans le ladder

uint16_t Sortie_2_Old_t1 = 0;     // Correspond à WM17 dans le ladder
uint16_t Sortie_2_Old_t2 = 0;     // Correspond à WM18 dans le ladder
uint16_t Sortie_2_Old_t3 = 0;     // Correspond à WM19 dans le ladder

uint16_t Sortie_3_Old_t1 = 0;     // Correspond à WM17 dans le ladder
uint16_t Sortie_3_Old_t2 = 0;     // Correspond à WM18 dans le ladder
uint16_t Sortie_3_Old_t3 = 0;     // Correspond à WM19 dans le ladder

uint16_t Commande_debut_rampe_1 = 0;  // Correspond à WM30 dans le ladder
uint16_t Commande_debut_rampe_2 = 0;  // Correspond à WM31 dans le ladder
uint16_t Commande_debut_rampe_3 = 0;  // Correspond à WM31 dans le ladder


unsigned long tempo_mode_test = 0;

uint32_t j = 0;
uint32_t k = 0;

#define etat_final 255         //etat_finale du grafcet

uint16_t banques_en_cours[4];


// =================================================================================================================================================================
// Durée trame
// =================================================================================================================================================================
unsigned long startTime = 0;
unsigned long endTime = 0;
unsigned long tempsFrame = 0;
// =================================================================================================================================================================
// Gestion des paramètres de configuration [Formatage des données à envoyer sur la carte SD] 
// =================================================================================================================================================================
 // Déclaration d'un tableau à deux dimensions
    const char* keys[4][7] = {
        { "modeCP", "typesCapteurs", "pointeurDCY", "pointeurACY", "pointeurACQ", "pointeurDEMAG", "pointeurCtrlFth" },                           // Ligne 1
        { "controleTetes", "controleFO", "secuVigitherm", "pointeurMesure", "pointeurPuissance1", "pointeurPuissance2", "pointeurTemps" },        // Ligne 2
        { "seuilMesure", "ImaxLu", "ImaxRef", "Umin", "Umax", "gainP", "gainKD"},                                                                 // Ligne 3
        { "offsetDemarrage", "gainFixeV1", "offsetFixeV1", "gainFixeV2", "offsetFixeV2","gainFixeV3","offsetFixeV3"}                                                          // Ligne 4
    };

    // Nombre de lignes dans le tableau (nombre d'éléments dans le tableau principal)
    const int numRows = sizeof(keys) / sizeof(keys[0]);

    // Nombre de colonnes dans chaque ligne (nombre d'éléments dans le premier sous-tableau)
    const int numCols = sizeof(keys[0]) / sizeof(keys[0][0]);


// =================================================================================================================================================================
// Horodotage
// =================================================================================================================================================================
uint8_t  heures = 0;
uint8_t  minutes = 0;
uint8_t  secondes = 0;

uint8_t  jour = 0;
uint8_t  mois = 0;
uint8_t  annee = 0;
// =================================================================================================================================================================
// Structure pour stocker les données du fichier INI
// =================================================================================================================================================================
struct INIEntry {
  String section;
  String key;
  String value;
};

struct configInfo {
  String section;
  int length;
};
// =================================================================================================================================================================
//Déclaration de la structure de donnée
// =================================================================================================================================================================

INIEntry entries[50];                                 // Nombre d'élément 
configInfo entriesInfo[10];                           // Structure contenant les informations des sections (nom et taille)

  // Variables globales pour stocker les données
  const int NUM_VALUES = 240;
  uint32_t globalData[NUM_VALUES];

  uint16_t nb_erreur_SD = 0; 
  uint16_t nb_erreur_COM_2[2] = {0,0}; 

// =================================================================================================================================================================
uint16_t offsetDemarrage = 0;
uint16_t gainFixeV1 = 0;
uint16_t offsetFixeV1= 0;
uint16_t gainFixeV2= 0;
uint16_t offsetFixeV2= 0;
uint16_t gainFixeV3= 0;
uint16_t offsetFixeV3= 0;

uint16_t recupConfigDemarrage = 2;

bool offset_dynamique_faite = 0;




  // The colors we actually want to use
  uint16_t Display_Text_Color = ST77XX_RED;
  uint16_t Display_Backround_Color = ST77XX_BLACK;

char* Affichage_1_Old = "00000";
char* Affichage_2_Old = "00000";

uint16_t valeurAffichage_1_Old = 0;
uint16_t valeurAffichage_2_Old = 0;

uint16_t Affichage_1_precedent = 0;
uint16_t Affichage_2_precedent = 0;




uint8_t configEcran = 0; 


uint32_t occurence_alarme = 0; 

bool affichagePuissance = 0;
// ========================================================================================
// Variables liés à la communication
// ========================================================================================
uint16_t initialisation = 1;       // Première reception correcte
uint16_t initialisation_2 = 1;     // frequence reception stable
uint16_t RT = 0;                   // Incrémentation de receptions
int inc_moy = 0;
uint16_t periodex1000 = 20000;

uint16_t Trig_COM_Tps = 3000; // Période minium de la communication Conv <-> C fille
uint16_t Trig_COM_cpt = 3;  // Nombre d'erreur consécutive 
uint16_t Coef_COM_cpt = 5;
// ========================================================================================
// Tests facteur Thermique 
// ========================================================================================
bool init_offset = 0; 

// SPIClass spi_1 = SPIClass(HSPI);          // Permet de stocker les paramètres SPI utile pour la communication
// ========================================================================================
    uint8_t WR_jour ;
    uint8_t WR_mois ;
    uint8_t WR_annee ;
    
    uint8_t WR_heure ;
    uint8_t WR_min ;
    uint8_t WR_sec  ;


#define ENABLE_NORMAL_MODE
// #define ENABLE_DEBUG_MODE                // En mode debug les pins du SPI utilisé sont différents

#ifdef ENABLE_NORMAL_MODE
    // ===========================================================================================================
    // Communication SPI (3 périphériques sont connectés au bus SPI )
    // ===========================================================================================================
    // Bus SPI
    // ***********************************************************************************************************
    #define MISO_PIN  12                  // Master In Slave Out  (  ESP32   <-- Carte SD  )
    #define MOSI_PIN  13                  // Master Out Salve In  (  ESP32   --> Carte SD  )
    #define SCLK_PIN  14                  // Horloge 
    // ***********************************************************************************************************
    // Périphérique 1 : Extendeur de GPIO  (Protocole de communication :  SPI ; Référence : MCP23S08)
    // ***********************************************************************************************************
    // #define ETH_RST 2                        // Cas carte 001
    #define ETH_RST 5                           // Cas carte 002
    #define CS3_PIN  4                       // Pin CS (Chip Select) pour le MCP23S08
    #define MCP23S08_ADDR  0x40              // Adresse du MCP23S08 (A2 A1 A0 = 000)

    // ***********************************************************************************************************
    // Périphérique 2 : Module lecture carte microSD (Protocole de communication : SPI)
    // ***********************************************************************************************************
    #define CS2_PIN 2                         // Pin CS (Chip Select) pour le module de lecture carte microSD | CS2_PIN = 5 (carte 001) |  CS2_PIN = 2 (carte 002) 
    // #define CS2_PIN 5                      // Cas carte 001

    File myFile;                             // Permet la récupération d'un fichier sur la carte SD 

    // ***********************************************************************************************************
    // Périphérique 3 : Ecran d'affichage           (Protocole de communication : SPI)
    // *****modbus_config_state******************************************************************************************************
    #define CS1_PIN 15                        // Pin CS (Chip Select) pour l'écran
    #define DC_PIN 32                         // Sélection du type d'information envoyé (Données ou Commande)
#endif


#ifdef ENABLE_DEBUG_MODE

    // ===========================================================================================================
    // Communication SPI (3 périphériques sont connectés au bus SPI )
    // ===========================================================================================================
    // Bus SPI
    // ***********************************************************************************************************
    #define MISO_PIN  19                  // Master In Slave Out  (  ESP32   <-- Carte SD  )
    #define MOSI_PIN  23                  // Master Out Salve In  (  ESP32   --> Carte SD  )
    #define SCLK_PIN  18                  // Horloge 
    // ***********************************************************************************************************
    // Périphérique 1 : Extendeur de GPIO  (Protocole de communication :  SPI ; Référence : MCP23S08)
    // ***********************************************************************************************************
    // #define ETH_RST 2                        // Cas carte 001
    #define ETH_RST 2                           // Cas carte 002
    #define CS3_PIN  4                       // Pin CS (Chip Select) pour le MCP23S08
    #define MCP23S08_ADDR  0x40              // Adresse du MCP23S08 (A2 A1 A0 = 000)

    // ***********************************************************************************************************
    // Périphérique 2 : Module lecture carte microSD (Protocole de communication : SPI)
    // ***********************************************************************************************************
    #define CS2_PIN 5                         // Pin CS (Chip Select) pour le module de lecture carte microSD | CS2_PIN = 5 (carte 001) |  CS2_PIN = 2 (carte 002) 
    // #define CS2_PIN 5                      // Cas carte 001

    File myFile;                             // Permet la récupération d'un fichier sur la carte SD 

    // ***********************************************************************************************************
    // Périphérique 3 : Ecran d'affichage           (Protocole de communication : SPI)
    // *****modbus_config_state******************************************************************************************************
    #define CS1_PIN 15                        // Pin CS (Chip Select) pour l'écran
    #define DC_PIN 32                         // Sélection du type d'information envoyé (Données ou Commande)

#endif



// =============================================================================================
uint16_t upload_file = 0;
uint8_t type_machine = 0;  // 0 => CH4X ; 1 => GT
// =============================================================================================
UBaseType_t stackWordsLeft;

uint8_t CONV_RX_CTRL;
uint8_t CONV_TX_CTRL;
uint8_t LADDER_CTRL;
uint8_t BASIC_CTRL;
uint8_t SD_CTRL;



File file_Write_Tmp;
File dataFth_binaire_tmp;
size_t n, n1 ,n2;


// inhiber la réécriture de gestion BASIC :
uint16_t modif_banque_wifi_en_cours = 0 ;



SemaphoreHandle_t spiMutex;

// Variables utilisé par l'écran
char AffichageBuffer_1[6], AffichageBuffer_2[6];


StaticJsonDocument<4096> doc;             // Variables utilisé dans les routes du serveur 

StaticJsonDocument<16384> config_SDP;     // Variables utilisé dans la communication avec la carte SD


uint32_t taskDataAnalysis[10];

// ======================================================================
// Gestion de la reception 
// ======================================================================
uint16_t RX_ESP32_nb_trames_correct = 0;   // Nombre de trame reçu par l'ESP32


// ======================================================================
const char page_upload[] PROGMEM =
"<!DOCTYPE html>"
"<html>"
"<head><meta charset='utf-8'><title>Upload fichier</title></head>"
"<body>"
"<h2>Uploader un fichier vers l'ESP32</h2>"
"<form method='POST' action='/upload' enctype='multipart/form-data'>"
"<input type='file' name='datafile'><br><br>"
"<input type='submit' value='Envoyer'>"
"</form>"
"</body>"
"</html>";

File uploadFile;

float offset_voie_1 , offset_voie_2 , offset_voie_3 , offset_voie_4, offset_voie_5 , offset_voie_6;


typedef enum {
    SD_INIT,          // Initialisation de la carte SD
    SD_ERROR,         // Erreur détectée
    SD_READ_JSON,     // Lecture du fichier JSON
    SD_CONFIG_OK,      // Paramètres récupérés
    SD_CONFIG_WIFI

} SD_State;


SD_State sdState = SD_INIT;

uint16_t nb_modifications = 0;

float offset_actuel = 0;
