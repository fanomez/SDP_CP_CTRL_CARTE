// ..............................................................................................................
  void registerRootRoutes() {

      
       /* char buffer[128];  // taille suffisante pour contenir le message
        snprintf(buffer, sizeof(buffer),
                "SREM Technologies : SDP-CP V2 | v%s | Machine: %s | DDL: %s",
                version,machine,date);*/

       doc.clear();
  
      doc["version"] = version; 
      doc["machine"] =  machine;
      doc["date"] =  date;

      char buffer[2048];
      size_t n = serializeJson(doc, buffer, sizeof(buffer));

      // Publier JSON sur topic "measures"
      if (clientMQTT.println("TOPIC:esp32/version") == 0){
        clientMQTT.stop(); // libère la connexion fantôme 

      }else{
          clientMQTT.println(buffer); // <-- println ajoute déjà '\n'
      }





  }
// ..............................................................................................................

