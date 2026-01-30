  void registerDefautSD() {
 
   
   doc.clear();
  
    doc["InitSD"] = *INIT_SD; 
    doc["fichier_present"] =  *READ_SD;
    doc["recuperation_donnes"] =  *EXTRACT_CONFIG;
    doc["ecriture_parametres"] = *WRITE_CONFIG;

    char buffer[2048];
    size_t n = serializeJson(doc, buffer, sizeof(buffer));

    // Publier JSON sur topic "measures"
    if (clientMQTT.println("TOPIC:esp32/defautSD") == 0){
      clientMQTT.stop(); // libère la connexion fantôme 

    }else{
        clientMQTT.println(buffer); // <-- println ajoute déjà '\n'
    }

    
}