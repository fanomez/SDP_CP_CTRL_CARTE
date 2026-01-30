  void registerDataFth() {
 
   
   doc.clear();
  
      doc["dataFth"]["G1"]["ID_0"]["periode"] = *Periode_Fth_N_C1[0];
      doc["dataFth"]["G1"]["ID_1"]["periode"] = *Periode_Fth_N_C1[1];
      doc["dataFth"]["G1"]["ID_2"]["periode"] = *Periode_Fth_N_C1[2];
      doc["dataFth"]["G1"]["ID_3"]["periode"] = *Periode_Fth_N_C1[3];

      doc["dataFth"]["G1"]["ID_0"]["Ith"] = *I_thermique_N_C1[0];
      doc["dataFth"]["G1"]["ID_1"]["Ith"] = *I_thermique_N_C1[1];
      doc["dataFth"]["G1"]["ID_2"]["Ith"] = *I_thermique_N_C1[2];
      doc["dataFth"]["G1"]["ID_3"]["Ith"] = *I_thermique_N_C1[3];

      // Générateur 2 :
      doc["dataFth"]["G2"]["ID_0"]["periode"] = *Periode_Fth_N_C2[0];
      doc["dataFth"]["G2"]["ID_1"]["periode"] = *Periode_Fth_N_C2[1];
      doc["dataFth"]["G2"]["ID_2"]["periode"] = *Periode_Fth_N_C2[2];
      doc["dataFth"]["G2"]["ID_3"]["periode"] = *Periode_Fth_N_C2[3];

      doc["dataFth"]["G2"]["ID_0"]["Ith"] = *I_thermique_N_C2[0];
      doc["dataFth"]["G2"]["ID_1"]["Ith"] = *I_thermique_N_C2[1];
      doc["dataFth"]["G2"]["ID_2"]["Ith"] = *I_thermique_N_C2[2];
      doc["dataFth"]["G2"]["ID_3"]["Ith"] = *I_thermique_N_C2[3];

      // Générateur 3 :
      doc["dataFth"]["G3"]["ID_0"]["periode"] = *Periode_Fth_N_C3[0];
      doc["dataFth"]["G3"]["ID_1"]["periode"] = *Periode_Fth_N_C3[1];
      doc["dataFth"]["G3"]["ID_2"]["periode"] = *Periode_Fth_N_C3[2];
      doc["dataFth"]["G3"]["ID_3"]["periode"] = *Periode_Fth_N_C3[3];

      doc["dataFth"]["G3"]["ID_0"]["Ith"] = *I_thermique_N_C3[0];
      doc["dataFth"]["G3"]["ID_1"]["Ith"] = *I_thermique_N_C3[1];
      doc["dataFth"]["G3"]["ID_2"]["Ith"] = *I_thermique_N_C3[2];
      doc["dataFth"]["G3"]["ID_3"]["Ith"] = *I_thermique_N_C3[3];

    char buffer[2048];
    size_t n = serializeJson(doc, buffer, sizeof(buffer));

    // Publier JSON sur topic "measures"
    if (clientMQTT.println("TOPIC:esp32/dataFth") == 0){
      clientMQTT.stop(); // libère la connexion fantôme 

    }else{
        clientMQTT.println(buffer); // <-- println ajoute déjà '\n'
    }

    
}