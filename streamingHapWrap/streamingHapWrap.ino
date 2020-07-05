//version 0.1
#include <FastLED.h>
#include "WiFi.h"
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

//pin of the onboard LED
#define LED 2

//
#define DATA_PIN 22
#define NUM_LEDS 34


AsyncWebServer server(80);
AsyncWebSocket ws("/ws");


//const char* ssid = "troysphone";
//const char* ssid = "Cubic";
//const char* password = "num1ininnovation";

const char* ssid = "chowderphone";
const char* password = "31415926";


StaticJsonDocument<10000> doc;

String incoming="";
CRGB leds[NUM_LEDS];

bool reciv = false;
//on a websocket event run this
void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  if(type == WS_EVT_CONNECT){
    Serial.println("Websocket client connection received");
    client->text("Hello from the hapWrap!");
 
  } else if(type == WS_EVT_DISCONNECT){
    Serial.println("Client disconnected");
 
  } if(type == WS_EVT_DATA){
    reciv=true;
    client->text("gotchu");
    //Serial.println("Got Data!");

    for(int i=0; i < len; i++)
          incoming += (char) data[i];
    
    //Serial.println(incoming);// incoming has the json string
    reciv=false;
  }
}

void setup() {
  pinMode(LED,OUTPUT);

  //initialize serial
  Serial.begin(115200);
  Serial.println("HIII");

  
  //initialize strip
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CRGB::Black;
  FastLED.show();
  
  //initialize wifi
  WiFi.begin(ssid, password);

  for (int i = 0; i < 3 && WiFi.status() != WL_CONNECTED; i++) { //try connceting to wifi a few times
    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  digitalWrite(LED,HIGH);

  
  if (WiFi.status() != WL_CONNECTED){
    Serial.println("Couldn't connect to wifi </3 resetting");
    ESP.restart();
  }

  
  Serial.println(WiFi.localIP());
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  server.begin();

}

void loop() {
    if(incoming != "" && !reciv){
      //parse and display
      char char_array[incoming.length() + 1]; 
      strcpy(char_array, incoming.c_str()); 
          
      DeserializationError error = deserializeJson(doc, char_array);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        ESP.restart();
      }
    
  
      for (int i = 0; i <= NUM_LEDS;i++){
        leds[i].red =(int) doc["red"][i];
        leds[i].blue =(int) doc["blue"][i];
        leds[i].green =(int) doc["green"][i];
      }
      
      FastLED.show();
      incoming="";
    }
}
