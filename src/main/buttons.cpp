#include "buttons.h"
#include "Arduino.h"

int up_last_button_state = LOW;
int down_last_button_state = LOW;

void setup_buttons(){
    pinMode(UP_BUTTON_PIN, INPUT);
    pinMode(DOWN_BUTTON_PIN, INPUT);
}

bool up_button_pressed(){
    int debounce_button_state = digitalRead(UP_BUTTON_PIN);
    delay(50);
    int up_button_state = digitalRead(UP_BUTTON_PIN);

    if ((up_button_state != up_last_button_state) && (up_button_state == debounce_button_state)) {
        up_last_button_state = up_button_state;
    }
    if (up_last_button_state == HIGH){
        return true;
    } else {
        return false;
    }
}

bool down_button_pressed(){
    int debounce_button_state = digitalRead(DOWN_BUTTON_PIN);
    delay(50);
    int down_button_state = digitalRead(DOWN_BUTTON_PIN);

    if ((down_button_state != down_last_button_state) && (down_button_state == debounce_button_state)) {
        down_last_button_state = down_button_state;
    }

    if (down_last_button_state == HIGH){
        return true;
    } else {
        return false;
    }
}