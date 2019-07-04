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

unsigned long LstartMicro;
unsigned long currMicro;
unsigned long aniStart;
int frame;
bool started = false;

/**********************/
//Application Specific variables!

//backwrap
int distan; 
int pattern;


AsyncWebSocketClient * client1 = NULL;

//on a websocket event run this
void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){

  client1 = client;//save the client so we can send it data later
  
  if(type == WS_EVT_CONNECT){
//    Serial.println("Websocket client connection received");
    client->text("Hello from ESP32 Server");
 
  } else if(type == WS_EVT_DISCONNECT){
//    Serial.println("Client disconnected");
    client1 = NULL;
 
  } if(type == WS_EVT_DATA){
//    Serial.println("Got Data!");

    for(int i=0; i < len; i++)
          incoming += (char) data[i];
    
//    Serial.println(incoming);// incoming has the json string

    if (buffSize < MAX_BUFF_LEN)
      buff[buffSize] = incoming;//add it to the buffer of commands if there's space

    buffSize += 1;
    incoming = "";
  }
}

void setup() {
  //initialize strip
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);

  //initialize serial
  Serial.begin(115200);
//  Serial.println("HIII");
  
  //initialize wifi
  WiFi.begin(ssid, password);

  for (int i = 0; i < 1000 && WiFi.status() != WL_CONNECTED; i++) { //try connceting to wifi a few times
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  
  if (WiFi.status() != WL_CONNECTED){
    wifi=false;
    Serial.println("Couldn't connect to wifi </3");
  }

  
  if (wifi){
    Serial.println(WiFi.localIP());
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
    server.begin();
  }

}

void loop() {
  LstartMicro = micros();
//  Serial.println(startMicro);
  /////////////////////////////////////////////
  //reading

  
  //serial
  if (Serial.available() > 0)
    if (buffSize < MAX_BUFF_LEN)
      buff[buffSize] = Serial.read();

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
  pattern = doc["data"][0];
  Serial.println(pattern);
  
  distan = doc["data"][1];
  Serial.println(distan);


  
 /**************************/
  for(int i = 1; i < buffSize ; i++)
    buff[i-1] = buff[i];
  buff[buffSize] = "";
  buffSize -= 1;
  started = true;
  aniStart = LstartMicro;
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
  //if time for frame switch
  if(started)//set all haxels off for frame switch
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CRGB::Black;
  //take the next frame off of the buffer if there is one and diaplay
    //loop through the frame setting every pixel to the appropriate color
    
  Serial.println("custom");
  /***************************/
  //put timing and execution code here!
  if(started){
    if(pattern == 1)
      a1(distan);
    if(pattern == 2)
      a2(distan);
    if(pattern == 3)
      r1(distan);
    if(pattern == 4)
      r2(distan);
  }  
  
  

  /**************************/

  Serial.println("trying LED write");
  FastLED.show();
  
  currMicro = micros();
  if (currMicro - LstartMicro >= 0) //protect from overflows
    delayMicroseconds(50000 - (currMicro - LstartMicro));// 
}


//non blocking animation manager
//buffers are handled above adding frames to be displayed
  //[frame][ms]
    //frames are a series of 0's or 1's
//display frame for X ms


void generalFrameProcessor()



void a1(int targetRow) {
  unsigned long onLen = 500 * 1000;//the length of time for each frame
  
  if (LstartMicro - aniStart < onLen) {
    leds[targetRow] = CRGB::White;
    leds[9 - targetRow] = CRGB::White;
  } else 
    started = false;
 
  
}

void a2(int targetRow){
  int numRepeats = 2;
  unsigned long onLen = 500 * 1000;//the length of time for each frame
  unsigned long ofLen = 250 * 1000;//the length of time for each frame

  totalTime = ((onLen * 2) + ofLen) * numRepeats;
  
  if(totalTime < (LstartMicro - aniStart)){
      iterationTime = totalTime % ((onLen * 2) + ofLen)
      if (iterationTime < onLen)
        leds[litRow] = CRGB::White;
      if (iterationTime - onLen < ofLen && iterationTime - onLen > 0)
        leds[litRow] = CRGB::Black;
      if (iterationTime - onLen < ofLen && iterationTime - onLen > 0)
        leds[litRow] = CRGB::White;
  } else 
    started = false;

}

void r1(int targetRow) {
  unsigned long onLen = 500 * 1000;//the length of time for each frame
  unsigned long ofLen = 250 * 1000;//the length of time for each frame

  int litRow = 0;
  
//  Serial.println("trying frame calc");
//  Serial.println(startMicro);
//  Serial.println(aniStart);
  if (LstartMicro - aniStart != 0)//calculate which frame to display
    frame = (LstartMicro - aniStart) / onLen;

  //functions relating frame number to haxels to activate
  Serial.println(frame);
  if (frame % 2 == 1){
    litRow = frame;

    Serial.println("trying LED set");
    leds[litRow] = CRGB::White;
    leds[9 - litRow] = CRGB::White;
  }
  
  if (litRow > targetRow){//ending condition
    started = false;
  }
}
void r2(int targetRow) {
  //snek
  //odd frames are on
  //even frames are off
  if (frame%3 == 0){
    
  }
}
