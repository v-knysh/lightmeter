#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "oled_monitor.h"
#include "constants.h"
#include "Monospaced_plain_12.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET    5
#define OLED_DC       4
#define OLED_CS       10
#define OLED_MOSI     6    /* connect to the DIN pin of OLED */
#define OLED_CLK      7     /* connect to the CLK pin of OLED */

Adafruit_SSD1306 oled_display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


OledMonitor::OledMonitor(){
}

void OledMonitor::setup(){
    if(!oled_display.begin(SSD1306_SWITCHCAPVCC)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    oled_display.setRotation(2);
    oled_display.display();
    delay(2000); // Pause for 2 seconds
    oled_display.clearDisplay();
    oled_display.display();
}

void OledMonitor::set_iso(int iso){
    sprintf(_iso_str,"ISO: %3d",iso);
}
void OledMonitor::set_top_av(int top_av){
    if (top_av <= 0){sprintf(_top_av_str,"   "); return;}
    if (top_av < 100){
        sprintf(_top_av_str,"%1d.%1d",int(top_av/10),int(top_av%10)); return;
    } else {
        sprintf(_top_av_str,"%1d",top_av/10); return;
    }
}
void OledMonitor::set_top_t(int top_t){
    if (top_t <= 0){sprintf(_top_t_str,"   "); return;}
    if (top_t < 100){
        sprintf(_top_t_str," %2d",top_t);
    } else {
        sprintf(_top_t_str,"%3d",top_t);
    }
}
void OledMonitor::set_main_av(int main_av){
    if (main_av < 100){
        sprintf(_main_av_str,"%1d.%1d",main_av/10,main_av%10);
    } else {
        sprintf(_main_av_str,"%2d",main_av/10);
    }
}
void OledMonitor::set_main_t(int main_t){
    if (main_t < 100){
        sprintf(_main_t_str," %2d",main_t);
    } else {
        sprintf(_main_t_str,"%3d",main_t);
    }
}
void OledMonitor::set_bottom_av(int bottom_av){
    if (bottom_av <= 0){sprintf(_bottom_av_str,"   "); return;}
    if (bottom_av < 100){
        sprintf(_bottom_av_str,"%1d.%1d",int(bottom_av/10),int(bottom_av%10)); return;
    } else {
        sprintf(_bottom_av_str,"%2d",int(bottom_av/10)); return;
    }}
void OledMonitor::set_bottom_t(int bottom_t){
    if (bottom_t <= 0){sprintf(_bottom_t_str,"   "); return;}
    if (bottom_t < 100){
        sprintf(_bottom_t_str," %2d",bottom_t);
    } else {
        sprintf(_bottom_t_str,"%3d",bottom_t);
    }}
void OledMonitor::set_ev(int ev_x100){
    int ev = ev_x100 / 100;
    sprintf(_ev_str,"EV: %2d.%1d", ev, (ev_x100%100) / 10);

    if (ev < MIN_EV){
        int delta = MIN_EV-ev;
        sprintf(_status_str,"-%1d",min(delta,9));return;
    }
    if (ev > MAX_EV){
        int delta = ev-MAX_EV;
        sprintf(_status_str,"+%1d",min(delta,9));return;
    }
    sprintf(_status_str,"  ");

}

void OledMonitor::render(){
    oled_display.clearDisplay();

    oled_display.setTextSize(1);             // Normal 1:1 pixel scale
    oled_display.setTextColor(SSD1306_WHITE);

    oled_display.setCursor(0,0+3);
    oled_display.println(F(CAMERA_NAME));

    oled_display.setCursor(79,0+3);
    oled_display.println(_iso_str);

    oled_display.setCursor(0, 15+3);
    oled_display.println(_top_av_str);
    oled_display.setCursor(110, 15+3);
    oled_display.println(_top_t_str);

    oled_display.setFont(&Monospaced_plain_12);
    oled_display.setCursor(3, 29+12);
    oled_display.println(_main_av_str);
    oled_display.setCursor(101, 29+12);
    oled_display.println(_main_t_str);

    oled_display.setCursor(56, 29+12);
    oled_display.println(_status_str);

    oled_display.setFont();




    oled_display.setCursor(0, 48+3);
    oled_display.println(_bottom_av_str);
    oled_display.setCursor(110, 48+3);
    oled_display.println(_bottom_t_str);

    oled_display.setCursor(40, 48+3);
    oled_display.println(_ev_str);

//    oled_display.drawLine(0, 13, 127, 13, SSD1306_WHITE);
//    oled_display.drawLine(0, 63, 127, 63, SSD1306_WHITE);
//    oled_display.drawLine(0, 0, 127, 0, SSD1306_WHITE);

    oled_display.drawRect(0, 27, 128, 21, SSD1306_WHITE);


    oled_display.display();
}
