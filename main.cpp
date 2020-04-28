#include "FLinfluxDB.hpp"
#include "MosqMQTTWrapper.hpp"
#include <iostream>
#include <thread>

using namespace std;
using namespace FLIDB;
using namespace MQTTW;

void MQTTDoorLoop(MosqMqttWrapper* MQTT)
{
    MQTT->loop_forever();
}

void MQTTCheckLoop(FLinfluxDB database, MosqMqttWrapper* MQTT)
{
    string input;
    while (1)
    {
        input = MQTT->GetMessage();
        if (input.find("@sunvalue") != std::string::npos)
        {
            input.erase(0,10);
            database.PostData("sun","russia","moscow",stof(input));
        }
    }
}

int main()
{
    MosqMqttWrapper* MQTT = new MosqMqttWrapper("influxdbclient", "localhost", 1883);
    FLinfluxDB FLDB("127.0.0.1", 8086,"FlowerLampDB");
    mosqpp::lib_init();
    std::thread t1 = std::thread(MQTTDoorLoop, MQTT);
    std::thread t2 = std::thread(MQTTCheckLoop, FLDB, MQTT);
    t1.detach();
    t2.detach();
    cin.get();
    return 0;
}

