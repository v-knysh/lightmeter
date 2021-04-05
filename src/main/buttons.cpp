#include "buttons.h"
#include "Arduino.h"

int up_last_button_time = 0;
int down_last_button_time = 0;

void setup_buttons(){
    pinMode(UP_BUTTON_PIN, INPUT);
    pinMode(DOWN_BUTTON_PIN, INPUT);
}

bool up_button_pressed(){
    if (up_last_button_time - millis() < 150) return false;

    up_last_button_time = millis();
    return true;
}

bool down_button_pressed(){
    if (down_last_button_time - millis() < 150) return false;

    down_last_button_time = millis();
    return true;
}