#include <math.h>
#include "Arduino.h"

#include "expopairs.h"
#include "constants.h"

#define CODE_MIN_EV -1
#define CODE_MAX_EV -2
#define CODE_EV_OK -4
#define CODE_NO_MORE_PAIRS -3


int first_shutter_speed_index(int ev){
  int delta_ev = ev - MIN_EV;
  return min(delta_ev, SHUTTER_SPEEDS_MAX_INDEX);
}

int first_aperture_index(int ev){
  int delta_ev = ev - MIN_EV;
  int delta = delta_ev - APERTURES_MAX_INDEX;
  return max(delta, 0);
}

int total_pairs_amount(int first_shutter_speed_index, int first_aperture_index){
  int delta = APERTURES_MAX_INDEX - first_aperture_index;
  return min(first_shutter_speed_index + 1, delta);
}

Expopair::Expopair(){
    _status = 0;
    _first_shutter_speed_index = 0;
    _first_aperture_index = 0;
    _amount_pairs = 0;
}

int Expopair::shutter_speed(int index){
    if ((_first_shutter_speed_index - index < 0) || (index < 0) || (index >= _amount_pairs)){
        return CODE_NO_MORE_PAIRS;
    }
    return shutter_speeds[_first_shutter_speed_index - index];
}

int Expopair::aperture_value(int index){
    if ((_first_aperture_index + index > APERTURES_MAX_INDEX) || (index >= _amount_pairs) || (index < 0)){
        return CODE_NO_MORE_PAIRS;
    }
    return apertures[_first_aperture_index + index];
}

int Expopair::status(){
    return _status;
}

char Expopair::status_str(){
    if (_status == CODE_MIN_EV){return '-';}
    if (_status == CODE_MAX_EV){return '+';}
    return ' ';
}

int Expopair::amount_pairs(){
    return _amount_pairs;
}

void Expopair::update(int ev){
  if (ev < MIN_EV){
    _status = CODE_MIN_EV;
    _first_shutter_speed_index = 0;
    _first_aperture_index = 0;
    _amount_pairs = 1;
    return 0;
  }
  if (ev > MAX_EV){
    _status = CODE_MAX_EV;
    _first_shutter_speed_index = SHUTTER_SPEEDS_MAX_INDEX;
    _first_aperture_index = APERTURES_MAX_INDEX;
    _amount_pairs = 1;
    return 0;
  }
  _first_shutter_speed_index = first_shutter_speed_index(ev);
  _first_aperture_index = first_aperture_index(ev);
  _amount_pairs = total_pairs_amount(_first_shutter_speed_index, _first_aperture_index);
  _status = CODE_EV_OK;
  return 0;
}
