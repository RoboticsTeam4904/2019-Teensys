#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUM_LEDS 12
int i = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin();
  strip.setBrightness(30);
  strip.show();
  
}
void loop() {
  for(i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 0, 40, 188);
    //strip.setPixelColor(1, 0, 255, 0);
    strip.show();
    delay(150);
  }
  for(i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 184, 232, 30);
    //strip.setPixelColor(1, 255, 0, 0);
    strip.show();
    delay(50);
  } 
  for(i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 97, 192, 255);
    //strip.setPixelColor(1, 255, 0, 0);
    strip.show();
    delay(50);
  } 
  for(i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 176, 196, 210);
    //strip.setPixelColor(1, 255, 0, 0);
    strip.show();
    delay(100);
  } 
   // strip.setPixelColor(i, 124, 252, 0);
    //strip.setPixelColor(1, 0, 255, 0);
   // strip.show();
   // delay(100);
  
}
