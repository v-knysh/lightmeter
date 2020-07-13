#include "Arduino.h"
#include <TM1637Display.h>
#include "monitor.h"

#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

void monitorSetup(){
    display.setBrightness(7);
}

void showOneDecimalPrecision(float num){
    int roundedToOneDecimal = (int) (num * 10 + 0.5);
    display.showNumberDecEx(roundedToOneDecimal, 0b00010000);
}
