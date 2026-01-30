
// ..............................................................................................................
// Route permettant la lecture des données de la carte SD
// ..............................................................................................................
  void registerReadSDRoutes(String gen , String banque) {


        // Récupération des paramètres dans l'URL, par exemple : /params_SD?gen=G1&banque=0
        // String gen = server.arg("gen");         // générique : "G1", "G2", "G3"
        // String banque = server.arg("banque");   // banque : "0", "1", ..., "15"

        doc.clear();
        
        // Remplir la section "General" (toujours envoyée)
        doc["General"]["Mode CP"] = *MODE;
        doc["General"]["Types Capteurs"] = *Types_Capteurs;
        doc["General"]["Pointeur DCY"] = *Pointeur_DCY;
        doc["General"]["Pointeur ACY"] = *Pointeur_ACY;
        doc["General"]["Pointeur ACQ"] = *Pointeur_ACQ;
        doc["General"]["Pointeur DEMAG"] = *Pointeur_DEMAG;
        doc["General"]["Pointeur CtrlFth"] = *Periode_Fth;
        doc["General"]["Pointeur TORS1"] = *Pointeur_TOR_S1;
        doc["General"]["Pointeur TORS2"] = *Pointeur_TOR_S2;
        doc["General"]["Pointeur TORS3"] = *Pointeur_TOR_S3;
        doc["General"]["Pointeur TORS4"] = *Pointeur_TOR_S4;
        doc["General"]["% stab Regul"] = *COEF_CONE_TUBE;
        doc["General"]["% gain Boost"] = *Gain_BOOST;
        doc["General"]["tps Pb Puissance"] = *Temps_Pb_puissance;

        // Champs supplémentaires si besoin
        doc["General"]["doubleAffichage"] = *OPTION_DOUBLE_AFFICHAGE;
        doc["General"]["sensModeCombine"] = *SENS_MODE_COMBINE;
        doc["General"]["arrosageModeCombine"] = *FIN_ARROSAGE_COMBINE_en_1;
        doc["General"]["pasPotard0.5"] = *PAS_POTARD_TEMPS_05S;
        doc["General"]["repos4sGT"] = *REPOS_4s_GT;

        // Initialisation d'une variable pour retrouver l'index du générateur
        int genIndex = -1;

        // On associe le nom du générateur à son index (dans les tableaux)"ctrlFO"
        if (gen == "G1") genIndex = 0;
        else if (gen == "G2") genIndex = 1;
        else if (gen == "G3") genIndex = 2;

        // Si un générateur a été spécifié correctement
        if (genIndex != -1) {
          // Création d'un objet JSON pour ce générateur
          JsonObject g = doc.createNestedObject(gen);

          // On ajoute les paramètres du générateur

          if(genIndex == 0){ g["ctrlTete"] = *OPTION_CTRL_TETES_12;}
          else if(genIndex == 1){ g["ctrlTete"] = *OPTION_CTRL_TETES_34;}
          else if(genIndex == 2){ g["ctrlTete"] = *OPTION_CTRL_TETES_56;}

          if(genIndex == 0){ g["secuVigitherm"] = *OPTION_DEFAUT_THERMIQUE_1;}
          else if(genIndex == 1){ g["secuVigitherm"] = *OPTION_DEFAUT_THERMIQUE_2;}
          else if(genIndex == 2){ g["secuVigitherm"] = *OPTION_DEFAUT_THERMIQUE_3;}

          if(genIndex == 0){ g["ctrlFO"] = *OPTION_CTRL_FORME_ONDE_1;}
          else if(genIndex == 1){ g["ctrlFO"] = *OPTION_CTRL_FORME_ONDE_2;}
          else if(genIndex == 2){ g["ctrlFO"] = *OPTION_CTRL_FORME_ONDE_3;}

          if(genIndex == 0){ g["ptrMesure"] = *Pointeur_mesure_C1;}
          else if(genIndex == 1){ g["ptrMesure"] = *Pointeur_mesure_C2;}
          else if(genIndex == 2){ g["ptrMesure"] = *Pointeur_mesure_C3;}


          if(genIndex == 0){ g["ptrPuissance1"] = *Pointeur_Puissance_C1 ;}
          else if(genIndex == 1){ g["ptrPuissance1"]  = *Pointeur_Puissance_C2;}
          else if(genIndex == 2){ g["ptrPuissance1"]  = *Pointeur_Puissance_C3;}      
          
          if(genIndex == 0){ g["ptrPuissance2"] = *Pointeur_Puissance_2_C1 ;}
          else if(genIndex == 1){ g["ptrPuissance2"]  = *Pointeur_Puissance_2_C2;}
          else if(genIndex == 2){ g["ptrPuissance2"]  = *Pointeur_Puissance_2_C3;}

          
          if(genIndex == 0){ g["ptrTps"] = *Pointeur_Temps_C1 ;}
          else if(genIndex == 1){ g["ptrTps"]  = *Pointeur_Temps_C2;}
          else if(genIndex == 2){ g["ptrTps"]  = *Pointeur_Temps_C3;}


          if(genIndex == 0){g["seuilCtrlBO"] = *Seuil_CTRL_BO_C1;}
          else if(genIndex == 1){g["seuilCtrlBO"] = *Seuil_CTRL_BO_C2;}
          else if(genIndex == 2){g["seuilCtrlBO"] = *Seuil_CTRL_BO_C3;}       


          if(genIndex == 0){g["%stabMesure"] = *Nb_val_stab_mesure_C1;}
          else if(genIndex == 1){g["%stabMesure"] = *Nb_val_stab_mesure_C2;}
          else if(genIndex == 2){g["%stabMesure"] = *Nb_val_stab_mesure_C3;}

          if(genIndex == 0){g["ptrFO"] = *Pointeur_FO_C1;}
          else if(genIndex == 1){g["ptrFO"] = *Pointeur_FO_C2;}
          else if(genIndex == 2){g["ptrFO"] = *Pointeur_FO_C3;}    

          
          if(genIndex == 0){ g["ptrET"] = *Pointeur_ET_C1 ;}
          else if(genIndex == 1){ g["ptrET"] = *Pointeur_ET_C2 ;}
          else if(genIndex == 2){ g["ptrET"] = *Pointeur_ET_C3 ;}      

          
        


          // Si une banque spécifique est demandée
          if (banque != "") {
            int b = banque.toInt();  // Conversion String -> int
            if (b >= 0 && b < 16) {  // Vérification que la banque est valide

              // Création de la structure JSON pour les banques
              JsonObject banqueObj = g.createNestedObject("banques");

              // Ajout uniquement de la banque demandée
              JsonObject bq = banqueObj.createNestedObject(banque);


          if(genIndex == 0){bq["seuilMesure"] = *Seuil_mesure_I_C1_B[b];}
          else if(genIndex == 1){bq["seuilMesure"] = *Seuil_mesure_I_C2_B[b];}
          else if(genIndex == 2){bq["seuilMesure"] = *Seuil_mesure_I_C3_B[b];}    


              // Remplissage des paramètres de cette banque
            if(genIndex == 0){bq["seuilMesure"] = *Seuil_mesure_I_C1_B[b];}
            else if(genIndex == 1){bq["seuilMesure"] = *Seuil_mesure_I_C2_B[b];}
            else if(genIndex == 2){bq["seuilMesure"] = *Seuil_mesure_I_C3_B[b];}    

            if(genIndex == 0){bq["ImaxLu"] = *I_MAX_LU_C1_B[b];}
            else if(genIndex == 1){bq["ImaxLu"] = *I_MAX_LU_C2_B[b];}
            else if(genIndex == 2){bq["ImaxLu"] = *I_MAX_LU_C3_B[b];} 


            if(genIndex == 0){bq["ImaxREF"] = *I_MAX_C1_B[b];}
            else if(genIndex == 1){bq["ImaxREF"] = *I_MAX_C2_B[b];}
            else if(genIndex == 2){bq["ImaxREF"] = *I_MAX_C3_B[b];}                  

            if(genIndex == 0){bq["Umin"] = *U_MIN_C1_B[b];}
            else if(genIndex == 1){bq["Umin"] = *U_MIN_C2_B[b];}
            else if(genIndex == 2){bq["Umin"] = *U_MIN_C3_B[b];}     

            if(genIndex == 0){bq["Umax"] = *U_MAX_C1_B[b];}
            else if(genIndex == 1){bq["Umax"] = *U_MAX_C2_B[b];}
            else if(genIndex == 2){bq["Umax"] = *U_MAX_C3_B[b];}     


            if(genIndex == 0){bq["GainP"] = *GP_C1_B[b];}
            else if(genIndex == 1){bq["GainP"] = *GP_C2_B[b];}
            else if(genIndex == 2){bq["GainP"] = *GP_C3_B[b];}     

            if(genIndex == 0){bq["GainKD"] = *KD_C1_B[b];}
            else if(genIndex == 1){bq["GainKD"] = *KD_C2_B[b];}
            else if(genIndex == 2){bq["GainKD"] = *KD_C3_B[b];}     

            if(genIndex == 0){bq["ID_Fth"] = *ID_Fth_C1_B[b];}
            else if(genIndex == 1){bq["ID_Fth"] = *ID_Fth_C2_B[b];}
            else if(genIndex == 2){bq["ID_Fth"] = *ID_Fth_C3_B[b];}   

            }
          }
        }


    

      size_t len = measureJson(doc);
      char buffer[2048];          // buffer fixe assez grand
      serializeJson(doc, buffer, sizeof(buffer));  // sérialisation

      // -------------------------------------------------
      // Ajouter un "topic" pour indiquer le type de message
      // -------------------------------------------------
      clientMQTT.println("TOPIC:esp32/param_SD");  // ou "TOPIC:esp32/measures" selon contexte
      clientMQTT.println(buffer);                 // println ajoute '\n' automatiquement
      
      }
// ===================================================================================================
// Ecriture route SD
// ====================================================================================================
void registerWriteSDRoutes() {

    modif_banque_wifi_en_cours = 1;

    // --- Traitement "general" ---
    if (doc.containsKey("general")) {
        JsonObject general = doc["general"];

            if (general.containsKey("Mode CP"))          *MODE = general["Mode CP"].as<int>();
            if (general.containsKey("Types Capteurs"))   *Types_Capteurs = general["Types Capteurs"].as<int>();
            if (general.containsKey("Types Capteurs Sup")) *Types_Capteurs_Sup = general["Types Capteurs Sup"].as<int>();
            if (general.containsKey("Pointeur DCY"))     *Pointeur_DCY = general["Pointeur DCY"].as<int>();
            if (general.containsKey("Pointeur ACY"))     *Pointeur_ACY = general["Pointeur ACY"].as<int>();
            if (general.containsKey("Pointeur ACQ"))     *Pointeur_ACQ = general["Pointeur ACQ"].as<int>();
            if (general.containsKey("Pointeur DEMAG"))   *Pointeur_DEMAG = general["Pointeur DEMAG"].as<int>();
            // if (general.containsKey("Pointeur CtrlFth")) *Pointeur_CtrlFth = general["Pointeur CtrlFth"].as<int>();
            if (general.containsKey("Pointeur TORS1"))   *Pointeur_TOR_S1 = general["Pointeur TORS1"].as<int>();
            if (general.containsKey("Pointeur TORS2"))   *Pointeur_TOR_S2 = general["Pointeur TORS2"].as<int>();
            if (general.containsKey("Pointeur TORS3"))   *Pointeur_TOR_S3 = general["Pointeur TORS3"].as<int>();
            if (general.containsKey("Pointeur TORS4"))   *Pointeur_TOR_S4 = general["Pointeur TORS4"].as<int>();
            if (general.containsKey("% stab Regul"))     *COEF_CONE_TUBE = general["% stab Regul"].as<int>();
            if (general.containsKey("% gain Boost"))     *Gain_BOOST = general["% gain Boost"].as<int>();
            if (general.containsKey("tps Pb Puissance")) *Temps_Pb_puissance = general["tps Pb Puissance"].as<int>();

            if (general.containsKey("doubleAffichage")) *OPTION_DOUBLE_AFFICHAGE = general["doubleAffichage"].as<bool>();
            if (general.containsKey("sensModeCombine")) *SENS_MODE_COMBINE = general["sensModeCombine"].as<bool>();
            if (general.containsKey("arrosageModeCombine")) *FIN_ARROSAGE_COMBINE_en_1 = general["arrosageModeCombine"].as<bool>();
            if (general.containsKey("pasPotard0.5")) *PAS_POTARD_TEMPS_05S = general["pasPotard0.5"].as<bool>();
            if (general.containsKey("repos4sGT")) *REPOS_4s_GT = general["repos4sGT"].as<bool>();



    }

    // --- Traitement des générateurs ---
    const char* genKeys[] = {"generateur1", "generateur2", "generateur3"};
    for (int i = 0; i < 3; i++) {
        const char* genKey = genKeys[i];
        if (!doc.containsKey(genKey)) continue;

        JsonObject gen = doc[genKey];

            // --- Mise à jour des variables par générateur ---
            if (gen.containsKey("ctrlTete")) {
                if (strcmp(genKey, "generateur1")==0) *OPTION_CTRL_TETES_12 = gen["ctrlTete"].as<bool>();
                else if (strcmp(genKey, "generateur2")==0) *OPTION_CTRL_TETES_34 = gen["ctrlTete"].as<bool>();
                else if (strcmp(genKey, "generateur3")==0) *OPTION_CTRL_TETES_56 = gen["ctrlTete"].as<bool>();
            }

            if (gen.containsKey("ctrlFO")) {
                if (strcmp(genKey, "generateur1")==0) *OPTION_CTRL_FORME_ONDE_1 = gen["ctrlFO"].as<bool>();
                else if (strcmp(genKey, "generateur2")==0) *OPTION_CTRL_FORME_ONDE_2 = gen["ctrlFO"].as<bool>();
                else if (strcmp(genKey, "generateur3")==0) *OPTION_CTRL_FORME_ONDE_3 = gen["ctrlFO"].as<bool>();
            }

            if (gen.containsKey("secuVigitherm")) {
                if (strcmp(genKey, "generateur1")==0) *OPTION_DEFAUT_THERMIQUE_1 = gen["secuVigitherm"].as<bool>();
                else if (strcmp(genKey, "generateur2")==0) *OPTION_DEFAUT_THERMIQUE_2 = gen["secuVigitherm"].as<bool>();
                else if (strcmp(genKey, "generateur3")==0) *OPTION_DEFAUT_THERMIQUE_3 = gen["secuVigitherm"].as<bool>();
            }

            if (gen.containsKey("ptrMesure")) {
                if (strcmp(genKey, "generateur1")==0) *Pointeur_mesure_C1 = gen["ptrMesure"].as<int>();
                else if (strcmp(genKey, "generateur2")==0) *Pointeur_mesure_C2 = gen["ptrMesure"].as<int>();
                else if (strcmp(genKey, "generateur3")==0) *Pointeur_mesure_C3 = gen["ptrMesure"].as<int>();
            }

            if (gen.containsKey("ptrPuissance1")) {
                if (strcmp(genKey, "generateur1")==0) *Pointeur_Puissance_C1 = gen["ptrPuissance1"].as<int>();
                else if (strcmp(genKey, "generateur2")==0) *Pointeur_Puissance_C2 = gen["ptrPuissance1"].as<int>();
                else if (strcmp(genKey, "generateur3")==0) *Pointeur_Puissance_C3 = gen["ptrPuissance1"].as<int>();
            }

            if (gen.containsKey("ptrPuissance2")) {
                if (strcmp(genKey, "generateur1")==0) *Pointeur_Puissance_2_C1 = gen["ptrPuissance2"].as<int>();
                else if (strcmp(genKey, "generateur2")==0) *Pointeur_Puissance_2_C2 = gen["ptrPuissance2"].as<int>();
                else if (strcmp(genKey, "generateur3")==0) *Pointeur_Puissance_2_C3 = gen["ptrPuissance2"].as<int>();
            }

            if (gen.containsKey("ptrTps")) {
                if (strcmp(genKey, "generateur1")==0) *Pointeur_Temps_C1 = gen["ptrTps"].as<int>();
                else if (strcmp(genKey, "generateur2")==0) *Pointeur_Temps_C2 = gen["ptrTps"].as<int>();
                else if (strcmp(genKey, "generateur3")==0) *Pointeur_Temps_C3 = gen["ptrTps"].as<int>();
            }

            if (gen.containsKey("seuilCtrlBO")) {
                if (strcmp(genKey, "generateur1")==0) *Seuil_CTRL_BO_C1 = gen["seuilCtrlBO"].as<int>();
                else if (strcmp(genKey, "generateur2")==0) *Seuil_CTRL_BO_C2 = gen["seuilCtrlBO"].as<int>();
                else if (strcmp(genKey, "generateur3")==0) *Seuil_CTRL_BO_C3 = gen["seuilCtrlBO"].as<int>();
            }

            if (gen.containsKey("%stabMesure")) {
                if (strcmp(genKey, "generateur1")==0) *Nb_val_stab_mesure_C1 = gen["%stabMesure"].as<int>();
                else if (strcmp(genKey, "generateur2")==0) *Nb_val_stab_mesure_C2 = gen["%stabMesure"].as<int>();
                else if (strcmp(genKey, "generateur3")==0) *Nb_val_stab_mesure_C3 = gen["%stabMesure"].as<int>();
            }

            if (gen.containsKey("ptrFO")) {
                if (strcmp(genKey, "generateur1")==0) *Pointeur_FO_C1 = gen["ptrFO"].as<int>();
                else if (strcmp(genKey, "generateur2")==0) *Pointeur_FO_C2 = gen["ptrFO"].as<int>();
                else if (strcmp(genKey, "generateur3")==0) *Pointeur_FO_C3 = gen["ptrFO"].as<int>();
            }

            if (gen.containsKey("ptrET")) {
                if (strcmp(genKey, "generateur1")==0) *Pointeur_ET_C1 = gen["ptrET"].as<int>();
                else if (strcmp(genKey, "generateur2")==0) *Pointeur_ET_C2 = gen["ptrET"].as<int>();
                else if (strcmp(genKey, "generateur3")==0) *Pointeur_ET_C3 = gen["ptrET"].as<int>();
            }

      // --- Banques ---
          if (gen.containsKey("banques")) {
              JsonObject banques = gen["banques"].as<JsonObject>();

              for (JsonPair kv : banques) {
                  const char* banque_id = kv.key().c_str();
                  JsonObject banque = kv.value().as<JsonObject>();
                  int id = atoi(banque_id);  // Conversion de la clé en entier

                  // --- SEUIL MESURE ---
                  if (banque.containsKey("seuilMesure")) {
                      if (strcmp(genKey, "generateur1") == 0) *Seuil_mesure_I_C1_B[id] = banque["seuilMesure"].as<int>();
                      else if (strcmp(genKey, "generateur2") == 0) *Seuil_mesure_I_C2_B[id] = banque["seuilMesure"].as<int>();
                      else if (strcmp(genKey, "generateur3") == 0) *Seuil_mesure_I_C3_B[id] = banque["seuilMesure"].as<int>();
                  }

                  // --- IMAX LU ---
                  if (banque.containsKey("ImaxLu")) {
                      if (strcmp(genKey, "generateur1") == 0) *I_MAX_LU_C1_B[id] = banque["ImaxLu"].as<int>();
                      else if (strcmp(genKey, "generateur2") == 0) *I_MAX_LU_C2_B[id] = banque["ImaxLu"].as<int>();
                      else if (strcmp(genKey, "generateur3") == 0) *I_MAX_LU_C3_B[id] = banque["ImaxLu"].as<int>();
                  }

                  // --- IMAX REF ---
                  if (banque.containsKey("ImaxREF")) {
                      if (strcmp(genKey, "generateur1") == 0) *I_MAX_C1_B[id] = banque["ImaxREF"].as<int>();
                      else if (strcmp(genKey, "generateur2") == 0) *I_MAX_C2_B[id] = banque["ImaxREF"].as<int>();
                      else if (strcmp(genKey, "generateur3") == 0) *I_MAX_C3_B[id] = banque["ImaxREF"].as<int>();
                  }

                  // --- UMIN ---
                  if (banque.containsKey("Umin")) {
                      if (strcmp(genKey, "generateur1") == 0) *U_MIN_C1_B[id] = banque["Umin"].as<int>();
                      else if (strcmp(genKey, "generateur2") == 0) *U_MIN_C2_B[id] = banque["Umin"].as<int>();
                      else if (strcmp(genKey, "generateur3") == 0) *U_MIN_C3_B[id] = banque["Umin"].as<int>();
                  }

                  // --- UMAX ---
                  if (banque.containsKey("Umax")) {
                      if (strcmp(genKey, "generateur1") == 0) *U_MAX_C1_B[id] = banque["Umax"].as<int>();
                      else if (strcmp(genKey, "generateur2") == 0) *U_MAX_C2_B[id] = banque["Umax"].as<int>();
                      else if (strcmp(genKey, "generateur3") == 0) *U_MAX_C3_B[id] = banque["Umax"].as<int>();
                  }

                  // --- GAIN P ---
                  if (banque.containsKey("GainP")) {
                      if (strcmp(genKey, "generateur1") == 0) *GP_C1_B[id] = banque["GainP"].as<int>();
                      else if (strcmp(genKey, "generateur2") == 0) *GP_C2_B[id] = banque["GainP"].as<int>();
                      else if (strcmp(genKey, "generateur3") == 0) *GP_C3_B[id] = banque["GainP"].as<int>();
                  }

                  // --- GAIN KD ---
                  if (banque.containsKey("GainKD")) {
                      if (strcmp(genKey, "generateur1") == 0) *KD_C1_B[id] = banque["GainKD"].as<int>();
                      else if (strcmp(genKey, "generateur2") == 0) *KD_C2_B[id] = banque["GainKD"].as<int>();
                      else if (strcmp(genKey, "generateur3") == 0) *KD_C3_B[id] = banque["GainKD"].as<int>();
                  }

                  // --- ID_FTH ----
                if (banque.containsKey("ID_Fth")) {
                      if (strcmp(genKey, "generateur1") == 0) *ID_Fth_C1_B[id] = banque["ID_Fth"].as<int>();
                      else if (strcmp(genKey, "generateur2") == 0) *ID_Fth_C2_B[id] = banque["ID_Fth"].as<int>();
                      else if (strcmp(genKey, "generateur3") == 0) *ID_Fth_C3_B[id] = banque["ID_Fth"].as<int>();
                }

              }


          }

    }// fin or 

          // --- Traitement "dataFth" ---
      if (doc.containsKey("dataFth")) {                                                       // Programmé mais pas encore testé

          // Générateur 1 : 
          *Periode_Fth_N_C1[0] = doc["dataFth"]["G1"]["ID_0"]["periode"].as<int>();
          *Periode_Fth_N_C1[1] = doc["dataFth"]["G1"]["ID_1"]["periode"].as<int>();
          *Periode_Fth_N_C1[2] = doc["dataFth"]["G1"]["ID_2"]["periode"].as<int>();
          *Periode_Fth_N_C1[3]= doc["dataFth"]["G1"]["ID_3"]["periode"].as<int>();

          *I_thermique_N_C1[0]= doc["dataFth"]["G1"]["ID_0"]["Ith"].as<int>();
          *I_thermique_N_C1[1]= doc["dataFth"]["G1"]["ID_1"]["Ith"].as<int>();
          *I_thermique_N_C1[2]= doc["dataFth"]["G1"]["ID_2"]["Ith"].as<int>();
          *I_thermique_N_C1[3]= doc["dataFth"]["G1"]["ID_3"]["Ith"].as<int>();

          // Générateur 2 : 
          *Periode_Fth_N_C2[0] = doc["dataFth"]["G2"]["ID_0"]["periode"].as<int>();
          *Periode_Fth_N_C2[1] = doc["dataFth"]["G2"]["ID_1"]["periode"].as<int>();
          *Periode_Fth_N_C2[2] = doc["dataFth"]["G2"]["ID_2"]["periode"].as<int>();
          *Periode_Fth_N_C2[3]= doc["dataFth"]["G2"]["ID_3"]["periode"].as<int>();

          *I_thermique_N_C2[0]= doc["dataFth"]["G2"]["ID_0"]["Ith"].as<int>();
          *I_thermique_N_C2[1]= doc["dataFth"]["G2"]["ID_1"]["Ith"].as<int>();
          *I_thermique_N_C2[2]= doc["dataFth"]["G2"]["ID_2"]["Ith"].as<int>();
          *I_thermique_N_C2[3]= doc["dataFth"]["G2"]["ID_3"]["Ith"].as<int>();

          // Générateur 3 : 
          *Periode_Fth_N_C3[0] = doc["dataFth"]["G3"]["ID_0"]["periode"].as<int>();
          *Periode_Fth_N_C3[1] = doc["dataFth"]["G3"]["ID_1"]["periode"].as<int>();
          *Periode_Fth_N_C3[2] = doc["dataFth"]["G3"]["ID_2"]["periode"].as<int>();
          *Periode_Fth_N_C3[3]= doc["dataFth"]["G3"]["ID_3"]["periode"].as<int>();

          *I_thermique_N_C3[0]= doc["dataFth"]["G3"]["ID_0"]["Ith"].as<int>();
          *I_thermique_N_C3[1]= doc["dataFth"]["G3"]["ID_1"]["Ith"].as<int>();
          *I_thermique_N_C3[2]= doc["dataFth"]["G3"]["ID_2"]["Ith"].as<int>();
          *I_thermique_N_C3[3]= doc["dataFth"]["G3"]["ID_3"]["Ith"].as<int>();  
      }

      // --- Traitement "config_mesures" ---

      if (doc.containsKey("configMesures")) {  

                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                  // 8.Récupération config voies de Mesure
                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!                  
                      float temp;
                      uint8_t offset_hex[4]={0};     // Tableau pour stocker les octets

                      *GAIN_V1 = doc["configMesures"]["Mesure_1"]["Gain"].as<int>();

                      temp = doc["configMesures"]["Mesure_1"]["Offset"].as<float>();

                      float_to_hex_array(-1*temp, offset_hex); 

                      *OFFSET_MSB_V1  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
                      *OFFSET_LSB_V1  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 

                      *OFFSET_DYN_V1 = doc["configMesures"]["Mesure_1"]["type"].as<int>();      // Si 1 => offset dyn actif sinon 0


                      // ....................................
                      *GAIN_V2 = doc["configMesures"]["Mesure_2"]["Gain"].as<int>();

                      temp = doc["configMesures"]["Mesure_2"]["Offset"].as<float>();

                      float_to_hex_array(-1*temp, offset_hex); 

                      *OFFSET_MSB_V2  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
                      *OFFSET_LSB_V2  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 

                      *OFFSET_DYN_V2 = doc["configMesures"]["Mesure_2"]["type"].as<int>();      // Si 1 => offset dyn actif sinon 0
                      // ....................................
                      *GAIN_V3  = doc["configMesures"]["Mesure_3"]["Gain"].as<int>();
  
                      temp = doc["configMesures"]["Mesure_3"]["Offset"].as<float>();

                      float_to_hex_array(-1*temp, offset_hex); 

                      *OFFSET_MSB_V3  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
                      *OFFSET_LSB_V3  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 

                      *OFFSET_DYN_V3 = doc["configMesures"]["Mesure_3"]["type"].as<int>();      // Si 1 => offset dyn actif sinon 0
                      // ....................................
                      *GAIN_V4  = doc["configMesures"]["Mesure_4"]["Gain"].as<int>();

                      temp = doc["configMesures"]["Mesure_4"]["Offset"].as<float>();

                      float_to_hex_array(-1*temp, offset_hex); 

                      *OFFSET_MSB_V4  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
                      *OFFSET_LSB_V4  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 

                      *OFFSET_DYN_V4 = doc["configMesures"]["Mesure_4"]["type"].as<int>();      // Si 1 => offset dyn actif sinon 0
                      // ....................................
                      *GAIN_V5  = doc["configMesures"]["Mesure_5"]["Gain"].as<int>();
                      
                      temp = doc["configMesures"]["Mesure_5"]["Offset"].as<float>();

                      float_to_hex_array(-1*temp, offset_hex); 

                      *OFFSET_MSB_V5  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
                      *OFFSET_LSB_V5  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 

                      *OFFSET_DYN_V5 = doc["configMesures"]["Mesure_5"]["type"].as<int>();      // Si 1 => offset dyn actif sinon 0
                      // ....................................
                      *GAIN_V6  = doc["configMesures"]["Mesure_6"]["Gain"].as<int>();

                      temp = doc["configMesures"]["Mesure_6"]["Offset"].as<float>();

                      float_to_hex_array(-1*temp, offset_hex); 

                      *OFFSET_MSB_V6  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
                      *OFFSET_LSB_V6  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 

                      *OFFSET_DYN_V6 = doc["configMesures"]["Mesure_6"]["type"].as<int>();      // Si 1 => offset dyn actif sinon 0

        }
            // Modification des registres courant de la banque sélectionné 
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

                  // Récupération des paramètres de facteur thermique en fonction de l'ID
                  *Periode_Fth_C3 = *Periode_Fth_N_C3[*ID_FTH_C3]; 
                  *I_thermique_C3 =  *I_thermique_N_C3[*ID_FTH_C3] ;


                  // Récupération des paramètres de facteur thermique en fonction de l'ID
                  *Periode_Fth_C2 = *Periode_Fth_N_C2[*ID_FTH_C2]; 
                  *I_thermique_C2 =  *I_thermique_N_C2[*ID_FTH_C2] ;


                  // Récupération des paramètres de facteur thermique en fonction de l'ID
                  *Periode_Fth = *Periode_Fth_N_C1[*ID_FTH_C1]; 
                  *I_thermique_C1 =  *I_thermique_N_C1[*ID_FTH_C1] ;
          
            // ..............................................................................
      
    modif_banque_wifi_en_cours = 2;

}
// ..............................................................................................................
