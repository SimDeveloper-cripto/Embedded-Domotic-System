#include "clientMQTT.hpp"

ClientMQTT::ClientMQTT(const char* id, const char* host, int port) : mosquittopp(id) {
    mosqpp::lib_init();
    connect(host, port, 60);
}

ClientMQTT::~ClientMQTT() {
    mosqpp::lib_cleanup();
}

/* [PUBLIC] */
void ClientMQTT::on_connect(int rc) {
    if (rc == 0) {
        std::cout << "Connected to MQTT broker." << std::endl;
        subscribe(nullptr, "your/topic");  // Subscribe to Topic
    } else {
        std::cerr << "Failed to connect, return code " << rc << std::endl;
    }
}

void ClientMQTT::on_message(const mosquitto_message* message) {
    if (message->payloadlen) {
        std::cout << "Received message on topic " << message->topic << ": "
                  << static_cast<char*>(message->payload) << std::endl;
        // Esegui l'elaborazione del messaggio qui
        processMessage(static_cast<char*>(message->payload));
    }
}

void ClientMQTT::on_subscribe(int mid, int qos_count, const int* granted_qos) {
    std::cout << "Subscription succeeded." << std::endl;
}

/* [PRIVATE] */
void ClientMQTT::processMessage(const char* message) {
    // Example
    std::cout << "Message lenght = " << std::strlen(message) << std::endl;
}