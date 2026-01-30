// ===========================================================================================================
// Tâche : Gestion Lecture et Ecriture carte SD
// ===========================================================================================================
void TaskSDcard(void * param){
  // -----------------------------------------------------------------------------------------------------------------
  // Gestion carte SD (bus SPI)
  // -----------------------------------------------------------------------------------------------------------------



  while(1){

      digitalWrite(CS1_PIN, HIGH); // Désélectionner l'écran               ==> Led rouge éteinte
      digitalWrite(CS3_PIN, HIGH); // Désélectionner l'extendeur de bus

      *ETAT_TASK_SD = !*ETAT_TASK_SD;

      // ........................................................................
      // Machine à états 
      // ........................................................................
      switch (sdState) {

          case SD_INIT:

              if(*INIT_SD == 1){
                  *COM_SD_ERR = 0;
                  sdState = SD_READ_JSON; // Transition vers lecture JSON
              }else{
                  *COM_SD_ERR = 1;
                  sdState = SD_ERROR; // Transition vers lecture JSON
              }
              break;

          case SD_ERROR:

              // ....................................................................................
              // Traitement de l'erreur lié à l'absence de fichier de paramétrage
              // ....................................................................................
              if (*INIT_SD){  
                  

                // -  Attente condition de reception de tous les données via le Wifi 
                if (modif_banque_wifi_en_cours == 2 ){

                    recupConfigJson("wifi");

                    if (*WRITE_CONFIG == 1){

                      *COM_SD_ERR  = 0;
                      sdState =  SD_CONFIG_OK;

                      modif_banque_wifi_en_cours = 0;

                    }

                }


              }
              // ....................................................................................
              // Traitement de l'erreur lié à l'absence de fichier de paramétrage
              // ....................................................................................
              else {        

                  *COM_SD_ERR  = 1;
                  *INIT_SD = 0 ;  
              }
              break;

          case SD_READ_JSON:

              recupConfigJson("init");

              if (!*READ_SD && !*EXTRACT_CONFIG) {
                  
                  *COM_SD_ERR = 1;

                  sdState = SD_ERROR;

              } else if (*READ_SD && !*EXTRACT_CONFIG) {
                  *COM_SD_ERR = 1;

                  sdState = SD_ERROR;

              } else if (*READ_SD && *EXTRACT_CONFIG) {

                  *COM_SD_ERR = 0;
                  recupConfigDemarrage = 1;
                  sdState = SD_CONFIG_OK; // Transition vers état final

                  recupCalculFth();
                  traitement_FTh();

              }

              break;

          case SD_CONFIG_OK:
              // Paramètres disponibles, fonctionnement normal
              *COM_SD_ERR = 0;

              // Actions <
                  recupConfigJson("loop");


                  if (!*READ_SD || !*EXTRACT_CONFIG){
                        
                        sdState = SD_ERROR;

                        if (!*READ_SD){
                           *COM_SD_ERR = 1;
                        }
                        
                  }

                // Permet de valider que la modif par wifi des données de la carte SD est OK
                  if (modif_banque_wifi_en_cours == 2){
                    modif_banque_wifi_en_cours = 0;
                  }

              break;

          case SD_CONFIG_WIFI:
          
              recupConfigJson("wifi");

              modif_banque_wifi_en_cours = 0;
              sdState = SD_CONFIG_OK;
              *COM_SD_ERR = 0;

            break;

          }
      // ........................................................................


       
        
            
    // ...................................................................
    // Calcul du stack disponible
    // ...................................................................
            stackWordsLeft = uxTaskGetStackHighWaterMark(NULL);
            taskDataAnalysis[1] = stackWordsLeft;
    // ...................................................................

     digitalWrite(CS1_PIN, LOW); // Désélectionner l'écran                           ==> Led rouge allumé
     digitalWrite(CS3_PIN, HIGH); // Désélectionner l'extendeur de bus

    

    vTaskDelay(2000);

  }

} // TaskSDcard

