#include <FlexCAN.h>
#include <Encoder.h>
#include <TeensyCANBase.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define NUM_LEDS 240
#define PIN 23
int i = 0;
//int e = 0;
int lowerbound = -40;
int upperbound = 40;
int toggle = 0;
int pin1 = 17;
int pin2 = 16;
int pin3 = 15;
int pin4 = 14;
Encoder enc(pin1, pin2);
Encoder enct(pin3, pin4);
float lastposition = 0;
float lastpositiont = 0;
float lasttime = millis();
int revolution = 1024;
int interval = 30;
int seconds = 1000;
int decimals = 2;
int colors[5][3] = {
  {176,224,230},
  {0,149,237},
  {65,105,225},
  {0,0,139},
  {0, 0, 255},
};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

float encoderposition(Encoder ence) {
  float position = ence.read();
  return position;
}
// velocity computed in rotations / second (1024 units / 1000 miliseconds)
float encodervelocity(Encoder ence) {
  float currentposition = encoderposition(ence);
  float difference = currentposition - lastposition;
  float dx = (float)difference / (float)revolution; // in revolutions
  float dt = 1; // in seconds
  float velocity = (float)dx / (float)dt;
  return velocity;
}
float encodervelocityt(Encoder ence) {
  float currentposition = encoderposition(ence);
  float difference = currentposition - lastpositiont;
  float dx = (float)difference / (float)revolution; // in revolutions
  float dt = 1; // in seconds
  float velocity = (float)dx / (float)dt;
  return velocity;
}
void resetlastposition(Encoder ence) {
  float currentposition = encoderposition(ence);
  lastposition = currentposition;
}
void resetlastpositiont(Encoder ence) {
  float currentposition = encoderposition(ence);
  lastpositiont = currentposition;
  }
void resetlasttime() {
  float currenttime = millis();
  lasttime = currenttime;
}
void displayNeoPixel(int velocity) {
  if (velocity > upperbound) {
    velocity = upperbound;
  } else if (velocity < lowerbound) {
    velocity = lowerbound;
  }
  int range = upperbound - lowerbound;
  int numcolors = sizeof(colors)/sizeof(colors[0]);
  float scalefactor = (float)range / (float)numcolors;
  int colorsindex = (velocity + (-lowerbound)) / scalefactor;
  int *color = colors[colorsindex];
  int r = color[0];
  int g = color[1];
  int b = color[2];
  for (i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
    strip.show();
    delay(1);
  }
}
void writeLongs(uint32_t id, long value1, long value2){
  byte * msg = new byte[8];

  for(int i = 0; i < 4; i++){
    msg[i] = (value1 >> i*8) & 0xFF;
  }
  for(int i = 0; i < 4; i++){
    msg[i + 4] = (value2 >> i*8) & 0xFF;
  }
  
  CAN_write(id, msg);

  delete msg;
  //Serial.println("sent");
  if (toggle == 1){
    digitalWrite(13, LOW);
    toggle = 0;
  } else {
    digitalWrite(13, HIGH);
    toggle = 1;
  }
}
void setup(void) {
  CAN_begin();
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  delay(1000);
  Serial.println("Teensy 3.X CAN Sender");
  digitalWrite(13, HIGH);
  toggle = 1;
  
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'

}
void loop(void) {
  CAN_update();
  if((int)(millis() - lasttime) % interval == 0) {
    float scaledvelocity = encodervelocity(enc) * pow(10, decimals);
    float scaledvelocityt = encodervelocityt(enct) * pow(10, decimals);
    Serial.println(scaledvelocity, encoderposition(enc));
    Serial.println(scaledvelocityt, encoderposition(enct));
    writeLongs(0x612, scaledvelocity, encoderposition(enc));
    writeLongs(0x613, scaledvelocityt, encoderposition(enct));
  }
  for (int e = 0; e < 5; e++) {
    /*if (rotations % i == 0){
      int listnumber = i;}*/
      for(i = 0; i < NUM_LEDS; i++) {
        String stre = (colors[e][1]);
    strip.setPixelColor(i, colors[e][0], colors[e][1], colors[e][2]);
    strip.show();
    Serial.println(stre);
    delay(10);
  }
       }
    //}
     
    
  if(millis() - lasttime >= seconds) {
    resetlastposition(enc);
    resetlastpositiont(enct);
    resetlasttime();
    
  } 

}
