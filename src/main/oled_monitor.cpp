#include <SPI.h>
#include <Wire.h>
#include "ssd1306.h"
#include "oled_monitor.h"
#include "constants.h"

#define VCCSTATE SSD1306_SWITCHCAPVCC
#define WIDTH     128
#define HEIGHT     64
#define PAGES       8

#define OLED_RST    9
#define OLED_DC     8
#define OLED_CS    10
#define SPI_MOSI   11    /* connect to the DIN pin of OLED */
#define SPI_SCK    13     /* connect to the CLK pin of OLED */

#define WHITE      1
#define BLACK      0
#define DOTS       2


uint8_t oled_buf[WIDTH * HEIGHT / 8];


OledMonitor::OledMonitor(){
}

void OledMonitor::setup(){
  SSD1306_begin();
  SSD1306_clear(oled_buf);
  SSD1306_string(0, 0, "START", 12, 1, oled_buf);
  SSD1306_display(oled_buf);
  delay(2000);
}


void SSD1306_horizontal_line(int x_start, int x_end, int y, char color, uint8_t* buffer){
    for (int x = x_start; x <= x_end; x++){
        char col = color;
        if(col==DOTS){col = x%2;}
        SSD1306_pixel(x, y, col, oled_buf);
    }
};
void SSD1306_vertical_line(int y_start, int y_end, int x, char color, uint8_t* buffer){
    for (int y = y_start; y <= y_end; y++){
        char col = color;
        if(col==DOTS){col = y%2;}
        SSD1306_pixel(x, y, col, oled_buf);
    }
};

void OledMonitor::set_iso(int iso){
    _iso = iso;
}
void OledMonitor::set_top_av(int top_av){
    _top_av = top_av;
}
void OledMonitor::set_top_t(int top_t){
    _top_t = top_t;
}
void OledMonitor::set_main_av(int main_av){
    _main_av = main_av;
}
void OledMonitor::set_main_t(int main_t){
    _main_t = main_t;
}
void OledMonitor::set_bottom_av(int bottom_av){
    _bottom_av = bottom_av;
}
void OledMonitor::set_bottom_t(int bottom_t){
    _bottom_t = bottom_t;
}
void OledMonitor::set_ev(float ev){
    _ev = ev;
}
void OledMonitor::set_status_str(String status_str){
    _status_str = status_str;
}

void OledMonitor::render(){

    char iso_str[8]; sprintf(iso_str,"ISO: %d",_iso);

    SSD1306_clear(oled_buf);
    SSD1306_string(0, 0, CAMERA_NAME, 12, WHITE, oled_buf);
    SSD1306_string(79, 0, iso_str, 12, WHITE, oled_buf);

    SSD1306_string(0, 15, "2.8", 12, WHITE, oled_buf);
    SSD1306_string(110, 15, "125", 12, WHITE, oled_buf);

    SSD1306_string(3, 29, "4.0", 16, WHITE, oled_buf);
    SSD1306_string(101, 29, " 60", 16, WHITE, oled_buf);

    SSD1306_string(60, 29, "+", 16, BLACK, oled_buf);

    SSD1306_string(0, 48, "5.6", 12, WHITE, oled_buf);
    SSD1306_string(110, 48, " 30", 12, WHITE, oled_buf);


    SSD1306_horizontal_line(0, 127, 27, DOTS, oled_buf);
    SSD1306_horizontal_line(0, 127, 47, DOTS, oled_buf);
    SSD1306_vertical_line(27, 47, 0, DOTS, oled_buf);
    SSD1306_vertical_line(27, 47, 127, DOTS, oled_buf);

    SSD1306_display(oled_buf);
}

