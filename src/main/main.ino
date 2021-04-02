#include <math.h>
#include <Wire.h>
// #include "lightsensor.h"
#include "light_calc.h"
// #include "monitor.h"
// #include "servo.h"
#include "expopairs.h"
#include "oled_monitor.h"
#include "constants.h"
#include "buttons.h"


#define UP_BUTTON_PIN 3
#define DOWN_BUTTON_PIN 2

float lux = 0;
float ev = 0;

int servoPin = 7;



int current_pair = 0;
int curr_ev = 0;
int pairs = 0;
int max_pair = 0;

Expopair expopair;
OledMonitor oled_monitor;

void setup() {
    Serial.begin(9600);
//    lightsensorSetup();
//    monitorSetup();
//    servoSetup(servoPin);
    oled_monitor.setup();

    setup_buttons();

    oled_monitor.set_iso(200);
}

void loop() {
//     lux = getlux();
//     ev = luxToEv(10.);
//     print(" lux: ", lux);
//     expopair.update(ev);
//     int pairs = expopair.amount_pairs();


    int ev = 12;

    if (ev != curr_ev){
        curr_ev = ev;
        expopair.update(ev);
        pairs = expopair.amount_pairs();
        current_pair = pairs / 2;
        max_pair = pairs - 1;
    }

    if (up_button_pressed()){
        current_pair--;
        current_pair = max(current_pair, 0);
        print(" updated pairs: ", current_pair);
    }

    if (down_button_pressed()){
        current_pair++;
        current_pair = min(current_pair, max_pair);
        print(" updated pairs: ", current_pair);
    }

    print(" ev: ", ev);
    print(" current_pair: ", current_pair);
    print(" pairs: ", pairs);
    print(" aperture_value: ", String(expopair.aperture_value(current_pair) / 10) + '.' + String(expopair.aperture_value(current_pair) % 10));
    print(" shutter_speed: ", expopair.shutter_speed(current_pair));
    print(" status: ", expopair.status_str());
    print("------------------------------: ", 0);

    oled_monitor.set_ev(ev);

    oled_monitor.set_top_av(expopair.aperture_value(current_pair-1));
    oled_monitor.set_top_t(expopair.shutter_speed(current_pair-1));

    oled_monitor.set_main_av(expopair.aperture_value(current_pair));
    oled_monitor.set_main_t(expopair.shutter_speed(current_pair));

    oled_monitor.set_bottom_av(expopair.aperture_value(current_pair+1));
    oled_monitor.set_bottom_t(expopair.shutter_speed(current_pair+1));

    oled_monitor.render();


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
void print(String key, double val) {
    print(key, String(val));
}
void print(String key, char val) {
    print(key, String(val));
}
