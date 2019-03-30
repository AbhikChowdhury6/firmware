#include <FastLED.h>
#include "WiFi.h"
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#define DATA_PIN 12
#define NUM_LEDS 10

#define MAX_JSON_LEN 100
#define MAX_BUFF_LEN 100

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const char* ssid = "chowderphone";
const char* password = "31415926";

bool wifi = true;

String buff[MAX_BUFF_LEN];
int buffSize = 0;
StaticJsonDocument<200> doc;

String incoming;
bool toSend = false;
CRGB leds[NUM_LEDS];

unsigned long startMicro;
unsigned long currMicro;
unsigned long aniStart;
int frame;
bool started = false;

/**********************/
//Application Specific variables!

//backwrap
int distan; 

//hapwrap
//int direct;
//int elevat;
//int distan;

//hapticChair
//int

//HapticCuffs
//int
//int
//int

AsyncWebSocketClient * client1 = NULL;

void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){

  client1 = client;
  
  if(type == WS_EVT_CONNECT){
 
    Serial.println("Websocket client connection received");
    client->text("Hello from ESP32 Server");
    
 
  } else if(type == WS_EVT_DISCONNECT){
    Serial.println("Client disconnected");
    client1 = NULL;
 
  } if(type == WS_EVT_DATA){
    Serial.println("Got Data!");

    for(int i=0; i < len; i++)
          incoming += (char) data[i];
    
    Serial.println(incoming);

    if (buffSize < MAX_BUFF_LEN)
      buff[buffSize] = incoming;

    buffSize += 1;
    incoming = "";
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
  if (Serial.available() > 0)
    if (buffSize < MAX_BUFF_LEN)
      buff[buffSize] = Serial.read();


  //buttons

  ///////////////////////////////////
  //parsing if data available
  if (buffSize > 0) {
    DeserializationError error = deserializeJson(doc, buff[0]);

    // Test if parsing succeeds.
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }
    
    Serial.println((char)doc["name"]);
    
  /*************************/
  //put command code here!
 
  //hapBack
  distan = doc["data"][0];
  Serial.println(distan);
  
  //hapWrap
//  direct = doc["data"][0];
//  elevat = doc["data"][1];
//  distan = doc["data"][2];
//  Serial.println(direct);
//  Serial.println(elevat);
//  Serial.println(distan);

//  //hapticChair
//  actionUnit = doc["data"][0];

//  //hapticCuffs
//  oneOn = doc["data"][0];
//  twoOn = doc["data"][1];
//  thrOn = doc["data"][2];


  
 /**************************/
  for(int i = 1; i < buffSize ; i++)
    buff[i-1] = buff[i];
  buff[buffSize] = "";
  buffSize -= 1;
  started = true;
  aniStart = startMicro;
  }

Serial.println("acting");
////////////////////////////
//acting

  if (wifi) //send any updates
    if(toSend)
      if (client1 != NULL) {
        client1->text("Hello from ESP32 Server");
        Serial.println("trying to Send");
      }

Serial.println("custom");
/***************************/
  //put timing and execution code here!
  if(started){
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CRGB::Black;
    a1(distan);
  }  
  
  

/**************************/

Serial.println("trying LED write");
  FastLED.show();
  
  currMicro = micros();
  if (currMicro - startMicro >= 0) //protect from overflows
    delayMicroseconds(50000 - (currMicro - startMicro));
}

void a1(int maxRow) {
  unsigned long msOnTIme = 500 * 1000;
  
  Serial.println("trying frame calc");
  Serial.println(startMicro);
  Serial.println(aniStart);
  if (startMicro - aniStart != 0)
    frame = (startMicro - aniStart) / msOnTIme;

  Serial.println(frame);
  int litRow = frame;

  Serial.println("trying LED set");
  
  leds[litRow] = CRGB::White;
  leds[9 - litRow] = CRGB::White;

  if (litRow > maxRow){
    started = false;
  }
}

void a2() {
  
}

void r1() {
  
}

void r2() {
  
}
