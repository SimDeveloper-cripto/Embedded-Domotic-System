// This is my personal MQTT Client Library!
// Author: Simone Catapano

#pragma once

#include <cstring>
#include <iostream>
#include <mosquittopp.h>

class ClientMQTT : public mosqpp::mosquittopp {
public:
    ClientMQTT(const char* id, const char* host, const int port);
    virtual ~ClientMQTT();

    void on_connect(int rc) override;
    void on_message(const mosquitto_message* message) override;
    void on_subscribe(int mid, int qos_count, const int* granted_qos) override;

private:
    void processMessage(const char* message);
};