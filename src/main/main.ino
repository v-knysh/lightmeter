#include <math.h>
#include <Wire.h>
#include "lightsensor.h"


//BH1750 lightMeter;

int loopDelay = 1000;
int lux = 0;
int ev = 0;
int lastTimerLoop = 0;
int servoAngle = 0;
int servoPin = 12;


byte evMin = 5;
byte evRange = 9; // 9 marks in circle

void setup() {
  Serial.begin(9600);
}

void loop() {
  lux = getlux();
  ev = (int) (log(lux / 2.5) / log(2.));
  print(" lux: ", lux);
  print(" ev: ", ev);
  delay(1000);
}


void print(String key, String val) {
  Serial.print(key);
  Serial.print(val);
  Serial.println(";");
}
void print(String key, int val) {
  print(key, String(val));
}
void print(String key, float val) {
  print(key, String(val));
}
