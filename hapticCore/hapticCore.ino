#include <FastLED.h>
#include "WiFi.h"
#include <QueueArray.h>
#include <ESPAsyncWebServer.h>

//WiFiServer wifiServer(80);

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const char* ssid = "chowderphone";
const char* password = "31415926";

bool wifi = true;

#define DATA_PIN 14
#define NUM_LEDS 1
#define MAX_CMD_LEN 100
#define MAX_BUFF_LEN 100

CRGB leds[NUM_LEDS];

QueueArray <String> buff;

String incoming = "";

unsigned long startMicro;
unsigned long currMicro;


void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
 
  if(type == WS_EVT_CONNECT){
 
    Serial.println("Websocket client connection received");
    client->text("Hello from ESP32 Server");
 
  } else if(type == WS_EVT_DISCONNECT){
    Serial.println("Client disconnected");
 
  }
}

void setup() {
  //initialize strip
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);

  //initialize serial
  Serial.begin(115200);
  Serial.println("HIII");
  //initialize wifi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println(WiFi.localIP());
  if (WiFi.status() != WL_CONNECTED)
    wifi=false;
  if (wifi){
    Serial.println(WiFi.localIP());
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
 
  server.begin();
  }

}

void loop() {
  startMicro = micros();
  Serial.println(startMicro);
  /////////////////////////////////////////////
  //reading

  //serial
  if (Serial.available() > 0) {
    incoming += Serial.read();
  }

  //wifi
//  if (wifi){
//    WiFiClient client = wifiServer.available();
//    if (client) {
//      Serial.println("Client Connected!");
//      while (client.connected()) {
//        while (client.available()>0) {
//          char c = client.read();
//          //client.write(c);
//        }
//       //delay(10);
//      }
//    } else
//      Serial.println("No Client");
//  }

  //buttons

///////////////////////////////////
//parsing if new data


////////////////////////////
//acting


  
  currMicro = micros();
  if (currMicro - startMicro >= 0) //protect from overflows
    delayMicroseconds(500000 - (currMicro - startMicro));
}

void a1() {
  
}

void a2() {
  
}

void r1() {
  
}

void r2() {
  
}
