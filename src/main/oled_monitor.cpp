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

//void SSD1306_vertical_line_dots(int y_start, int y_end, int x, char color, uint8_t* buffer){
//
//};




void OledMonitor::update(int i){
    SSD1306_clear(oled_buf);
    SSD1306_string(0, 0, CAMERA_NAME, 12, 1, oled_buf);
    SSD1306_string(79, 0, "ISO: 200", 12, 1, oled_buf);

    SSD1306_string(0, 15,  "2.8               125", 12, 1, oled_buf);
    SSD1306_string(2, 29, "4.0         60 ", 16, 1, oled_buf);
    SSD1306_string(0, 48, "5.6               30", 12, 1, oled_buf);

    SSD1306_horizontal_line(0, 127, 27, DOTS, oled_buf);
    SSD1306_horizontal_line(0, 127, 47, DOTS, oled_buf);
    SSD1306_vertical_line(27, 47, 0, DOTS, oled_buf);
    SSD1306_vertical_line(27, 47, 127, DOTS, oled_buf);

//    SSD1306_horizontal_line(0, 127, 60, BLACK, oled_buf);

//        SSD1306_string(50, 53, "123", 12, 1, oled_buf);
//    SSD1306_string(0, 0, "121111111111111111111111111111111111111111111111111111113", 12, 1, oled_buf);
//    for (int k = 0; k < 64)
    //        SSD1306_pixel(j, 12, j%2, oled_buf);
//        SSD1306_pixel(j, 27, j%2, oled_buf);
//        SSD1306_pixel(j, 47, j%2, oled_buf);
//        SSD1306_pixel(j, 52, j%2, oled_buf);
//        SSD1306_pixel(j, 64, j%2, oled_buf);
    SSD1306_display(oled_buf);
}

