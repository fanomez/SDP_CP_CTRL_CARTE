#include <EEPROM.h>
#include <HardwareSerial.h>
#include "variables_globales_basic.h"
#include "definition_banque.h"
#include <SD.h>


// #define DEBUG_EEPROM // Validation unitaire de la fonction EEPROM


// ========
// SD Card
// ========
 /* StaticJsonDocument<16384> doc;*/


#define SHUNT_EPPROM
#define VALIDEE 
#define PRET_A_TESTER




// ==== Gestion Basic ===
// Code initialement codé en BASIC sur le CUBLOC
// S'éxécute en permanence (tâche du multitâches)
// Active le calcul du facteur thermique
// Sauvegarde des valeurs dans l'EEPROM
// Changement des paramètres de configuration

void gestion_BASIC(void * param){
  while(1){
     
    // -------------------------------------------------------------------------------------------------------------
     if(Int_periodique){
      Int_periodique = 0; 
        

        #ifdef PRET_A_TESTER

       Scrut_ES_specifique();               // Incrémentation du nombre de mesures analogique reçue (utilisé pour le moyennage)  // Lance la conversion aprsè avoir reçu 20 valeurs 
        
        #endif

        Timer99 = 0;

    } 
     // -------------------------------------------------------------------------------------------------------------
     // Gestion du changement de config cycle 1 et 2
     // -------------------------------------------------------------------------------------------------------------
    if(M()[M_CYCLE_GENERAL_A_0] && modif_banque_wifi_en_cours == 0){    

        // Changment config cycle 1 et cycle 2
        if((WP_CONF_DYN_E & 0xFFF0) != (WM_CONF_DYN_L &0xFFF0)){    // Detection changement de banque 
             copie_WORD( (WM_CONF_DYN_L & 0x000F) | (WP_CONF_DYN_E & 0xFFF0) , WM() , 6*16);

             // ..............................................................................
             // Affectation des données de la banque en cours 
             // ..............................................................................
                  *U_MIN_C1 =           *U_MIN_C1_B[(WP_CONF_DYN_E & 0x0F00)>>8] ;
                  *U_MAX_C1 =           *U_MAX_C1_B[(WP_CONF_DYN_E & 0x0F00)>>8] ;
                  *GP_C1    =           *GP_C1_B[(WP_CONF_DYN_E & 0x0F00)>>8];
                  *I_MAX_C1 =           *I_MAX_C1_B[(WP_CONF_DYN_E & 0x0F00)>>8];
                  *Seuil_mesure_I_C1 =  *Seuil_mesure_I_C1_B[(WP_CONF_DYN_E & 0x0F00)>>8];
                  *KD_C1              = *KD_C1_B[(WP_CONF_DYN_E & 0x0F00)>>8];
                  *I_MAX_LU_C1        = *I_MAX_LU_C1_B[(WP_CONF_DYN_E & 0x0F00)>>8]; 

                  *U_MIN_C2 =           *U_MIN_C2_B[(WP_CONF_DYN_E & 0xF000)>>12] ;
                  *U_MAX_C2 =           *U_MAX_C2_B[(WP_CONF_DYN_E & 0xF000)>>12] ;
                  *GP_C2    =           *GP_C2_B[(WP_CONF_DYN_E & 0xF000)>>12] ;
                  *I_MAX_C2 =           *I_MAX_C2_B[(WP_CONF_DYN_E & 0xF000)>>12];
                  *Seuil_mesure_I_C2 =  *Seuil_mesure_I_C2_B[(WP_CONF_DYN_E & 0xF000)>>12];
                  *KD_C2              = *KD_C2_B[(WP_CONF_DYN_E & 0xF000)>>12];
                  *I_MAX_LU_C2        = *I_MAX_LU_C2_B[(WP_CONF_DYN_E & 0xF000)>>12]; 

                  *U_MIN_C3 =           *U_MIN_C3_B[(WP_CONF_DYN_E & 0x00F0)>>4] ;
                  *U_MAX_C3 =           *U_MAX_C3_B[(WP_CONF_DYN_E & 0x00F0)>>4] ;
                  *GP_C3    =           *GP_C3_B[(WP_CONF_DYN_E & 0x00F0)>>4] ;
                  *I_MAX_C3 =           *I_MAX_C3_B[(WP_CONF_DYN_E & 0x00F0)>>4];
                  *Seuil_mesure_I_C3 =  *Seuil_mesure_I_C3_B[(WP_CONF_DYN_E & 0x00F0)>>4];
                  *KD_C3              = *KD_C3_B[(WP_CONF_DYN_E & 0x00F0)>>4];
                  *I_MAX_LU_C3        = *I_MAX_LU_C3_B[(WP_CONF_DYN_E & 0x00F0)>>4]; 

                  *ID_FTH_C3 = *ID_Fth_C3_B[(WP_CONF_DYN_E & 0x00F0)>>4];
                  *ID_FTH_C1 = *ID_Fth_C1_B[(WP_CONF_DYN_E & 0x0F00)>>8];
                  *ID_FTH_C2 = *ID_Fth_C2_B[(WP_CONF_DYN_E & 0xF000)>>12];


             // ..............................................................................
        }

        banques_en_cours[0] = (WP_CONF_DYN_E & 0x0F00)>>8;   // G1
        banques_en_cours[1] = (WP_CONF_DYN_E & 0xF000)>>12;  // G2
        banques_en_cours[2] = (WP_CONF_DYN_E & 0x00F0)>>4;   // G3
        banques_en_cours[3] = (WP_CONF_DYN_E & 0x000F);      // Sonde de temperature   

         // Sauvegarde de la nouvelle modification via SDT Manager 
                  
        *U_MIN_C1_B[(WP_CONF_DYN_E & 0x0F00) >> 8]          = *U_MIN_C1;
        *U_MAX_C1_B[(WP_CONF_DYN_E & 0x0F00) >> 8]          = *U_MAX_C1;
        *GP_C1_B[(WP_CONF_DYN_E & 0x0F00) >> 8]             = *GP_C1;
        *I_MAX_C1_B[(WP_CONF_DYN_E & 0x0F00) >> 8]          = *I_MAX_C1;
        *Seuil_mesure_I_C1_B[(WP_CONF_DYN_E & 0x0F00) >> 8] = *Seuil_mesure_I_C1;
        *KD_C1_B[(WP_CONF_DYN_E & 0x0F00) >> 8]             = *KD_C1;
        *I_MAX_LU_C1_B[(WP_CONF_DYN_E & 0x0F00) >> 8]       = *I_MAX_LU_C1;

        *U_MIN_C2_B[(WP_CONF_DYN_E & 0xF000) >> 12]         = *U_MIN_C2;
        *U_MAX_C2_B[(WP_CONF_DYN_E & 0xF000) >> 12]         = *U_MAX_C2;
        *GP_C2_B[(WP_CONF_DYN_E & 0xF000) >> 12]            = *GP_C2;
        *I_MAX_C2_B[(WP_CONF_DYN_E & 0xF000) >> 12]         = *I_MAX_C2;
        *Seuil_mesure_I_C2_B[(WP_CONF_DYN_E & 0xF000) >> 12] = *Seuil_mesure_I_C2;
        *KD_C2_B[(WP_CONF_DYN_E & 0xF000) >> 12]            = *KD_C2;
        *I_MAX_LU_C2_B[(WP_CONF_DYN_E & 0xF000) >> 12]      = *I_MAX_LU_C2;


        *U_MIN_C3_B[(WP_CONF_DYN_E & 0x00F0) >> 4]         = *U_MIN_C3;
        *U_MAX_C3_B[(WP_CONF_DYN_E & 0x00F0) >> 4]         = *U_MAX_C3;
        *GP_C3_B[(WP_CONF_DYN_E & 0x00F0) >> 4]            = *GP_C3;
        *I_MAX_C3_B[(WP_CONF_DYN_E & 0x00F0) >> 4]         = *I_MAX_C3;
        *Seuil_mesure_I_C3_B[(WP_CONF_DYN_E & 0x00F0) >> 4]= *Seuil_mesure_I_C3;
        *KD_C3_B[(WP_CONF_DYN_E & 0x00F0) >> 4]            = *KD_C3;
        *I_MAX_LU_C3_B[(WP_CONF_DYN_E & 0x00F0) >> 4]      = *I_MAX_LU_C3;

        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        //  Detection d'un changement d'ID du G3 : 
        if (*ID_FTH_C3 != *ID_Fth_C3_B[(WP_CONF_DYN_E & 0x00F0)>>4]) {
          *ID_Fth_C3_B[(WP_CONF_DYN_E & 0x00F0)>>4] = *ID_FTH_C3;

          // Récupération des paramètres de facteur thermique en fonction de l'ID
          *Periode_Fth_C3 = *Periode_Fth_N_C3[*ID_FTH_C3]; 
          *I_thermique_C3 =  *I_thermique_N_C3[*ID_FTH_C3] ;

        }else{
           *Periode_Fth_N_C3[*ID_FTH_C3] = *Periode_Fth_C3;
           *I_thermique_N_C3[*ID_FTH_C3] = *I_thermique_C3;
        }

        //  Detection d'un changement d'ID du G2 : 
        if (*ID_FTH_C2 != *ID_Fth_C2_B[(WP_CONF_DYN_E & 0xF000) >> 12]) {
          *ID_Fth_C2_B[(WP_CONF_DYN_E & 0xF000) >> 12] = *ID_FTH_C2;

          // Récupération des paramètres de facteur thermique en fonction de l'ID
          *Periode_Fth_C2 = *Periode_Fth_N_C2[*ID_FTH_C2]; 
          *I_thermique_C2 =  *I_thermique_N_C2[*ID_FTH_C2] ;

        }else{
           *Periode_Fth_N_C2[*ID_FTH_C2] = *Periode_Fth_C2;
           *I_thermique_N_C2[*ID_FTH_C2] = *I_thermique_C2;
        }

        //  Detection d'un changement d'ID du G1 : 
        if (*ID_FTH_C1 != *ID_Fth_C1_B[(WP_CONF_DYN_E & 0x0F00) >> 8]) {
          *ID_Fth_C1_B[(WP_CONF_DYN_E & 0x0F00) >> 8] = *ID_FTH_C1;

          // Récupération des paramètres de facteur thermique en fonction de l'ID
          *Periode_Fth = *Periode_Fth_N_C1[*ID_FTH_C1]; 
          *I_thermique_C1 =  *I_thermique_N_C1[*ID_FTH_C1] ;
        }else{
           *Periode_Fth_N_C1[*ID_FTH_C1] = *Periode_Fth;
           *I_thermique_N_C1[*ID_FTH_C1] = *I_thermique_C1;
        }

        // .......................................................

        /// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // Contrôle modification 
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        #ifdef PRET_A_TESTER   // Validée le 09/10/2025


        // ............................................................................................................
        // Chargement de la config d'étalonnage  : Equivalent de RW_parametres_Etalonnage 3
        // ............................................................................................................
        if((WP_CONF_DYN_E & 0x000F) != (WM_CONF_DYN_L &0x000F)){       

              *Etalonnage_X1     = *Etalonnage_X1_B[(WP_CONF_DYN_E & 0x000F)];
              *Etalonnage_Y1     = *Etalonnage_Y1_B[(WP_CONF_DYN_E & 0x000F)];
              *Etalonnage_X2     = *Etalonnage_X2_B[(WP_CONF_DYN_E & 0x000F)];
              *Etalonnage_Y2     = *Etalonnage_Y2_B[(WP_CONF_DYN_E & 0x000F)];

              ActionChargModif (D_Etalonnage_X1);
              ActionChargModif (D_Etalonnage_X2);
              ActionChargModif (D_Etalonnage_Y1);
              ActionChargModif (D_Etalonnage_Y2);
              ActionChargModif (D_Seuil_Ctrl_Temperature);


              copie_WORD( (WM_CONF_DYN_L & 0xFFF0) | (WP_CONF_DYN_E & 0x000F) , WM() , 6*16);
          
        }

        if (Seuil_Ctrl_temperature[0]!= *Seuil_Ctrl_temperature || Seuil_Ctrl_temperature[1]!= *Seuil_Ctrl_temperature){

              Seuil_Ctrl_temperature[0] = *Seuil_Ctrl_temperature;
              Seuil_Ctrl_temperature[1] = *Seuil_Ctrl_temperature;

              ActionChargModif (D_Etalonnage_X1);
              ActionChargModif (D_Etalonnage_X2);
              ActionChargModif (D_Etalonnage_Y1);
              ActionChargModif (D_Etalonnage_Y2);
              ActionChargModif (D_Seuil_Ctrl_Temperature);

        }
        // ............................................................................................................
        // Sauvegarde de la nouvelle modification via SDT Manager (en fonciton du numéro de conversion choisi )
        // ............................................................................................................
        *Etalonnage_X1_B[(WP_CONF_DYN_E & 0x000F)] = *Etalonnage_X1;
        *Etalonnage_Y1_B[(WP_CONF_DYN_E & 0x000F)] = *Etalonnage_Y1;
        *Etalonnage_X2_B[(WP_CONF_DYN_E & 0x000F)] = *Etalonnage_X2;
        *Etalonnage_Y2_B[(WP_CONF_DYN_E & 0x000F)] = *Etalonnage_Y2;
        // ............................................................................................................

        #endif

        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        

    }
        


            stackWordsLeft = uxTaskGetStackHighWaterMark(NULL);

            taskDataAnalysis[8] = stackWordsLeft;

  
    vTaskDelay(10);  
  }
}


// -----------------------------------------------------------------------------------------------------------------------
// Gestion de l'erreur de COM 
// -----------------------------------------------------------------------------------------------------------------------
inline void Ctrl_COM(){
    
        // ......................................................................................
        // COM_ERR_2
        // @ RT : Nombre de receptions de trame venant du convertiseur (STM32)   ::
        // ......................................................................................
        if (Int_periodique == 1){

          if(RT == 0){
            
            *COM_ERR_2 = 1;
            
            nb_erreur_COM_2[0]= nb_erreur_COM_2[0]+1;

            
          }else if (RT < 10) {   

            globalData[4] = RT;
             *COM_ERR_2 = 1;

             nb_erreur_COM_2[1]= nb_erreur_COM_2[1]+1;
  
             
          }else{

              globalData[0] = RT;  

              *COM_ERR_2 = 0;    

          }


          RT = 0;
        }


        // ......................................................................................
        
}
// -----------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------
// Draft : 
// ----------------------------------------------------
// (WP_CONF_DYN_E & 0x00F0)>>4;   => n° banque G3
// (WP_CONF_DYN_E & 0x0F00)>>8;   => n° banque G1
// (WP_CONF_DYN_E & 0xF000)>>12;  => n° banque G2
// ----------------------------------------------------
