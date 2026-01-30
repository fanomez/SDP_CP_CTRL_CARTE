// ........................................................................................................
// Route permettant d'accéder à des variables de debugs , utile durant la phase de diagnostic et de debug
// ........................................................................................................
  void registerDegugRoutes() {
    
    doc.clear();

    // Entrée 1
    doc["Debug_Val_1"] = *C_Etat_Config_XPORT; 
    doc["Debug_Val_2"] = *C_Config_XPORT;
    doc["Debug_Val_3"] = *TOR_E3;
    doc["Debug_Val_4"] = *TOR_E4;
    doc["Debug_Val_5"] = *TOR_E5;
    doc["Debug_Val_6"] = *C_Debug_Val_6;
    doc["Debug_Val_7"] = *C_Debug_Val_7;
    doc["Debug_Val_8"] = *C_Debug_Val_8;
    doc["Debug_Val_9"] = *C_Debug_Val_9;
    doc["Debug_Val_10"] = *C_Debug_Val_10;
    doc["Debug_Val_11"] = *C_Debug_Val_11;
    doc["Debug_Val_12"] = *C_Debug_Val_12;

    char buffer[2048];
    size_t n = serializeJson(doc, buffer, sizeof(buffer));

    // Publier JSON sur topic "measures"
    if (clientMQTT.println("TOPIC:esp32/debug") == 0){
      clientMQTT.stop(); // libère la connexion fantôme 

    }else{
        clientMQTT.println(buffer); // <-- println ajoute déjà '\n'
    }


}
// ........................................................................................................
