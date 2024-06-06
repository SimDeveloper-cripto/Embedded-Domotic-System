#include "clientMQTT.hpp"

int main() {
    const char* id   = "MQTTClient";
    const char* host = "localhost";
    const int port   = 1883;

    ClientMQTT client(id, host, port);

    while (true) {
        int rc = client.loop();
        if (rc) {
            std::cout << "Connection error, trying to reconnect ..." << std::endl;
            client.reconnect();
        }
    }

    return 0;
}