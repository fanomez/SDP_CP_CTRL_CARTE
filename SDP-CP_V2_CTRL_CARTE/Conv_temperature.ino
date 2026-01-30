#include "variables_globales_basic.h"
#include "variables_globales.h"

#define PRET_A_TESTER


/**********************************************************************************************************************************
 * @brief Fonction permettant :
 *    - conversion en temperature des sorties des sondes
 * @note On dispose de deux entrées permettant l'exploitation de deux sondes de températures 
 *
 *********************************************************************************************************************************/
void Conversions_Mesures_Entrees_Ana(uint8_t num_Entree){

      test_temperature();


      if (num_Entree == 0){
          temp_mes = analogReadMilliVolts(SENSOR_VP);    // ESP32_ANA1 : CON_TEMPE_2  (nomenclature dans le schéma électrique)
      }else{
          temp_mes = analogReadMilliVolts(SENSOR_VN);     // ESP32_ANA0 : CON_TEMPE_1  (nomenclature dans le schéma électrique)
      }
      
      // num_valeur va de 0 à 20 (nb de valeurs moyennés)
      Somme_Moyennage[num_Entree] = Somme_Moyennage[num_Entree] - tab_moyennage[num_Entree][num_valeur] + temp_mes;

      tab_moyennage[num_Entree][num_valeur] = temp_mes;

      if (Activation_Conversions == 1){
              // ---------------------------------------------------------------------------------------------
              // Moyennage des valeurs mesurés sur l'ADC de l'ESP32
              // ---------------------------------------------------------------------------------------------    
              if (Somme_Moyennage[num_Entree] == 0){
                  Mesures_Ana[num_Entree] = 0;
              }else{
                  Mesures_Ana[num_Entree] = Somme_Moyennage[num_Entree]/Nb_Valeurs_Moyennage;  // 0 à 4095 points
              }
              
              // ---------------------------------------------------------------------------------------------
              // Déclenchement Alarme : Seuil Capteur temperature  : Matériel [pts]
              // ---------------------------------------------------------------------------------------------              
              if (Mesures_Ana[num_Entree] > Seuil_Ctrl_CAPTEUR_temperature[num_Entree][1] || Mesures_Ana[num_Entree] < Seuil_Ctrl_CAPTEUR_temperature[num_Entree][0]){
                P()[P_SEUIL_CAPTEUR_TEMPERATURE[num_Entree]] = 1 ;
              }else{
                P()[P_SEUIL_CAPTEUR_TEMPERATURE[num_Entree]] = 0 ;
              }
              // ---------------------------------------------------------------------------------------------
              // Pas besoin de récupération de pts, on peut directement récupérer les valeurs en  mV . 
              // ---------------------------------------------------------------------------------------------
              


              mesure_single = Mesures_Ana[num_Entree];

              if (mesure_single<0){
                Mesures_Converties[num_Entree][0] = 0;
              }else{
                Mesures_Converties[num_Entree][0] = mesure_single;
              }

              *C_Debug_Val_1 = mesure_single;

              
              // ---------------------------------------------------------------------------------------------
              // Conversion 2 : mV en dC
              // ---------------------------------------------------------------------------------------------
              mesure_single = Mesures_Converties[num_Entree][0]*Coeff_a[num_Entree][1]+Coeff_b[num_Entree][1];

              *C_Debug_Val_2 = Coeff_a[num_Entree][1];
              *C_Debug_Val_3 = Coeff_b[num_Entree][1];

              *C_Debug_Val_4 =  mesure_single; 

              if (mesure_single<0){
                
                Mesures_Converties[num_Entree][1] = 0;

              }else if (mesure_single>1500){
                Mesures_Converties[num_Entree][1]  = 1500;
              }else{
                Mesures_Converties[num_Entree][1]  = mesure_single;
              }

             *C_Debug_Val_5 = Seuil_Ctrl_temperature[num_Entree]; 




              // ---------------------------------------------------------------------------------------------
              // Déclenchement Alarme : dépassement seuil Capteur temperature  : Thermique [°C]
              // ---------------------------------------------------------------------------------------------   
              if (Mesures_Converties[num_Entree][1]>Seuil_Ctrl_temperature[num_Entree]){
                    P()[P_DEPASS_SEUIL_TEMPERATURE[num_Entree]] = 1;
              }else{
                    P()[P_DEPASS_SEUIL_TEMPERATURE[num_Entree]] = 0;
              }
              // ---------------------------------------------------------------------------------------------   
      }
   

}
/**********************************************************************************************************************************
 * @brief Fonction permettant :
 *    - 
 *    - 
 *
 *********************************************************************************************************************************/
 #ifdef PRET_A_TESTER   // 10/10/2025 (non validee)

void Select_mesures_Converties(){

	if(Num_conversion_ana_select == 1){
     *C_Mesure_source = Mesures_Converties[Num_Entree_ana_select][0];
  }else{
      *C_Mesure_source = Mesures_Ana[Num_Entree_ana_select];
  } 

	*C_Mesure_convertie = Mesures_Converties[Num_Entree_ana_select][Num_conversion_ana_select];

}
#endif

/**********************************************************************************************************************************
 * @brief Fonction permettant :
 *    - déclencher la conversion une fois qu'on a reçu N mesures
 *    - une moyenne sur effectués sur ces mesures
 *
 *********************************************************************************************************************************/
void Scrut_ES_specifique(){

  if (num_valeur == Nb_Valeurs_Moyennage){   // Valeur utilisé pour les entrée analogiques de l'ESP32
      num_valeur = 0 ;
      Activation_Conversions=1;
  }

  #ifdef PRET_A_TESTER   // 10/10/2025 (non validee)

    Conversions_Mesures_Entrees_Ana(0); // Première voie de température 
    Conversions_Mesures_Entrees_Ana(1); // Deuxième voie de température 

    Select_mesures_Converties();
  #endif


  num_valeur ++;
}



// ============================================================================================================
// Variables de moyennage de la température
// ============================================================================================================
void initVariablesTemperature(void){
    for (int i = 0; i<2;i++){
      for (int j=0;j<Nb_Valeurs_Moyennage;j++){
          tab_moyennage[i][j] = 0;
      }
      Somme_Moyennage[i] = 0;
    }
}
// ============================================================================================================

#ifdef PRET_A_TESTER
  // Objectif : Visualisation des mesures non converti
  void test_temperature(){

  // Debug
    *C_Debug_Val_7 =  analogReadMilliVolts(SENSOR_VP)  ; 
    *C_Debug_Val_8 =  analogReadMilliVolts(SENSOR_VN)  ; 

  }

#endif


