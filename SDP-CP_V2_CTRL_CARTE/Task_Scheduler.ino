// #define ENABLE_NORMAL_MODE
#define ENABLE_DEBUG_MODE
// .....................................................................
// Scheduler 
// .....................................................................
void app_scheduler(void *param) {

*wifi_cmd = 1;              // Activation du Wifi au démarrage (en mode debug)

// Améliorations : A organiser sous forme de machine à états
while(1){


    #ifdef ENABLE_NORMAL_MODE
    // .....................................................................
    // Récupération des paramètres, après que la COM STM32-ESP32 initialisé
    // .....................................................................
    if (RX_ESP32_nb_trames_correct > 50 &&  TaskSDcardHandler == NULL && TaskBASICHandler == NULL){   // Vérifier que la tâche n'as pas encore été lancée avant de le créer

     // Condition de lancement de lecture carte SD => receptions données horodatage pour calcul de facteur thermique 
      xTaskCreatePinnedToCore(
        TaskSDcard,          // Function to implement the task
        "Task SDcard",       // Name of the task
        5000,          // Stack size in words
        NULL,           // Task input parameter
        3,              // Priority of the task
        &TaskSDcardHandler,  // Task handle.
        1);             // Core where the task should run

      // Condition de lancement de la gestion BASIC => lecture de la carte SD lancée et données récupérées =>
       xTaskCreatePinnedToCore(
      gestion_BASIC, /* Function to implement the task */
      "Task BASIC", /* Name of the task */
      2048,  /* Stack size in words */
      NULL,  /* Task input parameter */
      2,  /* Priority of the task */
      &TaskBASICHandler,  /* Task handle. */
      1); /* Core where the task should run */  


    }
    // .....................................................................
    // Lancement de la tâche Modbus une fois que tout a été initialisé 
    // .....................................................................
    #ifdef ENABLE_XPORT
    if (/*/**INITIALISE == 1 && */TaskModbusHandler == NULL ){
              xTaskCreatePinnedToCore(
            TaskModbus,          // Function to implement the task
            "Task Modbus",       // Name of the task
            5000,          // Stack size in words
            NULL,           // Task input parameter
            4,              // Priority of the task
            &TaskModbusHandler,  // Task handle.
            1);             // Core where the task should run
    }
    #endif 
    // .....................................................................
    // Conditions de déclenchement des tâches du WiFi ---
    // .....................................................................


        // Strap d'activation du WiFi 
        bool strap ;
        strap = digitalRead(34);

        if(ESP32_boot_falling.process(strap)){     // Detection front descendant 
          *wifi_cmd = 1;
        }




      if (*wifi_cmd == 1 && TaskWifiHandler == NULL){
        xTaskCreatePinnedToCore(
            TaskComWifi, /* Function to implement the task */
            "Task Wifi", /* Name of the task */
            5000,  /* Stack size in words */
            NULL,  /* Task input parameter */
            3,  /* Priority of the task */
            &TaskWifiHandler,  /* Task handle. */
            1); /* Core where the task should run */ 

            *wifi_cmd = 0; 

      }else if (*wifi_cmd == 2)  {
            xTaskCreatePinnedToCore(
            TaskOTA, /* Function to implement the task */
            "Task OTA", /* Name of the task */
            4096,  /* Stack size in words */
            NULL,  /* Task input parameter */
            3,  /* Priority of the task */
            &TaskOTAHandler,  /* Task handle. */
            1); /* Core where the task should run */ 

            *wifi_cmd = 0; 

      }
      else if (*wifi_cmd == 3){

        WiFi.softAPdisconnect(true); // Déconnecte tous les clients et arrête l’AP
        WiFi.mode(WIFI_OFF);         // Coupe complètement le WiFi (si pas utilisé ailleurs)

        vTaskDelete(TaskWifiHandler);

        *wifi_cmd = 0;

      }
    // .....................................................................
    // Lancé uniquement si utilisation d'un GT 
    // .....................................................................
    if (type_machine == 1){   // Si 1 : CH4X ; si 0 : GT 
        xTaskCreatePinnedToCore(
        TaskComEcran,          // Function to implement the task
        "Task Com Ecran",       // Name of the task
        2048,          // Stack size in words
        NULL,           // Task input parameter
        2,              // Priority of the task
        &TaskComEcranHandler,  // Task handle.
        1);             // Core where the task should run 
    }
    // .....................................................................
    #endif

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    #ifdef ENABLE_DEBUG_MODE

    if (TaskWifiHandler == NULL){
        xTaskCreatePinnedToCore(
            TaskComWifi, /* Function to implement the task */
            "Task Wifi", /* Name of the task */
            5000,  /* Stack size in words */
            NULL,  /* Task input parameter */
            3,  /* Priority of the task */
            &TaskWifiHandler,  /* Task handle. */
            1); /* Core where the task should run */ 
    }

    if (TaskSDcardHandler == NULL){
          // Condition de lancement de lecture carte SD => receptions données horodatage pour calcul de facteur thermique 
      xTaskCreatePinnedToCore(
        TaskSDcard,          // Function to implement the task
        "Task SDcard",       // Name of the task
        5000,          // Stack size in words
        NULL,           // Task input parameter
        3,              // Priority of the task
        &TaskSDcardHandler,  // Task handle.
        1);             // Core where the task should run
    }

    if (TaskModbusHandler == NULL ){
              xTaskCreatePinnedToCore(
            TaskModbus,          // Function to implement the task
            "Task Modbus",       // Name of the task
            5000,          // Stack size in words
            NULL,           // Task input parameter
            4,              // Priority of the task
            &TaskModbusHandler,  // Task handle.
            1);             // Core where the task should run
    }



    #endif
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  

      stackWordsLeft = uxTaskGetStackHighWaterMark(NULL);

      taskDataAnalysis[4] = stackWordsLeft;

      vTaskDelay(1000);
    }
}