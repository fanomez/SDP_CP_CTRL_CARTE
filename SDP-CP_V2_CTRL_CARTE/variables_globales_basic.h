#pragma once
#define Ecrire_param_par_defaut   0 

// ===================================================================================================================
// Entrées capteurs de température 
// ===================================================================================================================
#define SENSOR_VP 36 
#define SENSOR_VN 39
// ===================================================================================================================

//#define DEBUG_VAL_PAR_DEFAUTS //affichage initialisation des valeurs par défauts

uint16_t Valeur_par_defaut_D[100];
uint16_t Valeur_par_defaut_WM[32];
uint16_t adr_eeprom;

uint8_t ID_elmt_Old_Bq[7] = {75, 76, 77, 78, 79, 90, 54};
uint8_t ID_elmt_New_Bq[7] = {134, 135, 136, 137, 138, 139, 140};

const char* banques_num[16]={"banque0","banque1","banque2","banque3","banque4","banque5","banque6","banque7","banque8","banque9","banque10","banque11","banque12","banque13","banque14","banque15"};
const char* banques_etalonnage[16]={"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15"};
  
// ===== Definitions Capteurs =================
// Configure les caracteristiques des capteurs utilisés sur le banc
// Ces caracteristiques sont enregistrer sous la fome d'un tableau
// Ce tableau est utilisé dans la fonction config_types_capteurs() présent dans le setup() 

// Tableau de référencement des capteurs (Modifiable)
// les lignes correspondent aux "types" des capteurs, les colonnes à leurs caractèristiques
//                                       SaturH  SaturB  Absence  DeriveH   DeriveB        
uint16_t Var_capteur[7][5] =  {       {  65535,       0,     0,    65535,        0},         //type 0 Sans
                                      {  65535,       0,     0,     3200,     2800},         //type 1 ABB(sans CTRL) 
                                      {   5000,    1000,   500,     3200,     2800},         //type 2 ABB
                                      {   4375,     625,   300,     2600,     2400},         //type 3 HASS-xxS
                                      {  65535,       0,     0,    65535,        0},         //type 4 vide
                                      {  65535,       0,     0,    65535,        0},         //type 5 vide
                                      {  65535,       0,     0,    65535,        0}    };    //...


//Facteurs thermique
#define Fth_nb_points_max 240
uint32_t Integral_Tab[2][Fth_nb_points_max];

// Variable temporaire de récupération 
float Integral_Tab_recup[2][Fth_nb_points_max];

uint32_t timer_dt_C1_recup[4] = {0,0,0,0};
uint32_t timer_dt_C2_recup[4] = {0,0,0,0};
uint32_t timer_dt_C3_recup[4] = {0,0,0,0};
  
float Integral_100ms[2]={0,0};
float Integral_dt[2] = {0,0};
float Integral_instantane[2] = {0,0};
float Seuil_Fth[2];
float Mesure_100ms[2] = {0,0};


uint16_t Pointeur_Eff_Fth[3];

uint16_t Timer_100ms;
uint16_t Timer_100ms_old;
uint16_t Timer_dt;
uint16_t Timer_dt_old;
uint16_t dT100ms;
uint16_t PeriodeFth;
uint16_t dT_Fth;
uint16_t Fth_nb_points;


uint16_t Timer_26ms;



//Capteurs
uint8_t type_capteur[7];
uint16_t types_capteurs;
uint16_t types_capteurs_sup;

//Etalonnage entrees ana Cubloc
#define Nb_Valeurs_Moyennage  20 //64 max
#define Nb_Entree_ana  4
#define Nb_Conversions 4
uint16_t temp_mes;
uint16_t tab_moyennage[Nb_Entree_ana][Nb_Valeurs_Moyennage];
uint16_t Somme_Moyennage[Nb_Entree_ana];
uint8_t Activation_Conversions = 0;
uint8_t num_valeur = 0 ;
float mesure_single;

const uint8_t Num_P_Eana[4] = {24,25,26,27};
 
float Coeff_a[Nb_Entree_ana][Nb_Conversions];
float Coeff_b[Nb_Entree_ana][Nb_Conversions];

uint16_t Mesures_Ana[Nb_Entree_ana];
uint16_t Seuil_Ctrl_temperature[Nb_Entree_ana];
uint16_t Seuil_Ctrl_CAPTEUR_temperature[Nb_Entree_ana][2];
uint16_t Mesures_Converties[Nb_Entree_ana][Nb_Conversions];
uint8_t Num_Entree_ana_select = 0;
uint8_t Num_conversion_ana_select = 0;


  //  Donnée facteur thermique C1 
  uint16_t Timer_100ms_C1[4];
  uint16_t Timer_100ms_old_C1[4];                   
  uint16_t Timer_dt_C1[4]; 
  uint16_t Timer_dt_old_C1[4];
  uint16_t dT_Fth_C1[4];
  uint16_t dT100ms_C1[4];

    float Integral_Tab_C1[4][240];

  float Integral_100ms_C1[4]={0,0,0,0};

  float Integral_dt_C1[4] = {0,0,0,0};
  float Integral_instantane_C1[4] = {0,0,0,0};
  float Seuil_Fth_C1[4];
  float Mesure_100ms_C1[4] = {0,0,0,0};

  //  Donnée facteur thermique C2 
  uint16_t Timer_100ms_C2[4];
  uint16_t Timer_100ms_old_C2[4];                   
  uint16_t Timer_dt_C2[4]; 
  uint16_t Timer_dt_old_C2[4];
  uint16_t dT_Fth_C2[4];
  uint16_t dT100ms_C2[4];

  float Integral_Tab_C2[4][240];

  float Integral_100ms_C2[4]={0,0,0,0};

  float Integral_dt_C2[4] = {0,0,0,0};
  float Integral_instantane_C2[4] = {0,0,0,0};
  float Seuil_Fth_C2[4];
  float Mesure_100ms_C2[4] = {0,0,0,0};


  //  Donnée facteur thermique C3
  uint16_t Timer_100ms_C3[4];
  uint16_t Timer_100ms_old_C3[4];                   
  uint16_t Timer_dt_C3[4]; 
  uint16_t Timer_dt_old_C3[4];
  uint16_t dT_Fth_C3[4];
  uint16_t dT100ms_C3[4];

  float Integral_Tab_C3[4][240];

  float Integral_100ms_C3[4]={0,0,0,0};

  float Integral_dt_C3[4] = {0,0,0,0};
  float Integral_instantane_C3[4] = {0,0,0,0};
  float Seuil_Fth_C3[4];
  float Mesure_100ms_C3[4] = {0,0,0,0};


/*
  float Integral_Tab_C1_recup[4][240];
  float Integral_Tab_C2_recup[4][240];
  float Integral_Tab_C3_recup[4][240];
*/

float sum_C1[4] = {0,0,0,0};
float sum_C2[4] = {0,0,0,0};
float sum_C3[4] = {0,0,0,0};
