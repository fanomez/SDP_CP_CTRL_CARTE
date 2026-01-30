// ........................................................................................................
// Route permmettant de configurer l'offset et le gain des voies de mesures
// ........................................................................................................
  void registerConfigOffsetRoutes(WebServer &server) {
    server.on("/set_bit", HTTP_POST, [&server](){
    
    doc.clear();
    
    DeserializationError err = deserializeJson(doc, server.arg(0));

    if (err) {
      server.send(400, "application/json", "{\"error\":\"JSON invalide\"}");
      return;
    }

    // Validate presence of keys
    if (!doc.containsKey("Mesure_1") || !doc.containsKey("Mesure_2")|| !doc.containsKey("Mesure_3")|| !doc.containsKey("Mesure_4") || !doc.containsKey("Mesure_5")|| !doc.containsKey("Mesure_6")) {
      server.send(400, "application/json", "{\"error\":\"Champs 'ANA' ou 'TOR' manquants\"}");
      return;
    }

    JsonObject EA_1 = doc["Mesure_1"];
    JsonObject EA_2 = doc["Mesure_2"];
    JsonObject EA_3 = doc["Mesure_3"];
    JsonObject EA_4 = doc["Mesure_4"];
    JsonObject EA_5 = doc["Mesure_5"];
    JsonObject EA_6 = doc["Mesure_6"];

  uint8_t offset_hex[4]={0};     // Tableau pour stocker les octets
  float temp;
  
  // .....................................................
  // Entrée EA1
  // .....................................................
  *GAIN_V1 = EA_1["Gain"].as<int>();

  temp = EA_1["Offset"].as<float>();

  float_to_hex_array(-1*temp, offset_hex); 

  *OFFSET_MSB_V1  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];   // MSB 
  *OFFSET_LSB_V1  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];   // LSB 

  *OFFSET_DYN_V1 = EA_1["Type"].as<int>();
  // .....................................................
  // Entrée EA2
  // .....................................................
  *GAIN_V2  = EA_2["Gain"].as<int>();

  temp = EA_2["Offset"].as<float>();

  float_to_hex_array(-1*temp, offset_hex); 

  *OFFSET_MSB_V2  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];   // MSB 
  *OFFSET_LSB_V2  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];   // LSB 

  *OFFSET_DYN_V2  = EA_2["Type"].as<int>();
  // .....................................................
  // Entrée EA3
  // .....................................................
  *GAIN_V3    = EA_3["Gain"].as<int>();

  temp = EA_3["Offset"].as<float>();

  float_to_hex_array(-1*temp, offset_hex); 

  *OFFSET_MSB_V3  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];   // MSB 
  *OFFSET_LSB_V3  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];   // LSB 

  *OFFSET_DYN_V3  = EA_3["Type"].as<int>();
  // .....................................................
  // Entrée EA4
  // .....................................................
  *GAIN_V4  = EA_4["Gain"].as<int>();

  temp = EA_4["Offset"].as<float>();

  float_to_hex_array(-1*temp, offset_hex); 

  *OFFSET_MSB_V4  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];   // MSB 
  *OFFSET_LSB_V4  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];   // LSB 

  *OFFSET_DYN_V4  = EA_4["Type"].as<int>();
  // .....................................................
  // Entrée EA5
  // .....................................................
  *GAIN_V5  = EA_5["Gain"].as<int>();

  temp = EA_5["Offset"].as<float>();

  float_to_hex_array(-1*temp, offset_hex); 

  *OFFSET_MSB_V5  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];    // MSB 
  *OFFSET_LSB_V5  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];    // LSB 

  *OFFSET_DYN_V5  = EA_5["Type"].as<int>();
  // .....................................................
  // Entrée EA6
  // .....................................................
  *GAIN_V6  = EA_6["Gain"].as<int>();

  temp = EA_6["Offset"].as<float>();

  float_to_hex_array(-1*temp, offset_hex); 

  *OFFSET_MSB_V6  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];   // MSB 
  *OFFSET_LSB_V6  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];   // LSB 


  *OFFSET_DYN_V6  = EA_6["Type"].as<int>();

  
  *offset_dyn_cmd = 1 ;

    server.send(200, "application/json", "{\"status\":\"Offset dyn\"}");
  });

}
// ........................................................................................................