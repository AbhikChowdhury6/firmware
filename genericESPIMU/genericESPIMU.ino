#include "WiFi.h"
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define BNO055_SAMPLERATE_DELAY_MS (20)
#define _sda 21
#define _scl 22 

#define LED 2

#define HZ_PER_LOOP 100


AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
AsyncWebSocketClient * theClient = NULL;


const char* ssid = "NSAHoneypot6";
const char* password = "izMGLR7tJLIes37R";

//const char* ssid = "chowderphone";
//const char* password = "31415926";

//d6nw5v1x2pc7st9m

Adafruit_BNO055 bno = Adafruit_BNO055(55);
uint8_t sys, gyro, accel, mag = 0;  
sensors_event_t event;

String toSend  = "";

void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  if(type == WS_EVT_CONNECT){
    Serial.println("Websocket client connection received");
    client->text("Hello from ESP32 Server");
    theClient = client;
 
  } else if(type == WS_EVT_DISCONNECT){
    Serial.println("Client disconnected");
    theClient = NULL;
 
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
  if(bno.begin())
    Serial.println("BNO Started!");
  bno.setExtCrystalUse(true);


}
int lastMillis = 0;
void loop() {
  // put your main code here, to run repeatedly:
  //read data
  //send every 
   
  bno.getEvent(&event);
  imu::Quaternion q = bno.getQuat();
  imu::Vector<3> a = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  imu::Vector<3> g = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  imu::Vector<3> m = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
  imu::Vector<3> la = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  bno.getCalibration(&sys, &gyro, &accel, &mag);
  toSend += String(millis()) + "\t" + String(q.x()) + "\t" + String(q.y()) + "\t" + String(q.w()) + "\t" + String(q.z()) + "\t" 
          + String(a.x()) + "\t" + String(a.y()) + "\t" + String(a.z()) 
          + "\t" + String(g.x()) + "\t" + String(g.y()) + "\t" + String(g.z()) 
          + "\t" + String(m.x()) + "\t" + String(m.y()) + "\t" + String(m.z()) 
          + "\t" + String(la.x()) + "\t" + String(la.y()) + "\t" + String(la.z())
          + "\t" + String(accel) + "\t" + String(gyro) + "\t" + String(mag) + "\t" + String(sys)+ "\n";
  if(theClient!=NULL && millis()-lastMillis > 200){
    lastMillis = millis();
//    Serial.println(toSend);
    theClient->text(toSend);
    toSend  = "";
  }
  if(theClient==NULL)
    toSend  = "";
  //delay(1);







  
}
