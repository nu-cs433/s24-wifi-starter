#include "Arduino.h"
#include "SPI.h"
#include <U8g2lib.h>
#include "images.h"
#include <Wire.h>
#include "WiFi.h"

// OLED display
// These are hardware specific to the Heltec WiFi LoRa 32 V3
// Cite: https://resource.heltec.cn/download/WiFi_LoRa_32_V3/HTIT-WB32LA(F)_V3.1_Schematic_Diagram.pdf
#define OLED_RESET 21 
#define OLED_SDA 17
#define OLED_SCL 18
U8G2_SSD1306_128X64_NONAME_F_SW_I2C display(U8G2_R0, /* clock=*/ OLED_SCL, /* data=*/ OLED_SDA, /* reset=*/ OLED_RESET);   // All Boards without Reset of the Display

// Screen drawing locations
#define X_MAX 128
#define Y_MAX 64
static uint8_t iteration_count = 0;
static uint32_t x_coor = 0;
static uint32_t y_coor = 10;
static int8_t x_rate = 4;
static int8_t y_rate = 4;

// String to draw on screen
static char display_str[80] = {0};

void logo()
{
	display.clearBuffer();
	display.drawXBM(0,0, logo_width, logo_height, (const unsigned char *)logo_bits);
	display.sendBuffer();
}

// Setup, code starts here and runs this function once
void setup(void) 
{
  // Start serial communications
	Serial.begin(115200);

  // Initialize the display
  display.begin();
	display.setFont(u8g2_font_NokiaSmallPlain_te);

  // Draw a logo image on boot
	logo();
	delay(3000);
	display.clear();
}

// Loop, after setup, this function is called repeatedly
void loop() 
{
  iteration_count++;

  // Draw text on screen
  snprintf(display_str, 80, "Itr: %03d", iteration_count);
  display.clearBuffer();
  display.drawStr(x_coor, y_coor, display_str);
  display.sendBuffer();

  // Update text location
  x_coor += x_rate;
  if (x_coor + x_rate > X_MAX || x_coor + x_rate < 0) {
    x_rate *= -1;
  }
  y_coor += y_rate;
  if (y_coor + y_rate > Y_MAX || y_coor + y_rate < 0) {
    y_rate *= -1;
  }

  // Sleep
  delay(100);
}
