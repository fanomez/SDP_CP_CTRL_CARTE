
// ============================================================
// Task  : COM WIFI
// ============================================================
void TaskComWifi(void *param) {
  // ===========================================
  // MQTT Test
  // ===========================================

  while(1){
        // ----------------------------------------------------------------------------------  
        // Accepter un client TCP
        // ----------------------------------------------------------------------------------  
        if (!clientMQTT || !clientMQTT.connected()) {
          clientMQTT = mqttBroker.available();          // Devient true quand le logiciel ouvre un socket
          if (clientMQTT) {
            // Serial.println("Client MQTT connecté !");
          }
        }
        // ----------------------------------------------------------------------------------  
        // Gestion du client TCP
        // ----------------------------------------------------------------------------------  
        if (clientMQTT && clientMQTT.connected()) {

        // ---------------------------------------------------------------------------------- 
        // Traitement des commandes venant du logiciel
        // ---------------------------------------------------------------------------------- 
        while (clientMQTT.available()) {
              String cmd = clientMQTT.readStringUntil('\n');
              cmd.trim();

              if (cmd.length() > 0) {

                  doc.clear();
                  DeserializationError error = deserializeJson(doc, cmd);
  	              // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  // Commandes sorties 
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  if (doc.containsKey("ANA")) {
                      registerCommandesRoutes(cmd);
                  }
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  // Commandes requêtes lecture carte SD
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  if (doc.containsKey("request_SD")) {
                      JsonObject req = doc["request_SD"];
                      String gen = req["gen"] | "";
                      String banque = req["banque"] | "";
                      registerReadSDRoutes(gen , banque);
                  }
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  // Commandes requêtes facteur thermique
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  if (doc.containsKey("fth_reinit")) {
                      registerFthRoutes();
                  }
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  // Etat defaut carte SD
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  if (doc.containsKey("defaut_SD")) {
                      registerDefautSD();
                  }
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  // Configuration de la chaine de mesure
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  if (doc.containsKey("request_config_mes")) {
                      registerChaineMesure();
                  }                                     
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  // Configuration de la chaine de mesure
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  if (doc.containsKey("request_dataFth")) {
                      registerDataFth();
                  }
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  // Request Task analysis
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~           
                  if (doc.containsKey("request_taskAnalysis")) {
                      registerTaskAnalysisRoutes();
                  }                                                        
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  // Commandes requêtes écriture carte SD
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  if (doc.containsKey("general") || doc.containsKey("generateur1") || doc.containsKey("generateur2") || doc.containsKey("generateur3") || doc.containsKey("dataFth") ||doc.containsKey("configMesures")) {
                        registerWriteSDRoutes();
                  }                 
                 // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  // Configuration de la chaine de mesure
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  if (doc.containsKey("configMesures")) {
                      registerUpdateChaineRoutes();
                  }  
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  // Configuration de l'Horodatage
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                  
                  if (doc.containsKey("Jour")) {
                      registerHorodatageRoutes();
                  }  
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  // Récupération des valeurs de debug
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  if (doc.containsKey("request_debug_val")) {
                      registerDegugRoutes();
                  }                                     
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  // Info sur la version
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  if (doc.containsKey("request_version")) {
                      registerRootRoutes();
                  }                                     
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  // Configuration XPORT
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  if (doc.containsKey("request_config_XPORT")) {
                      registerConfigXportRoutes();
                  }                                     
                  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   

              }
        }      
        // ----------------------------------------------------------------------------------  
        // Construction des JSON de mesures
        // ----------------------------------------------------------------------------------
          if (*horodotage_cmd != 1){
              registerMesuresRoutes();
          }

            stackWordsLeft = uxTaskGetStackHighWaterMark(NULL);

            taskDataAnalysis[2] = stackWordsLeft;
          

        }
        vTaskDelay(1000);
  }
  // ===========================================

  // --------------------------------------------------------------
     /* while (1) {

    
      server_SDP.handleClient();

      //  ulTaskNotifyTake(pdTRUE, portMAX_DELAY);


         // =========================
         TickType_t now = xTaskGetTickCount();

         if (*C_Config_XPORT == 1){
            switch (etat) {
          case WAIT_TRIGGER:
              
              digitalWrite(ETH_RST, LOW);
              startTime = now;
              chrono = now;
              etat = WAIT_LOW;

              *C_Etat_Config_XPORT = 1;     // Utilisé pour identifier à quel étape de la configuration on est

            break;

          case WAIT_LOW:
            if ((now - chrono) >= pdMS_TO_TICKS(1000)) {
              digitalWrite(ETH_RST, HIGH);
              etat = ENTRER_MODE_SETUP;
            }
              *C_Etat_Config_XPORT = 2;
            break;

          case ENTRER_MODE_SETUP:
            len = ModBus_Uart.available();

            *C_Etat_Config_XPORT = 3;

            result = (char)ModBus_Uart.read() ;
              if (result!= 'M') {
                ModBus_Uart.print("x");
                // vTaskDelay(pdMS_TO_TICKS(10));  //  Attente non bloquante de 10 ms
                chrono = now;
                
              } else {
                
                SEND_ENTER_XPORT();


                etat = CONFIG_IP_0;
                chrono = now;

                *C_Etat_Config_XPORT = 4;   // Avancement dans les étapes 

              }

            break;

          case CONFIG_IP_0:
              if ((now - chrono) >= pdMS_TO_TICKS(10)) {

                int k = 0;

                ModBus_Uart.print("1");

                      chrono = now;
                      etat = CONFIG_IP_1;
                      

                      *C_Etat_Config_XPORT = 5;
                          

              }
              break;

          case CONFIG_IP_1:
            if ((now - chrono) >= pdMS_TO_TICKS(1000)) {
              // Serial.println("[CONFIG_IP_1] IP : 192");
              ModBus_Uart.print(part0);
              
              etat = CONFIG_IP_2;
              chrono = now;
              *C_Etat_Config_XPORT = 6;

            }
            break;

          case CONFIG_IP_2:
            if ((now - chrono) >= pdMS_TO_TICKS(1000)) {
              SEND_ENTER_XPORT(); // Validation précédent changement

            //  Serial.println("[CONFIG_IP_2] IP : 168");
              ModBus_Uart.print(part1);

              etat = CONFIG_IP_3;
              chrono = now;
              *C_Etat_Config_XPORT = 7;
            }
            break;

          case CONFIG_IP_3:
            if ((now - chrono) >= pdMS_TO_TICKS(1000)) {
              SEND_ENTER_XPORT(); // Validation précédent changement
              
              // Serial.println("[CONFIG_IP_3] IP : 0");
              ModBus_Uart.print(part2);

              chrono = now;
              etat = CONFIG_IP_4;
              *C_Etat_Config_XPORT = 8;
            }
            break;

          case CONFIG_IP_4:
            if ((now - chrono) >= pdMS_TO_TICKS(1000)) {
              SEND_ENTER_XPORT(); // Validation précédent changement
              
              // Serial.println("[CONFIG_IP_4] IP : 20");
              ModBus_Uart.print(part3);

              chrono = now;
              etat = GATEWAY_IP;
              *C_Etat_Config_XPORT = 9;
            }
            break;

          case GATEWAY_IP:
            if ((now - chrono) >= pdMS_TO_TICKS(1000)) {
              SEND_ENTER_XPORT(); // Validation précédent changement
              
              // Serial.println("[GATEWAY] IP : Y/N");
              ModBus_Uart.print("N");

              chrono = now;
              etat = NETMASK_IP;
              *C_Etat_Config_XPORT = 10;
            }
            break;

          case NETMASK_IP:
            if ((now - chrono) >= pdMS_TO_TICKS(1000)) {
              SEND_ENTER_XPORT(); // Validation précédent changement
              
              // Serial.println("[NETMASK_IP] IP : Y/N");
              ModBus_Uart.print("N");
              
              chrono = now;
              etat = TELNET_PWD;
              *C_Etat_Config_XPORT = 11;
            }
            break;

          case TELNET_PWD:
            if ((now - chrono) >= pdMS_TO_TICKS(1000)) {
              SEND_ENTER_XPORT(); // Validation précédent changement
              
              // Serial.println("[TELNET_PWD] IP : Y/N");
              ModBus_Uart.print("N");
              
              chrono = now;
              etat = CONFIG_FIN;
              *C_Etat_Config_XPORT = 12;
            }
            break;

          case CONFIG_FIN:
            if ((now - chrono) >= pdMS_TO_TICKS(1000)) {
              // Serial.println("[CONFIG_FIN] Lecture finale de XPORT");
              // LECTURE_XPORT();
              ModBus_Uart.print("S");
              // LECTURE_XPORT_ALL();
              etat = SAUVEGARDE;
              chrono = now;
              *C_Etat_Config_XPORT = 13;
            }
            break;

          case SAUVEGARDE:
            if ((now - chrono) >= pdMS_TO_TICKS(10000)) {
              // Serial.println("[SAUVEGARDE] Lecture XPORT_ALL et fin de séquence");
              digitalWrite(ETH_RST,LOW);
  
              chrono = now;

              *C_Etat_Config_XPORT = 14;
              etat = TERMINE;
            }
            break;

          case TERMINE:
            if ((now - chrono) >= pdMS_TO_TICKS(1000)) {
            // Serial.println("[TERMINE] Séquence complétée");

            ESP.restart();
            etat = WAIT_TRIGGER;


            *C_Etat_Config_XPORT = 15;

            *C_Config_XPORT=  0;
            }
            break;

          } // fin switch
        // ===========================
      } // fin C_Config_XPORT

            stackWordsLeft = uxTaskGetStackHighWaterMark(NULL);

            taskDataAnalysis[2] = stackWordsLeft;


        vTaskDelay(1); // Small delay to avoid flooding the client check
      } // While (1)*/


} // Fin TaskComWifi
// ===========================================================================================================
// Task  : Gestion téléversement programme Other The Air 
// ===========================================================================================================
void TaskOTA(void *param) {
    // --------------------------------------------------------------
  // Point d'accés défini pour le téléversement à distance
  // --------------------------------------------------------------

  // Vérifier que le handle est valide avant de supprimer la tâche
  if (TaskReceptionTRMSHandler != NULL) vTaskDelete(TaskReceptionTRMSHandler);
  if (TaskComGUIHandler     != NULL) vTaskDelete(TaskComGUIHandler);
  // if (TaskComEcranHandler   != NULL) vTaskDelete(TaskComEcranHandler);
  if (TaskModbusHandler     != NULL) vTaskDelete(TaskModbusHandler);
  if (TaskEmissionTRMSHandler != NULL) vTaskDelete(TaskEmissionTRMSHandler);
  if (TaskBASICHandler      != NULL) vTaskDelete(TaskBASICHandler);
  if (TaskWifiHandler       != NULL) vTaskDelete(TaskWifiHandler);
  if (TaskSDcardHandler     != NULL) vTaskDelete(TaskSDcardHandler);


    const char *ssid = "SDP_CP_V2_INFO0274";
    const char *password = "123456789";
    WiFi.softAP(ssid, password);

    ArduinoOTA.begin();

  // --------------------------------------------------------------
      while (1) {
      ArduinoOTA.handle();

      vTaskDelay(1); // Small delay to avoid flooding the client check

      } // While (1)
}
// ===========================================================================================================


