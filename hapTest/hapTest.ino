#include <FastLED.h>

#define DATA_PIN 12
#define NUM_LEDS 100

CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  //initialize strip
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Turn the LED on, then pause
  for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = CRGB::White;
  FastLED.show();
  delay(500);
  // Now turn the LED off, then pause
  for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = CRGB::Black;
  FastLED.show();
  delay(500);
}
