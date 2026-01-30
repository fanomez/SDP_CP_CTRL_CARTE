// ..............................................................................................................
// Route permetttant l'acquisition des valeurs des entrées de mesure [TCP] 
// ..............................................................................................................
void registerMesuresRoutes() {  

    doc.clear();
    
    // Entrée 1
    doc["11"] = D()[11];
    doc["12"] = D()[12];
    doc["13"] = D()[13];
    doc["14"] = D()[14];
    doc["15"] = D()[15];

    // Entrée 2
    doc["21"] = D()[21];
    doc["22"] = D()[22];
    doc["23"] = D()[23];
    doc["24"] = D()[24];
    doc["25"] = D()[25];

    // Entrée 3
    doc["31"] = D()[31];
    doc["32"] = D()[32];
    doc["33"] = D()[33];
    doc["34"] = D()[34];
    doc["35"] = D()[35];

    // Entrée 4
    doc["41"] = D()[41];
    doc["42"] = D()[42];
    doc["43"] = D()[43];
    doc["44"] = D()[44];
    doc["45"] = D()[45];

    // Entrée 5
    doc["728"] = D()[728];
    doc["729"] = D()[729];
    doc["730"] = D()[730];
    doc["731"] = D()[731];
    doc["732"] = D()[732];        

    // Entrée 6
    doc["733"] = D()[733];
    doc["734"] = D()[734];
    doc["735"] = D()[735];
    doc["736"] = D()[736];
    doc["737"] = D()[737];        
     
    doc["heap"] = esp_get_free_heap_size() ;

    // Horodatage 
    doc["jj"] = jour; 
    doc["mo"] = mois; 
    doc["aa"] = annee; 

    doc["hh"] = *C_Hours; 
    doc["mm"] = *C_Minutes; 
    doc["ss"] = *C_Secondes;
    doc["bit_vie"] = etatBit;

    char buffer[2048];
    size_t n = serializeJson(doc, buffer, sizeof(buffer));

    // Publier JSON sur topic "measures"
    if (clientMQTT.println("TOPIC:esp32/measures") == 0){
      clientMQTT.stop(); // libère la connexion fantôme 

    }else{
        clientMQTT.println(buffer); // <-- println ajoute déjà '\n'
    }
    

}
// ..............................................................................................................