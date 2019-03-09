#include <FlexCAN.h>
#include <Encoder.h>
#include <TeensyCANBase.h>
#include <Adafruit_NeoPixel.h>
#define PIN 12
#define NUM_LEDS 30
int i = 0;
int lowerbound = -40;
int upperbound = 40;
int toggle = 0;
int pin1 = 10;
int pin2 = 9;
int pin3 = 7;
int pin4 = 8;
Encoder enc(pin1, pin2);
Encoder enct(pin3, pin4);
float lastposition = 0;
float lastpositiont = 0;
float lasttime = millis();
int revolution = 1024;
int interval = 30;
int seconds = 1000;
int decimals = 2;
void setup(void) {
  CAN_begin();
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  delay(1000);
  Serial.println("Teensy 3.X CAN Sender");
  digitalWrite(13, HIGH);
  toggle = 1;
}
float encoderposition(Encoder ence) {
  float position = ence.read();
  return position;
}
// velocity computed in rotations / second (1024 units / 1000 miliseconds)
float encodervelocity(Encoder ence, float lastpositione) {
  float currentposition = encoderposition(ence);
  float difference = currentposition - lastpositione;
  float dx = (float)difference / (float)revolution; // in revolutions
  float dt = 1; // in seconds
  float velocity = (float)dx / (float)dt;
  return velocity;
}
void resetlastpositiont(Encoder ence) {
  float currentposition = encoderposition(ence);
  lastpositiont = currentposition;
}

void resetlasttime() {
  float currenttime = millis();
  lasttime = currenttime;
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

void loop(void) {
  CAN_update();
  if((int)(millis() - lasttime) % interval == 0) {
    float scaledvelocity = encodervelocity(enc, lastposition) * pow(10, decimals);
    float scaledvelocityt = encodervelocity(enct, lastpositiont) * pow(10, decimals);
   writeLongs(0x612, encoderposition(enc), scaledvelocity);
   writeLongs(0x613, encoderposition(enct), scaledvelocityt);
  // Serial.print("speed");
    Serial.println(scaledvelocityt);
  }
  if(millis() - lasttime >= seconds) {
   // resetlastposition(enc, lastposition);
    resetlastpositiont(enct);
    resetlasttime();
  }
  delay(20);
}

