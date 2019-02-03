#include <FlexCAN.h>
#include <Adafruit_NeoPixel.h>
#include <TeensyCANBase.h>
#include <string.h>

#define PIN 6
#define NUM_LEDS 12

int i = 0;
int toggle = 0;
int themsg = 0;

int lowerbound = -15;
int upperbound = 15;

//rainbow colors
//int colors[9][3] = {
//  {255, 0, 0}, //red
//  {255, 127, 0},  //orange
//  {255, 255, 0}, //yellow
//  {0, 128, 0}, //dark green
//  {0, 47, 181}, // nueva blue?
//  {255, 0, 255}, //pink
//  {75, 0, 130}, //dark purple
//  {143, 0, 55} // light purple
//};

//red - blue gradient
int colors[25][3] = {
  {255, 0, 0},
  {244, 0, 10},
  {233, 0, 21},
  {223, 0, 31},
  {212, 0, 42},
  {201, 0, 53},
  {191, 0, 63},
  {180, 0, 74},
  {170, 0, 85},
  {159, 0, 95},
  {148, 0, 106},
  {138, 0, 116},
  {127, 0, 127},
  {116, 0, 138},
  {106, 0, 148},
  {95, 0, 159},
  {85, 0, 170},
  {74, 0, 180},
  {63, 0, 191},
  {53, 0, 201},
  {42, 0, 212},
  {31, 0, 223},
  {21, 0, 233},
  {10, 0, 244},
  {0, 0, 255}
};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

inline int16_t ReadINT16(uint8_t *ByteArray, int32_t Offset)
{
  int16_t result;
  uint8_t* ptr1 = (uint8_t*)&result;
  uint8_t* ptr2 = ptr1 + 1;
  *ptr1 = *ByteArray;
  *ptr2 = *(ByteArray + 1);
  return result;
}

// gets the first number (of the two) in the message sent
void checkCAN(byte* msg) {
  themsg = ReadINT16(msg, 0);
}

// get the message
int getMSG() {
  return themsg;
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
    delay(10);
  }
}

void setup(void) {
  CAN_begin();
  CAN_add_id(0x612, &checkCAN);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  strip.begin();
  delay(1000);
  Serial.println("Teensy 3.X CAN Receiver");
  digitalWrite(13, HIGH);
  toggle = 1;
}
void loop(void) {
  CAN_update();
  displayNeoPixel(getMSG());
  if (toggle == 1) {
    digitalWrite(13, LOW);
    toggle = 0;
  } else {
    digitalWrite(13, HIGH);
    toggle = 1;
  }
  delay(50);
}
