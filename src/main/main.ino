#include <math.h>
#include <Wire.h>
// #include "lightsensor.h"
// #include "light_calc.h"
// #include "monitor.h"
// #include "servo.h"
#include "expopairs.h"



float lux = 0;
float ev = 0;

int servoPin = 7;
Expopair expopair;

void setup() {
    Serial.begin(9600);
//    lightsensorSetup();
//    monitorSetup();
//    servoSetup(7);
}

void loop() {
//     lux = getlux();
//     ev = luxToEv(lux);
//     print(" lux: ", lux);
//     print(" ev: ", ev);
    for (int ev = 5; ev < 20; ev++){
          expopair.update(ev);
          int pairs = expopair.amount_pairs();
          print(" ev: ", ev);
          print(" status: ", expopair.status());
          print(" aperture_value: ", expopair.aperture_value(pairs / 2));
          print(" shutter_speed: ", expopair.shutter_speed(pairs / 2));
          delay(1000);
      }


//    showOneDecimalPrecision(ev);
   // Expect: ev with one decimal precision
    delay(1000);
//     showOnServo(ev);
//     delay(1000);
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
void print(String key, double val) {
    print(key, String(val));
}
