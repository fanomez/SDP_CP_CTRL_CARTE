
// ===========================================================================================================
// Tâche : Gestion communication Modbus    
// ===========================================================================================================
void TaskModbus(void * param) {
  while (1) {

    if (*C_Config_XPORT == 0 ){
       mb.task();

    }else if (*C_Config_XPORT == 1) {
          // -------------------------------------------------------------------------------------------
          if (*C_Etat_Config_XPORT == 0 ) {

              // 1.  Désactivation des tâches en arrière plan 
              if (TaskReceptionTRMSHandler != NULL) vTaskDelete(TaskReceptionTRMSHandler);
              if (TaskComGUIHandler     != NULL) vTaskDelete(TaskComGUIHandler);
              if (TaskEmissionTRMSHandler != NULL) vTaskDelete(TaskEmissionTRMSHandler);
              if (TaskBASICHandler      != NULL) vTaskDelete(TaskBASICHandler);
              if (TaskSDcardHandler     != NULL) vTaskDelete(TaskSDcardHandler);

              // 2. Réinitialisation des valeurs de stack :
              for(int i=0; i<10; i++){  taskDataAnalysis[i] = 0;  }

              *C_Etat_Config_XPORT = 1 ;
          // -------------------------------------------------------------------------------------------
          } else if (*C_Etat_Config_XPORT == 1 ) {          // Initialisation  du baudrate 
            ModBus_Uart.flush();
            ModBus_Uart.end();

            ModBus_Uart.begin(9600,SERIAL_8N1,16,17);

            *C_Etat_Config_XPORT = 2; 
          // -------------------------------------------------------------------------------------------
          } else{           // Gestion du cycle 

              TickType_t now = xTaskGetTickCount();
              
              switch (etat) {
              case WAIT_TRIGGER:
                  
                  digitalWrite(ETH_RST, LOW);
                  startTime = now;
                  chrono = now;
                  etat = WAIT_LOW;

                  *C_Etat_Config_XPORT = 3;     // Utilisé pour identifier à quel étape de la configuration on est

                break;

              case WAIT_LOW:
                if ((now - chrono) >= pdMS_TO_TICKS(1000)) {
                  digitalWrite(ETH_RST, HIGH);
                  etat = ENTRER_MODE_SETUP;
                }
                  *C_Etat_Config_XPORT = 4;
                break;

              case ENTRER_MODE_SETUP:
                if (ModBus_Uart.available()){

                    *C_Etat_Config_XPORT = 5;
                    result = (char)ModBus_Uart.read();

                      // Dès qu'on reçoit quelque chose → setup détecté
                      while (ModBus_Uart.available()) {
                          ModBus_Uart.read();
                          vTaskDelay(pdMS_TO_TICKS(1));
                      }

                      SEND_ENTER_XPORT(); 

                     while (ModBus_Uart.available()) {
                          ModBus_Uart.read();
                          vTaskDelay(pdMS_TO_TICKS(1));
                      }

                      etat = CONFIG_IP_0;
                      chrono = now;

                      *C_Etat_Config_XPORT = 6;   // Avancement dans les étapes 

                }else{

                      ModBus_Uart.print("x");
                      vTaskDelay(pdMS_TO_TICKS(50));

                }
                break;

              case CONFIG_IP_0:
                  if ((now - chrono) >= pdMS_TO_TICKS(2000)) {


                    ModBus_Uart.print("1");

                    while (ModBus_Uart.available()) {
                        ModBus_Uart.read(); // vide le buffer
                        vTaskDelay(pdMS_TO_TICKS(1));  //  Attente non bloquante de 10 ms
                    }

                          chrono = now;
                          etat = CONFIG_IP_1;
                          

                          *C_Etat_Config_XPORT = 7;
                              

                  }
                  break;

              case CONFIG_IP_1:
                if ((now - chrono) >= pdMS_TO_TICKS(100)) {

                  // Serial.println("[CONFIG_IP_1] IP : 192");
                  
                  ModBus_Uart.print(ip0);

                  SEND_ENTER_XPORT(); 
                  
                  etat = CONFIG_IP_2;
                  chrono = now;
                  *C_Etat_Config_XPORT = 8;

                }
                break;

              case CONFIG_IP_2:
                if ((now - chrono) >= pdMS_TO_TICKS(100)) {
                  
                    while (ModBus_Uart.available()) {
                        ModBus_Uart.read(); // vide le buffer
                        vTaskDelay(pdMS_TO_TICKS(1));  //  Attente non bloquante de 10 ms
                    }                  

                //  Serial.println("[CONFIG_IP_2] IP : 168");
                  ModBus_Uart.print(ip1);
                  SEND_ENTER_XPORT(); 


                  etat = CONFIG_IP_3;
                  chrono = now;
                  *C_Etat_Config_XPORT = 9;
                }
                break;

              case CONFIG_IP_3:
                if ((now - chrono) >= pdMS_TO_TICKS(100)) {
                  
                    while (ModBus_Uart.available()) {
                        ModBus_Uart.read(); // vide le buffer
                        vTaskDelay(pdMS_TO_TICKS(1));  //  Attente non bloquante de 10 ms
                    }

                  ModBus_Uart.print(ip2);
                  SEND_ENTER_XPORT(); 

                  chrono = now;
                  etat = CONFIG_IP_4;
                  *C_Etat_Config_XPORT = 10;
                }
                break;

              case CONFIG_IP_4:
                if ((now - chrono) >= pdMS_TO_TICKS(100)) {
                  
                    while (ModBus_Uart.available()) {
                        ModBus_Uart.read(); // vide le buffer
                        vTaskDelay(pdMS_TO_TICKS(1));  //  Attente non bloquante de 10 ms
                    }                  
                  
                  // Serial.println("[CONFIG_IP_4] IP : 20");
                  ModBus_Uart.print(ip3);
                  SEND_ENTER_XPORT(); 

                  chrono = now;
                  etat = GATEWAY_IP;
                  *C_Etat_Config_XPORT = 11;
                }
                break;

              case GATEWAY_IP:
                if ((now - chrono) >= pdMS_TO_TICKS(100)) {
                  
                    while (ModBus_Uart.available()) {
                        ModBus_Uart.read(); // vide le buffer
                        vTaskDelay(pdMS_TO_TICKS(1));  //  Attente non bloquante de 10 ms
                    }

                  // Serial.println("[GATEWAY] IP : Y/N");
                  ModBus_Uart.print("N");

                  chrono = now;
                  etat = NETMASK_IP;
                  *C_Etat_Config_XPORT = 12;
                }
                break;

              case NETMASK_IP:
                if ((now - chrono) >= pdMS_TO_TICKS(100)) {                  

                    while (ModBus_Uart.available()) {
                        ModBus_Uart.read(); // vide le buffer
                        vTaskDelay(pdMS_TO_TICKS(1));  //  Attente non bloquante de 10 ms
                    }

                  // Serial.println("[NETMASK_IP] IP : Y/N");
                  ModBus_Uart.print("N");
               
                  
                  chrono = now;
                  etat = TELNET_PWD;
                  *C_Etat_Config_XPORT = 13;
                }
                break;

              case TELNET_PWD:
                if ((now - chrono) >= pdMS_TO_TICKS(100)) {
                  // SEND_ENTER_XPORT(); // Validation précédent changement

                    while (ModBus_Uart.available()) {
                        ModBus_Uart.read(); // vide le buffer
                        vTaskDelay(pdMS_TO_TICKS(1));  //  Attente non bloquante de 10 ms
                    }  
                  
                  ModBus_Uart.print("N");


                  
                  chrono = now;
                  etat = CONFIG_FIN;
                  *C_Etat_Config_XPORT = 14;
                }
                break;

              case CONFIG_FIN:
                if ((now - chrono) >= pdMS_TO_TICKS(100)) {
                  // Serial.println("[CONFIG_FIN] Lecture finale de XPORT");


                    while (ModBus_Uart.available()) {
                        ModBus_Uart.read(); // vide le buffer
                        vTaskDelay(pdMS_TO_TICKS(1));  //  Attente non bloquante de 10 ms
                    }

                  ModBus_Uart.print("S");

                  etat = SAUVEGARDE;
                  chrono = now;
                  *C_Etat_Config_XPORT = 15;
                }
                break;

              case SAUVEGARDE:
                if ((now - chrono) >= pdMS_TO_TICKS(2000)) {

                    while (ModBus_Uart.available()) {
                        ModBus_Uart.read(); // vide le buffer
                        vTaskDelay(pdMS_TO_TICKS(1));  //  Attente non bloquante de 10 ms
                    }

                  chrono = now;

                  *C_Etat_Config_XPORT = 16;
                  etat = TERMINE;
                }
                break;

              case TERMINE:

              if ((now - chrono) >= pdMS_TO_TICKS(1000)) {

                ModBus_Uart.flush();
                ModBus_Uart.end();

                ModBus_Uart.begin(115200,SERIAL_8N1,16,17);  // Initialisation XPORT/MODBUS  (16 : RX ; 17 : TX)
                // Initialisation communication modbus
                mb.begin(&ModBus_Uart);
                mb.slave(1);                
                // Serial.println("[TERMINE] Séquence complétée");

                chrono = now;
                etat = WAIT_TRIGGER;
                *C_Etat_Config_XPORT = 0;

                *C_Config_XPORT=  0;
              }
  
                break;

              } // fin switch
          }
          
        



    }

    

    stackWordsLeft = uxTaskGetStackHighWaterMark(NULL);

    taskDataAnalysis[3] = stackWordsLeft;

    vTaskDelay(pdMS_TO_TICKS(1));
  }
}// Fin TaskModbus


