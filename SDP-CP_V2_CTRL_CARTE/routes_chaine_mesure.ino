//  ..................................................................................................
// Route permettant de réinitialiser le facteur thermique 
//  ..................................................................................................
  void registerChaineMesure() {

    doc.clear();
  
    doc["E1"]["gain"] = *GAIN_V1; 
    doc["E1"]["offset"] =  0;
    doc["E2"]["gain"] = *GAIN_V2; 
    doc["E2"]["offset"] =  0;
    doc["E3"]["gain"] = *GAIN_V3; 
    doc["E3"]["offset"] =  0;
    doc["E4"]["gain"] = *GAIN_V4; 
    doc["E4"]["offset"] =  0;
    doc["E5"]["gain"] = *GAIN_V5; 
    doc["E5"]["offset"] =  0;
    doc["E6"]["gain"] = *GAIN_V6; 
    doc["E6"]["offset"] =  0;

    char buffer[2048];
    size_t n = serializeJson(doc, buffer, sizeof(buffer));

    // Publier JSON sur topic "measures"
    if (clientMQTT.println("TOPIC:esp32/chaine_mesure") == 0){
      clientMQTT.stop(); // libère la connexion fantôme 

    }else{
        clientMQTT.println(buffer); // <-- println ajoute déjà '\n'
    }
  
  }
// ===================================================================================================
// Update chaine de mesures
// ====================================================================================================
void registerUpdateChaineRoutes() {


    uint8_t offset_hex[4]={0};     // Tableau pour stocker les octets
    float temp;
  
    *GAIN_V1  = doc["configMesures"]["Mesure_1"]["Gain"];
    temp = doc["configMesures"]["Mesure_1"]["Offset"].as<float>();
    float_to_hex_array(-1*temp, offset_hex); 
    *OFFSET_MSB_V1  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];   // MSB 
    *OFFSET_LSB_V1  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];   // LSB 
    *OFFSET_DYN_V1 = doc["configMesures"]["Mesure_1"]["type"];

    *GAIN_V2  = doc["configMesures"]["Mesure_2"]["Gain"];
    temp = doc["configMesures"]["Mesure_2"]["Offset"].as<float>();
    float_to_hex_array(-1*temp, offset_hex); 
    *OFFSET_MSB_V2  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];   // MSB 
    *OFFSET_LSB_V2  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];   // LSB     
    *OFFSET_DYN_V2 = doc["configMesures"]["Mesure_2"]["type"];
            
    *GAIN_V3  = doc["configMesures"]["Mesure_3"]["Gain"];
    temp = doc["configMesures"]["Mesure_3"]["Offset"].as<float>();
    float_to_hex_array(-1*temp, offset_hex); 
    *OFFSET_MSB_V3  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];   // MSB 
    *OFFSET_LSB_V3  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];   // LSB       
    *OFFSET_DYN_V3 = doc["configMesures"]["Mesure_3"]["type"];

    *GAIN_V4  = doc["configMesures"]["Mesure_4"]["Gain"];
    temp = doc["configMesures"]["Mesure_4"]["Offset"].as<float>();
    float_to_hex_array(-1*temp, offset_hex); 
    *OFFSET_MSB_V4  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];   // MSB 
    *OFFSET_LSB_V4  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];   // LSB       
    *OFFSET_DYN_V4 = doc["configMesures"]["Mesure_4"]["type"];  

    *GAIN_V5  = doc["configMesures"]["Mesure_5"]["Gain"];
    temp = doc["configMesures"]["Mesure_5"]["Offset"].as<float>();
    float_to_hex_array(-1*temp, offset_hex); 
    *OFFSET_MSB_V5  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];   // MSB 
    *OFFSET_LSB_V5  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];   // LSB       
    *OFFSET_DYN_V5 = doc["configMesures"]["Mesure_5"]["type"];     

    *GAIN_V6  = doc["configMesures"]["Mesure_6"]["Gain"];
    temp = doc["configMesures"]["Mesure_6"]["Offset"].as<float>();
    float_to_hex_array(-1*temp, offset_hex); 
    *OFFSET_MSB_V6  =  (static_cast<uint16_t>(offset_hex[0])<<8) | offset_hex[1];   // MSB 
    *OFFSET_LSB_V6  =  (static_cast<uint16_t>(offset_hex[2])<<8) | offset_hex[3];   // LSB       
    *OFFSET_DYN_V6 = doc["configMesures"]["Mesure_6"]["type"]; 

    *offset_dyn_cmd = 1;

}
// ..............................................................................................................


