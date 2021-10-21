#include <ESP8266WiFi.h>

#define SSID "PISCO"
#define PASSWD "6tsa-7cnpq-53js"
#define SOCK_PORT 123

WiFiServer sockServer(SOCK_PORT);

int leftSensorValue;
int rightSensorValue;

void setup(){
    pinMode(D0, OUTPUT);
    pinMode(D7, INPUT);
    pinMode(D1, INPUT);
    Serial.begin(9600);
    
    delay(1000);
    WiFi.begin(SSID,PASSWD);
    while (WiFi.status() != WL_CONNECTED){
      delay(100);
      Serial.println("Não conectado ao wifi!");
     }

    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    sockServer.begin(); //abre a porta 123
}

void loop(){
    digitalWrite(D0, HIGH);
    WiFiClient client = sockServer.available();
    if (client){
        while (client.connected()){
            String leftStr = "LEFT";
            String rightStr = ";RIGHT";
            leftSensorValue = !digitalRead(D7);
            rightSensorValue = digitalRead(D1);
            Serial.println(leftStr + leftSensorValue + rightStr + rightSensorValue);
            client.print(leftStr + leftSensorValue + rightStr + rightSensorValue);
            delay(500);
            while (client.available() > 0){
                uint8_t value = client.read();
                Serial.write(value);
                client.print("Hello from ESP32!");
            }
            delay(10);
        }
        client.stop(); //acabou a leitura dos dados. Finaliza o client.
    }
}