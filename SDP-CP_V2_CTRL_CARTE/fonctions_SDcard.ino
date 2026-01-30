float rebuild_float(uint16_t msb, uint16_t lsb);
// .........................................................................................................................
// Récupération données du fichier JSON
// @brief : Mode init : lancé au démarrage ; Mode run : lecture périodique pour comparaison
// .........................................................................................................................
void recupConfigJson(const char* mode){  

      // Prendre le mutex SPI uniquement pour la durée de l'accès SD
    xSemaphoreTake(spiMutex, portMAX_DELAY);  

  if (strcmp(mode, "init") == 0){
    File fileRead = SD.open("/parametres.json",FILE_READ);

    if (fileRead){

      *READ_SD = 1;  // Succès de l'ouverture du fichier de paramètres 
      

      DeserializationError error = deserializeJson(config_SDP, fileRead);

      fileRead.close(); 

      if (error){
        
        *EXTRACT_CONFIG = 0;  // Erreur de désérialisation du fichier de paramètres 
        
      }else{

        *EXTRACT_CONFIG = 1;  // Succès de désérialisation du fichier de paramètres 
        // ...............................................................................................
        // 1. Récupération paramètres  généraux
        // ...............................................................................................
                    if (config_SDP.containsKey("AccessPoint")){
                     if ( config_SDP["AccessPoint"].as<bool>() ){
                        *wifi_cmd = 1;
                     }
                    }
                    // Types capteurs
                    *MODE = config_SDP["general"]["modeCP"].as<int>();
                    if (config_SDP["general"].containsKey("modeCPsup")){ *MODE_SUP = config_SDP["general"]["modeCPsup"].as<int>(); }
                    
                    *Types_Capteurs     =         config_SDP["general"]["typesCapteurs"].as<int>();
                    *Types_Capteurs_Sup  =        config_SDP["general"]["typesCapteursSup"].as<int>();
                    
                    // Pointeurs 
                    *Pointeur_DCY       =         config_SDP["general"]["ptrDCY"].as<int>();
                    *Pointeur_ACY       =         config_SDP["general"]["ptrACY"].as<int>();
                    *Pointeur_ACQ       =         config_SDP["general"]["ptrACQ"].as<int>();
                    *Pointeur_DEMAG     =         config_SDP["general"]["ptrDEMAG"].as<int>();
                    
                    *Pointeur_TOR_S1    =         config_SDP["general"]["ptrTORS1"].as<int>();
                    *Pointeur_TOR_S2    =         config_SDP["general"]["ptrTORS2"].as<int>();
                    *Pointeur_TOR_S3    =         config_SDP["general"]["ptrTORS3"].as<int>();
                    *Pointeur_TOR_S4    =         config_SDP["general"]["ptrTORS4"].as<int>();

                    *COEF_CONE_TUBE     =         config_SDP["general"]["%stabRegul"].as<int>();   // Correspond à %stabRegul dans le fichier de parametres
                    *Gain_BOOST         =         config_SDP["general"]["%gainBoost"].as<int>();
                    *Temps_Pb_puissance =         config_SDP["general"]["tpsPbPuissance"].as<int>();

                    // Autres (à ajouter )
                    *OPTION_DOUBLE_AFFICHAGE = config_SDP["general"]["doubleAffichage"].as<bool>();

                    *SENS_MODE_COMBINE = config_SDP["general"]["sensModeCombine"].as<bool>();

                    //  ---- arrosageModecombine
                    *PAS_POTARD_TEMPS_05S = config_SDP["general"]["pasPotard0.5"].as<bool>();
                    *REPOS_4s_GT = config_SDP["general"]["repos4sGT"].as<bool>();

        // ...............................................................................................                            
        // 2.Récupération des paramètres des générateurs 
        // ...............................................................................................

                    *OPTION_CTRL_TETES_12 =                 config_SDP["generateur1"]["ctrlTete"].as<bool>();
                    *OPTION_CTRL_FORME_ONDE_1 =                 config_SDP["generateur1"]["ctrlFO"].as<bool>();
                    *OPTION_DEFAUT_THERMIQUE_1 =                 config_SDP["generateur1"]["secuVigitherm"].as<bool>();

                    *OPTION_CTRL_TETES_34 =                 config_SDP["generateur2"]["ctrlTete"].as<bool>();
                    *OPTION_CTRL_FORME_ONDE_2 =                 config_SDP["generateur2"]["ctrlFO"].as<bool>();
                    *OPTION_DEFAUT_THERMIQUE_2 =                 config_SDP["generateur2"]["secuVigitherm"].as<bool>();    

                    *Pointeur_Puissance_2_C1 =        config_SDP["generateur1"]["ptrPuissance2"].as<int>();
                    *Pointeur_Puissance_2_C2 =        config_SDP["generateur2"]["ptrPuissance2"].as<int>();
                    *Pointeur_Puissance_2_C3 =        config_SDP["generateur3"]["ptrPuissance2"].as<int>();

                    *Pointeur_Puissance_C1 =          config_SDP["generateur1"]["ptrPuissance1"].as<int>(); 
                    *Pointeur_Puissance_C2 =          config_SDP["generateur2"]["ptrPuissance1"].as<int>();
                    *Pointeur_Puissance_C3 =          config_SDP["generateur3"]["ptrPuissance1"].as<int>();

                    *Pointeur_Temps_C1 =              config_SDP["generateur1"]["ptrTps"].as<int>();
                    *Pointeur_Temps_C2 =              config_SDP["generateur2"]["ptrTps"].as<int>();
                    *Pointeur_Temps_C3 =              config_SDP["generateur3"]["ptrTps"].as<int>();

                    *Pointeur_mesure_C1 =             config_SDP["generateur1"]["ptrMesure"].as<int>();
                    *Pointeur_mesure_C2 =             config_SDP["generateur2"]["ptrMesure"].as<int>();
                    *Pointeur_mesure_C3 =             config_SDP["generateur3"]["ptrMesure"].as<int>();

                    *Seuil_CTRL_BO_C1 =               config_SDP["generateur1"]["seuilCtrlBO"].as<int>();
                    *Seuil_CTRL_BO_C2 =               config_SDP["generateur2"]["seuilCtrlBO"].as<int>();
                    *Seuil_CTRL_BO_C3 =               config_SDP["generateur3"]["seuilCtrlBO"].as<int>();

                    *Nb_val_stab_mesure_C1 =          config_SDP["generateur1"]["%stabMesure"].as<int>();
                    *Nb_val_stab_mesure_C2 =          config_SDP["generateur2"]["%stabMesure"].as<int>();
                    *Nb_val_stab_mesure_C3 =          config_SDP["generateur3"]["%stabMesure"].as<int>();

                    *Pointeur_FO_C1 =                 config_SDP["generateur1"]["ptrFO"].as<int>();
                    *Pointeur_FO_C2 =                 config_SDP["generateur2"]["ptrFO"].as<int>();
                    *Pointeur_FO_C3 =                 config_SDP["generateur3"]["ptrFO"].as<int>();

                    *Pointeur_ET_C1 =                 config_SDP["generateur1"]["ptrET"].as<int>();
                    *Pointeur_ET_C2 =                 config_SDP["generateur2"]["ptrET"].as<int>();
                    *Pointeur_ET_C3 =                 config_SDP["generateur3"]["ptrET"].as<int>();


                    // 3. Récupération paramètres cycles (Générateur 1)
                    for (int i=0;i<16;i++){
                        *U_MIN_C1_B[i]           =  config_SDP["generateur1"]["banques"][banques_num[i]]["Umin"].as<int>();
                        *U_MAX_C1_B[i]           =  config_SDP["generateur1"]["banques"][banques_num[i]]["Umax"].as<int>();
                        *GP_C1_B[i]              =  config_SDP["generateur1"]["banques"][banques_num[i]]["GainP"].as<int>();
                        *I_MAX_C1_B[i]           =  config_SDP["generateur1"]["banques"][banques_num[i]]["ImaxREF"].as<int>();
                        *Seuil_mesure_I_C1_B[i]  =  config_SDP["generateur1"]["banques"][banques_num[i]]["seuilMesure"].as<int>();
                        *KD_C1_B[i]              =  config_SDP["generateur1"]["banques"][banques_num[i]]["GainKD"].as<int>();
                        *I_MAX_LU_C1_B[i]        =  config_SDP["generateur1"]["banques"][banques_num[i]]["ImaxLu"].as<int>(); 
                        *ID_Fth_C1_B[i]          =  config_SDP["generateur1"]["banques"][banques_num[i]]["ID_Fth"].as<int>(); 
                    }   

                    // 3. Récupération paramètres cycles (Générateur 2)
                    for (int i=0;i<16;i++){
                        *U_MIN_C2_B[i]           =  config_SDP["generateur2"]["banques"][banques_num[i]]["Umin"].as<int>();
                        *U_MAX_C2_B[i]           =  config_SDP["generateur2"]["banques"][banques_num[i]]["Umax"].as<int>();
                        *GP_C2_B[i]              =  config_SDP["generateur2"]["banques"][banques_num[i]]["GainP"].as<int>();
                        *I_MAX_C2_B[i]           =  config_SDP["generateur2"]["banques"][banques_num[i]]["ImaxREF"].as<int>();
                        *Seuil_mesure_I_C2_B[i]  =  config_SDP["generateur2"]["banques"][banques_num[i]]["seuilMesure"].as<int>();
                        *KD_C2_B[i]              =  config_SDP["generateur2"]["banques"][banques_num[i]]["GainKD"].as<int>();
                        *I_MAX_LU_C2_B[i]        =  config_SDP["generateur2"]["banques"][banques_num[i]]["ImaxLu"].as<int>(); 
                        *ID_Fth_C2_B[i]          =  config_SDP["generateur2"]["banques"][banques_num[i]]["ID_Fth"].as<int>(); 
                    }
                    
                    // 3. Récupération paramètres cycles (Générateur 3)
                    for (int i=0;i<16;i++){
                      *U_MIN_C3_B[i]           =  config_SDP["generateur3"]["banques"][banques_num[i]]["Umin"].as<int>();
                      *U_MAX_C3_B[i]           =  config_SDP["generateur3"]["banques"][banques_num[i]]["Umax"].as<int>();
                      *GP_C3_B[i]              =  config_SDP["generateur3"]["banques"][banques_num[i]]["GainP"].as<int>();
                      *I_MAX_C3_B[i]           =  config_SDP["generateur3"]["banques"][banques_num[i]]["ImaxREF"].as<int>();
                      *Seuil_mesure_I_C3_B[i]  =  config_SDP["generateur3"]["banques"][banques_num[i]]["seuilMesure"].as<int>();
                      *KD_C3_B[i]              =  config_SDP["generateur3"]["banques"][banques_num[i]]["GainKD"].as<int>();
                      *I_MAX_LU_C3_B[i]        =  config_SDP["generateur3"]["banques"][banques_num[i]]["ImaxLu"].as<int>(); 
                      *ID_Fth_C3_B[i]          =  config_SDP["generateur3"]["banques"][banques_num[i]]["ID_Fth"].as<int>(); 
                    }

                    // 6. Récupération du temps sauvegardé au moment de la mise hors tension du contrôleur process (Conversion de l'heure en secondes) 
                    *C_HDT_tps_off = (uint16_t)(
                          config_SDP["dataFth"]["HDT"]["heures"].as<int>() * 3600U +
                          config_SDP["dataFth"]["HDT"]["min"].as<int>()   * 60U +
                          config_SDP["dataFth"]["HDT"]["sec"].as<int>()
                    );

                  // Nombre de secondes au moment de la mise hors tension de la machine
                    
                    // 7. Récupération des paramètres pour chaque calculs de facteurs thermique (4 par générateur)
                  *I_thermique_N_C1[0]          = config_SDP["dataFth"]["G1"]["ID_0"]["Ith"].as<int>();
                  *I_thermique_N_C1[1]          = config_SDP["dataFth"]["G1"]["ID_1"]["Ith"].as<int>();
                  *I_thermique_N_C1[2]          = config_SDP["dataFth"]["G1"]["ID_2"]["Ith"].as<int>();
                  *I_thermique_N_C1[3]          = config_SDP["dataFth"]["G1"]["ID_3"]["Ith"].as<int>();                 

                  *Periode_Fth_N_C1[0]  = config_SDP["dataFth"]["G1"]["ID_0"]["periode"].as<int>();
                  *Periode_Fth_N_C1[1]  = config_SDP["dataFth"]["G1"]["ID_1"]["periode"].as<int>();
                  *Periode_Fth_N_C1[2]  = config_SDP["dataFth"]["G1"]["ID_2"]["periode"].as<int>();
                  *Periode_Fth_N_C1[3]  = config_SDP["dataFth"]["G1"]["ID_3"]["periode"].as<int>();

                  *I_thermique_N_C2[0]          = config_SDP["dataFth"]["G2"]["ID_0"]["Ith"].as<int>();
                  *I_thermique_N_C2[1]          = config_SDP["dataFth"]["G2"]["ID_1"]["Ith"].as<int>();
                  *I_thermique_N_C2[2]          = config_SDP["dataFth"]["G2"]["ID_2"]["Ith"].as<int>();
                  *I_thermique_N_C2[3]          = config_SDP["dataFth"]["G2"]["ID_3"]["Ith"].as<int>();                 

                  *Periode_Fth_N_C2[0]  = config_SDP["dataFth"]["G2"]["ID_0"]["periode"].as<int>();
                  *Periode_Fth_N_C2[1]  = config_SDP["dataFth"]["G2"]["ID_1"]["periode"].as<int>();
                  *Periode_Fth_N_C2[2]  = config_SDP["dataFth"]["G2"]["ID_2"]["periode"].as<int>();
                  *Periode_Fth_N_C2[3]  = config_SDP["dataFth"]["G2"]["ID_3"]["periode"].as<int>();

                  *I_thermique_N_C3[0]          = config_SDP["dataFth"]["G3"]["ID_0"]["Ith"].as<int>();
                  *I_thermique_N_C3[1]          = config_SDP["dataFth"]["G3"]["ID_1"]["Ith"].as<int>();
                  *I_thermique_N_C3[2]          = config_SDP["dataFth"]["G3"]["ID_2"]["Ith"].as<int>();
                  *I_thermique_N_C3[3]          = config_SDP["dataFth"]["G3"]["ID_3"]["Ith"].as<int>();                 

                  *Periode_Fth_N_C3[0]  = config_SDP["dataFth"]["G3"]["ID_0"]["periode"].as<int>();
                  *Periode_Fth_N_C3[1]  = config_SDP["dataFth"]["G3"]["ID_1"]["periode"].as<int>();
                  *Periode_Fth_N_C3[2]  = config_SDP["dataFth"]["G3"]["ID_2"]["periode"].as<int>();
                  *Periode_Fth_N_C3[3]  = config_SDP["dataFth"]["G3"]["ID_3"]["periode"].as<int>();                                  

                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                  // 8.Récupération config voies de Mesure
                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!                  
                      float temp;
                      uint8_t offset_hex[4]={0};     // Tableau pour stocker les octets

                      *GAIN_V1 = config_SDP["configMesures"]["Mesure_1"]["Gain"].as<int>();

                      temp = config_SDP["configMesures"]["Mesure_1"]["Offset"].as<float>();

                      float_to_hex_array(-1*temp, offset_hex); 

                      *OFFSET_MSB_V1  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
                      *OFFSET_LSB_V1  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 

                      *OFFSET_DYN_V1 = config_SDP["configMesures"]["Mesure_1"]["type"].as<int>();      // Si 1 => offset dyn actif sinon 0


                      // ....................................
                      *GAIN_V2 = config_SDP["configMesures"]["Mesure_2"]["Gain"].as<int>();

                      temp = config_SDP["configMesures"]["Mesure_2"]["Offset"].as<float>();

                      float_to_hex_array(-1*temp, offset_hex); 

                      *OFFSET_MSB_V2  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
                      *OFFSET_LSB_V2  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 

                      *OFFSET_DYN_V2 = config_SDP["configMesures"]["Mesure_2"]["type"].as<int>();      // Si 1 => offset dyn actif sinon 0
                      // ....................................
                      *GAIN_V3  = config_SDP["configMesures"]["Mesure_3"]["Gain"].as<int>();
  
                      temp = config_SDP["configMesures"]["Mesure_3"]["Offset"].as<float>();

                      float_to_hex_array(-1*temp, offset_hex); 

                      *OFFSET_MSB_V3  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
                      *OFFSET_LSB_V3  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 

                      *OFFSET_DYN_V3 = config_SDP["configMesures"]["Mesure_3"]["type"].as<int>();      // Si 1 => offset dyn actif sinon 0
                      // ....................................
                      *GAIN_V4  = config_SDP["configMesures"]["Mesure_4"]["Gain"].as<int>();

                      temp = config_SDP["configMesures"]["Mesure_4"]["Offset"].as<float>();

                      float_to_hex_array(-1*temp, offset_hex); 

                      *OFFSET_MSB_V4  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
                      *OFFSET_LSB_V4  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 

                      *OFFSET_DYN_V4 = config_SDP["configMesures"]["Mesure_4"]["type"].as<int>();      // Si 1 => offset dyn actif sinon 0
                      // ....................................
                      *GAIN_V5  = config_SDP["configMesures"]["Mesure_5"]["Gain"].as<int>();
                      
                      temp = config_SDP["configMesures"]["Mesure_5"]["Offset"].as<float>();

                      float_to_hex_array(-1*temp, offset_hex); 

                      *OFFSET_MSB_V5  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
                      *OFFSET_LSB_V5  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 

                      *OFFSET_DYN_V5 = config_SDP["configMesures"]["Mesure_5"]["type"].as<int>();      // Si 1 => offset dyn actif sinon 0
                      // ....................................
                      *GAIN_V6  = config_SDP["configMesures"]["Mesure_6"]["Gain"].as<int>();

                      temp = config_SDP["configMesures"]["Mesure_6"]["Offset"].as<float>();

                      float_to_hex_array(-1*temp, offset_hex); 

                      *OFFSET_MSB_V6  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
                      *OFFSET_LSB_V6  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 

                      *OFFSET_DYN_V6 = config_SDP["configMesures"]["Mesure_6"]["type"].as<int>();      // Si 1 => offset dyn actif sinon 0

                    // ..............................................................................
                    // 9.Récupération des données d'étallonage capteur 
                    // .............................................................................. 
                    for (int i=0;i<16;i++){
                        *Etalonnage_X1_B[i] = config_SDP["Etalonnage"]["X1"][banques_etalonnage[i]].as<int>();
                        *Etalonnage_Y1_B[i] = config_SDP["Etalonnage"]["Y1"][banques_etalonnage[i]].as<int>();
                        *Etalonnage_X2_B[i] = config_SDP["Etalonnage"]["X2"][banques_etalonnage[i]].as<int>();
                        *Etalonnage_Y2_B[i] = config_SDP["Etalonnage"]["Y2"][banques_etalonnage[i]].as<int>();
                    }

                  *Seuil_Ctrl_Temperature = config_SDP["Etalonnage"]["Seuil_Ctrl_Temperature"].as<int>(); 
              
                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                  // Traitement des données récupérés : Affectation au registre courant (Facteur thermique)
                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    *ID_FTH_C3 = *ID_Fth_C3_B[(WP_CONF_DYN_E & 0x00F0) >> 4];
                    *ID_FTH_C2 = *ID_Fth_C2_B[(WP_CONF_DYN_E & 0xF000) >> 12];
                    *ID_FTH_C1 = *ID_Fth_C1_B[(WP_CONF_DYN_E & 0x0F00) >> 8];

                    *Periode_Fth_C3 = *Periode_Fth_N_C3[*ID_Fth_C3_B[(WP_CONF_DYN_E & 0x00F0) >> 4] ]; 
                    *I_thermique_C3 =  *I_thermique_N_C3[*ID_Fth_C3_B[(WP_CONF_DYN_E & 0x00F0) >> 4]] ;

                    *Periode_Fth_C2 = *Periode_Fth_N_C2[*ID_Fth_C2_B[(WP_CONF_DYN_E & 0xF000) >> 12]]; 
                    *I_thermique_C2 =  *I_thermique_N_C2[*ID_Fth_C2_B[(WP_CONF_DYN_E & 0xF000) >> 12]] ;

                    *Periode_Fth = *Periode_Fth_N_C1[*ID_Fth_C1_B[(WP_CONF_DYN_E & 0x0F00) >> 8]]; 
                    *I_thermique_C1 =  *I_thermique_N_C1[*ID_Fth_C1_B[(WP_CONF_DYN_E & 0x0F00) >> 8]] ;

                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                  // Traitement des données récupérés : Affectation au registre courant (Données de régulation)
                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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

                    *MODE_TEST = 0;

                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                  // Traitement des données récupérés : Affectation au registre courant (Etalonnage sonde de température)
                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                    *Etalonnage_X1 = *Etalonnage_X1_B[(WP_CONF_DYN_E & 0x000F)];
                    *Etalonnage_Y1 = *Etalonnage_Y1_B[(WP_CONF_DYN_E & 0x000F)];
                    *Etalonnage_X2 = *Etalonnage_X2_B[(WP_CONF_DYN_E & 0x000F)];
                    *Etalonnage_Y2 = *Etalonnage_Y2_B[(WP_CONF_DYN_E & 0x000F)];

                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!       
    }
    
    }else{
      *READ_SD = 0;  // Echecs de l'ouverture du fichier de paramètres 
    }

  }
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  else if (strcmp(mode, "loop") == 0){

    File fileRead = SD.open("/parametres.json",FILE_READ);

    if (fileRead){

      *READ_SD = 1;  // Succès de l'ouverture du fichier de paramètres 
      
      config_SDP.clear();

      DeserializationError error = deserializeJson(config_SDP, fileRead);
      fileRead.close();

        if (error){     
          
          *EXTRACT_CONFIG = 0;  // Erreur de désérialisation du fichier de paramètres 
          
        }else{

          *EXTRACT_CONFIG = 1;  // Succès de désérialisation du fichier de paramètres

          nb_modifications = 0; 

          // ...............................................................................................
          // 1. Récupération paramètres  généraux
          // ...............................................................................................

                  if (*MODE != config_SDP["general"]["modeCP"].as<int>()) {
                      nb_modifications++;
                      config_SDP["general"]["modeCP"] = *MODE;
                  }
                  
                  if (config_SDP["general"].containsKey("modeCPsup")){
                    if (*MODE_SUP != config_SDP["general"]["modeCPsup"].as<int>()) {
                        nb_modifications++;
                        config_SDP["general"]["modeCPsup"] = *MODE_SUP;
                    }
                  }

                  if (*Types_Capteurs != config_SDP["general"]["typesCapteurs"].as<int>()) {
                      nb_modifications++;
                      config_SDP["general"]["typesCapteurs"] = *Types_Capteurs;
                  }

                  if (*Types_Capteurs_Sup != config_SDP["general"]["typesCapteursSup"].as<int>()) {
                      nb_modifications++;
                      config_SDP["general"]["typesCapteursSup"] = *Types_Capteurs_Sup;
                  }

                  // Pointeurs
                  if (*Pointeur_DCY != config_SDP["general"]["ptrDCY"].as<int>()) {
                      nb_modifications++;
                      config_SDP["general"]["ptrDCY"] = *Pointeur_DCY;
                  }

                  if (*Pointeur_ACY != config_SDP["general"]["ptrACY"].as<int>()) {
                      nb_modifications++;
                      config_SDP["general"]["ptrACY"] = *Pointeur_ACY;
                  }

                  if (*Pointeur_ACQ != config_SDP["general"]["ptrACQ"].as<int>()) {
                      nb_modifications++;
                      config_SDP["general"]["ptrACQ"] = *Pointeur_ACQ;
                  }

                  if (*Pointeur_DEMAG != config_SDP["general"]["ptrDEMAG"].as<int>()) {
                      nb_modifications++;
                      config_SDP["general"]["ptrDEMAG"] = *Pointeur_DEMAG;
                  }

                  if (*Pointeur_TOR_S1 != config_SDP["general"]["ptrTORS1"].as<int>()) {
                      nb_modifications++;
                      config_SDP["general"]["ptrTORS1"] = *Pointeur_TOR_S1;
                  }

                  if (*Pointeur_TOR_S2 != config_SDP["general"]["ptrTORS2"].as<int>()) {
                      nb_modifications++;
                      config_SDP["general"]["ptrTORS2"] = *Pointeur_TOR_S2;
                  }

                  if (*Pointeur_TOR_S3 != config_SDP["general"]["ptrTORS3"].as<int>()) {
                      nb_modifications++;
                      config_SDP["general"]["ptrTORS3"] = *Pointeur_TOR_S3;
                  }

                  if (*Pointeur_TOR_S4 != config_SDP["general"]["ptrTORS4"].as<int>()) {
                      nb_modifications++;
                      config_SDP["general"]["ptrTORS4"] = *Pointeur_TOR_S4;
                  }

                  if (*COEF_CONE_TUBE != config_SDP["general"]["%stabRegul"].as<int>()) {
                      nb_modifications++;
                      config_SDP["general"]["%stabRegul"] = *COEF_CONE_TUBE;
                  }

                  if (*Gain_BOOST != config_SDP["general"]["%gainBoost"].as<int>()) {
                      nb_modifications++;
                      config_SDP["general"]["%gainBoost"] = *Gain_BOOST;
                  }

                  if (*Temps_Pb_puissance != config_SDP["general"]["tpsPbPuissance"].as<int>()) {
                      nb_modifications++;
                      config_SDP["general"]["tpsPbPuissance"] = *Temps_Pb_puissance;
                  }


                  // Autres (à ajouter )

                  if ( *OPTION_DOUBLE_AFFICHAGE != config_SDP["general"]["doubleAffichage"].as<bool>()){
                      nb_modifications++;
                      config_SDP["general"]["doubleAffichage"] = *OPTION_DOUBLE_AFFICHAGE;
                  }

                  if (*SENS_MODE_COMBINE != config_SDP["general"]["sensModeCombine"].as<bool>()){
                      nb_modifications++;
                      config_SDP["general"]["sensModeCombine"] = *SENS_MODE_COMBINE;
                  }

                  if ( *FIN_ARROSAGE_COMBINE_en_1 != config_SDP["general"]["arrosageModeCombine"].as<bool>()){
                      nb_modifications++;
                      config_SDP["general"]["arrosageModeCombine"] = *FIN_ARROSAGE_COMBINE_en_1 ;
                  }

                    
                  if ( *PAS_POTARD_TEMPS_05S != config_SDP["general"]["pasPotard0.5"].as<bool>()){
                      nb_modifications++;
                      config_SDP["general"]["pasPotard0.5"]= *PAS_POTARD_TEMPS_05S ;
                  }
                  
                  if (*REPOS_4s_GT != config_SDP["general"]["repos4sGT"].as<bool>()){
                    nb_modifications++;
                    config_SDP["general"]["repos4sGT"] = *REPOS_4s_GT;
                  }
                    

          // ...............................................................................................                            
          // 2.Récupération des paramètres des générateurs 
          // ...............................................................................................
                    // Générateur 1
                    if (*OPTION_CTRL_TETES_12 != config_SDP["generateur1"]["ctrlTete"].as<bool>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["ctrlTete"] = *OPTION_CTRL_TETES_12;
                    }

                    if (*OPTION_CTRL_FORME_ONDE_1 != config_SDP["generateur1"]["ctrlFO"].as<bool>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["ctrlFO"] = *OPTION_CTRL_FORME_ONDE_1;
                    }

                    if (*OPTION_DEFAUT_THERMIQUE_1 != config_SDP["generateur1"]["secuVigitherm"].as<bool>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["secuVigitherm"] = *OPTION_DEFAUT_THERMIQUE_1;
                    }

                    // Générateur 2
                    if (*OPTION_CTRL_TETES_34 != config_SDP["generateur2"]["ctrlTete"].as<bool>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["ctrlTete"] = *OPTION_CTRL_TETES_34;
                    }

                    if (*OPTION_CTRL_FORME_ONDE_2 != config_SDP["generateur2"]["ctrlFO"].as<bool>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["ctrlFO"] = *OPTION_CTRL_FORME_ONDE_2;
                    }

                    if (*OPTION_DEFAUT_THERMIQUE_2 != config_SDP["generateur2"]["secuVigitherm"].as<bool>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["secuVigitherm"] = *OPTION_DEFAUT_THERMIQUE_2;
                    }

                    // Puissance 2
                    if (*Pointeur_Puissance_2_C1 != config_SDP["generateur1"]["ptrPuissance2"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["ptrPuissance2"] = *Pointeur_Puissance_2_C1;
                    }

                    if (*Pointeur_Puissance_2_C2 != config_SDP["generateur2"]["ptrPuissance2"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["ptrPuissance2"] = *Pointeur_Puissance_2_C2;
                    }

                    if (*Pointeur_Puissance_2_C3 != config_SDP["generateur3"]["ptrPuissance2"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur3"]["ptrPuissance2"] = *Pointeur_Puissance_2_C3;
                    }

                    // Puissance 1
                    if (*Pointeur_Puissance_C1 != config_SDP["generateur1"]["ptrPuissance1"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["ptrPuissance1"] = *Pointeur_Puissance_C1;
                    }

                    if (*Pointeur_Puissance_C2 != config_SDP["generateur2"]["ptrPuissance1"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["ptrPuissance1"] = *Pointeur_Puissance_C2;
                    }

                    if (*Pointeur_Puissance_C3 != config_SDP["generateur3"]["ptrPuissance1"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur3"]["ptrPuissance1"] = *Pointeur_Puissance_C3;
                    }

                    // Temps
                    if (*Pointeur_Temps_C1 != config_SDP["generateur1"]["ptrTps"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["ptrTps"] = *Pointeur_Temps_C1;
                    }

                    if (*Pointeur_Temps_C2 != config_SDP["generateur2"]["ptrTps"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["ptrTps"] = *Pointeur_Temps_C2;
                    }

                    if (*Pointeur_Temps_C3 != config_SDP["generateur3"]["ptrTps"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur3"]["ptrTps"] = *Pointeur_Temps_C3;
                    }

                    // Mesure
                    if (*Pointeur_mesure_C1 != config_SDP["generateur1"]["ptrMesure"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["ptrMesure"] = *Pointeur_mesure_C1;
                    }

                    if (*Pointeur_mesure_C2 != config_SDP["generateur2"]["ptrMesure"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["ptrMesure"] = *Pointeur_mesure_C2;
                    }

                    if (*Pointeur_mesure_C3 != config_SDP["generateur3"]["ptrMesure"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur3"]["ptrMesure"] = *Pointeur_mesure_C3;
                    }

                    // Seuil CTRL BO
                    if (*Seuil_CTRL_BO_C1 != config_SDP["generateur1"]["seuilCtrlBO"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["seuilCtrlBO"] = *Seuil_CTRL_BO_C1;
                    }

                    if (*Seuil_CTRL_BO_C2 != config_SDP["generateur2"]["seuilCtrlBO"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["seuilCtrlBO"] = *Seuil_CTRL_BO_C2;
                    }

                    if (*Seuil_CTRL_BO_C3 != config_SDP["generateur3"]["seuilCtrlBO"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur3"]["seuilCtrlBO"] = *Seuil_CTRL_BO_C3;
                    }

                    // Nb valeurs stab mesure
                    if (*Nb_val_stab_mesure_C1 != config_SDP["generateur1"]["%stabMesure"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["%stabMesure"] = *Nb_val_stab_mesure_C1;
                    }

                    if (*Nb_val_stab_mesure_C2 != config_SDP["generateur2"]["%stabMesure"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["%stabMesure"] = *Nb_val_stab_mesure_C2;
                    }

                    if (*Nb_val_stab_mesure_C3 != config_SDP["generateur3"]["%stabMesure"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur3"]["%stabMesure"] = *Nb_val_stab_mesure_C3;
                    }

                    // FO
                    if (*Pointeur_FO_C1 != config_SDP["generateur1"]["ptrFO"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["ptrFO"] = *Pointeur_FO_C1;
                    }

                    if (*Pointeur_FO_C2 != config_SDP["generateur2"]["ptrFO"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["ptrFO"] = *Pointeur_FO_C2;
                    }

                    if (*Pointeur_FO_C3 != config_SDP["generateur3"]["ptrFO"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur3"]["ptrFO"] = *Pointeur_FO_C3;
                    }

                    // ET
                    if (*Pointeur_ET_C1 != config_SDP["generateur1"]["ptrET"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["ptrET"] = *Pointeur_ET_C1;
                    }

                    if (*Pointeur_ET_C2 != config_SDP["generateur2"]["ptrET"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["ptrET"] = *Pointeur_ET_C2;
                    }

                    if (*Pointeur_ET_C3 != config_SDP["generateur3"]["ptrET"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur3"]["ptrET"] = *Pointeur_ET_C3;
                    }
                    // Générateur 1
                    if (*OPTION_CTRL_TETES_12 != config_SDP["generateur1"]["ctrlTete"].as<bool>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["ctrlTete"] = *OPTION_CTRL_TETES_12;
                    }

                    if (*OPTION_CTRL_FORME_ONDE_1 != config_SDP["generateur1"]["ctrlFO"].as<bool>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["ctrlFO"] = *OPTION_CTRL_FORME_ONDE_1;
                    }

                    if (*OPTION_DEFAUT_THERMIQUE_1 != config_SDP["generateur1"]["secuVigitherm"].as<bool>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["secuVigitherm"] = *OPTION_DEFAUT_THERMIQUE_1;
                    }

                    // Générateur 2
                    if (*OPTION_CTRL_TETES_34 != config_SDP["generateur2"]["ctrlTete"].as<bool>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["ctrlTete"] = *OPTION_CTRL_TETES_34;
                    }

                    if (*OPTION_CTRL_FORME_ONDE_2 != config_SDP["generateur2"]["ctrlFO"].as<bool>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["ctrlFO"] = *OPTION_CTRL_FORME_ONDE_2;
                    }

                    if (*OPTION_DEFAUT_THERMIQUE_2 != config_SDP["generateur2"]["secuVigitherm"].as<bool>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["secuVigitherm"] = *OPTION_DEFAUT_THERMIQUE_2;
                    }

                    // Puissance 2
                    if (*Pointeur_Puissance_2_C1 != config_SDP["generateur1"]["ptrPuissance2"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["ptrPuissance2"] = *Pointeur_Puissance_2_C1;
                    }

                    if (*Pointeur_Puissance_2_C2 != config_SDP["generateur2"]["ptrPuissance2"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["ptrPuissance2"] = *Pointeur_Puissance_2_C2;
                    }

                    if (*Pointeur_Puissance_2_C3 != config_SDP["generateur3"]["ptrPuissance2"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur3"]["ptrPuissance2"] = *Pointeur_Puissance_2_C3;
                    }

                    // Puissance 1
                    if (*Pointeur_Puissance_C1 != config_SDP["generateur1"]["ptrPuissance1"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["ptrPuissance1"] = *Pointeur_Puissance_C1;
                    }

                    if (*Pointeur_Puissance_C2 != config_SDP["generateur2"]["ptrPuissance1"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["ptrPuissance1"] = *Pointeur_Puissance_C2;
                    }

                    if (*Pointeur_Puissance_C3 != config_SDP["generateur3"]["ptrPuissance1"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur3"]["ptrPuissance1"] = *Pointeur_Puissance_C3;
                    }

                    // Temps
                    if (*Pointeur_Temps_C1 != config_SDP["generateur1"]["ptrTps"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["ptrTps"] = *Pointeur_Temps_C1;
                    }

                    if (*Pointeur_Temps_C2 != config_SDP["generateur2"]["ptrTps"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["ptrTps"] = *Pointeur_Temps_C2;
                    }

                    if (*Pointeur_Temps_C3 != config_SDP["generateur3"]["ptrTps"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur3"]["ptrTps"] = *Pointeur_Temps_C3;
                    }

                    // Mesure
                    if (*Pointeur_mesure_C1 != config_SDP["generateur1"]["ptrMesure"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["ptrMesure"] = *Pointeur_mesure_C1;
                    }

                    if (*Pointeur_mesure_C2 != config_SDP["generateur2"]["ptrMesure"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["ptrMesure"] = *Pointeur_mesure_C2;
                    }

                    if (*Pointeur_mesure_C3 != config_SDP["generateur3"]["ptrMesure"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur3"]["ptrMesure"] = *Pointeur_mesure_C3;
                    }

                    // Seuil CTRL BO
                    if (*Seuil_CTRL_BO_C1 != config_SDP["generateur1"]["seuilCtrlBO"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["seuilCtrlBO"] = *Seuil_CTRL_BO_C1;
                    }

                    if (*Seuil_CTRL_BO_C2 != config_SDP["generateur2"]["seuilCtrlBO"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["seuilCtrlBO"] = *Seuil_CTRL_BO_C2;
                    }

                    if (*Seuil_CTRL_BO_C3 != config_SDP["generateur3"]["seuilCtrlBO"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur3"]["seuilCtrlBO"] = *Seuil_CTRL_BO_C3;
                    }

                    // Nb valeurs stab mesure
                    if (*Nb_val_stab_mesure_C1 != config_SDP["generateur1"]["%stabMesure"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["%stabMesure"] = *Nb_val_stab_mesure_C1;
                    }

                    if (*Nb_val_stab_mesure_C2 != config_SDP["generateur2"]["%stabMesure"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["%stabMesure"] = *Nb_val_stab_mesure_C2;
                    }

                    if (*Nb_val_stab_mesure_C3 != config_SDP["generateur3"]["%stabMesure"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur3"]["%stabMesure"] = *Nb_val_stab_mesure_C3;
                    }

                    // FO
                    if (*Pointeur_FO_C1 != config_SDP["generateur1"]["ptrFO"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["ptrFO"] = *Pointeur_FO_C1;
                    }

                    if (*Pointeur_FO_C2 != config_SDP["generateur2"]["ptrFO"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["ptrFO"] = *Pointeur_FO_C2;
                    }

                    if (*Pointeur_FO_C3 != config_SDP["generateur3"]["ptrFO"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur3"]["ptrFO"] = *Pointeur_FO_C3;
                    }

                    // ET
                    if (*Pointeur_ET_C1 != config_SDP["generateur1"]["ptrET"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur1"]["ptrET"] = *Pointeur_ET_C1;
                    }

                    if (*Pointeur_ET_C2 != config_SDP["generateur2"]["ptrET"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur2"]["ptrET"] = *Pointeur_ET_C2;
                    }

                    if (*Pointeur_ET_C3 != config_SDP["generateur3"]["ptrET"].as<int>()) {
                        nb_modifications++;
                        config_SDP["generateur3"]["ptrET"] = *Pointeur_ET_C3;
                    }



          // ...............................................................................................                            
          // 3.Récupération des paramètres des banques
          // ...............................................................................................
                      // Générateur 1
                      for (int i = 0; i < 16; i++) {
                          if (*U_MIN_C1_B[i] != config_SDP["generateur1"]["banques"][banques_num[i]]["Umin"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur1"]["banques"][banques_num[i]]["Umin"] = *U_MIN_C1_B[i];
                          }

                          if (*U_MAX_C1_B[i] != config_SDP["generateur1"]["banques"][banques_num[i]]["Umax"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur1"]["banques"][banques_num[i]]["Umax"] = *U_MAX_C1_B[i];
                          }

                          if (*GP_C1_B[i] != config_SDP["generateur1"]["banques"][banques_num[i]]["GainP"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur1"]["banques"][banques_num[i]]["GainP"] = *GP_C1_B[i];
                          }

                          if (*I_MAX_C1_B[i] != config_SDP["generateur1"]["banques"][banques_num[i]]["ImaxREF"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur1"]["banques"][banques_num[i]]["ImaxREF"] = *I_MAX_C1_B[i];
                          }

                          if (*Seuil_mesure_I_C1_B[i] != config_SDP["generateur1"]["banques"][banques_num[i]]["seuilMesure"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur1"]["banques"][banques_num[i]]["seuilMesure"] = *Seuil_mesure_I_C1_B[i];
                          }

                          if (*KD_C1_B[i] != config_SDP["generateur1"]["banques"][banques_num[i]]["GainKD"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur1"]["banques"][banques_num[i]]["GainKD"] = *KD_C1_B[i];
                          }

                          if (*I_MAX_LU_C1_B[i] != config_SDP["generateur1"]["banques"][banques_num[i]]["ImaxLu"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur1"]["banques"][banques_num[i]]["ImaxLu"] = *I_MAX_LU_C1_B[i];
                          }

                          if (*ID_Fth_C1_B[i] != config_SDP["generateur1"]["banques"][banques_num[i]]["ID_Fth"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur1"]["banques"][banques_num[i]]["ID_Fth"] = *ID_Fth_C1_B[i];
                          }
                      }

                      // Générateur 2
                      for (int i = 0; i < 16; i++) {
                          if (*U_MIN_C2_B[i] != config_SDP["generateur2"]["banques"][banques_num[i]]["Umin"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur2"]["banques"][banques_num[i]]["Umin"] = *U_MIN_C2_B[i];
                          }

                          if (*U_MAX_C2_B[i] != config_SDP["generateur2"]["banques"][banques_num[i]]["Umax"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur2"]["banques"][banques_num[i]]["Umax"] = *U_MAX_C2_B[i];
                          }

                          if (*GP_C2_B[i] != config_SDP["generateur2"]["banques"][banques_num[i]]["GainP"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur2"]["banques"][banques_num[i]]["GainP"] = *GP_C2_B[i];
                          }

                          if (*I_MAX_C2_B[i] != config_SDP["generateur2"]["banques"][banques_num[i]]["ImaxREF"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur2"]["banques"][banques_num[i]]["ImaxREF"] = *I_MAX_C2_B[i];
                          }

                          if (*Seuil_mesure_I_C2_B[i] != config_SDP["generateur2"]["banques"][banques_num[i]]["seuilMesure"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur2"]["banques"][banques_num[i]]["seuilMesure"] = *Seuil_mesure_I_C2_B[i];
                          }

                          if (*KD_C2_B[i] != config_SDP["generateur2"]["banques"][banques_num[i]]["GainKD"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur2"]["banques"][banques_num[i]]["GainKD"] = *KD_C2_B[i];
                          }

                          if (*I_MAX_LU_C2_B[i] != config_SDP["generateur2"]["banques"][banques_num[i]]["ImaxLu"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur2"]["banques"][banques_num[i]]["ImaxLu"] = *I_MAX_LU_C2_B[i];
                          }

                          if (*ID_Fth_C2_B[i] != config_SDP["generateur2"]["banques"][banques_num[i]]["ID_Fth"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur2"]["banques"][banques_num[i]]["ID_Fth"] = *ID_Fth_C2_B[i];
                          }
                      }

                      // Générateur 3
                      for (int i = 0; i < 16; i++) {
                          if (*U_MIN_C3_B[i] != config_SDP["generateur3"]["banques"][banques_num[i]]["Umin"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur3"]["banques"][banques_num[i]]["Umin"] = *U_MIN_C3_B[i];
                          }

                          if (*U_MAX_C3_B[i] != config_SDP["generateur3"]["banques"][banques_num[i]]["Umax"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur3"]["banques"][banques_num[i]]["Umax"] = *U_MAX_C3_B[i];
                          }

                          if (*GP_C3_B[i] != config_SDP["generateur3"]["banques"][banques_num[i]]["GainP"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur3"]["banques"][banques_num[i]]["GainP"] = *GP_C3_B[i];
                          }

                          if (*I_MAX_C3_B[i] != config_SDP["generateur3"]["banques"][banques_num[i]]["ImaxREF"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur3"]["banques"][banques_num[i]]["ImaxREF"] = *I_MAX_C3_B[i];
                          }

                          if (*Seuil_mesure_I_C3_B[i] != config_SDP["generateur3"]["banques"][banques_num[i]]["seuilMesure"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur3"]["banques"][banques_num[i]]["seuilMesure"] = *Seuil_mesure_I_C3_B[i];
                          }

                          if (*KD_C3_B[i] != config_SDP["generateur3"]["banques"][banques_num[i]]["GainKD"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur3"]["banques"][banques_num[i]]["GainKD"] = *KD_C3_B[i];
                          }

                          if (*I_MAX_LU_C3_B[i] != config_SDP["generateur3"]["banques"][banques_num[i]]["ImaxLu"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur3"]["banques"][banques_num[i]]["ImaxLu"] = *I_MAX_LU_C3_B[i];
                          }

                          if (*ID_Fth_C3_B[i] != config_SDP["generateur3"]["banques"][banques_num[i]]["ID_Fth"].as<int>()) {
                              nb_modifications++;
                              config_SDP["generateur3"]["banques"][banques_num[i]]["ID_Fth"] = *ID_Fth_C3_B[i];
                          }
                      }
          // ...............................................................................................                            
          // 4.Récupération des paramètres de facteur thermmique
          // ...............................................................................................                      
                          // Générateur 1 - Intensités thermiques
                          if (*I_thermique_N_C1[0] != config_SDP["dataFth"]["G1"]["ID_0"]["Ith"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G1"]["ID_0"]["Ith"] = *I_thermique_N_C1[0];
                          }

                          if (*I_thermique_N_C1[1] != config_SDP["dataFth"]["G1"]["ID_1"]["Ith"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G1"]["ID_1"]["Ith"] = *I_thermique_N_C1[1];
                          }

                          if (*I_thermique_N_C1[2] != config_SDP["dataFth"]["G1"]["ID_2"]["Ith"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G1"]["ID_2"]["Ith"] = *I_thermique_N_C1[2];
                          }

                          if (*I_thermique_N_C1[3] != config_SDP["dataFth"]["G1"]["ID_3"]["Ith"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G1"]["ID_3"]["Ith"] = *I_thermique_N_C1[3];
                          }

                          // Générateur 1 - Périodes
                          if (*Periode_Fth_N_C1[0] != config_SDP["dataFth"]["G1"]["ID_0"]["periode"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G1"]["ID_0"]["periode"] = *Periode_Fth_N_C1[0];
                          }

                          if (*Periode_Fth_N_C1[1] != config_SDP["dataFth"]["G1"]["ID_1"]["periode"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G1"]["ID_1"]["periode"] = *Periode_Fth_N_C1[1];
                          }

                          if (*Periode_Fth_N_C1[2] != config_SDP["dataFth"]["G1"]["ID_2"]["periode"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G1"]["ID_2"]["periode"] = *Periode_Fth_N_C1[2];
                          }

                          if (*Periode_Fth_N_C1[3] != config_SDP["dataFth"]["G1"]["ID_3"]["periode"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G1"]["ID_3"]["periode"] = *Periode_Fth_N_C1[3];
                          }

                          // Générateur 2 - Intensités thermiques
                          if (*I_thermique_N_C2[0] != config_SDP["dataFth"]["G2"]["ID_0"]["Ith"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G2"]["ID_0"]["Ith"] = *I_thermique_N_C2[0];
                          }

                          if (*I_thermique_N_C2[1] != config_SDP["dataFth"]["G2"]["ID_1"]["Ith"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G2"]["ID_1"]["Ith"] = *I_thermique_N_C2[1];
                          }

                          if (*I_thermique_N_C2[2] != config_SDP["dataFth"]["G2"]["ID_2"]["Ith"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G2"]["ID_2"]["Ith"] = *I_thermique_N_C2[2];
                          }

                          if (*I_thermique_N_C2[3] != config_SDP["dataFth"]["G2"]["ID_3"]["Ith"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G2"]["ID_3"]["Ith"] = *I_thermique_N_C2[3];
                          }

                          // Générateur 2 - Périodes
                          if (*Periode_Fth_N_C2[0] != config_SDP["dataFth"]["G2"]["ID_0"]["periode"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G2"]["ID_0"]["periode"] = *Periode_Fth_N_C2[0];
                          }

                          if (*Periode_Fth_N_C2[1] != config_SDP["dataFth"]["G2"]["ID_1"]["periode"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G2"]["ID_1"]["periode"] = *Periode_Fth_N_C2[1];
                          }

                          if (*Periode_Fth_N_C2[2] != config_SDP["dataFth"]["G2"]["ID_2"]["periode"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G2"]["ID_2"]["periode"] = *Periode_Fth_N_C2[2];
                          }

                          if (*Periode_Fth_N_C2[3] != config_SDP["dataFth"]["G2"]["ID_3"]["periode"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G2"]["ID_3"]["periode"] = *Periode_Fth_N_C2[3];
                          }

                          // Générateur 3 - Intensités thermiques
                          if (*I_thermique_N_C3[0] != config_SDP["dataFth"]["G3"]["ID_0"]["Ith"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G3"]["ID_0"]["Ith"] = *I_thermique_N_C3[0];
                          }

                          if (*I_thermique_N_C3[1] != config_SDP["dataFth"]["G3"]["ID_1"]["Ith"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G3"]["ID_1"]["Ith"] = *I_thermique_N_C3[1];
                          }

                          if (*I_thermique_N_C3[2] != config_SDP["dataFth"]["G3"]["ID_2"]["Ith"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G3"]["ID_2"]["Ith"] = *I_thermique_N_C3[2];
                          }

                          if (*I_thermique_N_C3[3] != config_SDP["dataFth"]["G3"]["ID_3"]["Ith"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G3"]["ID_3"]["Ith"] = *I_thermique_N_C3[3];
                          }

                          // Générateur 3 - Périodes
                          if (*Periode_Fth_N_C3[0] != config_SDP["dataFth"]["G3"]["ID_0"]["periode"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G3"]["ID_0"]["periode"] = *Periode_Fth_N_C3[0];
                          }

                          if (*Periode_Fth_N_C3[1] != config_SDP["dataFth"]["G3"]["ID_1"]["periode"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G3"]["ID_1"]["periode"] = *Periode_Fth_N_C3[1];
                          }

                          if (*Periode_Fth_N_C3[2] != config_SDP["dataFth"]["G3"]["ID_2"]["periode"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G3"]["ID_2"]["periode"] = *Periode_Fth_N_C3[2];
                          }

                          if (*Periode_Fth_N_C3[3] != config_SDP["dataFth"]["G3"]["ID_3"]["periode"].as<int>()) {
                              nb_modifications++;
                              config_SDP["dataFth"]["G3"]["ID_3"]["periode"] = *Periode_Fth_N_C3[3];
                          }
          // ...............................................................................................                            
          // 5.Récupération des paramètres de config Mesure
          // ...............................................................................................                           

                          if (*GAIN_V1 != config_SDP["configMesures"]["Mesure_1"]["Gain"].as<int>()) {
                              nb_modifications++;
                              config_SDP["configMesures"]["Mesure_1"]["Gain"] = *GAIN_V1;
                          }

                          if (*GAIN_V2 != config_SDP["configMesures"]["Mesure_2"]["Gain"].as<int>()) {
                              nb_modifications++;
                              config_SDP["configMesures"]["Mesure_2"]["Gain"] = *GAIN_V2;
                          }

                          if (*GAIN_V3 != config_SDP["configMesures"]["Mesure_3"]["Gain"].as<int>()) {
                              nb_modifications++;
                              config_SDP["configMesures"]["Mesure_3"]["Gain"] = *GAIN_V3;
                          }

                          if (*GAIN_V4 != config_SDP["configMesures"]["Mesure_4"]["Gain"].as<int>()) {
                              nb_modifications++;
                              config_SDP["configMesures"]["Mesure_4"]["Gain"] = *GAIN_V4;
                          }

                          if (*GAIN_V5 != config_SDP["configMesures"]["Mesure_5"]["Gain"].as<int>()) {
                              nb_modifications++;
                              config_SDP["configMesures"]["Mesure_5"]["Gain"] = *GAIN_V5;
                          }

                          if (*GAIN_V6 != config_SDP["configMesures"]["Mesure_6"]["Gain"].as<int>()) {
                              nb_modifications++;
                              config_SDP["configMesures"]["Mesure_6"]["Gain"] = *GAIN_V6;
                          }

                          if (*OFFSET_DYN_V1 != config_SDP["configMesures"]["Mesure_1"]["type"].as<int>()){
                            nb_modifications++;
                            config_SDP["configMesures"]["Mesure_1"]["type"] = *OFFSET_DYN_V1;
                          } 

                          if (*OFFSET_DYN_V2 != config_SDP["configMesures"]["Mesure_2"]["type"].as<int>()){
                            nb_modifications++;
                            config_SDP["configMesures"]["Mesure_2"]["type"] = *OFFSET_DYN_V2;
                          } 

                          if (*OFFSET_DYN_V3 != config_SDP["configMesures"]["Mesure_3"]["type"].as<int>()){
                            nb_modifications++;
                            config_SDP["configMesures"]["Mesure_3"]["type"] = *OFFSET_DYN_V3;
                          } 

                          if (*OFFSET_DYN_V4 != config_SDP["configMesures"]["Mesure_4"]["type"].as<int>()){
                            nb_modifications++;
                            config_SDP["configMesures"]["Mesure_4"]["type"] = *OFFSET_DYN_V4;
                          }  

                          if (*OFFSET_DYN_V5 != config_SDP["configMesures"]["Mesure_5"]["type"].as<int>()){
                            nb_modifications++;
                            config_SDP["configMesures"]["Mesure_5"]["type"] = *OFFSET_DYN_V5;
                          } 

                          if (*OFFSET_DYN_V6 != config_SDP["configMesures"]["Mesure_6"]["type"].as<int>()){
                            nb_modifications++;
                            config_SDP["configMesures"]["Mesure_6"]["type"] = *OFFSET_DYN_V6;
                          } 

                      
                      offset_actuel = rebuild_float(*OFFSET_MSB_V1, *OFFSET_LSB_V1);

                      if (offset_actuel != config_SDP["configMesures"]["Mesure_1"]["Offset"].as<float>()){
                            nb_modifications++;
                            config_SDP["configMesures"]["Mesure_1"]["Offset"] = offset_actuel;
                      } 

                      offset_actuel = rebuild_float(*OFFSET_MSB_V2, *OFFSET_LSB_V2);

                      if (offset_actuel != config_SDP["configMesures"]["Mesure_2"]["Offset"].as<float>()){
                            nb_modifications++;
                            config_SDP["configMesures"]["Mesure_2"]["Offset"] = offset_actuel;
                      }

                      offset_actuel = rebuild_float(*OFFSET_MSB_V3, *OFFSET_LSB_V2);

                      if (offset_actuel != config_SDP["configMesures"]["Mesure_3"]["Offset"].as<float>()){
                            nb_modifications++;
                            config_SDP["configMesures"]["Mesure_3"]["Offset"] = offset_actuel;
                      } 

                      offset_actuel = rebuild_float(*OFFSET_MSB_V4, *OFFSET_LSB_V4);

                      if (offset_actuel != config_SDP["configMesures"]["Mesure_4"]["Offset"].as<float>()){
                            nb_modifications++;
                            config_SDP["configMesures"]["Mesure_4"]["Offset"] = offset_actuel;
                      }

                      offset_actuel = rebuild_float(*OFFSET_MSB_V5, *OFFSET_LSB_V5);

                      if (offset_actuel != config_SDP["configMesures"]["Mesure_5"]["Offset"].as<float>()){
                            nb_modifications++;
                            config_SDP["configMesures"]["Mesure_5"]["Offset"] = offset_actuel;
                      } 

                      offset_actuel = rebuild_float(*OFFSET_MSB_V6, *OFFSET_LSB_V6);

                      if (offset_actuel != config_SDP["configMesures"]["Mesure_6"]["Offset"].as<float>()){
                            nb_modifications++;
                            config_SDP["configMesures"]["Mesure_6"]["Offset"] = offset_actuel;
                      }

          // ...............................................................................................                            
          // 6. Récupération étalonnage capteurs
          // ............................................................................................... 
          for (int i = 0; i < 16; i++) {
                if (*Etalonnage_X1_B[i] != config_SDP["Etalonnage"]["X1"][banques_etalonnage[i]].as<int>()) {
                    nb_modifications++;
                    config_SDP["Etalonnage"]["X1"][banques_etalonnage[i]] = *Etalonnage_X1_B[i];
                }

                if (*Etalonnage_Y1_B[i] != config_SDP["Etalonnage"]["Y1"][banques_etalonnage[i]].as<int>()) {
                    nb_modifications++;
                    config_SDP["Etalonnage"]["Y1"][banques_etalonnage[i]] = *Etalonnage_Y1_B[i];
                }

                if (*Etalonnage_X2_B[i] != config_SDP["Etalonnage"]["X2"][banques_etalonnage[i]].as<int>()) {
                    nb_modifications++;
                    config_SDP["Etalonnage"]["X2"][banques_etalonnage[i]] = *Etalonnage_X2_B[i];
                }

                if (*Etalonnage_Y2_B[i] != config_SDP["Etalonnage"]["Y2"][banques_etalonnage[i]].as<int>()) {
                    nb_modifications++;
                    config_SDP["Etalonnage"]["Y2"][banques_etalonnage[i]] = *Etalonnage_Y2_B[i];
                }
            }

            if (*Seuil_Ctrl_Temperature != config_SDP["Etalonnage"]["Seuil_Ctrl_Temperature"].as<int>()) {
                nb_modifications++;
                config_SDP["Etalonnage"]["Seuil_Ctrl_Temperature"] = *Seuil_Ctrl_Temperature;
            }
          // ............................................................................................... 
          // Ecriture si modification
          // ...............................................................................................
          if (nb_modifications > 0) {

              // Ouvrir un fichier temporaire en écriture
              File fileTmp = SD.open("/parametres_tmp.json", FILE_WRITE);
              if (!fileTmp) {
                  *WRITE_CONFIG = 0;
              } else {
                  fileTmp.seek(0); // commencer au début
                  n = serializeJsonPretty(config_SDP, fileTmp);

                  fileTmp.flush();
                  fileTmp.close();

                  if (n == 0) {
                      *WRITE_CONFIG = 0;
                      SD.remove("/parametres_tmp.json"); // supprimer le temporaire si erreur
                  } else {
                      *WRITE_CONFIG = 1;

                      // Remplacer l’ancien fichier par le nouveau
                      SD.remove("/parametres.json"); // supprimer l’original
                      SD.rename("/parametres_tmp.json", "/parametres.json"); // renommer le temporaire

                      // Debug
                      globalData[5] = nb_modifications;

                      // Actions après chargement
                      ActionChargModif(D_Types_Capteurs);
                      ActionChargModif(D_Temps_Pb_puissance);
                      ActionChargModif(D_Pointeur_mesure_C[1]);
                      ActionChargModif(D_Pointeur_mesure_C[2]);
                      ActionChargModif(D_Pointeur_mesure_C[3]);
                      ActionChargModif(D_Periode_Fth);
                      ActionChargModif(D_I_thermique_C[1]);
                      ActionChargModif(D_I_thermique_C[2]);
                      ActionChargModif(D_Etalonnage_X1);
                      ActionChargModif(D_Etalonnage_X2);
                      ActionChargModif(D_Etalonnage_Y1);
                      ActionChargModif(D_Etalonnage_Y2);
                      ActionChargModif(D_Seuil_Ctrl_Temperature);
                  }
              }
          }


          // ...............................................................................................

          if(nb_modifications == 65530){
              nb_modifications = 0;
          }
                     
                      
      } // endif déserialisation 
    
    }else{  

      *READ_SD = 0;  // Echecs de l'ouverture du fichier de paramètres 

    }  // endif SD.open 

    writeDataFth();
      
  } // endif mode : loop
  else if (strcmp(mode, "wifi") == 0){

      // ................................................................................
    // 1. Préparation des données : 
    // ................................................................................
          // ...............................................................................................
          // a. Récupération paramètres  généraux
          // ...............................................................................................
                      config_SDP["general"]["typesCapteurs"] = *Types_Capteurs;
                      config_SDP["general"]["typesCapteursSup"] = *Types_Capteurs_Sup;
                      config_SDP["general"]["ptrDCY"] = *Pointeur_DCY;
                      config_SDP["general"]["ptrACY"] = *Pointeur_ACY;
                      config_SDP["general"]["ptrACQ"] = *Pointeur_ACQ;
                      config_SDP["general"]["ptrDEMAG"] = *Pointeur_DEMAG;
                      config_SDP["general"]["ptrTORS1"] = *Pointeur_TOR_S1;
                      config_SDP["general"]["ptrTORS2"] = *Pointeur_TOR_S2;
                      config_SDP["general"]["ptrTORS3"] = *Pointeur_TOR_S3;
                      config_SDP["general"]["ptrTORS4"] = *Pointeur_TOR_S4;
                      config_SDP["general"]["%stabRegul"] = *COEF_CONE_TUBE;
                      config_SDP["general"]["%gainBoost"] = *Gain_BOOST;
                      config_SDP["general"]["tpsPbPuissance"] = *Temps_Pb_puissance;
                  
                      config_SDP["general"]["doubleAffichage"] = *OPTION_DOUBLE_AFFICHAGE;

                      config_SDP["general"]["sensModeCombine"].as<bool>();
                   
                      config_SDP["general"]["pasPotard0.5"].as<bool>();

                      config_SDP["general"]["repos4sGT"].as<bool>();
          // ...............................................................................................
          // b. Récupération paramètres  générateur
          // ...............................................................................................
                    // Générateur 1
                      config_SDP["generateur1"]["ctrlTete"] = *OPTION_CTRL_TETES_12;
                      config_SDP["generateur1"]["ctrlFO"] = *OPTION_CTRL_FORME_ONDE_1;
                      config_SDP["generateur1"]["secuVigitherm"] = *OPTION_DEFAUT_THERMIQUE_1;

                    // Générateur 2
                      config_SDP["generateur2"]["ctrlTete"] = *OPTION_CTRL_TETES_34;
                      config_SDP["generateur2"]["ctrlFO"] = *OPTION_CTRL_FORME_ONDE_2;
                      config_SDP["generateur2"]["secuVigitherm"] = *OPTION_DEFAUT_THERMIQUE_2;

                    // Puissance 2
                      config_SDP["generateur1"]["ptrPuissance2"] = *Pointeur_Puissance_2_C1;
                      config_SDP["generateur2"]["ptrPuissance2"] = *Pointeur_Puissance_2_C2;
                      config_SDP["generateur3"]["ptrPuissance2"] = *Pointeur_Puissance_2_C3;

                    // Puissance 1

                        config_SDP["generateur1"]["ptrPuissance1"] = *Pointeur_Puissance_C1;
                        config_SDP["generateur2"]["ptrPuissance1"] = *Pointeur_Puissance_C2;
                        config_SDP["generateur3"]["ptrPuissance1"] = *Pointeur_Puissance_C3;

                    // Temps
                        config_SDP["generateur1"]["ptrTps"] = *Pointeur_Temps_C1;
                        config_SDP["generateur2"]["ptrTps"] = *Pointeur_Temps_C2;
                        config_SDP["generateur3"]["ptrTps"] = *Pointeur_Temps_C3;


                    // Mesure
                        config_SDP["generateur1"]["ptrMesure"] = *Pointeur_mesure_C1;
                        config_SDP["generateur2"]["ptrMesure"] = *Pointeur_mesure_C2;
                        config_SDP["generateur3"]["ptrMesure"] = *Pointeur_mesure_C3;                                        

                    // Seuil CTRL BO
                        config_SDP["generateur1"]["seuilCtrlBO"] = *Seuil_CTRL_BO_C1;
                        config_SDP["generateur2"]["seuilCtrlBO"] = *Seuil_CTRL_BO_C2;                        
                        config_SDP["generateur3"]["seuilCtrlBO"] = *Seuil_CTRL_BO_C3;

                    // Nb valeurs stab mesure
                        config_SDP["generateur1"]["%stabMesure"] = *Nb_val_stab_mesure_C1;
                        config_SDP["generateur2"]["%stabMesure"] = *Nb_val_stab_mesure_C2;
                        config_SDP["generateur3"]["%stabMesure"] = *Nb_val_stab_mesure_C3;


                    // FO
                        config_SDP["generateur1"]["ptrFO"] = *Pointeur_FO_C1;
                        config_SDP["generateur2"]["ptrFO"] = *Pointeur_FO_C2;
                        config_SDP["generateur3"]["ptrFO"] = *Pointeur_FO_C3;

                    // ET
                        config_SDP["generateur1"]["ptrET"] = *Pointeur_ET_C1;
                        config_SDP["generateur2"]["ptrET"] = *Pointeur_ET_C2;
                        config_SDP["generateur3"]["ptrET"] = *Pointeur_ET_C3;

          // ...............................................................................................                            
          // c.Récupération des paramètres des banques
          // ...............................................................................................
                      // Générateur 1
                      for (int i = 0; i < 16; i++) {
                              config_SDP["generateur1"]["banques"][banques_num[i]]["Umin"] = *U_MIN_C1_B[i];
                              config_SDP["generateur1"]["banques"][banques_num[i]]["Umax"] = *U_MAX_C1_B[i];
                              config_SDP["generateur1"]["banques"][banques_num[i]]["GainP"] = *GP_C1_B[i];
                              config_SDP["generateur1"]["banques"][banques_num[i]]["ImaxREF"] = *I_MAX_C1_B[i];
                              config_SDP["generateur1"]["banques"][banques_num[i]]["seuilMesure"] = *Seuil_mesure_I_C1_B[i];
                              config_SDP["generateur1"]["banques"][banques_num[i]]["GainKD"] = *KD_C1_B[i];
                              config_SDP["generateur1"]["banques"][banques_num[i]]["ImaxLu"] = *I_MAX_LU_C1_B[i];
                              config_SDP["generateur1"]["banques"][banques_num[i]]["ID_Fth"] = *ID_Fth_C1_B[i];
                      }
                      // Générateur 2
                      for (int i = 0; i < 16; i++) {
                              config_SDP["generateur2"]["banques"][banques_num[i]]["Umin"] = *U_MIN_C2_B[i];
                              config_SDP["generateur2"]["banques"][banques_num[i]]["Umax"] = *U_MAX_C2_B[i];
                              config_SDP["generateur2"]["banques"][banques_num[i]]["GainP"] = *GP_C2_B[i];
                              config_SDP["generateur2"]["banques"][banques_num[i]]["ImaxREF"] = *I_MAX_C2_B[i];
                              config_SDP["generateur2"]["banques"][banques_num[i]]["seuilMesure"] = *Seuil_mesure_I_C2_B[i];
                              config_SDP["generateur2"]["banques"][banques_num[i]]["GainKD"] = *KD_C2_B[i];
                              config_SDP["generateur2"]["banques"][banques_num[i]]["ImaxLu"] = *I_MAX_LU_C2_B[i];
                              config_SDP["generateur2"]["banques"][banques_num[i]]["ID_Fth"] = *ID_Fth_C2_B[i];
                      }

                      // Générateur 3
                      for (int i = 0; i < 16; i++) {
                              config_SDP["generateur3"]["banques"][banques_num[i]]["Umin"] = *U_MIN_C3_B[i];
                              config_SDP["generateur3"]["banques"][banques_num[i]]["Umax"] = *U_MAX_C3_B[i];
                              config_SDP["generateur3"]["banques"][banques_num[i]]["GainP"] = *GP_C3_B[i];
                              config_SDP["generateur3"]["banques"][banques_num[i]]["ImaxREF"] = *I_MAX_C3_B[i];
                              config_SDP["generateur3"]["banques"][banques_num[i]]["seuilMesure"] = *Seuil_mesure_I_C3_B[i];
                              config_SDP["generateur3"]["banques"][banques_num[i]]["GainKD"] = *KD_C3_B[i];
                              config_SDP["generateur3"]["banques"][banques_num[i]]["ImaxLu"] = *I_MAX_LU_C3_B[i];
                              config_SDP["generateur3"]["banques"][banques_num[i]]["ID_Fth"] = *ID_Fth_C3_B[i];
                      }
          // ...............................................................................................                            
          // d.Récupération des paramètres de facteur thermmique
          // ...............................................................................................                      
                          // Générateur 1 - Intensités thermiques
                              config_SDP["dataFth"]["G1"]["ID_0"]["Ith"] = *I_thermique_N_C1[0];
                              config_SDP["dataFth"]["G1"]["ID_1"]["Ith"] = *I_thermique_N_C1[1];
                              config_SDP["dataFth"]["G1"]["ID_2"]["Ith"] = *I_thermique_N_C1[2];
                              config_SDP["dataFth"]["G1"]["ID_3"]["Ith"] = *I_thermique_N_C1[3];
                              config_SDP["dataFth"]["G1"]["ID_0"]["periode"] = *Periode_Fth_N_C1[0];
                              config_SDP["dataFth"]["G1"]["ID_1"]["periode"] = *Periode_Fth_N_C1[1];
                              config_SDP["dataFth"]["G1"]["ID_2"]["periode"] = *Periode_Fth_N_C1[2];
                              config_SDP["dataFth"]["G1"]["ID_3"]["periode"] = *Periode_Fth_N_C1[3];
                              config_SDP["dataFth"]["G2"]["ID_0"]["Ith"] = *I_thermique_N_C2[0];
                              config_SDP["dataFth"]["G2"]["ID_1"]["Ith"] = *I_thermique_N_C2[1];
                              config_SDP["dataFth"]["G2"]["ID_2"]["Ith"] = *I_thermique_N_C2[2];
                              config_SDP["dataFth"]["G2"]["ID_3"]["Ith"] = *I_thermique_N_C2[3];
                              config_SDP["dataFth"]["G2"]["ID_0"]["periode"] = *Periode_Fth_N_C2[0];
                              config_SDP["dataFth"]["G2"]["ID_1"]["periode"] = *Periode_Fth_N_C2[1];
                              config_SDP["dataFth"]["G2"]["ID_2"]["periode"] = *Periode_Fth_N_C2[2];
                              config_SDP["dataFth"]["G2"]["ID_3"]["periode"] = *Periode_Fth_N_C2[3];

                          // Générateur 3 - Intensités thermiques
                              config_SDP["dataFth"]["G3"]["ID_0"]["Ith"] = *I_thermique_N_C3[0];
                              config_SDP["dataFth"]["G3"]["ID_1"]["Ith"] = *I_thermique_N_C3[1];
                              config_SDP["dataFth"]["G3"]["ID_2"]["Ith"] = *I_thermique_N_C3[2];
                              config_SDP["dataFth"]["G3"]["ID_3"]["Ith"] = *I_thermique_N_C3[3];
                              config_SDP["dataFth"]["G3"]["ID_0"]["periode"] = *Periode_Fth_N_C3[0];
                              config_SDP["dataFth"]["G3"]["ID_1"]["periode"] = *Periode_Fth_N_C3[1];
                              config_SDP["dataFth"]["G3"]["ID_2"]["periode"] = *Periode_Fth_N_C3[2];
                              config_SDP["dataFth"]["G3"]["ID_3"]["periode"] = *Periode_Fth_N_C3[3];
          // ...............................................................................................                            
          // e.Récupération des paramètres de config Mesure
          // ...............................................................................................                           
                              config_SDP["configMesures"]["Mesure_1"]["Gain"] = *GAIN_V1;
                              config_SDP["configMesures"]["Mesure_2"]["Gain"] = *GAIN_V2;
                              config_SDP["configMesures"]["Mesure_3"]["Gain"] = *GAIN_V3;
                              config_SDP["configMesures"]["Mesure_4"]["Gain"] = *GAIN_V4;
                              config_SDP["configMesures"]["Mesure_5"]["Gain"] = *GAIN_V5;
                              config_SDP["configMesures"]["Mesure_6"]["Gain"] = *GAIN_V6;
                              config_SDP["configMesures"]["Mesure_1"]["type"] = *OFFSET_DYN_V1;
                              config_SDP["configMesures"]["Mesure_2"]["type"] = *OFFSET_DYN_V2;
                              config_SDP["configMesures"]["Mesure_3"]["type"] = *OFFSET_DYN_V3;
                              config_SDP["configMesures"]["Mesure_4"]["type"] = *OFFSET_DYN_V4;
                              config_SDP["configMesures"]["Mesure_5"]["type"] = *OFFSET_DYN_V5;
                              config_SDP["configMesures"]["Mesure_6"]["type"] = *OFFSET_DYN_V6;

                      
                      offset_actuel = rebuild_float(*OFFSET_MSB_V1, *OFFSET_LSB_V1);
                            config_SDP["configMesures"]["Mesure_1"]["Offset"] = offset_actuel;

                      offset_actuel = rebuild_float(*OFFSET_MSB_V2, *OFFSET_LSB_V2);

                            config_SDP["configMesures"]["Mesure_2"]["Offset"] = offset_actuel;

                      offset_actuel = rebuild_float(*OFFSET_MSB_V3, *OFFSET_LSB_V2);

                            config_SDP["configMesures"]["Mesure_3"]["Offset"] = offset_actuel;

                      offset_actuel = rebuild_float(*OFFSET_MSB_V4, *OFFSET_LSB_V4);

                            config_SDP["configMesures"]["Mesure_4"]["Offset"] = offset_actuel;

                      offset_actuel = rebuild_float(*OFFSET_MSB_V5, *OFFSET_LSB_V5);

                            config_SDP["configMesures"]["Mesure_5"]["Offset"] = offset_actuel;

                      offset_actuel = rebuild_float(*OFFSET_MSB_V6, *OFFSET_LSB_V6);

                            config_SDP["configMesures"]["Mesure_6"]["Offset"] = offset_actuel;
          // ...............................................................................................                            
          // f. Récupération étalonnage capteurs
          // ............................................................................................... 
          for (int i = 0; i < 16; i++) {
                    config_SDP["Etalonnage"]["X1"][banques_etalonnage[i]] = *Etalonnage_X1_B[i];
                    config_SDP["Etalonnage"]["Y1"][banques_etalonnage[i]] = *Etalonnage_Y1_B[i];
                    config_SDP["Etalonnage"]["X2"][banques_etalonnage[i]] = *Etalonnage_X2_B[i];
                    config_SDP["Etalonnage"]["Y2"][banques_etalonnage[i]] = *Etalonnage_Y2_B[i];
          }
                config_SDP["Etalonnage"]["Seuil_Ctrl_Temperature"] = *Seuil_Ctrl_Temperature;
                
          // .................................................................................................
          // g. Affectation des données de la banque en cours 
          // .................................................................................................
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


                  // Récupération des paramètres de facteur thermique en fonction de l'ID
                  *Periode_Fth_C3 = *Periode_Fth_N_C3[*ID_FTH_C3]; 
                  *I_thermique_C3 =  *I_thermique_N_C3[*ID_FTH_C3] ;


                  // Récupération des paramètres de facteur thermique en fonction de l'ID
                  *Periode_Fth_C2 = *Periode_Fth_N_C2[*ID_FTH_C2]; 
                  *I_thermique_C2 =  *I_thermique_N_C2[*ID_FTH_C2] ;


                  // Récupération des paramètres de facteur thermique en fonction de l'ID
                  *Periode_Fth = *Periode_Fth_N_C1[*ID_FTH_C1]; 
                  *I_thermique_C1 =  *I_thermique_N_C1[*ID_FTH_C1] ;

             // .................................................................................................


    // ................................................................................
    // 2. Ecriture 
    // ................................................................................

              // Ouvrir un fichier temporaire en écriture
              File fileTmp = SD.open("/parametres_tmp.json", FILE_WRITE);
              if (!fileTmp) {
                  *WRITE_CONFIG = 0;
              } else {
                  fileTmp.seek(0); // commencer au début
                  n = serializeJsonPretty(config_SDP, fileTmp);

                  fileTmp.flush();
                  fileTmp.close();

                  if (n == 0) {
                      *WRITE_CONFIG = 0;
                      SD.remove("/parametres_tmp.json"); // supprimer le temporaire si erreur
                  } else {
                      *WRITE_CONFIG = 1;

                      // Remplacer l’ancien fichier par le nouveau
                      SD.remove("/parametres.json"); // supprimer l’original
                      SD.rename("/parametres_tmp.json", "/parametres.json"); // renommer le temporaire


                      // Actions après chargement
                      ActionChargModif(D_Types_Capteurs);
                      ActionChargModif(D_Temps_Pb_puissance);
                      ActionChargModif(D_Pointeur_mesure_C[1]);
                      ActionChargModif(D_Pointeur_mesure_C[2]);
                      ActionChargModif(D_Pointeur_mesure_C[3]);
                      ActionChargModif(D_Periode_Fth);
                      ActionChargModif(D_I_thermique_C[1]);
                      ActionChargModif(D_I_thermique_C[2]);
                      ActionChargModif(D_Etalonnage_X1);
                      ActionChargModif(D_Etalonnage_X2);
                      ActionChargModif(D_Etalonnage_Y1);
                      ActionChargModif(D_Etalonnage_Y2);
                      ActionChargModif(D_Seuil_Ctrl_Temperature);
                  }
              }

  }
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

 xSemaphoreGive(spiMutex);
}
// .........................................................................................................................
// Récupération données du fichier binaire (calcul Fth après redémarrage)
// .........................................................................................................................
void recupCalculFth(){

    // Prendre le mutex SPI uniquement pour la durée de l'accès SD
    xSemaphoreTake(spiMutex, portMAX_DELAY);
    
   File dataFth_bin = SD.open("/data.bin", FILE_READ);

    if (dataFth_bin) {

      M()[307] = 1;                                               // Lecture fichier OK 

        // Vérification de la taille totale nécessaire
        size_t needSize = sizeof(Integral_Tab_C1) +
                          sizeof(Integral_Tab_C2) +
                          sizeof(Integral_Tab_C3);

        if (dataFth_bin.size() >= needSize) {

            // Lecture avec vérification
            bool ok = true;
            ok &= (dataFth_bin.read((uint8_t*)Integral_Tab_C1, sizeof(Integral_Tab_C1)) == sizeof(Integral_Tab_C1));
            ok &= (dataFth_bin.read((uint8_t*)Integral_Tab_C2, sizeof(Integral_Tab_C2)) == sizeof(Integral_Tab_C2));
            ok &= (dataFth_bin.read((uint8_t*)Integral_Tab_C3, sizeof(Integral_Tab_C3)) == sizeof(Integral_Tab_C3));

            M()[310] = ok ? 1 : 0;                                // Correspondance taille fichier OK

        } else {
            // Fichier trop petit
            M()[310] = 0;
        }

        dataFth_bin.close();

    } else {
        // Impossible d'ouvrir le fichier
        M()[307] = 0;
    }

     xSemaphoreGive(spiMutex);
}
// .........................................................................................................................
// Récupération données du fichier JSON
// .........................................................................................................................
void recupConfigJsonV2(){

      M()[306] = 1;  // Succès de désérialisation du fichier de paramètres 

      // 1. Récupération paramètres  généraux
                  *Temps_Pb_puissance =         config_SDP["general"]["tpsPbPuissance"].as<int>();
                  *Periode_Fth        =         config_SDP["general"]["ptrCtrlFth"].as<int>();
                  *Gain_BOOST         =         config_SDP["general"]["%gainBoost"].as<int>();
                  *Pointeur_TOR_S1    =         config_SDP["general"]["ptrTORS1"].as<int>();
                  *Pointeur_TOR_S2    =         config_SDP["general"]["ptrTORS2"].as<int>();
                  *Pointeur_TOR_S3    =         config_SDP["general"]["ptrTORS3"].as<int>();
                  *Pointeur_TOR_S4    =         config_SDP["general"]["ptrTORS4"].as<int>();
                  *COEF_CONE_TUBE     =         config_SDP["general"]["%stabRegul"].as<int>();
                  *Types_Capteurs     =         config_SDP["general"]["typesCapteurs"].as<int>();
                  *Types_Capteurs_Sup  =        config_SDP["general"]["typesCapteursSup"].as<int>();
                  *Pointeur_ACQ       =         config_SDP["general"]["ptrACQ"].as<int>();
                  *Pointeur_DEMAG     =         config_SDP["general"]["ptrDEMAG"].as<int>();
                  *Pointeur_DCY       =         config_SDP["general"]["ptrDCY"].as<int>();
                  *Pointeur_ACY       =         config_SDP["general"]["ptrACY"].as<int>();
      // 2.Récupération des paramètres des générateurs 

                  *OPTION_CTRL_TETES_12 =                 config_SDP["generateur1"]["ctrlTete"].as<bool>();
                  *OPTION_CTRL_FORME_ONDE_1 =                 config_SDP["generateur1"]["ctrlFO"].as<bool>();
                  *OPTION_DEFAUT_THERMIQUE_1 =                 config_SDP["generateur1"]["secuVigitherm"].as<bool>();

                  *OPTION_CTRL_TETES_34 =                 config_SDP["generateur2"]["ctrlTete"].as<bool>();
                  *OPTION_CTRL_FORME_ONDE_2 =                 config_SDP["generateur2"]["ctrlFO"].as<bool>();
                  *OPTION_DEFAUT_THERMIQUE_2 =                 config_SDP["generateur2"]["secuVigitherm"].as<bool>();    

                  *I_thermique_C1 =                 config_SDP["generateur1"]["ptrIth"].as<int>();
                  *I_thermique_C2 =                 config_SDP["generateur2"]["ptrIth"].as<int>();
                  *I_thermique_C3 =                 config_SDP["generateur3"]["ptrIth"].as<int>();

                  *Pointeur_Puissance_2_C1 =        config_SDP["generateur1"]["ptrPuissance2"].as<int>();
                  *Pointeur_Puissance_2_C2 =        config_SDP["generateur2"]["ptrPuissance2"].as<int>();
                  *Pointeur_Puissance_2_C3 =        config_SDP["generateur3"]["ptrPuissance2"].as<int>();

                  *Pointeur_Puissance_C1 =          config_SDP["generateur1"]["ptrPuissance1"].as<int>(); 
                  *Pointeur_Puissance_C2 =          config_SDP["generateur2"]["ptrPuissance1"].as<int>();
                  *Pointeur_Puissance_C3 =          config_SDP["generateur3"]["ptrPuissance1"].as<int>();

                  *Pointeur_Temps_C1 =              config_SDP["generateur1"]["ptrTps"].as<int>();
                  *Pointeur_Temps_C2 =              config_SDP["generateur2"]["ptrTps"].as<int>();
                  *Pointeur_Temps_C3 =              config_SDP["generateur3"]["ptrTps"].as<int>();

                  *Pointeur_mesure_C1 =             config_SDP["generateur1"]["ptrMesure"].as<int>();
                  *Pointeur_mesure_C2 =             config_SDP["generateur2"]["ptrMesure"].as<int>();
                  *Pointeur_mesure_C3 =             config_SDP["generateur3"]["ptrMesure"].as<int>();

                  *Seuil_CTRL_BO_C1 =               config_SDP["generateur1"]["seuilCtrlBO"].as<int>();
                  *Seuil_CTRL_BO_C2 =               config_SDP["generateur2"]["seuilCtrlBO"].as<int>();
                  *Seuil_CTRL_BO_C3 =               config_SDP["generateur3"]["seuilCtrlBO"].as<int>();

                  *Nb_val_stab_mesure_C1 =          config_SDP["generateur1"]["%stabMesure"].as<int>();
                  *Nb_val_stab_mesure_C2 =          config_SDP["generateur2"]["%stabMesure"].as<int>();
                  *Nb_val_stab_mesure_C3 =          config_SDP["generateur3"]["%stabMesure"].as<int>();

                  *Pointeur_FO_C1 =                 config_SDP["generateur1"]["ptrFO"].as<int>();
                  *Pointeur_FO_C2 =                 config_SDP["generateur2"]["ptrFO"].as<int>();
                  *Pointeur_FO_C3 =                 config_SDP["generateur3"]["ptrFO"].as<int>();

                  *Pointeur_ET_C1 =                 config_SDP["generateur1"]["ptrET"].as<int>();
                  *Pointeur_ET_C2 =                 config_SDP["generateur2"]["ptrET"].as<int>();
                  *Pointeur_ET_C3 =                 config_SDP["generateur3"]["ptrET"].as<int>();


                  // 3. Récupération paramètres cycles (Générateur 1)
                  for (int i=0;i<16;i++){
                      *U_MIN_C1_B[i]           =  config_SDP["generateur1"]["banques"][banques_num[i]]["Umin"].as<int>();
                      *U_MAX_C1_B[i]           =  config_SDP["generateur1"]["banques"][banques_num[i]]["Umax"].as<int>();
                      *GP_C1_B[i]              =  config_SDP["generateur1"]["banques"][banques_num[i]]["GainP"].as<int>();
                      *I_MAX_C1_B[i]           =  config_SDP["generateur1"]["banques"][banques_num[i]]["ImaxREF"].as<int>();
                      *Seuil_mesure_I_C1_B[i]  =  config_SDP["generateur1"]["banques"][banques_num[i]]["seuilMesure"].as<int>();
                      *KD_C1_B[i]              =  config_SDP["generateur1"]["banques"][banques_num[i]]["GainKD"].as<int>();
                      *I_MAX_LU_C1_B[i]        =  config_SDP["generateur1"]["banques"][banques_num[i]]["ImaxLu"].as<int>(); 
                      *ID_Fth_C1_B[i]          =  config_SDP["generateur1"]["banques"][banques_num[i]]["ID_Fth"].as<int>(); 
                  }   

                  // 3. Récupération paramètres cycles (Générateur 2)
                  for (int i=0;i<16;i++){
                      *U_MIN_C2_B[i]           =  config_SDP["generateur2"]["banques"][banques_num[i]]["Umin"].as<int>();
                      *U_MAX_C2_B[i]           =  config_SDP["generateur2"]["banques"][banques_num[i]]["Umax"].as<int>();
                      *GP_C2_B[i]              =  config_SDP["generateur2"]["banques"][banques_num[i]]["GainP"].as<int>();
                      *I_MAX_C2_B[i]           =  config_SDP["generateur2"]["banques"][banques_num[i]]["ImaxREF"].as<int>();
                      *Seuil_mesure_I_C2_B[i]  =  config_SDP["generateur2"]["banques"][banques_num[i]]["seuilMesure"].as<int>();
                      *KD_C2_B[i]              =  config_SDP["generateur2"]["banques"][banques_num[i]]["GainKD"].as<int>();
                      *I_MAX_LU_C2_B[i]        =  config_SDP["generateur2"]["banques"][banques_num[i]]["ImaxLu"].as<int>(); 
                      *ID_Fth_C2_B[i]          =  config_SDP["generateur2"]["banques"][banques_num[i]]["ID_Fth"].as<int>(); 
                  }
                  
                  // 3. Récupération paramètres cycles (Générateur 3)
                  for (int i=0;i<16;i++){
                     *U_MIN_C3_B[i]           =  config_SDP["generateur3"]["banques"][banques_num[i]]["Umin"].as<int>();
                     *U_MAX_C3_B[i]           =  config_SDP["generateur3"]["banques"][banques_num[i]]["Umax"].as<int>();
                     *GP_C3_B[i]              =  config_SDP["generateur3"]["banques"][banques_num[i]]["GainP"].as<int>();
                     *I_MAX_C3_B[i]           =  config_SDP["generateur3"]["banques"][banques_num[i]]["ImaxREF"].as<int>();
                     *Seuil_mesure_I_C3_B[i]  =  config_SDP["generateur3"]["banques"][banques_num[i]]["seuilMesure"].as<int>();
                     *KD_C3_B[i]              =  config_SDP["generateur3"]["banques"][banques_num[i]]["GainKD"].as<int>();
                     *I_MAX_LU_C3_B[i]        =  config_SDP["generateur3"]["banques"][banques_num[i]]["ImaxLu"].as<int>(); 
                     *ID_Fth_C3_B[i]          =  config_SDP["generateur3"]["banques"][banques_num[i]]["ID_Fth"].as<int>(); 
                  }

                  // 6. Récupération du temps sauvegardé au moment de la mise hors tension du contrôleur process (Conversion de l'heure en secondes) 
                  *C_HDT_tps_off = (uint16_t)(
                        config_SDP["dataFth"]["HDT"]["heures"].as<int>() * 3600U +
                        config_SDP["dataFth"]["HDT"]["min"].as<int>()   * 60U +
                        config_SDP["dataFth"]["HDT"]["sec"].as<int>()
                  );

                // Nombre de secondes au moment de la mise hors tension de la machine
                  
                  // 7. Récupération des paramètres pour chaque calculs de facteurs thermique (4 par générateur)
                 *I_thermique_N_C1[0]          = config_SDP["dataFth"]["G1"]["ID_0"]["Ith"].as<int>();
                 *I_thermique_N_C1[1]          = config_SDP["dataFth"]["G1"]["ID_1"]["Ith"].as<int>();
                 *I_thermique_N_C1[2]          = config_SDP["dataFth"]["G1"]["ID_2"]["Ith"].as<int>();
                 *I_thermique_N_C1[3]          = config_SDP["dataFth"]["G1"]["ID_3"]["Ith"].as<int>();                 

                 *Periode_Fth_N_C1[0]  = config_SDP["dataFth"]["G1"]["ID_0"]["periode"].as<int>();
                 *Periode_Fth_N_C1[1]  = config_SDP["dataFth"]["G1"]["ID_1"]["periode"].as<int>();
                 *Periode_Fth_N_C1[2]  = config_SDP["dataFth"]["G1"]["ID_2"]["periode"].as<int>();
                 *Periode_Fth_N_C1[3]  = config_SDP["dataFth"]["G1"]["ID_3"]["periode"].as<int>();

                 *I_thermique_N_C2[0]          = config_SDP["dataFth"]["G2"]["ID_0"]["Ith"].as<int>();
                 *I_thermique_N_C2[1]          = config_SDP["dataFth"]["G2"]["ID_1"]["Ith"].as<int>();
                 *I_thermique_N_C2[2]          = config_SDP["dataFth"]["G2"]["ID_2"]["Ith"].as<int>();
                 *I_thermique_N_C2[3]          = config_SDP["dataFth"]["G2"]["ID_3"]["Ith"].as<int>();                 

                 *Periode_Fth_N_C2[0]  = config_SDP["dataFth"]["G2"]["ID_0"]["periode"].as<int>();
                 *Periode_Fth_N_C2[1]  = config_SDP["dataFth"]["G2"]["ID_1"]["periode"].as<int>();
                 *Periode_Fth_N_C2[2]  = config_SDP["dataFth"]["G2"]["ID_2"]["periode"].as<int>();
                 *Periode_Fth_N_C2[3]  = config_SDP["dataFth"]["G2"]["ID_3"]["periode"].as<int>();

                 *I_thermique_N_C3[0]          = config_SDP["dataFth"]["G3"]["ID_0"]["Ith"].as<int>();
                 *I_thermique_N_C3[1]          = config_SDP["dataFth"]["G3"]["ID_1"]["Ith"].as<int>();
                 *I_thermique_N_C3[2]          = config_SDP["dataFth"]["G3"]["ID_2"]["Ith"].as<int>();
                 *I_thermique_N_C3[3]          = config_SDP["dataFth"]["G3"]["ID_3"]["Ith"].as<int>();                 

                 *Periode_Fth_N_C3[0]  = config_SDP["dataFth"]["G3"]["ID_0"]["periode"].as<int>();
                 *Periode_Fth_N_C3[1]  = config_SDP["dataFth"]["G3"]["ID_1"]["periode"].as<int>();
                 *Periode_Fth_N_C3[2]  = config_SDP["dataFth"]["G3"]["ID_2"]["periode"].as<int>();
                 *Periode_Fth_N_C3[3]  = config_SDP["dataFth"]["G3"]["ID_3"]["periode"].as<int>();                                  

                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                  // Récupératio état défaut thermique si défaut apparu avant la mise hors tension (Debug)
                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
                   *FACTEUR_THERMIQUE_1 =   config_SDP["dataFth"]["G1"]["ID_0"]["etat_defaut"].as<bool>();
                   *FACTEUR_THERMIQUE_C1[0] =   config_SDP["dataFth"]["G1"]["ID_0"]["etat_defaut"].as<bool>();  // Registre à créer
                   *FACTEUR_THERMIQUE_C1[1] =   config_SDP["dataFth"]["G1"]["ID_1"]["etat_defaut"].as<bool>();  // Registre à créer
                   *FACTEUR_THERMIQUE_C1[2] =   config_SDP["dataFth"]["G1"]["ID_2"]["etat_defaut"].as<bool>();  // Registre à créer
                   *FACTEUR_THERMIQUE_C1[3] =   config_SDP["dataFth"]["G1"]["ID_3"]["etat_defaut"].as<bool>();  // Registre à créer

                   *FACTEUR_THERMIQUE_2 =   config_SDP["dataFth"]["G2"]["ID_0"]["etat_defaut"].as<bool>();
                   *FACTEUR_THERMIQUE_C2[0] =   config_SDP["dataFth"]["G1"]["ID_0"]["etat_defaut"].as<bool>();  // Registre à créer
                   *FACTEUR_THERMIQUE_C2[1] =   config_SDP["dataFth"]["G1"]["ID_1"]["etat_defaut"].as<bool>();  // Registre à créer
                   *FACTEUR_THERMIQUE_C2[2] =   config_SDP["dataFth"]["G1"]["ID_2"]["etat_defaut"].as<bool>();  // Registre à créer
                   *FACTEUR_THERMIQUE_C2[3] =   config_SDP["dataFth"]["G1"]["ID_3"]["etat_defaut"].as<bool>();  // Registre à créer

                   *FACTEUR_THERMIQUE_3 =   config_SDP["dataFth"]["G3"]["ID_0"]["etat_defaut"].as<bool>();
                   *FACTEUR_THERMIQUE_C3[0] =   config_SDP["dataFth"]["G1"]["ID_0"]["etat_defaut"].as<bool>();  // Registre à créer
                   *FACTEUR_THERMIQUE_C3[1] =   config_SDP["dataFth"]["G1"]["ID_1"]["etat_defaut"].as<bool>();  // Registre à créer
                   *FACTEUR_THERMIQUE_C3[2] =   config_SDP["dataFth"]["G1"]["ID_2"]["etat_defaut"].as<bool>();  // Registre à créer
                   *FACTEUR_THERMIQUE_C3[3] =   config_SDP["dataFth"]["G1"]["ID_3"]["etat_defaut"].as<bool>();  // Registre à créer

                   *C_Pourc_puiss_thermique_C1_ID[0] =   config_SDP["dataFth"]["G1"]["ID_0"]["pourc_Fth"].as<bool>();  // Registre à créer
                   *C_Pourc_puiss_thermique_C1_ID[1] =   config_SDP["dataFth"]["G1"]["ID_1"]["pourc_Fth"].as<bool>();  // Registre à créer
                   *C_Pourc_puiss_thermique_C1_ID[2] =   config_SDP["dataFth"]["G1"]["ID_2"]["pourc_Fth"].as<bool>();  // Registre à créer
                   *C_Pourc_puiss_thermique_C1_ID[3] =   config_SDP["dataFth"]["G1"]["ID_3"]["pourc_Fth"].as<bool>();  // Registre à créer

                   *C_Pourc_puiss_thermique_C2_ID[0] =   config_SDP["dataFth"]["G2"]["ID_0"]["pourc_Fth"].as<bool>();  // Registre à créer
                   *C_Pourc_puiss_thermique_C2_ID[1] =   config_SDP["dataFth"]["G2"]["ID_1"]["pourc_Fth"].as<bool>();  // Registre à créer
                   *C_Pourc_puiss_thermique_C2_ID[2] =   config_SDP["dataFth"]["G2"]["ID_2"]["pourc_Fth"].as<bool>();  // Registre à créer
                   *C_Pourc_puiss_thermique_C2_ID[3] =   config_SDP["dataFth"]["G2"]["ID_3"]["pourc_Fth"].as<bool>();  // Registre à créer

                   *C_Pourc_puiss_thermique_C3_ID[0] =   config_SDP["dataFth"]["G3"]["ID_0"]["pourc_Fth"].as<bool>();  // Registre à créer
                   *C_Pourc_puiss_thermique_C3_ID[1] =   config_SDP["dataFth"]["G3"]["ID_1"]["pourc_Fth"].as<bool>();  // Registre à créer
                   *C_Pourc_puiss_thermique_C3_ID[2] =   config_SDP["dataFth"]["G3"]["ID_2"]["pourc_Fth"].as<bool>();  // Registre à créer
                   *C_Pourc_puiss_thermique_C3_ID[3] =   config_SDP["dataFth"]["G3"]["ID_3"]["pourc_Fth"].as<bool>();  // Registre à créer


                  // Récuépération des données de période , ID thermique et I thermique: 

                  *ID_FTH_C3 = *ID_Fth_C3_B[(WP_CONF_DYN_E & 0x00F0) >> 4];
                  *ID_FTH_C2 = *ID_Fth_C2_B[(WP_CONF_DYN_E & 0xF000) >> 12];
                  *ID_FTH_C1 = *ID_Fth_C1_B[(WP_CONF_DYN_E & 0x0F00) >> 8];

                  *Periode_Fth_C3 = *Periode_Fth_N_C3[*ID_Fth_C3_B[(WP_CONF_DYN_E & 0x00F0) >> 4] ]; 
                  *I_thermique_C3 =  *I_thermique_N_C3[*ID_Fth_C3_B[(WP_CONF_DYN_E & 0x00F0) >> 4]] ;

                  *Periode_Fth_C2 = *Periode_Fth_N_C2[*ID_Fth_C2_B[(WP_CONF_DYN_E & 0xF000) >> 12]]; 
                  *I_thermique_C2 =  *I_thermique_N_C2[*ID_Fth_C2_B[(WP_CONF_DYN_E & 0xF000) >> 12]] ;

                  *Periode_Fth = *Periode_Fth_N_C1[*ID_Fth_C1_B[(WP_CONF_DYN_E & 0x0F00) >> 8]]; 
                  *I_thermique_C1 =  *I_thermique_N_C1[*ID_Fth_C1_B[(WP_CONF_DYN_E & 0x0F00) >> 8]] ;

                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                  // Récupération config voies de Mesure
                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!                    
                    float temp;
                    uint8_t offset_hex[4]={0};     // Tableau pour stocker les octets

                    *GAIN_V1 = config_SDP["configMesures"]["Mesure_1"]["Gain"].as<int>();

                    temp = config_SDP["configMesures"]["Mesure_1"]["Offset"].as<float>();

                    float_to_hex_array(-1*temp, offset_hex); 

                    *OFFSET_MSB_V1  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
                    *OFFSET_LSB_V1  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 
                    // ....................................
                    *GAIN_V2 = config_SDP["configMesures"]["Mesure_2"]["Gain"].as<int>();

                    temp = config_SDP["configMesures"]["Mesure_2"]["Offset"].as<float>();

                    float_to_hex_array(-1*temp, offset_hex); 

                    *OFFSET_MSB_V2  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
                    *OFFSET_LSB_V2  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 
                    // ....................................
                    *GAIN_V3  = config_SDP["configMesures"]["Mesure_3"]["Gain"].as<int>();
 
                    temp = config_SDP["configMesures"]["Mesure_3"]["Offset"].as<float>();

                    float_to_hex_array(-1*temp, offset_hex); 

                    *OFFSET_MSB_V3  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
                    *OFFSET_LSB_V3  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 
                    // ....................................
                    *GAIN_V4  = config_SDP["configMesures"]["Mesure_4"]["Gain"].as<int>();

                    temp = config_SDP["configMesures"]["Mesure_4"]["Offset"].as<float>();

                    float_to_hex_array(-1*temp, offset_hex); 

                    *OFFSET_MSB_V4  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
                    *OFFSET_LSB_V4  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 
                    // ....................................
                    *GAIN_V5  = config_SDP["configMesures"]["Mesure_5"]["Gain"].as<int>();
                    
                    temp = config_SDP["configMesures"]["Mesure_5"]["Offset"].as<float>();

                    float_to_hex_array(-1*temp, offset_hex); 

                    *OFFSET_MSB_V5  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
                    *OFFSET_LSB_V5  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 
                    // ....................................
                    *GAIN_V6  = config_SDP["configMesures"]["Mesure_6"]["Gain"].as<int>();

                    temp = config_SDP["configMesures"]["Mesure_6"]["Offset"].as<float>();

                    float_to_hex_array(-1*temp, offset_hex); 

                    *OFFSET_MSB_V6  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
                    *OFFSET_LSB_V6  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 
                 


                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
                  // ..............................................................................
             // Récupération des nouveaux paramètres du cycle dans la carte SD [A développer]
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


                  // ..............................................................................
                  // Récupération du mode
                  // ..............................................................................  
                  *MODE_TEST  = config_SDP["debug"]["wifi_mode"].as<int>();

                  *MODE_TEST = 0;

                  // !!!!!!!!!
                  

                  // !!!!!!!!!

                   timer_dt_C1_recup[0] = config_SDP["dataFth"]["G1"]["ID_0"]["timer_dt"].as<int>();
                   timer_dt_C1_recup[1] = config_SDP["dataFth"]["G1"]["ID_1"]["timer_dt"].as<int>();
                   timer_dt_C1_recup[2] = config_SDP["dataFth"]["G1"]["ID_2"]["timer_dt"].as<int>();
                   timer_dt_C1_recup[3] = config_SDP["dataFth"]["G1"]["ID_3"]["timer_dt"].as<int>();

                   timer_dt_C2_recup[0] = config_SDP["dataFth"]["G2"]["ID_0"]["timer_dt"].as<int>();
                   timer_dt_C2_recup[1] = config_SDP["dataFth"]["G2"]["ID_1"]["timer_dt"].as<int>();
                   timer_dt_C2_recup[2] = config_SDP["dataFth"]["G2"]["ID_2"]["timer_dt"].as<int>();
                   timer_dt_C2_recup[3] = config_SDP["dataFth"]["G2"]["ID_3"]["timer_dt"].as<int>();
                  // ..............................................................................  


                            // ..............................................................................
                            // Récupération des données d'étallonage capteur 
                            // .............................................................................. 
                              for (int i=0;i<16;i++){
                                  *Etalonnage_X1_B[i] = config_SDP["Etalonnage"]["X1"][banques_etalonnage[i]].as<int>();
                                  *Etalonnage_Y1_B[i] = config_SDP["Etalonnage"]["Y1"][banques_etalonnage[i]].as<int>();
                                  *Etalonnage_X2_B[i] = config_SDP["Etalonnage"]["X2"][banques_etalonnage[i]].as<int>();
                                  *Etalonnage_Y2_B[i] = config_SDP["Etalonnage"]["Y2"][banques_etalonnage[i]].as<int>();
                              }

                              *Etalonnage_X1 = *Etalonnage_X1_B[(WP_CONF_DYN_E & 0x000F)];
                              *Etalonnage_Y1 = *Etalonnage_Y1_B[(WP_CONF_DYN_E & 0x000F)];
                              *Etalonnage_X2 = *Etalonnage_X2_B[(WP_CONF_DYN_E & 0x000F)];
                              *Etalonnage_Y2 = *Etalonnage_Y2_B[(WP_CONF_DYN_E & 0x000F)];

                              *Seuil_Ctrl_Temperature = config_SDP["Etalonnage"]["Seuil_Ctrl_Temperature"].as<int>(); 

                              // .............................................................................. 

     

}
// .........................................................................................................................
void traitement_FTh(){
  
  uint32_t duree_extinction_pts;
  uint32_t pas_fth_max;
  // .............................................................................................................................................................
  // Traitement G1 : ID_Fth = 0 à 3
  // .............................................................................................................................................................

  for (int indice_fth = 0; indice_fth<4;indice_fth++){

      duree_extinction_pts = (*C_HDT_duree_tps_off*10)/((*Periode_Fth_N_C1[indice_fth]/Fth_nb_points_max)+1); // Nombre de pas Fth correspondant au temps d'extinction de la machine 

        pas_fth_max =  *Periode_Fth_N_C1[indice_fth]/((*Periode_Fth_N_C1[indice_fth]/240)+1);    // Pas fth max (en points) // Pour l'instant commun au deux généteurs (modifier plus tard)

        // .............................................................................................................................................................
        // A l'arrêt le traitement du tableau de contrôle Fth s'arrête, reprendre ce traitement en tenant compte du temps d'extinction de la machine
        // .............................................................................................................................................................

        while (duree_extinction_pts > 0){                     // Décrémentation de l'indice de temps d'extinction' ( en pas de temps du cycle de contrôle Fth)

        if (timer_dt_C1_recup[indice_fth] < pas_fth_max){                    // i : indice de Timer_dt à l'extinction
              
              timer_dt_C1_recup[indice_fth] = timer_dt_C1_recup[indice_fth]+ 1;                               // Nouvel indice où on se trouve le calcul de facteur thermique G1

              Integral_Tab_C1[indice_fth][timer_dt_C1_recup[indice_fth]] = 0;  // G1 

        }else{                                                                     
        
        // Exécuté quand on a fini une période de contrôle de facteur thermique
                timer_dt_C1_recup[indice_fth] = 0; // G1

        }

          duree_extinction_pts = duree_extinction_pts - 1;            // Décrémentation de l'indice de temps de repos
        }

        // ...............................................................................
        // Réorganisation du tableau pour tenir en compte du temps de repos pour le calcul de pourcentage
        // ...............................................................................

        uint32_t temporary[240];

          for (int i = 0; i<240;i++) {
            temporary[i]=Integral_Tab_C1[indice_fth][i];
          }


        for (int i=0; i<240; i++){

              // Pas nécessaire avant de revenir au pas initial du ctrl de facteur thermique : pas_fth_max - timer_dt_recup[0] ;  
              // Au démarrage, on commence le calcul au pas initial => un décalage doit être fait sinon la décroissance se fait trop rapidement

              // .....................................................................
              // Exemple de calcul : timer_dt_recup[0] = 100 ; pas_fth_max = 230 [G1]
              // .....................................................................
              if (timer_dt_C1_recup[indice_fth]+ i < pas_fth_max){
                Integral_Tab_C1[indice_fth][i] = temporary[timer_dt_C1_recup[indice_fth]+i];                   // Integral_recup[0][0] = temporary[100]  ; Integral_recup[0][1] = temporary[101] ; .... ; Integral_recup[0][129] = temporary[229]
              }else{
                Integral_Tab_C1[indice_fth][i] = temporary[i-(pas_fth_max-timer_dt_C1_recup[indice_fth])];     // Integral_recup[0][130] = temporary[0] ; Integral_recup[0][131] = temporary[1] ; ... ; Integral_recup[0][229] = temporary[99]
              }

        }

            // .................
            // Générateur 1
            // .................
            for (int i = 0; i< pas_fth_max;i++){
                sum_C1[indice_fth] = sum_C1[indice_fth] + Integral_Tab_C1[indice_fth][i];
            }
            // .................
        
  }
  // .............................................................................................................................................................
  // Traitement G2 : ID_Fth = 0 à 3
  // .............................................................................................................................................................

  for (int indice_fth = 0; indice_fth<4;indice_fth++){

      duree_extinction_pts = (*C_HDT_duree_tps_off*10)/((*Periode_Fth_N_C2[indice_fth]/Fth_nb_points_max)+1); // Nombre de pas Fth correspondant au temps d'extinction de la machine 

        pas_fth_max =  *Periode_Fth_N_C2[indice_fth]/((*Periode_Fth_N_C2[indice_fth]/240)+1);    // Pas fth max (en points) // Pour l'instant commun au deux généteurs (modifier plus tard)

        // .............................................................................................................................................................
        // A l'arrêt le traitement du tableau de contrôle Fth s'arrête, reprendre ce traitement en tenant compte du temps d'extinction de la machine
        // .............................................................................................................................................................

        while (duree_extinction_pts > 0){                     // Décrémentation de l'indice de temps d'extinction' ( en pas de temps du cycle de contrôle Fth)

        if (timer_dt_C2_recup[indice_fth] < pas_fth_max){                    // i : indice de Timer_dt à l'extinction
              
              timer_dt_C2_recup[indice_fth] = timer_dt_C2_recup[indice_fth]+ 1;                               // Nouvel indice où on se trouve le calcul de facteur thermique G1

              Integral_Tab_C2[indice_fth][timer_dt_C2_recup[indice_fth]] = 0;  // G1 

        }else{                                                                     
        
        // Exécuté quand on a fini une période de contrôle de facteur thermique
                timer_dt_C2_recup[indice_fth] = 0; // G1

        }

          duree_extinction_pts = duree_extinction_pts - 1;            // Décrémentation de l'indice de temps de repos
        }

        // ...............................................................................
        // Réorganisation du tableau pour tenir en compte du temps de repos pour le calcul de pourcentage
        // ...............................................................................

        uint32_t temporary[240];

          for (int i = 0; i<240;i++) {
            temporary[i]=Integral_Tab_C2[indice_fth][i];
          }


        for (int i=0; i< pas_fth_max; i++){

              // Pas nécessaire avant de revenir au pas initial du ctrl de facteur thermique : pas_fth_max - timer_dt_recup[0] ;  
              // Au démarrage, on commence le calcul au pas initial => un décalage doit être fait sinon la décroissance se fait trop rapidement

              // .....................................................................
              // Exemple de calcul : timer_dt_recup[0] = 100 ; pas_fth_max = 230 [G1]
              // .....................................................................
              if (timer_dt_C2_recup[indice_fth]+ i < pas_fth_max){
                Integral_Tab_C2[indice_fth][i] = temporary[timer_dt_C2_recup[indice_fth]+i];                   // Integral_recup[0][0] = temporary[100]  ; Integral_recup[0][1] = temporary[101] ; .... ; Integral_recup[0][129] = temporary[229]
              }else{
                Integral_Tab_C2[indice_fth][i] = temporary[i-(pas_fth_max-timer_dt_C2_recup[indice_fth])];     // Integral_recup[0][130] = temporary[0] ; Integral_recup[0][131] = temporary[1] ; ... ; Integral_recup[0][229] = temporary[99]
              }

        }

            // .................
            // Générateur 2
            // .................
            for (int i = 0; i< pas_fth_max;i++){
                sum_C2[indice_fth] = sum_C2[indice_fth] + Integral_Tab_C2[indice_fth][i];
            }
            // .................
            

  }
// .............................................................................................................................................................
  // Traitement G3 : ID_Fth = 0 à 3
  // .............................................................................................................................................................

  for (int indice_fth = 0; indice_fth<4;indice_fth++){

      duree_extinction_pts = (*C_HDT_duree_tps_off*10)/((*Periode_Fth_N_C3[indice_fth]/Fth_nb_points_max)+1); // Nombre de pas Fth correspondant au temps d'extinction de la machine 

        pas_fth_max =  *Periode_Fth_N_C3[indice_fth]/((*Periode_Fth_N_C3[indice_fth]/240)+1);    // Pas fth max (en points) // Pour l'instant commun au deux généteurs (modifier plus tard)

        // .............................................................................................................................................................
        // A l'arrêt le traitement du tableau de contrôle Fth s'arrête, reprendre ce traitement en tenant compte du temps d'extinction de la machine
        // .............................................................................................................................................................

        while (duree_extinction_pts > 0){                     // Décrémentation de l'indice de temps d'extinction' ( en pas de temps du cycle de contrôle Fth)

        if (timer_dt_C3_recup[indice_fth] < pas_fth_max){                    // i : indice de Timer_dt à l'extinction
              
              timer_dt_C3_recup[indice_fth] = timer_dt_C3_recup[indice_fth]+ 1;                               // Nouvel indice où on se trouve le calcul de facteur thermique G1

              Integral_Tab_C3[indice_fth][timer_dt_C3_recup[indice_fth]] = 0;  // G1 

        }else{                                                                     
        
        // Exécuté quand on a fini une période de contrôle de facteur thermique
                timer_dt_C3_recup[indice_fth] = 0; // G1

        }

          duree_extinction_pts = duree_extinction_pts - 1;            // Décrémentation de l'indice de temps de repos
        }

        // ...............................................................................
        // Réorganisation du tableau pour tenir en compte du temps de repos pour le calcul de pourcentage
        // ...............................................................................

        uint32_t temporary[240];

          for (int i = 0; i<240;i++) {
            temporary[i]=Integral_Tab_C3[indice_fth][i];
          }


        for (int i=0; i< pas_fth_max; i++){

              // Pas nécessaire avant de revenir au pas initial du ctrl de facteur thermique : pas_fth_max - timer_dt_recup[0] ;  
              // Au démarrage, on commence le calcul au pas initial => un décalage doit être fait sinon la décroissance se fait trop rapidement

              // .....................................................................
              // Exemple de calcul : timer_dt_recup[0] = 100 ; pas_fth_max = 230 [G1]
              // .....................................................................
              if (timer_dt_C3_recup[indice_fth]+ i < pas_fth_max){
                Integral_Tab_C3[indice_fth][i] = temporary[timer_dt_C3_recup[indice_fth]+i];                   // Integral_recup[0][0] = temporary[100]  ; Integral_recup[0][1] = temporary[101] ; .... ; Integral_recup[0][129] = temporary[229]
              }else{
                Integral_Tab_C3[indice_fth][i] = temporary[i-(pas_fth_max-timer_dt_C3_recup[indice_fth])];     // Integral_recup[0][130] = temporary[0] ; Integral_recup[0][131] = temporary[1] ; ... ; Integral_recup[0][229] = temporary[99]
              }

        }

            // .................
            // Générateur 3
            // .................
            for (int i = 0; i< pas_fth_max;i++){
                sum_C3[indice_fth] = sum_C3[indice_fth] + Integral_Tab_C3[indice_fth][i];
            }
            // .................
            

  }
}

// -------------------------------------------------------------------------------------------------------
// @brief : Valeurs retournés : 
// - nombre de valeurs modifié 
// -------------------------------------------------------------------------------------------------------
void structation_modif_params(uint16_t* nb_valeurs_modifie, uint16_t* nb_erreurs){

// - RecupJSON 
// - Comparaison
// - Incrémentation à chaque fois qu'on détecte une modification 
// - Incrémentation du nombre d'erreurs 


}
// -------------------------------------------------------------------------------------------------------
void writeDataFth(){
                              
                              File dataFth_binaire_tmp = SD.open("/data_tmp.bin", FILE_WRITE);

                              if (dataFth_binaire_tmp){
                  
                                  n  = dataFth_binaire_tmp.write((uint8_t*)Integral_Tab_C1, sizeof(Integral_Tab_C1));
                                  n1 = dataFth_binaire_tmp.write((uint8_t*)Integral_Tab_C2, sizeof(Integral_Tab_C2));
                                  n2 = dataFth_binaire_tmp.write((uint8_t*)Integral_Tab_C3, sizeof(Integral_Tab_C3));

                                  dataFth_binaire_tmp.flush(); 
                                  dataFth_binaire_tmp.close();  

                                  if (n == sizeof(Integral_Tab_C1) && n1 == sizeof(Integral_Tab_C2) && n2 == sizeof(Integral_Tab_C3)) {

                                      *WRITE_DATA_FTH = 1;  // Succès écriture des données dans la carte SD;

                                      // Remplacer l'ancien fichier par le nouveau
                                      SD.remove("/data.bin");                     // Supprimer ancien fichier
                                      if (!SD.rename("/data_tmp.bin", "/data.bin")) {
                                        
                                      } else {
                                         
                                      }
                                  }else{
                                    *WRITE_DATA_FTH = 0;  // Succès écriture des données dans la carte SD;
                                  }



                              }else{
                                *WRITE_DATA_FTH = 0;  // Succès écriture des données dans la carte SD;
                              }
}


float rebuild_float(uint16_t msb, uint16_t lsb) {
    uint32_t hex_value = (static_cast<uint32_t>(msb) << 16) | lsb;
    float float_value = *(float*)&hex_value;
    return float_value;
}