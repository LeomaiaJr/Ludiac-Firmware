#include <ESP8266WiFi.h>

#define SSID "PISCO"
#define PASSWD "6tsa-7cnpq-53js"
#define SOCK_PORT 123
#define MAX_CLIENTS 2

WiFiServer sockServer(SOCK_PORT);

int leftSensorValue;
int rightSensorValue;

WiFiClient *clients[MAX_CLIENTS] = { NULL };

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

    sockServer.begin();
}

void loop(){
    digitalWrite(D0, HIGH);
    WiFiClient newClient = sockServer.available();
    if (newClient){
        Serial.println("new client");
        for (int i=0 ; i<MAX_CLIENTS ; ++i) {
          if (NULL == clients[i]) {
              clients[i] = new WiFiClient(newClient);
              break;
          }
        }
    }
    String leftStr = "LEFT";
    String rightStr = ";RIGHT";
    leftSensorValue = !digitalRead(D7);
    rightSensorValue = digitalRead(D1);
    Serial.println(leftStr + leftSensorValue + rightStr + rightSensorValue);
    
    for (int j=0 ; j<MAX_CLIENTS ; ++j) {
      if (NULL != clients[j]) {
        if(clients[j]->connected()){
          clients[j]->print(leftStr + leftSensorValue + rightStr + rightSensorValue);
        }
      }
    }
    delay(400);
}