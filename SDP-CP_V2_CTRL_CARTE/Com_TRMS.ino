#include <Arduino.h>
#include <WiFi.h>
#include <ModbusRTU.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <plcLib.h>
#include <gestion_registres.h>
#include <EEPROM.h>
// =====================================================================================
// Inclusion de mes propres libraires 
// =====================================================================================
#include "definition_banque.h"
#include "Banque_EEPROM.h"
#include "Myfunctions.h"
#include "variables_globales.h"
#include <perso.h>
// =====================================================================================

#define PRET_A_TESTER


// ===========================================================================================
// Task 1: Reception des trames venant du convertisseur (via UART)
// ===========================================================================================
void TaskReceptionTRMS(void *param) {
  while (1) {

      stackWordsLeft = uxTaskGetStackHighWaterMark(NULL);
      taskDataAnalysis[5] = stackWordsLeft;


      if (reception == 1){
        reception = 0;

        // .................................................. 
        // Attente de reception si aucune trame disponible sur l'UART
        // ..................................................
        while(!Serial.available()){

                reception = 1;   

           vTaskDelay(1);
        }
        // ..................................................
        // Calcul du CRC
        // ..................................................
       len = Serial.available();  // renvoie le nombre d'octets reçu sur l'UART 

          // Lecture des octets reçu sur l'UART
          Serial.readBytes(frame_rcv, len); 

          // Récupération du CRC
          RX_crc = (frame_rcv[len-1]) <<8 | frame_rcv[len-2] ; // LSB | MSB 

          // Calcul du CRC
          crc = calcCRC(frame_rcv, len-2);

          RT ++;
        // ..................................................
        // Comparaison du CRC 
        // ..................................................
          if (crc == RX_crc){   

             initialisation = 0;                     // Mis à 0 à la première reception correcte

             *CONVER_COM_ERR = 0;      // Erreur calcul CRC de la trame reçu du convertisseur 
              
            // ....................................................................................................
            // Traitement des trames des mesures 
            // ....................................................................................................
            if(frame_rcv[0] == RX_Mesures_ID){   

                Timer105 = millis();

                  uint8_t bit0 = 0, bit1 = 0 , bit2 = 0, bit3 = 0, bit4 = 0; 

                  *TOR_E1 = frame_rcv[3] & 0x01;           // etat_cmd entrée TOR 1 
                  *TOR_E2 = (frame_rcv[3] & 0x02) >> 1;    // etat_cmd entrée TOR 2 
                  *TOR_E3 = (frame_rcv[3] & 0x04) >> 2;    // etat_cmd entrée TOR 3 
                  *TOR_E4 = (frame_rcv[3] & 0x08) >> 3;    // etat_cmd entrée TOR 4 
                   bit4 = (frame_rcv[3] & 0x10) >> 4;    // etat_cmd entrée TOR 5

                  

                  // =========================================================================
                  // Voie 1 
                  // =========================================================================
                  D()[12] = (frame_rcv[4] << 8) | frame_rcv[5];    // Mesure Icrete

                  D()[11] =  (frame_rcv[6] << 8) | frame_rcv[7];  // Mesure Ieff

                  D()[13] = (frame_rcv[8] << 8) | frame_rcv[9];  // Mesure Imoy

                  D()[14]  = (frame_rcv[10] << 8) | frame_rcv[11];  // Mesure Imin

                  D()[15] = (frame_rcv[12] << 8) | frame_rcv[13];  // Mesure Imax
                  // =========================================================================
                  // Voie 2
                  // =========================================================================
                  D()[22] = (frame_rcv[14] << 8) | frame_rcv[15];    // Mesure Ieff

                  D()[21] = (frame_rcv[16] << 8) | frame_rcv[17];  // Mesure Icrete

                  D()[23] = (frame_rcv[18] << 8) | frame_rcv[19];  // Mesure Imoy

                  D()[24] = (frame_rcv[20] << 8) | frame_rcv[21];  // Mesure Imin

                  D()[25] = (frame_rcv[22] << 8) | frame_rcv[23];  // Mesure Imax


                  // =========================================================================
                  // Voie 3 
                  // =========================================================================
                  D()[32] = (frame_rcv[24] << 8) | frame_rcv[25];    // Mesure Icrete

                  D()[31] = (frame_rcv[26] << 8) | frame_rcv[27];  // Mesure Ieff

                  D()[33] = (frame_rcv[28] << 8) | frame_rcv[29];  // Mesure Imoy

                  D()[34] = (frame_rcv[30] << 8) | frame_rcv[31];  // Mesure Imin

                  D()[35] = (frame_rcv[32] << 8) | frame_rcv[33];  // Mesure Imax
                  // =========================================================================
                  // Voie 4
                  // =========================================================================
                  D()[42] = (frame_rcv[34] << 8) | frame_rcv[35];    // Mesure Icrete

                  D()[41] = (frame_rcv[36] << 8) | frame_rcv[37];  // Mesure Ieff

                  D()[43] = (frame_rcv[38] << 8) | frame_rcv[39];  // Mesure Imoy

                  D()[44] = (frame_rcv[40] << 8) | frame_rcv[41];  // Mesure Imin

                  D()[45]= (frame_rcv[42] << 8) | frame_rcv[43];  // Mesure Imax
                  // =========================================================================
                  // Voie 5
                  // =========================================================================
                  *Entree_ana_crete_V5 = (frame_rcv[44] << 8) | frame_rcv[45];    // Mesure Icrete

                  *Entree_ana_efficace_V5 =   (frame_rcv[46] << 8) | frame_rcv[47];  // Mesure Ieff

                  *Entree_ana_moyen_V5 = (frame_rcv[48] << 8) | frame_rcv[49];  // Mesure Imoy

                  *Entree_ana_min_V5 = (frame_rcv[50] << 8) | frame_rcv[51];  // Mesure Imin

                  *Entree_ana_max_V5= (frame_rcv[52] << 8) | frame_rcv[53];  // Mesure Imax
                  // =========================================================================
                  // Voie 6
                  // =========================================================================
                  *Entree_ana_crete_V6 = (frame_rcv[54] << 8) | frame_rcv[55];    // Mesure crete

                  *Entree_ana_efficace_V6 = (frame_rcv[56] << 8) | frame_rcv[57];  // Mesure Ieff

                  *Entree_ana_moyen_V6 = (frame_rcv[58] << 8) | frame_rcv[59];  // Mesure Imoy


                
                  *Entree_ana_min_V6 = (frame_rcv[60] << 8) | frame_rcv[61];  // Mesure Imin

                  *Entree_ana_max_V6 = (frame_rcv[62] << 8) | frame_rcv[63];  // Mesure Imax  

                
                  // =========================================================================
                  // Horodatage 
                  // =========================================================================
                  jour = frame_rcv[64];
                  mois = frame_rcv[65];
                  annee = frame_rcv[66];

                  *C_Hours = frame_rcv[67];
                  *C_Minutes = frame_rcv[68];
                  *C_Secondes = frame_rcv[69];

                  // !!!!!!!!!!!!!!Vérification date correcte  !!!!!!!!!!!!!!!!!!!!!!!!!!
                  // Horodatage par défaut si pile défaillante 
                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                  if (jour == 1 && mois == 1 && annee == 0){
                     // *C_Debug_Val_1 = 404;   // Ressources demandée introuvable : erreur 404 
                  }else{
                     //  *C_Debug_Val_1 = 200;   // Succès de la requête 
                  }
                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                  // =========================================================================
                  // Entrées active : entête de réception 
                  // -------------------------------------------------------------------------


                  *ENTREE_ACTIVE_1 = 1;
                  *ENTREE_ACTIVE_2 = 1;
                  *ENTREE_ACTIVE_3 = 1;
                  *ENTREE_ACTIVE_4 = 1;
                  // =========================================================================
                        
    
                  // .............................................................................................
                  // S'assurer que la lreception com de l'ESP32 est stabilisée
                  // .............................................................................................

                  if (RX_ESP32_nb_trames_correct < 100){    // Reception de 100 trames corrects (résulat empirique)

                        emission = 1;

                  }else{

                       balayage  = 1;      // lancement de la tâche de balayage

                  }
                  // .............................................................................................
                  
                  
                  vTaskDelay(1);  

            }
            
            // ....................................................................................................
            // Traitement des trames d'acknwoledge des commandes
            // ....................................................................................................
            if(frame_rcv[0] == Commandes_ID){

              // -----------------------------------------------------------
              // Erreur en cours de test
              // -----------------------------------------------------------

               if (frame_rcv[2] == 0x00){

                *CFILLE_COM_ERR = 0;     
                

                // ...................................
                // Nombre de retours positif commandes
                // ...................................
                
                if ( RX_ESP32_nb_trames_correct < 65530){
                  RX_ESP32_nb_trames_correct  = RX_ESP32_nb_trames_correct + 1;
                }
                // ...................................

               }else{

                 *CFILLE_COM_ERR = 1;   // Mis à le convertisseur n'a pas compris la trame envoyée par l'ESP32
               }


              reception = 1;

              vTaskDelay(1); 
          } 

            // ....................................................................................................
            if(frame_rcv[0] == Config_ID){    // Exécuté si reception Aknwoledge reception commandes 
            
              reception = 1;

              vTaskDelay(1);   
            }
            // ....................................................................................................
            if(frame_rcv[0] == RX_Horodatage_ID){    // Exécuté si reception Aknwoledge reception commandes 
            
              reception = 1;

              vTaskDelay(1);   
            }
            // ....................................................................................................

      } // Fin if CRC correct
      else{
          
          *CONVER_COM_ERR = 1;      // Erreur calcul CRC de la trame reçu du convertisseur 

          reception = 1;

          vTaskDelay(1);
      }
           
    } // Fin if reception
    vTaskDelay(1); // Small delay to prevent busy-waiting  // 20 ms
  } // Fin While(1)
}



// ===========================================================================================
// Task 2: Envoi de la trame venant du convertisseur 
// ===========================================================================================
void TaskEmissionTRMS(void *param) {
  while (1) {

    stackWordsLeft = uxTaskGetStackHighWaterMark(NULL);
    taskDataAnalysis[7] = stackWordsLeft;


    if (emission) {
      emission = 0;

      // .........................................................................................................................
      // @brief : Tant qu'on a pas reçu un certain nombre de feedback positif par rapport aux commandes qu'on envoie, 
      // on ne passe pas encore au balayage ladder, on continue d'envoyer des commandes
      // .........................................................................................................................
      if (RX_ESP32_nb_trames_correct < 100){
          TX_ID = Commandes_ID;
      }
      // .........................................................................................................................     
                
                // ===============================================================================================================
                // Envoi valeurs Sorties analogique / Sortie TOR  
                // ===============================================================================================================
                 if (TX_ID == Commandes_ID){


                        uint8_t resultat = 0;

                        // Positionner chaque booléen dans le bon bit
                        resultat |= (*TOR_S1 << 0); // Bit 0
                        resultat |= (*TOR_S2 << 1); // Bit 1
                        resultat |= (*TOR_S3 << 2); // Bit 2
                        resultat |= (*TOR_S4 << 3); // Bit 3



                          frame_snd[0]= Commandes_ID;  
                          frame_snd[1]= 0x0A;
                          frame_snd[2]= 0x00;  // Memo Offset Dynamique    [A commander via le GUI]
                          frame_snd[3]= resultat ;   
                          frame_snd[4]= (*Sortie_analogique_V1>>8)& 0xFF ; // Sortie aJnalogique 1 [MSB]
                          frame_snd[5]= *Sortie_analogique_V1 & 0xFF;      // Sortie analogique 1 [LSB]    
                          frame_snd[6]= (*Sortie_analogique_V2>>8)& 0xFF ; // Sortie analogique 2 [MSB] 
                          frame_snd[7]= *Sortie_analogique_V2 & 0xFF;      // Sortie analogique 2 [LSB] 
                          frame_snd[8]= (*Sortie_analogique_V3>>8)& 0xFF ; // Sortie analogique 3 [MSB]     
                          frame_snd[9]= *Sortie_analogique_V3 & 0xFF;      // Sortie analogique 3 [LSB] 
                          frame_snd[10]= (*Sortie_analogique_V4>>8)& 0xFF ; // Sortie analogique 4 [MSB]
                          frame_snd[11]= *Sortie_analogique_V4 & 0xFF;      // Sortie analogique 4 [LSB] 

                          crc = calcCRC(frame_snd,12);
                           
                          frame_snd[12] = crc & 0xFF;         // LSB
                          frame_snd[13] = (crc>>8)& 0xFF;     // MSB 

                          Serial.write(frame_snd, 14);

                 }
                // ===============================================================================================================
                // Envoi valeurs de configuration RTC 
                // ===============================================================================================================
                 else if (TX_ID == Horodotage_ID){

                          // Le traitement de la trame frame_snd se trouve dans balayage.ino

                          Serial.write(frame_snd, 10);
                          etat_cmd = ' ';  

                 }else if (TX_ID == Commandes_unitaire_ID){   // Commande unitaire des sorties ana et TOR  // Ne sert pas vraiment à grand chose, vu que les sorties sont réinitialisé à chaque début de cycle. 
                           // Le traitement de la trame frame_snd se trouve dans balayage.ino
                          Serial.write(frame_snd, 14);
                          etat_cmd = ' ';  

                }else if (TX_ID == Config_ID || TX_ID == Commande_Offset_ID){   // Config

                          // Le traitement de la trame frame_snd se trouve dans balayage.ino
                          Serial.write(frame_snd, 66);
                          etat_cmd = ' ';  

                }
                 // ===============================================================================================================
    
    reception = 1;
    } // fin appel emission 

    vTaskDelay(1); // Small delay to prevent busy-waiting 
  }
}