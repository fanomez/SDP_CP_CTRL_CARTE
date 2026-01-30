// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                         EVENTS ETHERNET
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void WiFiEvent(WiFiEvent_t event) {

    switch (event) {

        case ARDUINO_EVENT_ETH_START:
            ETH.setHostname("esp32-lan8720");
            eth_connected = false;
            eth_server_started = false;
            break;

        case ARDUINO_EVENT_ETH_CONNECTED:
            // PHY OK, pas encore d'IP
            break;

        case ARDUINO_EVENT_ETH_GOT_IP:
            // Réseau prêt
            eth_connected = true;
            break;

        case ARDUINO_EVENT_ETH_DISCONNECTED:
            eth_connected = false;
            eth_server_started = false;
            break;

        case ARDUINO_EVENT_ETH_STOP:
            eth_connected = false;
            eth_server_started = false;
            break;

        default:
            break;
    }
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
