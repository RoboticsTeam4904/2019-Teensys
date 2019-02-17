// Sender for PCBs
// Send message * 100 to keep two decimal points

#include <Encoder.h>
#include <FlexCAN.h>
#include <TeensyCANBase.h>

int pin1 = 7;
int pin2 = 8;

Encoder enc(pin1, pin2);

float lastposition = 0;
float lasttime = millis();
int toggle = 0;
int revolution = 1024;
int interval = 50;
int seconds = 1000;

int decimals = 2;

float encoderposition() {
  float position = enc.read();
  return position;
}

// velocity computed in rotations / second (1024 units / 1000 miliseconds)
float encodervelocity() {
  float currentposition = encoderposition();
  float difference = currentposition - lastposition;
  float dx = (float)difference / (float)revolution; // in revolutions
  float dt = 1; // in seconds
  float velocity = (float)dx / (float)dt;
  return velocity;
}

void resetlastposition() {
  float currentposition = encoderposition();
  lastposition = currentposition;
}

void resetlasttime() {
  float currenttime = millis();
  lasttime = currenttime;
}

// writeLongs(id of receiver, msg 1, msg 2)
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
}

void loop() {
  CAN_update();
  if((int)(millis() - lasttime) % interval == 0) {
    float scaledvelocity = encodervelocity() * pow(10, decimals);
    Serial.println(scaledvelocity);
    writeLongs(0x612, scaledvelocity, encoderposition());
  }
  if(millis() - lasttime >= seconds) {
    resetlastposition();
    resetlasttime();
  }
}
