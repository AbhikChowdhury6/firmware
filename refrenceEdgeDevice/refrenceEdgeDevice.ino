//version 0.01

//implements a remote led actuator and a button sensor
//

#include "WiFi.h"
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#define LED 2

#define MAX_BUFF_LEN 100

#define HZ_PER_LOOP 100

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const char* ssid = "chowderphone";
const char* password = "31415926";

String buff[MAX_BUFF_LEN];
int buffSize = 0;
StaticJsonDocument<1000> doc;
AsyncWebSocketClient * theClient = NULL;
String incoming;
//make a variable to store the data


unsigned long LstartMicro;
unsigned long currMicro;
int coun = 0;

//variables for actuator and sensor
int led_state = 0;
int buttonPin = 12;

int refreshRate = 100;



void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  if(type == WS_EVT_CONNECT){
    Serial.println("Websocket client connection received");
    client->text("Hello from ESP32 Server");
    theClient = client;
 
  } else if(type == WS_EVT_DISCONNECT){
    Serial.println("Client disconnected");
    theClient = NULL;
 
  } if(type == WS_EVT_DATA){
    Serial.println("Got Data!");

    for(int i=0; i < len; i++)
          incoming += (char) data[i];
    
    Serial.println(incoming);// incoming has the json string

    if (buffSize < MAX_BUFF_LEN)
      buff[buffSize] = incoming;//add it to the buffer of commands if there's space

    buffSize += 1;
    incoming = "";
    Serial.println("Added to Buffer!");
  }
}


void setup() {
  pinMode(LED,OUTPUT);
  
  //initialize serial
  Serial.begin(115200);
  Serial.println("HIII");

  //initialize wifi
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED){
    digitalWrite(LED,HIGH);
    delay(200);
    digitalWrite(LED,LOW);
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  digitalWrite(LED,HIGH);
  delay(1000);
  digitalWrite(LED,LOW);

  Serial.println(WiFi.localIP());
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  server.begin();


  //initialize sensor
  pinMode(button, INPUT);

}

void loop() {
  LstartMicro = micros();

  if (buffSize > 0) {
    Serial.println("got new command!, now parsing JSON");
    Serial.println(buff[0]);
    
    int n = buff[0].length(); 
    char char_array[n + 1]; 
    strcpy(char_array, buff[0].c_str());       
    DeserializationError error = deserializeJson(doc, char_array);

    // Test if parsing succeeds.
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }

    //parse command
    led_state = (int)doc["led"];
    Serial.print("turning: ");
    Serial.println(led_state);

    //execute command
    Serial.println("trying LED write");
    digitalWrite(LED,led_state);

    
    //take command off of the buffer
    for(int i = 1; i < buffSize; i++)
      buff[i-1] = buff[i];
    buff[buffSize] = "";
    buffSize -= 1;
  }

  //take in sensor data if the time is right
  if (coun % HZ_PER_LOOP/refreshRate) == 0){
    
  }

  //send the data if there is some
  if(dat != NULL){
    theClient->writeBinary(dat);
    //delete the data
    dat == NULL;
  }

  coun++:
  currMicro = micros();
  if (currMicro - LstartMicro >= 0) //protect from overflows
    delayMicroseconds((1000/HZ_PER_LOOP) * 1000 - (currMicro - LstartMicro));
}
