#include <Encoder.h>
#include <FlexCAN.h>
#include <TeensyCANBase.h>
int pin1 = 11;
int pin2 = 12;
Encoder enc(pin1, pin2);
float lastposition = 0;
int toggle = 0;
float encoderposition() {
  float position = enc.read();
  return position;
}
float encodervelocity() {
  float currentposition = encoderposition();
  float velocity = (currentposition - lastposition) / 2;
  return velocity;
}
void resetlastposition() {
  float currentposition = encoderposition();
  lastposition = currentposition;
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
  Serial.println("sent");
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
int framecount = 0;
int interval = 1000;
void loop() {
  CAN_update();
  if(framecount % interval == 0) {
    writeLongs(0x612, encoderposition(), encodervelocity());
    resetlastposition();
  }
  framecount += 1;
}
