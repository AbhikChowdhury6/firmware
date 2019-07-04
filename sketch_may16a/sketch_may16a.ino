#include "WiFi.h";
#include <FastLED.h>
#define LED 2
#define NUM_LEDS 3
#define DATA_PIN 12
// Define the array of leds
CRGB leds[NUM_LEDS];
//#include &lt;WiFi.h&gt; 
const char* ssid = "Redmiy1";
const char* password =  "oindrila";
WiFiClient client; 
const uint16_t port = 8090;
//host has to be the ip address of your pi,since it is acting as a server
const char * host = "192.168.43.122";

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
 
void setup()
{

  pinMode(LED,OUTPUT);
  Serial.begin(115200);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
  if (!client.connect(host, port)) {
 
        Serial.println("Connection to host failed");
 
        delay(1000);
        return;
    }
    else{
      Serial.println("Connected to server successful!");
    }
    
}
 
void loop()
{
    client.print("From Right!!");
    String req = client.readString();
    Serial.println(req); 
    String part01 = getValue(req,':',0);
    Serial.println(part01);
    String part02 = getValue(req,':',1);    
    Serial.println(part02);
    int i=part02.toInt();
    if(req != " "){    
    digitalWrite(LED,HIGH);
    delay(250);
    digitalWrite(LED,LOW);
    delay(250);
    }
    delay(500);
    if(part01=="Right"){
     // Turn the LED on, then pause
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(500);
  // Now turn the LED off, then pause
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(500);
    }
    
}
