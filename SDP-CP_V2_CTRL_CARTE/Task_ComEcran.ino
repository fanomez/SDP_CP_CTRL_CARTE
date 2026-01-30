// ===============================================================================================================================
// Tâche : Gestion écran   
// ===============================================================================================================================
void TaskComEcran(void *param) {
 
  uint16_t i = 0;
  uint16_t j = 0;
/*
    // -----------------------------------------------------------------------------------------------------------------
  // Gestion écran
  // -----------------------------------------------------------------------------------------------------------------
  #ifdef ENABLE_AFFICHAGE
          // Color definitions : RGB565      (5 bit pour le rouge , 6 bit pour le vert , 5 bit pour le bleu )
          const uint16_t Display_Color_Black = 0x0000;
          const uint16_t Display_Color_White = 0xFFFF;
          const uint16_t Display_Color_Red = 0xF800;
          const uint16_t Display_Color_Blue = 0x01FF; // Jaune

        *C_Consigne_Temps_C1 = 2000;
        *C_Consigne_Puissance_1_C1 = 0;

        /*  digitalWrite(CS1_PIN, LOW); // Désélectionner l'écran
          digitalWrite(CS3_PIN, HIGH); // Désélectionner l'extendeur de bus
          digitalWrite(CS2_PIN, HIGH); // Sélectionner la SD Card

          


          tft.init(240, 320);

          tft.invertDisplay(false); // Restaure l'affichage avec les couleurs normales
          tft.setRotation(1);
          
          tft.fillScreen(Display_Backround_Color);
          tft.setTextColor(Display_Text_Color);
          tft.setTextSize(10); // Adjust text size as needed
          
          // ---------------------------------------------------------------------
          // Gestion affichage des valeurs et de leurs unités
          // ---------------------------------------------------------------------
          Affichage_valeur(1, *C_Consigne_Puissance_1_C1);
          Affichage_unite(1,"A");*/
 /* #endif*/

  
  while (1) {

  /* if (xSemaphoreTake(spiMutex, portMAX_DELAY)) {
      // --------------------------------------------------------------------------------------
      // gestion de l'affichage de la températue 
      // --------------------------------------------------------------------------------------
      // Affichage_Temperature();
      // --------------------------------------------------------------------------------------
      
      if ((*CYCLE_EN_COURS_1 || *CYCLE_EN_COURS_2 ) && (S1 != 0 || S2!=0 ) && (S1!=255 || S2!=255 )){  // Affichage lors de la magnétisation

              if (*CYCLE_EN_COURS_1) {
                Affichage_valeur(1,*C_Mesure_Affichage_C1);

                    Affichage_unite(1,"kA");                            // => Unité : kA si > 9999
    
              }

              if (*CYCLE_EN_COURS_2) {
                Affichage_valeur(1,*C_Mesure_Affichage_C2);

                  Affichage_unite(1,"kA");                            // => Unité : kA si > 9999

              }


      }else if (*TOR_E3 && (S1 != 0 || S2!=0 ) ){  // Affichage lors de la démagnétisation
                if(*CYCLE_EN_COURS_1_DEMAG || *CYCLE_EN_COURS_2_DEMAG ){

                      if (*CYCLE_EN_COURS_1_DEMAG) {
                        Affichage_valeur(1,*C_Mesure_Affichage_C1);

                          Affichage_unite(1,"kA");

                      } 

                      if (*CYCLE_EN_COURS_2_DEMAG) {
                          Affichage_valeur(1,*C_Mesure_Affichage_C2);

                            Affichage_unite(1,"kA");
                      }

                }
      }else{

        // ===============================================================================================================================
        // Gestion Affichage 1 
        // ===============================================================================================================================      
                    if ( affichagePuissance ){                                  // Vaut 1 si changement de valeur su potard
                        if(*BO_BF || *BO_BF2 ){                                             // Affichage de la consigne en A si boucle fermée
                            Affichage_valeur(1,  *Potard_V4_Puissance);
                            Affichage_unite(1,"kA");
                        }else if (!*BO_BF || !*BO_BF2 )
                        {
                          Affichage_valeur(1,  *Potard_V4_Puissance);        // Affichage de la consigne en % si boucle ouverte
                            Affichage_unite(1,"%");
                        }

                        affichagePuissance = 0 ; 
                  }

        // ===============================================================================================================================
        // Gestion Affichage 2 
        // ===============================================================================================================================
        if ((DWM(0)>0) || (WM(2)> 0)){                                 // Traitement si détéction de défaut 
          
            if (M()[M_FACTEUR_THERMIQUE_1] == 1){                                        // Si les deux sont vraies, seule la première sera exécuté à chaque itération 
                      Affichage_alarme(M_FACTEUR_THERMIQUE_1);
                      Affichage_Fth();

            }else if(M()[M_TEMPERATURE_0] == 1){
                      Affichage_alarme(M_TEMPERATURE_0);
                      Affichage_Fth();
            }
            // ----------------------------------------------------------
            for (int i=0;i<40;i++){
                if (M()[i] == 1){                                        // Si les deux sont vraies, seule la première sera exécuté à chaque itération 
                          Affichage_alarme(i);
                          Affichage_Fth();
                }
            }
            // ----------------------------------------------------------

        }else{
                  if(!*Mode0){ Affichage_valeur(2,  *C_Consigne_Temps_C1*100); }
                  if(*Mode0){ Affichage_valeur(2,  *C_Consigne_Temps_C2*100); }
                    
                    Affichage_unite(2,"s");

                    Affichage_Fth();  // Affichage facteur thermique en continu à la fin de chaque tir
          
                    occurence_alarme = 0; // Remise à du flag pour l'effacement avant l'affichage de l'alarme
        }
        // ===============================================================================================================================
      }
  // #endif

  if (*C_Debug_Val_5 <65535){
      *C_Debug_Val_5 = *C_Debug_Val_5 + 1 ;
  }else{
      *C_Debug_Val_5 = 0;
  }

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // Activation du WiFI après 5s si mode test activé (soit modification registre modbus soit modification carte SD)
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  if(*MODE_TEST == 1){

  if(tOnperso(&TimerWifiSAT,5000)){
          
         
          *wifi_cmd = 1 ;

           TimerWifiSAT = 0;

          *MODE_TEST = 0;
      }
  }
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  
   
    
      xSemaphoreGive(spiMutex);
  }*/

  stackWordsLeft = uxTaskGetStackHighWaterMark(NULL);

  taskDataAnalysis[0] = stackWordsLeft;

  
  
  // -------------------------------------------------------
  vTaskDelay(1); // Small delay to prevent busy-waiting  (Avec ce temps d'attente l'écran est assez fluide : Pas de problème observé avec le Wifi)
  } // fin while 
}  // fin TaskComEcran

// ===============================================================================================================================
// Fonctions pour la gestion de l'affichage de l'écran 
// ===============================================================================================================================
// Gestion de la valeur à afficher sur la ligne 1 ou 2 
// ------------------------------------------------------------------------------------------------------ 
  void Affichage_valeur(uint8_t num_affichage,uint16_t inputMessage){
      
      // Sélection bus SPI
      digitalWrite(CS1_PIN, LOW); // Sélectionner l'écran
      digitalWrite(CS3_PIN, HIGH); // Désélectionner l'extendeur de bus
      digitalWrite(CS2_PIN, HIGH); // Sélectionner la SD Card

      // Modification affichage 
      tft.setTextColor(Display_Text_Color,Display_Backround_Color);
      tft.setTextSize(10); // Adjust text size as need

      if(num_affichage == 2){ 

              tft.setCursor(5, 140);          // Ligne 2 
              sprintf(AffichageBuffer_1, "%04.1f", (float)inputMessage/1000); // [0 : remplit avec des zéros à gauche / 4: 4 caractères /.1 : 1 chiffre après la virgule]
              tft.print(AffichageBuffer_1);

      }else if (num_affichage == 1){


              tft.setCursor(5, 20);

              float val = (float)inputMessage / 1000.0f;
              val = (int)(val * 10) / 10.0f;  // Troncature à 1 décimale

              sprintf(AffichageBuffer_1, "%04.1f", val);

              tft.print(AffichageBuffer_1);
      }

      // Désélection bus SPI
      digitalWrite(CS1_PIN, HIGH); // Sélectionner l'écran
  }
  // ------------------------------------------------------------------------------------------------------ 
  // Gestion du nettoyage de la valeur à afficher
  // ------------------------------------------------------------------------------------------------------ 
  void Nettoyage_Affichage(uint8_t num_affichage){
      
      // Sélection bus SPI
      digitalWrite(CS1_PIN, LOW); // Sélectionner l'écran
      digitalWrite(CS3_PIN, HIGH); // Désélectionner l'extendeur de bus
      digitalWrite(CS2_PIN, HIGH); // Sélectionner la SD Card

      // Nettoyage affichage valeur 
      tft.setTextColor(Display_Backround_Color,Display_Backround_Color);
      tft.setTextSize(10); // Adjust text size as need

      if(num_affichage == 1){             // Ligne 1 
          tft.setCursor(5, 20);
      }else{
         tft.setCursor(5, 140);          // Ligne 2 
      }

              sprintf(AffichageBuffer_1, "%.2f", (float)(*C_Consigne_Temps_C1*100)/1000); // Format the old number with five digits
              tft.print(AffichageBuffer_1);


      // Nettoyage affichage unité
      tft.setTextColor(Display_Backround_Color,Display_Backround_Color);
      tft.setTextSize(5); // Adjust text size as need
      if(num_affichage == 1){
          tft.setCursor(250, 20);
          tft.print("A");
      }else{
         tft.setCursor(250, 140);
         tft.print("s");
      }
      
      // Désélection bus SPI
      digitalWrite(CS1_PIN, HIGH); // Sélectionner l'écran
  }


  // ------------------------------------------------------------------------------------------------------ 
  // Gestion de l'unité de la valeur à afficher 
  // ------------------------------------------------------------------------------------------------------ 
    void Affichage_unite(uint8_t num_affichage,char *inputMessage){
      
      // Sélection bus SPI
      digitalWrite(CS1_PIN, LOW); // Sélectionner l'écran
      digitalWrite(CS3_PIN, HIGH); // Désélectionner l'extendeur de bus
      digitalWrite(CS2_PIN, HIGH); // Sélectionner la SD Card

      // Modification affichage 
      tft.setTextColor(Display_Text_Color,Display_Backround_Color);
      tft.setTextSize(5); // Adjust text size as need
      if(num_affichage == 1){   
          tft.setCursor(250, 20);
          tft.print(inputMessage);

          tft.setTextSize(3);
          tft.setCursor(250, 70);
          tft.print("trs");
          
      }else{
         tft.setCursor(250, 140);
         tft.print(" ");
         tft.print(inputMessage);
      }

      
      


      // Désélection bus SPI
      digitalWrite(CS1_PIN, HIGH); // Sélectionner l'écran
  }
  // ------------------------------------------------------------------------------------------------------ 
  // Gestion de l'affichage d'erreur
  // ------------------------------------------------------------------------------------------------------ 
  void Affichage_alarme(uint16_t num_alarme){

      // Sélection bus SPI
      digitalWrite(CS1_PIN, LOW); // Sélectionner l'écran
      digitalWrite(CS3_PIN, HIGH); // Désélectionner l'extendeur de bus
      digitalWrite(CS2_PIN, HIGH); // Sélectionner la SD Card

      if (occurence_alarme == 0){   // Effacer la consigne de temps (nécessaire car la taille de l'affichage de l'alarme est beaucoup plus petite) 
          Nettoyage_Affichage(2);
      }

              // Modification affichage
              tft.setTextSize(4);
              tft.setTextColor(ST77XX_RED,ST77XX_BLACK);
              tft.setCursor(60 , 140);

              char numberStr[10];
              char destination[50] = "AL.";
              sprintf(destination + strlen(destination), "%02d", num_alarme);

              tft.print(destination);

              tft.setCursor(60 , 180);
              sprintf(numberStr, "%03d%%", *C_Pourc_puiss_thermique_C1); // Format the old number with five digits
              tft.print(numberStr);

      // Désélection bus SPI
      digitalWrite(CS1_PIN, HIGH); // Sélectionner l'écran

      occurence_alarme++;
  }
  // ------------------------------------------------------------------------------------------------------ 
  void Affichage_Fth(){
          // Modification affichage

              char numberStr[10];
              tft.setTextSize(2);
              tft.setTextColor(ST77XX_RED,ST77XX_BLACK);
              tft.setCursor(200 , 220);
              sprintf(numberStr, "Fth:%03d%%", *C_Pourc_puiss_thermique_C1); // Format the old number with five digits
              tft.print(numberStr);
      // Désélection bus SPI
      digitalWrite(CS1_PIN, HIGH); // Sélectionner l'écran

  }
  // ------------------------------------------------------------------------------------------------------ 
  void Affichage_Temperature(){

      char numberStr[20];

      digitalWrite(CS1_PIN, LOW); // déSélectionner l'écran

      // -----------------------------------------------------------------------------------------------------------------------
      // Affichage coefficients
      // -----------------------------------------------------------------------------------------------------------------------
            /*  tft.setTextSize(2);
              tft.setTextColor(ST77XX_RED,ST77XX_BLACK);
              tft.setCursor(5 , 220);
              sprintf(numberStr, "Coeff %.02f/%.02f",Coeff_a[0][0],Coeff_b[0][0]); // Format the old number with five digits
              tft.print(numberStr);*/
      // -----------------------------------------------------------------------------------------------------------------------
      // Affichage valeur en points non converties
      // -----------------------------------------------------------------------------------------------------------------------
      // Remarques : La valeur numérique mesuré en points (=> Etalonnage_X2) sera utilisé avec la valeur analogique mesuré au multimère (=> Etalonnage_Y2)
      // Ces deux valeurs seront utilisés comme un point d'étalonnage de notre système :
      //  (valeur numérique  => Etalonnage_X2) 
      //  (valeur analogique => Etalonnage_Y2)
      // -----------------------------------------------------------------------------------------------------------------------
              tft.setTextSize(2);
              tft.setTextColor(ST77XX_RED,ST77XX_BLACK);
              tft.setCursor(5 , 220);
              // sprintf(numberStr, "Temp : %04u pts /",mesure_single); 
              // sprintf(numberStr, "%04u pts|%.01f mV",Mesures_Ana[0],mesure_single); 
              sprintf(numberStr, "Temp :%03d deg C",Mesures_Converties[0][1]); 
              tft.print(numberStr);
      // -----------------------------------------------------------------------------------------------------------------------

      // Désélection bus SPI
      digitalWrite(CS1_PIN, HIGH); // déSélectionner l'écran

  }