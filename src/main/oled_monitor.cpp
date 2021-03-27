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
    sprintf(_iso_str,"ISO: %3d",iso);
}
void OledMonitor::set_top_av(int top_av){
    if (top_av == 0){sprintf(_top_av_str,"   "); return;}
    if (top_av < 100){
        sprintf(_top_av_str,"%1d.%1d",int(top_av/10),int(top_av%10)); return;
    } else {
        sprintf(_top_av_str,"%1d",top_av/10); return;
    }
}
void OledMonitor::set_top_t(int top_t){
    if (top_t == 0){sprintf(_top_t_str,"   "); return;}
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
    if (bottom_av == 0){sprintf(_bottom_av_str,"   "); return;}
    if (bottom_av < 100){
        sprintf(_bottom_av_str,"%1d.%1d",int(bottom_av/10),int(bottom_av%10)); return;
    } else {
        sprintf(_bottom_av_str,"%2d",int(bottom_av/10)); return;
    }}
void OledMonitor::set_bottom_t(int bottom_t){
    if (bottom_t == 0){sprintf(_bottom_t_str,"   "); return;}
    if (bottom_t < 100){
        sprintf(_bottom_t_str," %2d",bottom_t);
    } else {
        sprintf(_bottom_t_str,"%3d",bottom_t);
    }}
void OledMonitor::set_ev(float ev){
    sprintf(_ev_str,"EV: %2d.%1d",int(ev),int(int(ev*10)%10));
}
void OledMonitor::set_status_str(String status_str){
    _status_str = status_str;
}

void OledMonitor::render(){

    SSD1306_clear(oled_buf);
    SSD1306_string(0, 0, CAMERA_NAME, 12, WHITE, oled_buf);
    SSD1306_string(79, 0, _iso_str, 12, WHITE, oled_buf);

//    SSD1306_string(0, 15, "2.8", 12, WHITE, oled_buf);
//    SSD1306_string(110, 15, "125", 12, WHITE, oled_buf);



//    char main_t_str[3]; sprintf(iso_str,"%d",_main_t);

    SSD1306_string(3, 29, _main_av_str, 16, WHITE, oled_buf);
    SSD1306_string(101, 29, _main_t_str, 16, WHITE, oled_buf);

//    SSD1306_string(60, 29, "+", 16, BLACK, oled_buf);

//    SSD1306_string(0, 48, "5.6", 12, WHITE, oled_buf);
//    SSD1306_string(110, 48, " 30", 12, WHITE, oled_buf);

//    SSD1306_string(55, 48, "EV: ", 12, WHITE, oled_buf);


    SSD1306_horizontal_line(0, 127, 27, DOTS, oled_buf);
    SSD1306_horizontal_line(0, 127, 47, DOTS, oled_buf);
    SSD1306_vertical_line(27, 47, 0, DOTS, oled_buf);
    SSD1306_vertical_line(27, 47, 127, DOTS, oled_buf);

    SSD1306_display(oled_buf);
}

