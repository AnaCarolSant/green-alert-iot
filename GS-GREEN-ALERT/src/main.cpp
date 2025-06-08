

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>



#define boardLED 2
#define DHTPIN 12
#define DHTTYPE DHT22
#define POTPIN 34

const char* ID = "GS";
const char* moduleID = "GREEN-ALERT";
const char* SSID = "Wokwi-GUEST";
const char* PASSWORD = "";

const char* BROKER_MQTT  = "4.201.157.200"; 
const int   BROKER_PORT  = 1883;
const char* mqttUser     = "iot"; 
const char* mqttPassword = "Fiap@2tdsvms"; 

#define TOPICO_PUBLISH "sensores/ac"



WiFiClient espClient;
PubSubClient MQTT(espClient);
JsonDocument doc;
char buffer[256];

DHT dht(DHTPIN, DHTTYPE);

float temperatura = 0.0;
float umidade = 0.0;
int valorPot = 0;

void initWiFi() {
    WiFi.begin(SSID, PASSWORD);
    Serial.print("Conectando ao Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}

void reconectaWiFi() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Reconectando Wi-Fi...");
        initWiFi();
    }
}


void initMQTT() {
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);
    while (!MQTT.connected()) {
        Serial.println("Conectando ao Broker MQTT...");
        if (MQTT.connect(moduleID, mqttUser, mqttPassword)) {
            Serial.println("Conectado ao Broker!");
        } else {
            Serial.print("Falha na conexão. Estado: ");
            Serial.println(MQTT.state());
            delay(2000);
        }
    }
}

void verificaConexoesWiFiEMQTT() {
    reconectaWiFi();
    if (!MQTT.connected()) {
        initMQTT();
    }
    MQTT.loop();
}



bool lerSensorDHT(float* temp, float* umid) {
    float t = dht.readTemperature();
    float u = dht.readHumidity();

    if (!isnan(t) && !isnan(u)) {
        *temp = t;
        *umid = u;
        return true;
    }
    return false;
}



void piscaLed() {
    digitalWrite(boardLED, HIGH);
    delay(300);
    digitalWrite(boardLED, LOW);
}



void enviaEstadoOutputMQTT() {
    MQTT.publish(TOPICO_PUBLISH, buffer);
    Serial.println("Mensagem publicada com sucesso!");
}



void setup() {
    Serial.begin(115200);
    pinMode(boardLED, OUTPUT);
    pinMode(POTPIN, INPUT);
    dht.begin();
    initWiFi();
    initMQTT();
}



void loop() {
    verificaConexoesWiFiEMQTT();

   
    valorPot = analogRead(POTPIN);

    bool leituraOk = lerSensorDHT(&temperatura, &umidade);

    
    doc.clear();
    doc["ID"] = ID;
    doc["Sensor"] = moduleID;
    doc["IP"] = WiFi.localIP().toString();
    doc["MAC"] = WiFi.macAddress();

    if (leituraOk) {
        doc["Temperatura"] = temperatura;
        doc["Umidade"] = umidade;
    } else {
        doc["Temperatura"] = "Falha";
        doc["Umidade"] = "Falha";
    }

    doc["Potenciometro"] = valorPot;

    serializeJson(doc, buffer);
    Serial.println(buffer);
    enviaEstadoOutputMQTT();
    piscaLed();

    delay(10000);
}
