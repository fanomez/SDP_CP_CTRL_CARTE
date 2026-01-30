// ........................................................................................................
// Route permettant de configurer le XPORT
// ........................................................................................................
  void registerConfigXportRoutes() {

      if (doc.containsKey("request_config_XPORT")) {

        JsonObject IP = doc["request_config_XPORT"];

          

          ip0 = IP["IP0"].as<int>();
          ip1 = IP["IP1"].as<int>();
          ip2 = IP["IP2"].as<int>();
          ip3 = IP["IP3"].as<int>();

          *C_Debug_Val_9 = ip0;
          *C_Debug_Val_10 = ip1;
          *C_Debug_Val_11 = ip2;
          *C_Debug_Val_12 = ip3;


      // Flag indiquant qu'on est dans le mode configuration de la COM Modbus 
        *C_Config_XPORT = 1 ;

  }

}
// ........................................................................................................