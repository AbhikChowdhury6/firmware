#include <FastLED.h>

#define DATA_PIN 12
#define NUM_LEDS 5

int buttonPin = 14;
CRGB leds[NUM_LEDS];

byte in[7];
bool pushed = false;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  pinMode(buttonPin, INPUT);

//  Serial.println("Started!");

}

void loop() {

  if (!pushed && digitalRead(buttonPin)){
    Serial.print("1");
    pushed = true;
  }
    
  if (!digitalRead(buttonPin))
    pushed = false;
   
  if (Serial.available() > 0) {
    Serial.readBytes(in,7); // read the incoming bytes:
//    Serial.println("gotem");
//    Serial.println(in[0]);
//    Serial.println(in[1]);
//    Serial.println(in[2]);
//    Serial.println(in[3]);
//    Serial.println(in[4]);
//    Serial.println(in[5]);
//    Serial.println(in[6]);
//    Serial.println(in[7]);
  }

  for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = CRGB::Black;
  
  if (in[0] == '1')
    leds[0] = CRGB::White;
  if (in[1] == '1')
    leds[1] = CRGB::White;
  if (in[2] == '1')
    leds[2] = CRGB::White;
  if (in[3] == '1')
    leds[3] = CRGB::White;
  if (in[4] == '1')
    leds[4] = CRGB::White;

  
    FastLED.show();

}
