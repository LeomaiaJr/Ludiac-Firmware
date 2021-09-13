#include <ESP8266WiFi.h>

#define SSID "PISCO"
#define PASSWD "6tsa-7cnpq-53js"
#define SOCK_PORT 123

WiFiServer sockServer(SOCK_PORT);

void setup(){
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
    WiFiClient client = sockServer.available();
    if (client){
        while (client.connected()){
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
