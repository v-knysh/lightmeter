#include <avr/pgmspace.h>

#ifndef SHUTTERS_TABLE
    #define SHUTTERS_TABLE
#endif

#define LEN_SHUTTER_SPEEDS 5
#define LEN_APERTURES 6
#define SHUTTER_SPEEDS_MAX_INDEX 4
#define APERTURES_MAX_INDEX 5
#define MIN_EV 8
#define MAX_EV 17
#define CAMERA_NAME "FED5"
#define MAX_PAIRS 5

const int shutter_speeds[] PROGMEM = {30, 60, 125, 250, 500};
const int apertures[] PROGMEM = {28, 40, 56, 80, 110, 160};