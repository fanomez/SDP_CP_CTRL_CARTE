// ===============================================================================================================
// Route permettant de récupérer le fichier /data.bin stocké dans la carte SD
// ===============================================================================================================
  void registerBinaryFilesRoutes(WebServer &server) {

  server.on("/data.bin", HTTP_GET, [&server]() {


    digitalWrite(CS1_PIN, HIGH); // Désélectionner l'écran
    digitalWrite(CS3_PIN, HIGH); // Désélectionner l'extendeur de bus
    digitalWrite(CS2_PIN, LOW); // Sélectionner la SD Card

  if (xSemaphoreTake(spiMutex, portMAX_DELAY)) {

    File file = SD.open("/data.bin", FILE_READ);  // Remplace par le nom de ton fichier
    if (!file) {
          server.send(404, "text/plain", "Fichier introuvable");
          return;
      }

      // Envoi du fichier en binaire
        server.streamFile(file, "application/octet-stream");
        file.close();

    xSemaphoreGive(spiMutex);

    digitalWrite(CS1_PIN, LOW); // Désélectionner l'écran
    digitalWrite(CS3_PIN, HIGH); // Désélectionner l'extendeur de bus
    digitalWrite(CS2_PIN, HIGH); // Sélectionner la SD Card

  }
});
}
// ===============================================================================================================
// Ecrire un fichier JSON dans la carte SD
// @suggestion : 
// - on sait que la modification des paramètres via mon interface fonctionne 
// - si beaucoup trop de traitement pour l'ESP32 pour gérer le téléversement d'un nouveau fichier parametres.json 
// - 
// ===============================================================================================================
void registerJsonFilesRoutes(WebServer &server) {
    // .................................................................................................
    // Etapes 0 : Inhiber toutes les tâches :  ??????
    // .................................................................................................
    // Etape 1 : page d'accueil 
    // .................................................................................................
    server.on("/accueil.upload", HTTP_GET, [&server]() {
    server.send_P(200, "text/html", page_upload);
    });
    // .................................................................................................
    // Etape 2 : Récupération du fichier uploader via le configurateur et écriture dans la carte SD
    // .................................................................................................

    server.on("/upload", HTTP_POST, [&server]() {
        server.send(200, "text/plain", "Upload terminé");
    }, [&server]() {

        // Vérifier que le handle est valide avant de supprimer la tâche
      if (TaskReceptionTRMSHandler != NULL) vTaskDelete(TaskReceptionTRMSHandler);
      if (TaskComGUIHandler     != NULL) vTaskDelete(TaskComGUIHandler);
      if (TaskComEcranHandler   != NULL) vTaskDelete(TaskComEcranHandler);
      if (TaskModbusHandler     != NULL) vTaskDelete(TaskModbusHandler);
      if (TaskEmissionTRMSHandler != NULL) vTaskDelete(TaskEmissionTRMSHandler);
      if (TaskBASICHandler      != NULL) vTaskDelete(TaskBASICHandler);
      // if (TaskWifiHandler       != NULL) vTaskDelete(TaskWifiHandler);
      if (TaskSDcardHandler     != NULL) vTaskDelete(TaskSDcardHandler);

        HTTPUpload &upload = server.upload();

        // Buffer dynamique en HEAP (Option 1)
        // ----------------------------------------------------
        static uint8_t *jsonBuffer = nullptr;
        static size_t offset = 0;

        if (upload.status == UPLOAD_FILE_START) {

            modif_banque_wifi_en_cours = 1;   // Bloquer les modifications des banques
            offset = 0;

            // Allouer 16 Ko dans la heap (PAS dans DRAM0)
            jsonBuffer = (uint8_t*) malloc(16384);
            if (!jsonBuffer) {
                // Serial.println("ERREUR: malloc jsonBuffer échoué !");
                // return;
            }
        }

        else if (upload.status == UPLOAD_FILE_WRITE) {

            if (jsonBuffer) {
                if (offset + upload.currentSize < 16384) {
                    memcpy(jsonBuffer + offset, upload.buf, upload.currentSize);
                    offset += upload.currentSize;
                } else {
                    // Serial.println("ERREUR: JSON trop gros !");
                    offset = 0;
                }
            }
        }

        else if (upload.status == UPLOAD_FILE_END) {

            if (!jsonBuffer) {
                // Serial.println("ERREUR: Buffer JSON non alloué !");
                modif_banque_wifi_en_cours = 0;
                // return;
            }

            // --------------------------------------------------------
            // Désérialisation depuis le buffer HEAP
            // --------------------------------------------------------
            DeserializationError error = deserializeJson(config_SDP, jsonBuffer, offset);

            if (error) {
                // Serial.println("ERREUR: Désérialisation JSON ratée !");
                free(jsonBuffer);
                jsonBuffer = nullptr;
                modif_banque_wifi_en_cours = 0;
                // return;
            }

            // Libérer le buffer après parse
            free(jsonBuffer);
            jsonBuffer = nullptr;

            // --------------------------------------------------------
            // Écriture SD protégée
            // --------------------------------------------------------
            if (xSemaphoreTake(spiMutex, portMAX_DELAY)) {

                digitalWrite(CS1_PIN, HIGH);
                digitalWrite(CS3_PIN, HIGH);
                digitalWrite(CS2_PIN, LOW);

                SD.remove("/parametres.json");
                SD.remove("/parametres_tmp.json");

                File file_Write_Tmp = SD.open("/parametres_tmp.json", FILE_WRITE);

                if (file_Write_Tmp) {

                    size_t n = serializeJsonPretty(config_SDP, file_Write_Tmp);

                    file_Write_Tmp.flush();
                    file_Write_Tmp.close();

                    if (n != 0) {
                        SD.remove("/parametres.json");
                        SD.rename("/parametres_tmp.json", "/parametres.json");
                    } else {
                        // Serial.println("ERREUR: Ecriture fichier JSON");
                    }
                } 
                else {
                    // Serial.println("ERREUR: Impossible d'ouvrir parametres_tmp.json");
                }

                recupConfigJsonV2();

                digitalWrite(CS2_PIN, HIGH);
                xSemaphoreGive(spiMutex);
            }

            modif_banque_wifi_en_cours = 0;
        }

    }); // fin endpoint upload




      #ifdef NOT_READY  // @date : 25/11/25 


      #endif


}
// ===============================================================================================================