// ...............................................................................;
// Route permettant de vérifier l'état du stack des tâches
// ...............................................................................;
  void registerTaskAnalysisRoutes() {
 
   
   doc.clear();
  
    // Entrée 1 : 

    doc["Ecran"] = taskDataAnalysis[0]; 
    doc["SD"] =  taskDataAnalysis[1];
    doc["WiFi"] =  taskDataAnalysis[2];
    doc["Modbus"] = taskDataAnalysis[3];
    doc["Scheduler"] = taskDataAnalysis[4];
    doc["Reception"] = taskDataAnalysis[5];
    doc["Ladder"] = taskDataAnalysis[6];
    doc["Emission"] =  taskDataAnalysis[7];
    doc["Basic"] =  taskDataAnalysis[8];


    char buffer[2048];
    size_t n = serializeJson(doc, buffer, sizeof(buffer));

    // Publier JSON sur topic "measures"
    if (clientMQTT.println("TOPIC:esp32/taskAnalysis") == 0){
      clientMQTT.stop(); // libère la connexion fantôme 

    }else{
        clientMQTT.println(buffer); // <-- println ajoute déjà '\n'
    }

    

}
//  ..................................................................................................