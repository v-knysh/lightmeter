#include <math.h>
#include <Wire.h>
#include "lightsensor.h"
#include "light_calc.h"


//BH1750 lightMeter;

float lux = 0;
float ev = 0;

void setup() {
  Serial.begin(9600);
  lightsensorSetup();
}

void loop() {
  lux = getlux();
  ev = luxToEv(lux);
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
