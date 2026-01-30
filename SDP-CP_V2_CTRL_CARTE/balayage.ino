#include <ModbusRTU.h>
#include <plcLib.h>

#include <gestion_registres.h>
#include <HardwareSerial.h>
#include <SD.h>

#include <Adafruit_GFX.h>    // Bibliothèque de base pour Adafruit GFX
#include <Adafruit_ST7789.h> // Bibliothèque pour l'écran ST7789


#include "definition_banque.h"
#include "variables_globales.h"

extern WiFiServer server;


extern File myFile;

extern Adafruit_ST7789 tft;



bool etape2 = 0; 

bool offset_demarrage = 1;


#define TEST_SD_CARD
#define PRET_A_TESTER
#define VALIDEE



// ===============================================================================================
// Prototype fonctions 
// ===============================================================================================
inline void offset_dynamique_md();
uint8_t assemble_lsb(uint8_t b1,uint8_t b2,uint8_t b3,uint8_t b4,uint8_t b5,uint8_t b6);


// ===============================================================================================
inline void SATcycle(void);


R_Trig acqt_def;
R_Trig rising_BO_BF;
F_Trig falling_BO_BF;
R_Trig rising_SAT_CYCLE_1;
F_Trig falling_SAT_CYCLE_1; // DEBUG 
R_Trig rising_SAT_CYCLE_2;
R_Trig rising_ACY;


/**
 * @brief Tâche qui gère le fonctionnement des différents cycles de la machine
 *
 * Cette tâche traite les valaeurs des mesures, les valeurs des entrées TOR et met à jour les sorties analogiques et les sorties TOR
 *
 * @param pvParameters Pointeur générique vers les paramètres (ex: handle de la file).
 * @return Aucun 
 *
 * @note Cette tâche est lancée après réception des mesures venant du convertisseur (STM32)
 * @warning Ne pas bloquer plus de 500 ms, sinon la réactivité du système sera réduite.
 * @see vTaskDelay(), xQueueSend()
 */

void TaskComGUI(void *param) {
  while (1) {

    stackWordsLeft = uxTaskGetStackHighWaterMark(NULL);
    taskDataAnalysis[6] = stackWordsLeft;

        if (balayage) {
          balayage  = 0;  // Reset the emission flag after sending the message

          

         
              //Ecretage sortie analogiques 1,2,3,4 (10000pts)
          if (*Sortie_analogique_V1 > 10000){ *Sortie_analogique_V1 = 10000; }
          if (*Sortie_analogique_V2 > 10000){ *Sortie_analogique_V2 = 10000; }
          if (*Sortie_analogique_V3 > 10000){ *Sortie_analogique_V3 = 10000; }


          // ...............................................................................................................
          // Gestion du calcul de l'offset     
          // ...............................................................................................................
          if (offset_demarrage == 0 /*&& tOnperso(&TimerOffsetDyn,1000)*/){  // offset_demarrage mis à 1 après récupération des données dans la carte SD
              *offset_dyn_cmd = 1;
          }
          // ..............
          if (*offset_dyn_cmd == 1 /*|| offset_demarrage == 0*/){          // 3ème condition : S'assure que 
              
            offset_dynamique_md();

             offset_dynamique_faite = 0;   // Flag indiquant si l'offset dynamique a été faite

             *offset_dyn_cmd = 2;          // Flag permettant de valider que la remise à 0 a bien été effectué, et permet le passage à l'étape suivante (Recalcul de l'offset dynamique)

             offset_demarrage = 1;         // Flag Utilisée pour le lancement de l'offset au démarrage

             TimerOffsetDyn = 0;

          }else if(*offset_dyn_cmd == 2  && !offset_dynamique_faite){     // Commande de recalcul de l'offset dynamique
             
              offset_dynamique_faite = 1;

              *INITIALISE  = 1;

          }
          // ...............................................................................................................
          // Gestion de l'horodatage    
          // ...............................................................................................................
      
          if (*horodotage_cmd == 1 ){

           frame_snd[0]= Horodotage_ID;     // config  ID
           frame_snd[1]= 0x06;     // Nb d'octets de données  
           frame_snd[2]= WR_jour;    // jour (25)
           frame_snd[3]= WR_mois;    // mois 
           frame_snd[4]= WR_annee;   //  annee 

           frame_snd[5]= WR_heure;     //    heure
           frame_snd[6]= WR_min;     //    min
           frame_snd[7]= WR_sec;    //    secondes

            // Calcul du CRC
            crc = calcCRC(frame_snd,8);
            // Affectation du CRC
            
            frame_snd[8] = crc & 0xFF;         // LSB
            frame_snd[9] = (crc>>8)& 0xFF;     // MSB 

              *horodotage_cmd = 0;
              etat_cmd = 'J';
          }
          // ...............................................................................................................


            

          //=====================================================================================================================
          // Choix du type de trame à envoyer 
          //=====================================================================================================================
          if (etat_cmd == 'J') {    // Config horodotage
            TX_ID = Horodotage_ID;
          }else if (etat_cmd == 'A'){                      // Commandes Une à une des sorties analogiques
              TX_ID = Commandes_unitaire_ID;

          }else if (etat_cmd == 'C'){    // Configuration gain et Offset
              TX_ID = Config_ID;

          }else if (etat_cmd == 'O'){    // Configuration gain et Offset
              TX_ID = Commande_Offset_ID;
          }
          else{                      // Commandes Boucles 
              TX_ID = Commandes_ID;
          }
          //=================================================================================================   

           emission = 1 ;       
          } // fin balayage

        vTaskDelay(1); // Small delay before checking again
      }
}


/**********************************************************************************************************************************
 * @brief Calcul d'offset des voies de mesures
 *
 * Permet la préparation de la trame à envoyer au convertisseur (STM32)
 *
 * @note Fonction utilisée actuellement
 *********************************************************************************************************************************/
inline void offset_dynamique_md(){
          etat_cmd = 'C'; 

            
                                  frame_snd[0]= 0x10;     // config 
                                  frame_snd[1]= 0x3E;     // Nb d'octets de données 

                                  frame_snd[2]= 1;    // 50 Hz 

                                  frame_snd[3]= 0x00;    // Asynchrone (20ms + 6 ms) [bit = 0]   / Synchrone (20ms) [bit = 1] 

                                  frame_snd[4]= 0x03;    // duréeMesureOffsetDynamique (périodes)     
                                  
                                  
                                  frame_snd[5]=  assemble_lsb(*OFFSET_DYN_V1,*OFFSET_DYN_V2,*OFFSET_DYN_V3,*OFFSET_DYN_V4,*OFFSET_DYN_V5,*OFFSET_DYN_V6); // 0x3F; // Activation Offset  ;   //  Activation offset dynamique
                                  
                                  // 0x0001 => 100 ms
                                  frame_snd[6]= 0x00;     //    tempsAvantActivationOffset dynamique   
                                  frame_snd[7]= 0x01;     //    tempsAvantActivationOffset dynamique  

                                  

                                  frame_snd[8]= assemble_lsb(*OFFSET_DYN_V1,*OFFSET_DYN_V2,*OFFSET_DYN_V3,*OFFSET_DYN_V4,*OFFSET_DYN_V5,*OFFSET_DYN_V6);  // 0x3F; // Memo Offset Dynamique

                                  frame_snd[9] = 0x02;     // Config Seuil Raz Moyenne   (%)

                                  // ==================================================================
                                  // Voie 1           
                                  // ===================================================================          
                                  uint8_t gain_hex[4]={0};     // Tableau pour stocker les octets
                                  uint8_t offset_hex[4]={0};     // Tableau pour stocker les octets

                                  // uint16_t* GAIN_V1 = &T()[110];                                   // D:20590
                                  // uint16_t* OFFSET_LSB_V1 = &T()[111];                             // D:20591
                                  // uint16_t* OFFSET_MSB_V1 = &T()[112];                             // D:20592  

                                  frame_snd[10] = 0X0A;      // Nombre de points pour le moyennage

                                  // *GAIN_V1 = 2000;
                                  float_to_hex_array((float)*GAIN_V1, gain_hex);

                                  frame_snd[11] = gain_hex[0];     // Gain 
                                  frame_snd[12] = gain_hex[1];     // Gain
                                  frame_snd[13] = gain_hex[2];     // Gain
                                  frame_snd[14] = gain_hex[3];      // Gain

                                 float_to_hex_array(2.5, offset_hex);

                                  frame_snd[15] = offset_hex[0];      // offset 
                                  frame_snd[16] = offset_hex[1];     // offset
                                  frame_snd[17] = offset_hex[2];     // Gain
                                  frame_snd[18] = offset_hex[3];    // Gain
                                  // ==================================================================
                                  // Voie 2 
                                  // ==================================================================
                                  frame_snd[19] = 0X0A;      // Nombre de points Moyen (10 en decimal)

                                  // *GAIN_V2 = 10000;
                                  float_to_hex_array((float)*GAIN_V2, gain_hex);

                                  frame_snd[20] = gain_hex[0];     // Gain 
                                  frame_snd[21] = gain_hex[1];     // Gain
                                  frame_snd[22] = gain_hex[2];     // Gain
                                  frame_snd[23] = gain_hex[3];     // Gain

                                  float_to_hex_array(2.5, offset_hex);

                                  frame_snd[24] = offset_hex[0];     // offset 
                                  frame_snd[25] = offset_hex[1];     // offset
                                  frame_snd[26] = offset_hex[2];     // Gain
                                  frame_snd[27] = offset_hex[3];     // Gain
                                  // ==================================================================
                                  // Voie 3 
                                  // ==================================================================

                                  frame_snd[28] = 0X0A;      // Nombre de points Moyen 

                                  //*GAIN_V3 = 16000;
                                  float_to_hex_array((float)*GAIN_V3, gain_hex);

                                  frame_snd[29] = gain_hex[0];     // Gain 
                                  frame_snd[30] = gain_hex[1];     // Gain
                                  frame_snd[31] = gain_hex[2];     // Gain
                                  frame_snd[32] = gain_hex[3];     // Gain

                                  float_to_hex_array(2.5, offset_hex);
                                  
                                  frame_snd[33] = offset_hex[0];     // offset 
                                  frame_snd[34] = offset_hex[1];     // offset
                                  frame_snd[35] = offset_hex[2];     // Gain
                                  frame_snd[36] = offset_hex[3];     // Gain
                                  // ==================================================================
                                  // Voie 4 
                                  // ==================================================================

                                  frame_snd[37] = 0X0A;      // Nombre de points Moyen 

                                  // *GAIN_V4 = 32000;
                                  float_to_hex_array((float)*GAIN_V4, gain_hex);

                                  frame_snd[38] = gain_hex[0];     // Gain 
                                  frame_snd[39] = gain_hex[1];    // Gain
                                  frame_snd[40] = gain_hex[2];     // Gain
                                  frame_snd[41] = gain_hex[3];     // Gain

                                  float_to_hex_array(2.5, offset_hex);
                                  
                                  frame_snd[42] = offset_hex[0];     // offset 
                                  frame_snd[43] = offset_hex[1];     // offset
                                  frame_snd[44] = offset_hex[2];    // Gain
                                  frame_snd[45] = offset_hex[3];     // Gain
                                  // ==================================================================
                                  // Voie 5
                                  // ==================================================================
                                  frame_snd[46] = 0X0A;      // Nombre de points Moyen 

                                  // *GAIN_V5 = 2000;
                                  float_to_hex_array((float)*GAIN_V5, gain_hex);

                                  frame_snd[47] = gain_hex[0];     // Gain 
                                  frame_snd[48] = gain_hex[1];     // Gain
                                  frame_snd[49] = gain_hex[2];     // Gain
                                  frame_snd[50] = gain_hex[3];     // Gain


                                  frame_snd[51] = (*OFFSET_MSB_V5>>8) & 0xFF;     // offset   MSB of the MSB
                                  frame_snd[52] = (*OFFSET_MSB_V5)&0xFF;          // offset   LSB of the MSB

                                  frame_snd[53] = (*OFFSET_LSB_V5>>8) & 0xFF;     // offset   MSB of the LSB
                                  frame_snd[54] = (*OFFSET_LSB_V5)&0xFF;          // offset   LSB of the LSB

           
                                  // ==================================================================
                                  // Voie 6 
                                  // ==================================================================
                                  frame_snd[55] = 0X0A;      // Nombre de points Moyen

                                  // *GAIN_V6 = 10000;
                                  float_to_hex_array((float)*GAIN_V6, gain_hex);

                                  frame_snd[56] = gain_hex[0];     // Gain 
                                  frame_snd[57] = gain_hex[1];     // Gain
                                  frame_snd[58] = gain_hex[2];     // Gain
                                  frame_snd[59] = gain_hex[3];     // Gain

                                 
                                    frame_snd[60] = (*OFFSET_MSB_V6>>8) & 0xFF;     // offset 
                                    frame_snd[61] = (*OFFSET_MSB_V6) & 0xFF;     // offset

                                    frame_snd[62] = (*OFFSET_LSB_V6>>8) & 0xFF;     // Gain
                                    frame_snd[63] = (*OFFSET_LSB_V6)&0xFF;     // Gain
                                 
                                  // ==================================================================
                                  crc = calcCRC(frame_snd,64);
                                  
                                  frame_snd[64] = crc & 0xFF;         // LSB
                                  frame_snd[65] = (crc>>8)& 0xFF;     // MSB 
  
}

uint8_t assemble_lsb(uint8_t b1,uint8_t b2,uint8_t b3,uint8_t b4,uint8_t b5,uint8_t b6) {
    b1 = b1 & 1u;
    b2 = b2 & 1u;
    b3 = b3 & 1u;
    b4 = b4 & 1u;
    b5 = b5 & 1u;
    b6 = b6 & 1u;

    uint8_t value = (b1 << 0) | (b2 << 1) | (b3 << 2)
                  | (b4 << 3) | (b5 << 4) | (b6 << 5);

    return value; // 0..63
}