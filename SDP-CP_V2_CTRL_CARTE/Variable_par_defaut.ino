#include <EEPROM.h>
#include <HardwareSerial.h>
#include "variables_globales_basic.h"
#include "Banque_EEPROM.h"

// Valeur par défaut GT

// ====== Valeurs par défauts =================
//  La fonction Valeur_defaut() charge les valeurs par défauts de la config dans les tableaux Valeur_par_defaut_D[] et  Valeur_par_defaut_WM[]: 
//    - configuration options des générateurs 1 et 2
//    - valeurs par défauts du la configuration générale
//    - valeurs par défauts des paramètre d'étalonnage
//    - valeurs par défauts de pointeurs
//    - valeurs par défauts des banques de paramètres de régulation et linéarisations
// La fonction Valeur_defaut() est appellé dans le setup()


// Ecrit la valeur par défauts dan la banque D
void defaut_D(uint16_t D,uint16_t param){
  Valeur_par_defaut_D[D] = param;
  #if defined DEBUG_VAL_PAR_DEFAUTS
  printf("valeur par defaut D[%d] = %d\n",D,param);
  #endif
}

// Ecrit la valeur par défauts dan la banque WM
void defaut_WM(uint8_t WM,uint16_t param){
  Valeur_par_defaut_WM [WM] = param;
  #if defined DEBUG_VAL_PAR_DEFAUTS
  printf("valeur par defaut WM[%d] = %d\n",WM,param);
  #endif
}

void Valeur_defaut(void){
// configuration options des générateurs 1 et 2
  defaut_WM(BITS_CONFIG_G1   , 0);
  defaut_WM(BITS_CONFIG_G2   , 0);

// valeurs par défauts du la configuration générale
  defaut_D (D_MODE  , 0); //28681
  defaut_D (D_Types_Capteurs      , 17);  // D:28737     4352 =>  Voie 1 / 2 : sans capteur ; Voie 3/4 : capteur ABB (sans ctrl)     //
  defaut_D (D_Temps_Pb_puissance   , 40); // D:28728
  defaut_D (D_Periode_Fth       , 6000);  // D:28729
  defaut_D (D_Seuil_Ctrl_Temperature  , 140); //D:28730
  defaut_D (D_COEF_CONE_TUBE      , 1000); // D:28736
  defaut_D (D_Gain_BOOST        , 6000); // D:28731
  
// valeurs par défauts des paramètre d'étalonnage
  // Valeurs en points 
  defaut_D (D_Etalonnage_X1   , 2723);  // D:28722             // Mesuré par l'ESP32         
  defaut_D (D_Etalonnage_X2       , 4095); // D:28723

  // Valeurs en mV
  defaut_D (D_Etalonnage_Y1       , 2215);  // D:28724         // Mesuré au multimètre
  defaut_D (D_Etalonnage_Y2       , 3300);  // D:28725

// valeurs par défauts de pointeurs++++++++++++++++++++++++++++++++++++++++++++++++++++
// Finalité : D()[68] = 143
  defaut_D (D_Pointeur_DCY        , 143); // D:28740   // M TOR_E1    Valeur_par_defaut_D[D_Pointeur_DCY = 68] = 143
  defaut_D (D_Pointeur_ACY        , 142); // D:28741   // M TOR_E2
  defaut_D (D_Pointeur_ACQ        , 142); // D:28738
  defaut_D (D_Pointeur_DEMAG      , 141); // D:28739
  defaut_D (D_Pointeur_TOR_S[1]    , 53);      // D:28732
  defaut_D (D_Pointeur_TOR_S[2]     , 49);     // D:28733
  defaut_D (D_Pointeur_TOR_S[3]     , 54);     // D:28734
  defaut_D (D_Pointeur_TOR_S[4]     , 51);     // D:28735

// Générateur 1  
  defaut_D (D_I_thermique_C[1]     , 800);  // D:28742
  
  defaut_D (D_Pointeur_Puissance_2_C[1] , D_Potard_V4_Puissance);       // D:28743
  defaut_D (D_Pointeur_Puissance_C[1] , D_Potard_V4_Puissance);         // D:28744
  defaut_D (D_Pointeur_Temps_C[1]  , D_Potard_V3_Temps       );         // D:28745
  defaut_D (D_Pointeur_mesure_C[1]    , D_Mesure_simulee_C[1] /*D_Entree_ana_efficace_V5*/);  // D:28746 // D()[27] = Valeur efficace sur la voie 1 / 2
  defaut_D (D_Seuil_CTRL_BO_C[1]    , 0);      // D:28764
  defaut_D (D_Nb_val_stab_mesure_C[1] , 200);  //2%  // D:28766
  defaut_D (D_Pointeur_FO_C[1]      , 62);   // D:28768
  defaut_D (D_Pointeur_ET_C[1]      , 60);   // D:28770
  
// valeurs par défauts des banques de paramètres de régulation et linéarisations
  defaut_D (D_Seuil_mesure_I_C[1]   , 30);  // D:28751
  defaut_D (D_I_MAX_C[1]        , 2800);    // D:28750
  defaut_D (D_I_MAX_LU_C[1]       , 65535);
  defaut_D (D_U_MIN_C[1]        , 600);  // D:28747
  defaut_D (D_U_MAX_C[1]        ,5000);  // D:28748
  defaut_D (D_GP_C[1]         , 4000);   // D:28749
  defaut_D (D_KD_C[1]         , 7500);   // D:28762
  
// Générateur 2
  defaut_D (D_I_thermique_C[2]      , 800);                                        // D:28752

  defaut_D (D_Pointeur_Puissance_2_C[2] , D_Potard_V4_Puissance); // 19            // D:28753
  defaut_D (D_Pointeur_Puissance_C[2] , D_Potard_V4_Puissance);                    // D:28754
  defaut_D (D_Pointeur_Temps_C[2]   , D_Potard_V3_Temps);         // 18            // D:28755
  defaut_D (D_Pointeur_mesure_C[2]    , D_Mesure_simulee_C[2]);                    // D:28756
  defaut_D (D_Seuil_CTRL_BO_C[2]    , 0);                                          // D:28765
  defaut_D (D_Nb_val_stab_mesure_C[2] , 200);                                      // D:28767
  defaut_D (D_Pointeur_FO_C[2]  , 63);                                             // D:28768
  defaut_D (D_Pointeur_ET_C[2] , 61);                                              // D:28771

//  valeurs par défauts des banques de paramètres de régulation et linéarisations
  defaut_D (D_Seuil_mesure_I_C[2]  , 30);                                          // D:28761
  defaut_D (D_I_MAX_C[2]  , 2800);                                                 // D:28760
  defaut_D (D_I_MAX_LU_C[2]  , 65535);                                             // D:28727
  defaut_D (D_U_MIN_C[2]  , 600);                                                    // D:28757
  defaut_D (D_U_MAX_C[2]  , 5000);                                                // D:28758
  defaut_D (D_GP_C[2] , 4000);                                                      // D:28759
  defaut_D (D_KD_C[2] , 7500);                                                     // D:28763
}

// Charge les valeurs par défauts préent dans les tableaux Valeur_par_defaut_D[] et Valeur_par_defaut_WM[] dans les registres associés
// D()[68] = Valeur_par_defaut_D[D_Pointeur_DCY = 68]
void chargement_Valeur_defaut(void){ 
  #if defined DEBUG_VAL_PAR_DEFAUTS
  printf("\n\n\n");
  #endif
  
   for(int i = 0; i < 100; i++){
    D()[i] = Valeur_par_defaut_D[i];
    #if defined DEBUG_VAL_PAR_DEFAUTS
    printf("D[%d] = %d\n",i,D()[i]);
    #endif
   }

   for(int i = 0; i < 32; i++){
    WM()[i] = Valeur_par_defaut_WM[i];
    #if defined DEBUG_VAL_PAR_DEFAUTS
    printf("WM[%d] = %d\n",i,WM()[i]);
    #endif
   }
}


