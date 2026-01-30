// ........................................................................................................
// Route permettant de commander les sorties analogiques 
// ........................................................................................................
  /*void registerCommandesRoutes(WebServer &server) {

server.on("/set_values", HTTP_POST, [&server](){
  
  doc.clear();

  DeserializationError err = deserializeJson(doc, server.arg(0));

  if (err) {
    server.send(400, "application/json", "{\"error\":\"JSON invalide\"}");
    return;
  }

  // Validate presence of keys
  if (!doc.containsKey("ANA") || !doc.containsKey("TOR")) {
    server.send(400, "application/json", "{\"error\":\"Champs 'ANA' ou 'TOR' manquants\"}");
    return;
  }

  JsonObject ana = doc["ANA"];
  JsonObject tor = doc["TOR"];

  

 *Sortie_analogique_V1 = ana["ANA_1"].as<int>();
 *Sortie_analogique_V2 = ana["ANA_2"].as<int>();
 *Sortie_analogique_V3 = ana["ANA_3"].as<int>();
 *Sortie_analogique_V4 = ana["ANA_4"].as<int>();
  // ---------------------------------------------------------------------------------------------------------------------------------------
  // Lancer le mode test
 // --------------------------------------------------------------------------------------------------------------------------------------- 
 if (*Sortie_analogique_V1 > 0 || *Sortie_analogique_V2 > 0 || *Sortie_analogique_V3 > 0 || *Sortie_analogique_V4 > 0){
      *MODE_TEST = 1; 
 }else if (*Sortie_analogique_V1 == 0 && *Sortie_analogique_V2 == 0 && *Sortie_analogique_V3 == 0 && *Sortie_analogique_V4 == 0){
      *MODE_TEST = 0; 
 }
 // ---------------------------------------------------------------------------------------------------------------------------------------


  server.send(200, "application/json", "{\"status\":\"Valeurs ANA et TOR traitées\"}");
});

}*/
// ........................................................................................................
// Route permettant de commander les sorties analogiques 
// ........................................................................................................
  void registerCommandesRoutes(String cmd) {


                if (doc.containsKey("ANA")) {

                  JsonObject ana = doc["ANA"];

                  if (ana.containsKey("ANA_1")) {
                    *Sortie_analogique_V1 = ana["ANA_1"].as<int>();
                  }

                  if (ana.containsKey("ANA_2")) {
                    *Sortie_analogique_V2 = ana["ANA_2"].as<int>();
                  }

                  if (ana.containsKey("ANA_3")) {
                      *Sortie_analogique_V3 = ana["ANA_3"].as<int>();
                  }

                  if (ana.containsKey("ANA_4")) {
                      *Sortie_analogique_V4 = ana["ANA_4"].as<int>();
                  }
                }



                if (doc.containsKey("TOR")) {

                  JsonObject tor = doc["TOR"];

                  if (tor.containsKey("TOR_1")) {
                    *TOR_S1 = tor["TOR_1"].as<bool>();
                  }

                  if (tor.containsKey("TOR_2")) {
                    *TOR_S2 = tor["TOR_2"].as<bool>();
                  }

                  if (tor.containsKey("TOR_3")) {
                    *TOR_S3 = tor["TOR_3"].as<bool>();
                  }

                  if (tor.containsKey("TOR_4")) {
                    *TOR_S4 = tor["TOR_4"].as<bool>();
                  }
                }

                // ---------------------------------------------------------------------------------------------------------------------------------------
                // Lancer le mode test
                // --------------------------------------------------------------------------------------------------------------------------------------- 
                if (*Sortie_analogique_V1 > 0 || *Sortie_analogique_V2 > 0 || *Sortie_analogique_V3 > 0 || *Sortie_analogique_V4 > 0){
                      *MODE_TEST = 1; 
                }else if (*Sortie_analogique_V1 == 0 && *Sortie_analogique_V2 == 0 && *Sortie_analogique_V3 == 0 && *Sortie_analogique_V4 == 0){
                      *MODE_TEST = 0; 
                }
                // ---------------------------------------------------------------------------------------------------------------------------------------

}
// ........................................................................................................