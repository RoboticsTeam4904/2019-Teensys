#include <Encoder.h>
int pin1 = 2;
int pin2 = 4;
Encoder enc(pin1, pin2);
float lastposition = 0;
long lasttime = millis();
int colorsArray[8][3]= {
  {255, 0, 0}, //red
  {255, 127, 0},  //orange
  {255, 255, 0}, //yelow
  {0, 0, 255}, // nueva blue?
  {255, 0, 255}, //pink
  {0, 128, 0}, //dark green
  {75, 0, 130}, //dark purple
  {143, 0, 55} // light purple
  };
float encoderposition() {
  float position = enc.read();
  return position;
}


#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUM_LEDS 12
int i = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

float encodervelocity() {
  float currentposition = encoderposition();
  float velocity = (currentposition - lastposition)/(millis() - lasttime);
  return velocity;
}
void resetlastposition() {
  float currentposition = encoderposition();
  lastposition = currentposition;
  lasttime = millis();
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(30);
  strip.show();
}
int framecount = 0;
int interval = 60;
void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(encoderposition());
  //Serial.println(enc.read());
  int listnumber = encodervelocity() / 0.25 + 3;
  if(framecount % interval == 0) {
    Serial.println(encodervelocity());
    for(i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, colorsArray[listnumber][0], colorsArray[listnumber][1], colorsArray[listnumber][2]);
    strip.show();
    delay(10);
  }
    //Serial.println
    resetlastposition();
  }
  framecount += 1;
  delay(1);
}
