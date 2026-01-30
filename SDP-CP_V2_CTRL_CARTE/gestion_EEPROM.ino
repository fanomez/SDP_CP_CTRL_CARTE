#include "variables_globales_basic.h"
#include "Banque_EEPROM.h"
#include <gestion_registres.h>
#include <perso.h>

#define PRET_A_TESTER
#define VALIDEE

/*

  #ifdef DEV_EN_COURS   // 10/10/2025

  #endif

  #ifdef PRET_A_TESTER

  #endif 

  #ifdef VALIDEE

  #endif

*/

// ==== Gestion de l'EEPROM ======
// Contient les fonctions de sauvegarde des parametres dans l'EEPROM
// Ces fonctions sont appellées dans gestion_BASIC() dans gestion_BASIC.ino


//************Gestion parametres config: Initeeprom, Chargement, Sauvegarde************************************************

// Limite_Max_CONF[6] = {65535,99,511,5000,10000,54000};
// LM = 0 => Valeur max : 65535
// LM = 4 => Valeur max : 10000
// -----------------------------------------------
// Adresses EEPROM / Size EEPROM : 512 octets => 0-2048
// ----------------------------------------------- 
// D()[0] :  16 bits (2 octets)
// adr_eeprom : 0 * 2 = 0
// -----------------------------
// D()[1] :  16 bits (2 octets)
// adr_eeprom : 1 * 2  = 2
// -----------------------------
// D()[99] :  16 bits (2 octets)
// adr_eeprom : 99 * 2  = 198
// -----------------------------------------------


void RW_parametre (uint8_t RW,uint8_t Bank ,uint8_t LM ,uint16_t D){ // 0 -200
  adr_eeprom = (D *2) + Bank*200;  // Adresse EEPROM = indice du WM*2(banque en octets donc 2 octets pour un mots) + 0(= debut de la plage des D)
  if ( RW == 0 ){         
    Init_eeprom(adr_eeprom,D,LM);               //Initialisation de l'EEPROM
  }else if( RW == 1 ){
    Chargement_parametre(adr_eeprom,D,LM);      // Récupeation(charegement) des valeurs de l'EEPROM
  }else if( RW == 2 ){
    Sauvegarde_parametre(adr_eeprom,D,LM);      // Sauvegarde des valeurs dans l'EEPROM
  }
}

// Initialisation de l'EEPROM ( pas d'EEPROM dans l'ESP32 mais simulation de celui-ci avec la memoire flash)
void Init_eeprom( uint16_t adr,uint16_t indiceD , uint8_t LM ){
  if (  (((EEPROM.read(adr) && EEPROM.read(adr+1)) == 0xFF) & (Valeur_par_defaut_D[indiceD] != 65535))   // Condition : EEPROM Pas encore écrit && Valeur_par_defaut différent de 0XFF
        | (Ecrire_param_par_defaut == 1) 
        | ( (EEPROM.read(adr) + (EEPROM.read(adr+1)<<8)) > Limite_Max_CONF[LM]) ) {
          
        D()[indiceD] = Valeur_par_defaut_D[indiceD];
        Sauvegarde_parametre (adr,indiceD,LM);                               
  }
  vTaskDelay(10);         // pas nécésaaire sur l'ESP32 ???
}

// chargements des paramêtres de l'EEPROM ( pas d'EEPROM dans l'ESP32 mais simulation de celui-ci avec la memoire flash)
void Chargement_parametre (uint16_t adr, uint16_t indiceD,uint8_t LM){ // 0 -200
  D()[indiceD] = EEPROM.read(adr) + (EEPROM.read(adr+1)<<8);

  if (D(indiceD) > Limite_Max_CONF[LM]) {                // Si limites dépassé , utilisation des variables par défaut
     D()[indiceD] = Valeur_par_defaut_D[indiceD];
  }  
  ActionChargModif(indiceD);
}

// Sauvegarde des paramêtres dans l'EEPROM ( pas d'eeprom dans l'ESP32 mais simulation de celui-ci avec la memoire flash)
void Sauvegarde_parametre (uint16_t adr , uint16_t indiceD, uint8_t LM){ // 0 -200

  if (D(indiceD) > Limite_Max_CONF[LM]){ 
    D()[indiceD] = Valeur_par_defaut_D[indiceD];
  }
  if ( EEPROM.read(adr) + (EEPROM.read(adr+1)<<8) != D(indiceD)){
    EEPROM.write(adr,D(indiceD)&0xFF);
    EEPROM.write(adr+1,(D(indiceD)>>8)&0xFF);
    EEPROM.commit();        // indispensable à l'écriture dans la mémoire (valide les changements dans la mémoire)

    ActionChargModif(indiceD);

  }
     vTaskDelay(1);          // pas nécésaaire sur l'ESP32 ???
  
}


void RW_parametres (uint8_t RW){   // RW = 0 (initialisation de l'EEPROM) ; RW = 1 (Récupération des valeurs de l'EEPROM ) ; RW = 2 (Stockage des valeurs de l'EEPROM)

  // --------------------------------------------------------------------------------------------------------------------------------------------
  // Type de paramètres n°01 : Réglage général
  // --------------------------------------------------------------------------------------------------------------------------------------------
  RW_parametre_WM( RW,BITS_CONFIG_G1);  //WM
  //RW_parametre_WM( RW,BITS_CONFIG_G2);


  // Shunté pour l'instant car remplacé par la carte SD

 /* RW_parametre(RW,0,0,D_Temps_Pb_puissance);   // (RW , Bank , LM : limite max de configuration [0 = 65535] , D : indice)
  RW_parametre(RW,0,5,D_Periode_Fth);
  RW_parametre(RW,0,0,D_Gain_BOOST);
  RW_parametre(RW,0,2,D_Pointeur_TOR_S[1]);
  RW_parametre(RW,0,2,D_Pointeur_TOR_S[2]);
  RW_parametre(RW,0,2,D_Pointeur_TOR_S[3]);
  RW_parametre(RW,0,2,D_Pointeur_TOR_S[4]);
  RW_parametre(RW,0,4,D_COEF_CONE_TUBE);
  RW_parametre(RW,0,0,D_Types_Capteurs);
  RW_parametre(RW,0,2,D_Pointeur_ACQ);
  RW_parametre(RW,0,2,D_Pointeur_DEMAG);
  RW_parametre(RW,0,2,D_Pointeur_DCY);
  RW_parametre(RW,0,2,D_Pointeur_ACY);*/

  if ((*MODE_ESCLAVE == 0) | (RW != 2) ){
    RW_parametre(RW,0,0,D_MODE);
  }
  // --------------------------------------------------------------------------------------------------------------------------------------------
  // Type de paramètres n°02 : Réglage générateur
  // --------------------------------------------------------------------------------------------------------------------------------------------
  // Limite_Max_CONF[6] = {65535,99,511,5000,10000,54000};
  // LM = 0 => Valeur max : 65535
  // LM = 4 => Valeur max : 10000

  // (RW , Bank , LM : limite max de configuration [0 = 65535] , D : indice)

/*
  RW_parametre(RW,0,0,D_I_thermique_C[1]);    
  RW_parametre(RW,0,1,D_Pointeur_Puissance_2_C[1]);
  RW_parametre(RW,0,1,D_Pointeur_Puissance_C[1]);
  RW_parametre(RW,0,1,D_Pointeur_Temps_C[1]);
  RW_parametre(RW,0,1,D_Pointeur_mesure_C[1]);        // D74
  RW_parametre(RW,0,4,D_Seuil_CTRL_BO_C[1]);
  RW_parametre(RW,0,4,D_Nb_val_stab_mesure_C[1]);
  RW_parametre(RW,0,2,D_Pointeur_FO_C[1]);
  RW_parametre(RW,0,2,D_Pointeur_ET_C[1]);
  RW_parametre(RW,0,0,D_I_thermique_C[1]);

  RW_parametre(RW,0,1,D_Pointeur_Puissance_2_C[2] );
  RW_parametre(RW,0,1,D_Pointeur_Puissance_C[2] );
  RW_parametre(RW,0,1,D_Pointeur_Temps_C[2] );
  RW_parametre(RW,0,1,D_Pointeur_mesure_C[2] );       // D84
  RW_parametre(RW,0,4,D_Seuil_CTRL_BO_C[2] );
  RW_parametre(RW,0,4,D_Nb_val_stab_mesure_C[2] );
  RW_parametre(RW,0,2,D_Pointeur_FO_C[2] );
  RW_parametre(RW,0,2,D_Pointeur_ET_C[2] );*/

  // --------------------------------------------------------------------------------------------------------------------------------------------
  // Type de paramètres n°03 : Banque de régulation
  // --------------------------------------------------------------------------------------------------------------------------------------------
  // RW_parametres_cycles(RW);                       // Sauvegarde / récupération paramètres dans BANC 
    // --------------------------------------------------------------------------------------------------------------------------------------------
  // Type de paramètres n°04 : Etalonnage des entrées analogique de l'ESP32
  // -------------------------------------------------------------------------------------------------------------------------------------------- 
  // RW_parametres_Etalonnage(RW);
  // -------------------------------------------------------------------------------------------------------------------------------------------- 
}

// -----------------------------------------------------------------------------------------------------------------------------------------------
void RW_list_parametres_cycles (uint8_t RW,uint8_t Bank,uint8_t cycle){
  RW_parametre(RW,Bank,4,D_U_MIN_C[cycle] );  // Bank : 0 à 15 disponible
  RW_parametre(RW,Bank,4,D_U_MAX_C[cycle] );
  RW_parametre(RW,Bank,0,D_GP_C[cycle] );
  RW_parametre(RW,Bank,0,D_I_MAX_C[cycle] );
  RW_parametre(RW,Bank,0,D_I_MAX_LU_C[cycle] );
  RW_parametre(RW,Bank,0,D_Seuil_mesure_I_C[cycle] );
  RW_parametre(RW,Bank,4,D_KD_C[cycle] );
}
// -----------------------------------------------------------------------------------------------------------------------------------------------
void RW_list_parametres_Etalonnage(uint8_t RW,uint8_t Bank){
  RW_parametre(RW,Bank,0,D_Etalonnage_X1);
  RW_parametre(RW,Bank,0,D_Etalonnage_X2);
  RW_parametre(RW,Bank,0,D_Etalonnage_Y1);
  RW_parametre(RW,Bank,0,D_Etalonnage_Y2);
  RW_parametre(RW,Bank/4,0,D_Seuil_Ctrl_Temperature);
}
// -----------------------------------------------------------------------------------------------------------------------------------------------

void RW_parametres_Etalonnage (uint8_t RW){

      // ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      // Config_cycles & 0x000F  =>   NUM_ENTREE_1 | NUM_ENTREE_0 | CONVERSION_1 | CONVERSION_0                  (MSB First)

      // |NUM_ENTREE_1 | NUM_ENTREE_0 | CONVERSION_1  | CONVERSION_0 |          
      // |     0       |       0      |       0       |      0       |    =>    Voie 1 / Numéro de conversion 0
      // |     0       |       0      |       0       |      1       |    =>    Voie 1 / Numéro de conversion 1

      // |     0       |       1      |       0       |      0       |    =>    Voie 2 / Numéro de conversion 0
      // |     0       |       1      |       0       |      1       |    =>    Voie 2 / Numéro de conversion 0
      // ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint16_t iter_pc;
uint16_t Config_cycles;

  // ------------------------------------------------
  // Initialisation des valeurs dans l'EEPROM
  // ------------------------------------------------
  if( RW == 0) {           // Initialisation de l'EEPROM 
    for( iter_pc = 0 ;  iter_pc <= 15 ; iter_pc++){
      RW_list_parametres_Etalonnage(0,iter_pc);
    }
  }
  // ------------------------------------------------
  // Récupération des valeurs dans l'EEPROM
  // ------------------------------------------------ 
  else if(RW == 1) {      // Récupération valeurs dans l'EEPROM   
     
      // Identification de la banque d'étalonnage
      Config_cycles = WP_CONF_DYN_E;   // Cette variable va varier de 0 à 15 

      RW_list_parametres_Etalonnage(1,Config_cycles & 0x000F);          // Nible 0

      // ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      // Etape 1 : Récupération des valeurs de CONVERSION_0, CONVERSION_1 , NUM_ENTREE_0 et NUM_ENTREE_1 [4 premiers bits du registre WP_CONF_DYN_E] 
      // Etape 2 : Affectation de ces valeurs à CONVERSION_0_MODBUS_CTRL , CONVERSION_1_MODBUS_CTRL , NUM_ENTREE_0_MODBUS_CTRL et NUM_ENTREE_1_MODBUS_CTRL [4 premiers bits du registre WM_CONF_DYN_L]   
      // ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      copie_WORD( (WM_CONF_DYN_L & 0xFFF0 ) | (Config_cycles & 0x000F) , WM() , 6*16);         
      // ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  }
  // ------------------------------------------------
  // Modification des valeurs dans l'EEPROM
  // ------------------------------------------------  
  else if (RW == 2) {    
    Config_cycles = WM_CONF_DYN_L;
    //Config_cycles = 0;   // Solution provisoire
    RW_list_parametres_Etalonnage(2,Config_cycles & 0x000F);            // Nible 0 
  
  }else if (RW == 3) {   //chargement spe
    Config_cycles = WP_CONF_DYN_E; 
    RW_list_parametres_Etalonnage(1,Config_cycles & 0x000F);         // Nible 0
    copie_WORD( (WM_CONF_DYN_L & 0xFFF0 ) | (Config_cycles & 0x000F) , WM() , 6*16);     // fonction dans perso.cppWM() , 6*16)
  }
}
// -----------------------------------------------------------------------------------------------------------------------------------------------
void RW_parametres_cycles (uint8_t RW){
  uint8_t iter_pc;
  uint16_t Config_cycles;
  // ------------------------------------------------
  // Initialisation des valeurs dans l'EEPROM
  // ------------------------------------------------
  if( RW == 0 ){
    for (iter_pc = 0 ; iter_pc <= 15 ;iter_pc++){
      RW_list_parametres_cycles(0,iter_pc,1);
      RW_list_parametres_cycles(0,iter_pc,2);
    }
  }
  // ------------------------------------------------
  // Récupération des valeurs dans l'EEPROM
  // ------------------------------------------------
  else if( RW == 1){                          
    Config_cycles = WP_CONF_DYN_E; 
    RW_list_parametres_cycles(1, (Config_cycles & 0x0F00) >> 8 ,1);     // Nib 2 
    RW_list_parametres_cycles(1, (Config_cycles & 0xF000) >> 12 ,2);    // Nib 3
    
    copie_WORD( (WM_CONF_DYN_L & 0x00FF) | (Config_cycles & 0xFF00) , WM() , 6*16);     // fonction dans perso.cpp
  }
  // ------------------------------------------------
  // Modification des valeurs dans l'EEPROM
  // ------------------------------------------------  
  else if( RW == 2 ){   
    Config_cycles = WM_CONF_DYN_L; 

    RW_list_parametres_cycles(2,(Config_cycles & 0x0F00) >> 8  ,1  );  // Nib 2 
    RW_list_parametres_cycles(2,(Config_cycles & 0xF000) >> 12 ,2  );  // Nib 3 
  }
}
// -----------------------------------------------------------------------------------------------------------------------------------------------
// Modification des configurations concerné par les changements (sur la Banque D)

void ActionChargModif (uint16_t indiceD){
  if( indiceD == D_Types_Capteurs){  
    config_types_capteurs();                    // configuration des capteurs     : Permet l'affectation des différents seuils de contrôle du capteur (Saturation, Absence, Dérive)                                
  }else if( indiceD == D_Temps_Pb_puissance) {
    config_Temps_probleme_puissance();          // Configuration des temps problème puissance des cycles
  }else if( indiceD == D_Pointeur_mesure_C[1]) {    // D74
    config_Pointeur_mesure_C(1);                // Configuration pointeur de mesure cycle 1
  }else if ( indiceD == D_Pointeur_mesure_C[2]){    // D84
    config_Pointeur_mesure_C(2);                // Configuration pointeur de mesure cycle 2
  }else if (indiceD == D_Pointeur_mesure_C[3]){
    config_Pointeur_mesure_C(3);  
  }
  else if ( indiceD == D_Periode_Fth) {
    config_D_Periode_Fth();                     // relatif au calcul du facteur thermique
  }else if ( indiceD == D_I_thermique_C[1] ){
    config_D_I_thermique_C(1);                  // relatif au calcul du facteur thermique
  }else if ( indiceD == D_I_thermique_C[2] ){ 
    config_D_I_thermique_C(2);                  // relatif au calcul du facteur thermique
  }else if (( indiceD == D_Etalonnage_X1) | (indiceD == D_Etalonnage_X2) | (indiceD == D_Etalonnage_Y1)  | (indiceD == D_Etalonnage_Y2) | (indiceD == D_Seuil_Ctrl_Temperature) ){
    config_Etalonnage();                        // Configuration étalonnage
  }
}

//************Actions sur chargement ou modification***********************************************************
// Calcul le temps de fonctionnement avant problème puissance
// ------------------------------------------------------
// 1 cycle = 26.3 ms 
// 10000 ms => 380 cycle 
// Sachant que 100 = 10s => 
//  100                     -->    380 cycle
//  Temps_Pb_puissance (40) -->     ?  cycle
// ------------------------------------------------------
void config_Temps_probleme_puissance(void){
  if( *Temps_Pb_puissance < 5){   // Temps_pb_puissance défini dans variable_defaut.ino   [ 5 => 0.5 secondes]
    *Temps_Pb_puissance = 5;
  }else if( *Temps_Pb_puissance > 100) {  // [ 100 => 10 secondes]
    *Temps_Pb_puissance = 100;              
  }
  *Temps_pb_puissance_cycle = *Temps_Pb_puissance*380/100*27;     // valeur en nombre de cycle donc x27ms
}

// ***********************************************************************************************************
void config_Etalonnage(void){

  // ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Récupération du type de conversion et choix d'entrée pour le capteur de température
  // ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //Dim Num_Entree_ana As Byte
  //Dim Num_conversion_ana As Byte
  Num_conversion_ana_select = (WP_CONF_DYN_E  & 0x000F) & 3;    // Conversion n°1 : pts => mV  ;  Conversion n°02 : mV => °C  [CONVERSION_1|CONVERSION_0]
  Num_Entree_ana_select = (WP_CONF_DYN_E  & 0x000F) / 4;        // Choix de l'entrée : entrée 0,1,2,3 (voie 1)  [NUM_ENTREE_1|NUM_ENTREE_0]  [La division par 4 permet d'obtenur le n°0 de la voie]

  // ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Coefficient étalonnage
  // ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  Coeff_a[Num_Entree_ana_select][Num_conversion_ana_select] = ((*Etalonnage_Y2)*1.0 - (*Etalonnage_Y1)*1.0)/((*Etalonnage_X2)*1.0 - (*Etalonnage_X1)*1.0);
  Coeff_b[Num_Entree_ana_select][Num_conversion_ana_select] = (*Etalonnage_Y1)*1.0 - ( Coeff_a[Num_Entree_ana_select][Num_conversion_ana_select])*((*Etalonnage_X1)*1.0);



  //  [SDP-CP V2] : R = 7.5 kOhm => à 0°C => U = 2.048 V et à 150°C => U = 3173 V 

  // ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Gestion des seuils de contrôle température
  // ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  if(D()[D_Seuil_Ctrl_Temperature]>1400){  // 140°C

      D()[D_Seuil_Ctrl_Temperature] = 1400;

  }

  if(D()[D_Seuil_Ctrl_Temperature]>0 ) {
    
          Seuil_Ctrl_temperature[Num_Entree_ana_select] = D()[D_Seuil_Ctrl_Temperature];

        for (int i=0;i<4;i++){
          Seuil_Ctrl_CAPTEUR_temperature[i][0] = 1882 ; // unité : pts  // Limite basse 
          Seuil_Ctrl_CAPTEUR_temperature[i][1] = 2660 ; // unité : pts  // Limite haute
        }



  }else{
          Seuil_Ctrl_temperature[Num_Entree_ana_select] =  65535;

        for (int i=0;i<4;i++){
          Seuil_Ctrl_CAPTEUR_temperature[i][0] = 0 ; // unité : pts  // Limite basse 
          Seuil_Ctrl_CAPTEUR_temperature[i][1] = 65535 ; // unité : pts  // Limite haute
        }
  }
  // ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------





}

void config_D_I_thermique_C(uint8_t ncyclesub){
    uint32_t Ith_int;

    /*
    Ith_int = D()[D_I_thermique_C[ncyclesub]]*1.0;  // 800 

    Seuil_Fth[ncyclesub-1] = PeriodeFth * Ith_int * Ith_int; // 6000*800^2


    for(uint8_t iter_ith = 0; iter_ith < Fth_nb_points ; iter_ith++){
      Integral_Tab[ncyclesub-1][iter_ith] = 0;
    }
    //Decr_Fth[ncyclesub-1] = 0;
    Integral_dt[ncyclesub-1] = 0;
    Integral_100ms[ncyclesub-1] = 0;*/
}


void config_D_Periode_Fth(void){

    if( *Periode_Fth < (Fth_nb_points_max*5)) {    // D()[57] 600.0s == 6000  (a valider)
      *Periode_Fth = Fth_nb_points_max*5;
    }
    *Temps_Facteur_thermique = *Periode_Fth;    // T()[67] = D()[57]

    PeriodeFth = *Periode_Fth;  // D()[57] = 6000

    dT_Fth = ( PeriodeFth/Fth_nb_points_max )+1 ; // 26

    if(dT_Fth<20){
      dT_Fth=20;
      //Fth_nb_points = PeriodeFth / dT_Fth;
    }
    /*else{
    ' Fth_nb_points = Fth_nb_points_max;
    }*/
    Fth_nb_points = PeriodeFth/dT_Fth;  // 
    // config_D_I_thermique_C() a revoir (reset provoqué par cette fonction)
    config_D_I_thermique_C(1);
    config_D_I_thermique_C(2);
}

// Configuration des capteurs
void config_types_capteurs(void){
  uint8_t num_V ;             // numero de voie
  uint8_t n_type_cap;            
    
   types_capteurs = *Types_Capteurs;            // récupération de la config des capteurs
   type_capteur[0] = types_capteurs & 0x000F;  // récupération de la config du capteurs sur l'entrée analogique 1
   type_capteur[1] = (types_capteurs & 0x00F0) >> 4;  // récupération de la config du capteurs sur l'entrée analogique 2
   type_capteur[2] = (types_capteurs & 0x0F00) >> 8;  // récupération de la config du capteurs sur l'entrée analogique 3
   type_capteur[3] = (types_capteurs & 0xF000) >> 12;  // récupération de la config du capteurs sur l'entrée analogique 4


   // Gestion capteurs supplémentaires 
   types_capteurs_sup= *Types_Capteurs_Sup;
   type_capteur[4] = types_capteurs_sup & 0x000F;           // récupération de la config du capteurs sur l'entrée analogique 5
   type_capteur[5] = (types_capteurs_sup & 0x00F0) >> 4;    // récupération de la config du capteurs sur l'entrée analogique 6






   // Affectation des caracteristiques de chaque capteurs en fonctions du tableau des caracteristiques de la fonctions liste_capteurs dans le ficier def_capteurs.ino
   // Pour plus de précision voir aussi Manuel developpeur page 32-33
   for(num_V = 0; num_V < 6 ; num_V++){
     n_type_cap = type_capteur[num_V]; 

     T()[T_Seuil_Saturation_H[num_V]] = Var_capteur[n_type_cap][0]; 
     T()[T_Seuil_Saturation_B[num_V]] = Var_capteur[n_type_cap][1] ;
     T()[T_Seuil_Presence[num_V]] = Var_capteur[n_type_cap][2] ;
     T()[T_Seuil_Derive_H[num_V]] = Var_capteur[n_type_cap][3] ;
     T()[T_Seuil_Derive_B[num_V]] = Var_capteur[n_type_cap][4] ;


   }


  // configure les pointeurs de mesures
  config_Pointeur_mesure_C(1);
  config_Pointeur_mesure_C(2);
  
  config_Pointeur_mesure_C(3);   // Pointeurs Mesure du générateur 3 


}



// fonctions d'affectations de variable dans la banque T
void Affecte_T(uint16_t num_T_sub, uint16_t param_sub){
  T()[num_T_sub]  = param_sub;
}
// fonctions d'affectations de variable dans la banque D
void Affecte_D(uint16_t num_D_sub, uint16_t param_sub){
  D()[num_D_sub]  = param_sub;
}

// configure la valeur du pointeur de mesure ( choix de la voie à mesurer)
void config_Pointeur_mesure_C(uint8_t ncyclesub){
  uint8_t voie_sub;

  uint8_t iter_point_mes;         // itération pointeur mesure
  voie_sub = 0 ;

  // ........................................................................
  if (ncyclesub != 3 ){
    // On a à notre disposition le pointeur de mesure du générateur via le registre Modbus  D()[D_Pointeur_mesure_C[ncyclesub]]

  // Identification de la voie de mesure utilisée par le générateur ainsi que le type de valeur pointée (efficace ou crete)  
  for( iter_point_mes = 1 ; iter_point_mes <= 6 ; iter_point_mes++){
    if (D()[D_Pointeur_mesure_C[ncyclesub]] == D_Mesure_eff_V[iter_point_mes] ){         // Si le pointeur mesure du cycle pointe sur une des voies de mesures de valeurs efficaces
      voie_sub = iter_point_mes;    // Voie_sub = 0 si le pointeur de mesure pointe sur une valeur crete ; Voie_sub > 0 si le pointeur de mesure pointe sur une valeur efficice 
    } 
  }
  
  // --------------------------------------------------------------------------------------------
  // Condition validée si valeur pointée efficace 
  // --------------------------------------------------------------------------------------------
  if( voie_sub > 0 ){ 
    
    // --------------------------------------------------------------------------------------------
    // Registres permettant d'identifier le type de mesure pointée (Efficace ou crête)
    // --------------------------------------------------------------------------------------------
    M()[M_MESURE_EFF_C[ncyclesub]]  = 1;                    // Pointe sur une valeur efficace
    M()[M_MESURE_CRETE_C[ncyclesub]]  = 0;                  // Ne pointe pas sur une valeur crête
    // --------------------------------------------------------------------------------------------

    D()[D_Pointeur_mesure_sec_C[ncyclesub]] = D_Mesure_cre_V[voie_sub] ;    // affecte la nouvelle valeur de pointeur de mesure sur la mesure de la valeur crête de la voie selectionné

    //#If Device = 380  
      Pointeur_Eff_Fth[ncyclesub-1] = D_Mesure_eff_V[voie_sub];   // Utilisé pour les calculs des facteurs thermiques (fonction F2M())
    //#Endif


  }
  // --------------------------------------------------------------------------------------------
  // Condition validée si valeur pointée Crête
  // --------------------------------------------------------------------------------------------
  else{ 

    M()[M_MESURE_EFF_C[ncyclesub]] = 0;         // Ne pointe pas sur une valeur efficace
    // scrutation des mesures de valeurs crêtes
    for( iter_point_mes = 1 ; iter_point_mes <= 6 ; iter_point_mes++){
      if( D()[D_Pointeur_mesure_C[ncyclesub]] == D_Mesure_cre_V[iter_point_mes] ){   // Si le pointeur mesure du cycle pointe sur une des voies de mesures de valeurs crête
        voie_sub = iter_point_mes;                                              // La voie étudié sera cette même voie
      }
    }

    // Si une voie est étudié (valeur crête)
    if( voie_sub>0 ){
      M()[M_MESURE_CRETE_C[ncyclesub]]  = 1;      // Pointe sur une valeur crête
      D()[D_Pointeur_mesure_sec_C[ncyclesub]] = D_Mesure_eff_V[voie_sub] ;  // affecte la nouvelle valeur du pointeur de mesure sur la mesure de la valeur crête de la voie selectionné 
      //#If Device = 380  
        Pointeur_Eff_Fth[ncyclesub-1]= D_Mesure_eff_V[voie_sub];
      //#Endif

    }else{                                      // Sinon
      M()[M_MESURE_CRETE_C[ncyclesub]]  = 0;    // Ne pointe pas non plus sur une valeur crête
      D()[D_Pointeur_mesure_sec_C[ncyclesub]] =  D()[D_Pointeur_mesure_C[ncyclesub]]; // La nouvelle valeur du pointeur ne change pas
      //#If Device = 380  
      Pointeur_Eff_Fth[ncyclesub-1] = D()[D_Pointeur_mesure_C[ncyclesub]];        // Récupération du pointeur de la valeur efficace  pour les calculs des facteurs thermiques (fonction F2M())
      //#Endif
    }
  }
  // -------------------------------------------------------------------------------------------------------------
  // Permet de définir sur quelle voie le contrôle de forme d'onde sera effectué pour un générateur donné 
  // -------------------------------------------------------------------------------------------------------------
  // | N_VOIE_FO_B0_C1 | N_VOIE_FO_B0_C1 | 
  // |        0        |        0        |             => voie 1 
  // |        1        |        0        |             => voie 2
  // |        0        |        1        |             => voie 3
  // |        1        |        1        |             => voie 4
  // -------------------------------------------------------------------------------------------------------------
  P()[P_N_VOIE_FO_B0_C[ncyclesub]]  =  P_N_VOIE_FO_B0_V[voie_sub];      
  P()[P_N_VOIE_FO_B1_C[ncyclesub]]  =  P_N_VOIE_FO_B1_V[voie_sub];
  P()[P_N_VOIE_FO_B2_C[ncyclesub]]  =  P_N_VOIE_FO_B2_V[voie_sub];        
  // -------------------------------------------------------------------------------------------------------------
  }
  // ........................................................................
  else {  // Générateur 3

    voie_sub = 0 ;

    
    // ......................................................................
    // Etape 1 : Est-ce que le générateur pointe sur une valeur efficace  
    // ......................................................................
    for( iter_point_mes = 7 ; iter_point_mes <= 9 ; iter_point_mes++){
      if (D()[D_Pointeur_mesure_C[ncyclesub]] == D_Mesure_eff_V[iter_point_mes] ){         // Si le pointeur mesure du cycle pointe sur une des voies de mesures de valeurs efficaces
        voie_sub = iter_point_mes;    // Voie_sub = 0 si le pointeur de mesure pointe sur une valeur crete ; Voie_sub > 0 si le pointeur de mesure pointe sur une valeur efficice 
      } 
    }

    #ifdef DRAFT

    #endif

  // --------------------------------------------------------------------------------------------
    // Condition validée si valeur pointée efficace 
    // --------------------------------------------------------------------------------------------
    if( voie_sub > 0 ){ 
      
      // --------------------------------------------------------------------------------------------
      // Registres permettant d'identifier le type de mesure pointée (Efficace ou crête)
      // --------------------------------------------------------------------------------------------
      M()[M_MESURE_EFF_C[ncyclesub]]  = 1;                    // Pointe sur une valeur efficace
      M()[M_MESURE_CRETE_C[ncyclesub]]  = 0;                  // Ne pointe pas sur une valeur crête
      // --------------------------------------------------------------------------------------------

      D()[D_Pointeur_mesure_sec_C[ncyclesub]] = D_Mesure_cre_V[voie_sub] ;    // affecte la nouvelle valeur de pointeur de mesure sur la mesure de la valeur crête de la voie selectionné

      //#If Device = 380  
        Pointeur_Eff_Fth[ncyclesub-1] = D_Mesure_eff_V[voie_sub];   // Utilisé pour les calculs des facteurs thermiques (fonction F2M())
      //#Endif


    }
    // --------------------------------------------------------------------------------------------
    // Condition validée si valeur pointée Crête
    // --------------------------------------------------------------------------------------------
    else{ 

      M()[M_MESURE_EFF_C[ncyclesub]] = 0;         // Ne pointe pas sur une valeur efficace
      // scrutation des mesures de valeurs crêtes
      for( iter_point_mes = 7 ; iter_point_mes <= 9 ; iter_point_mes++){
        if( D()[D_Pointeur_mesure_C[ncyclesub]] == D_Mesure_cre_V[iter_point_mes] ){   // Si le pointeur mesure du cycle pointe sur une des voies de mesures de valeurs crête
          voie_sub = iter_point_mes;                                              // La voie étudié sera cette même voie
        }
      }

      

      // Si une voie est étudié (valeur crête)
      if( voie_sub>0 ){
        M()[M_MESURE_CRETE_C[ncyclesub]]  = 1;      // Pointe sur une valeur crête
        D()[D_Pointeur_mesure_sec_C[ncyclesub]] = D_Mesure_eff_V[voie_sub] ;  // affecte la nouvelle valeur du pointeur de mesure sur la mesure de la valeur crête de la voie selectionné 
        //#If Device = 380  
          Pointeur_Eff_Fth[ncyclesub-1]= D_Mesure_eff_V[voie_sub];
        //#Endif

      }else{                                      // Sinon
        M()[M_MESURE_CRETE_C[ncyclesub]]  = 0;    // Ne pointe pas non plus sur une valeur crête
        D()[D_Pointeur_mesure_sec_C[ncyclesub]] =  D()[D_Pointeur_mesure_C[ncyclesub]]; // La nouvelle valeur du pointeur ne change pas
        //#If Device = 380  
        Pointeur_Eff_Fth[ncyclesub-1] = D()[D_Pointeur_mesure_C[ncyclesub]];        // Récupération du pointeur de la valeur efficace  pour les calculs des facteurs thermiques (fonction F2M())
        //#Endif
      }
    }

      P()[P_N_VOIE_FO_B0_C[ncyclesub]]  =  P_N_VOIE_FO_B0_V[voie_sub];      
      P()[P_N_VOIE_FO_B1_C[ncyclesub]]  =  P_N_VOIE_FO_B1_V[voie_sub];
      P()[P_N_VOIE_FO_B2_C[ncyclesub]]  =  P_N_VOIE_FO_B2_V[voie_sub];    

    
    // ......................................................................


  }

  
}


// --------------- action sur WM --------------------
void RW_parametre_WM (uint8_t RW, uint8_t WM){ //0 -200
  adr_eeprom = (WM*2) + 300;      // Adresse EEPROM = indice du WM*2(banque en octets donc 2 octets pour un mots) + 300(= debut de la plage des WM)
  if( RW == 0 ){
    Init_eeprom_WM (adr_eeprom,WM);
  }else if( RW == 1 ){
    Chargement_parametre_WM (adr_eeprom,WM);
  }else if( RW == 2 ){
    Sauvegarde_parametre_WM (adr_eeprom,WM);
  }
}

void Init_eeprom_WM(uint16_t adr,uint8_t indiceWM){
  if(  ((EEPROM.read(adr) && EEPROM.read(adr+1)) == 0xFF)  // Si case mémoire EEPROM non écrite
        & (Valeur_par_defaut_D[indiceWM] != 65535)         // Si valeur par défaut différent de 65535
        | (Ecrire_param_par_defaut == 1) ){                // 
        
    WM()[indiceWM*16]= Valeur_par_defaut_WM[indiceWM];
    Sauvegarde_parametre_WM(adr,indiceWM);  
  }
  vTaskDelay(10);   // pas nécésaaire sur l'ESP32 ???
}

void Chargement_parametre_WM (uint16_t adr , uint8_t indiceWM ){ // 0 -200
  WM()[indiceWM*16] = EEPROM.read(adr) + (EEPROM.read(adr+1)<<8);
  ActionChargModif_WM(indiceWM);
}

void Sauvegarde_parametre_WM (uint16_t adr, uint8_t indiceWM){ // 0 -200
  if ((EEPROM.read(adr) + (EEPROM.read(adr+1)<<8)) != WM()[indiceWM*16]) { 
    EEPROM.write(adr,WM(indiceWM)&0xFF);
    EEPROM.write(adr+1,(WM(indiceWM)>>8)&0xFF);
    EEPROM.commit();        // indispensable à l'écriture dans la mémoire (valide les changements dans la mémoire)
    vTaskDelay(1);          // pas nécésaaire sur l'ESP32 ???
    ActionChargModif_WM(indiceWM);
  }
}

void ActionChargModif_WM(uint8_t WM){
}


// -----------------------------------------------------------------------------------------------------
