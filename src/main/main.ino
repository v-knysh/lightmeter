#include <math.h>
#include <Wire.h>
#include "lightsensor.h"
#include "light_calc.h"
// #include "monitor.h"
// #include "servo.h"
#include "expopairs.h"
#include "oled_monitor.h"
#include "constants.h"
#include "buttons.h"

// int servoPin = 7;

int current_pair = 0;
int curr_ev_x100 = 0;
uint8_t pairs = 0;
uint8_t max_pair = 0;

Expopair expopair;
OledMonitor oled_monitor;

void setup() {
    Serial.begin(9600);
//    monitorSetup();
//    servoSetup(servoPin);

//     print(F(" before sensor memory: "), freeMemory());
    lightsensorSetup();
    print(F(" sensor setup ok"), 0);

//     print(F(" before monitor memory: "), freeMemory());
    oled_monitor.setup();
    print(F(" monitor setup ok"), 0);



//     print(F(" after monitor and sensor memory: "), freeMemory());

    setup_buttons();
    print(F(" buttons setup ok"), 0);

    oled_monitor.set_iso(200);

    attachInterrupt(digitalPinToInterrupt(UP_BUTTON_PIN), update_current_pair_up, RISING);
    attachInterrupt(digitalPinToInterrupt(DOWN_BUTTON_PIN), update_current_pair_down, RISING);

}

void update_current_pair_up(){
    print(F(" update_current_pair_up start"), 0);
    if (up_button_pressed()){
        current_pair--;
        current_pair = max(current_pair, 0);
        print(F(" updated pairs up: "), current_pair);
    }
}

void update_current_pair_down(){
    print(F(" update_current_pair_down start"), 0);
    if (down_button_pressed()){
        current_pair++;
        current_pair = min(current_pair, max_pair);
        print(F(" updated pairs down: "), current_pair);
    }
}

void render_monitor(){

    oled_monitor.set_ev(curr_ev_x100);

    oled_monitor.set_top_av(expopair.aperture_value(current_pair-1));
    oled_monitor.set_top_t(expopair.shutter_speed(current_pair-1));

    oled_monitor.set_main_av(expopair.aperture_value(current_pair));
    oled_monitor.set_main_t(expopair.shutter_speed(current_pair));

    oled_monitor.set_bottom_av(expopair.aperture_value(current_pair+1));
    oled_monitor.set_bottom_t(expopair.shutter_speed(current_pair+1));

    oled_monitor.render();
}

void loop() {
    noInterrupts();

    float lux = getlux();
    int ev_x100 = luxToEv(lux);

    if (ev_x100 != curr_ev_x100){
        curr_ev_x100 = ev_x100;
        expopair.update(curr_ev_x100);
        pairs = expopair.amount_pairs();
        current_pair = pairs / 2;
        max_pair = pairs - 1;
    }

     print(F(" ev: "), ev_x100);
     print(F(" current_pair: "), current_pair);
     print(F(" pairs: "), pairs);
     print(F(" aperture_value: "), String(expopair.aperture_value(current_pair) / 10) + '.' + String(expopair.aperture_value(current_pair) % 10));
     print(F(" shutter_speed: "), expopair.shutter_speed(current_pair));

    render_monitor();

    interrupts();

    delay(100);

}

void print(String key, String val) {
    Serial.print(key);
    Serial.print(val);
    Serial.println(F(";"));
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

void print_(String key) {
    Serial.print(key);
    Serial.println(F(";"));
}
