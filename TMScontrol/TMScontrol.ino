
#include "WiFi.h"
#include <ESPAsyncWebServer.h>

int potIncrement = 100;//set to max to then be decreased

void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  if(type == WS_EVT_CONNECT){
    Serial.println("Websocket client connection received");
    client->text("Hello from ESP32 Server");
 
  } else if(type == WS_EVT_DISCONNECT){
    Serial.println("Client disconnected");
 
  } if(type == WS_EVT_DATA){
    Serial.println("Got Data!");
    reciv = true;

    for(int i=0; i < len; i++)
          incoming += (char) data[i];
    
    moveTo(incoming.toInt());
  }
}

void setup() {
  //define u/d and incrementpin
  pinMode(udPIN, OUTPUT);
  pinMode(incPIN, OUTPUT);
  //move to postion zero
  moveTo(0);
  //move to a comfortable temprature
   //the ui will take in an absolute value and then go to it
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(potIncrement);
  delay(200)

}

void moveTo(int){
  
}
