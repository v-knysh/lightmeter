#include "buttons.h"
#include "Arduino.h"

int up_last_button_state = LOW;
int up_last_button_time = 0;
int down_last_button_state = LOW;
int down_last_button_time = 0;

void setup_buttons(){
    pinMode(UP_BUTTON_PIN, INPUT);
    pinMode(DOWN_BUTTON_PIN, INPUT);
}

bool up_button_pressed(){
    if (up_last_button_time - millis() < 30) return false;

    int up_button_state = digitalRead(UP_BUTTON_PIN);

    if ((up_button_state != up_last_button_state)) {
        up_last_button_state = up_button_state;
        up_last_button_time = millis();

    }
    if (up_last_button_state == HIGH){
        return true;
    } else {
        return false;
    }
}

bool down_button_pressed(){
    if (down_last_button_time - millis() < 30) return false;

    int down_button_state = digitalRead(DOWN_BUTTON_PIN);

    if ((down_button_state != down_last_button_state)) {
        down_last_button_state = down_button_state;
        down_last_button_time = millis();
    }

    if (down_last_button_state == HIGH){
        return true;
    } else {
        return false;
    }
}