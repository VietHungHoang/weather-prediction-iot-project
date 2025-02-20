#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <SimpleTimer.h>
#include <DHT.h>
#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_BMP085.h>

// DHT11 Pin
#define DHT_PIN 33

// Hall Pin
#define HALL_PIN 4

// TFT Pin
#define TFT_CS 5     // CS
#define TFT_RST 15   // Reset
#define TFT_DC 32    // AO/DC
#define TFT_MOSI 23  // SDA
#define TFT_SCLK 18  // SCLK/SCK

//Buzzer Pin
#define BUZZER_PIN  17;

//Led Pin
#define LED1 13;
#define LED2 14;
#define LED3 27;
#define LED4 26;
#define LED5 25;

// Color
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

// WiFi
const char* ssid = "thuy kieu";
const char* password = "thuykieu180301";

// Time
const char* poolName = "pool.ntp.org";
const int timeOffset = 25200;
String Days[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
String timeFormatted;
int day, date, month, year;

//Init variable
WiFiUDP ntpUDP; 
NTPClient timeClient(ntpUDP);
SimpleTimer timer_updateTime;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
DHT dht(DHT_PIN, DHT11);
BH1750 lightMeter;
Adafruit_BMP085 bmp;

static const uint8_t temperature[] = {
  0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x00, 0x4c, 0x80, 0x00, 0x48, 0xc0, 0x18, 0x0a, 0x70, 0x09,
  0xfa, 0x70, 0x03, 0x1a, 0x40, 0x06, 0x0a, 0x70, 0x04, 0x0a, 0xc0, 0x0c, 0x0a, 0x70, 0xec, 0x0a,
  0xc0, 0x04, 0x0a, 0x40, 0x04, 0x13, 0x60, 0x02, 0x17, 0xa0, 0x01, 0xf7, 0x20, 0x08, 0x5a, 0x60,
  0x18, 0x0c, 0xc0, 0x00, 0x47, 0x80, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00
};
static const uint8_t humidity[] = {
  0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0x00, 0xd0, 0x00, 0x01, 0x98, 0x00, 0x03,
  0x0c, 0x00, 0x06, 0x06, 0x00, 0x04, 0x03, 0x00, 0x08, 0x01, 0x00, 0x18, 0x01, 0x80, 0x10, 0x00,
  0x80, 0x10, 0x00, 0xc0, 0x14, 0x00, 0xc0, 0x14, 0x00, 0xc0, 0x16, 0x00, 0x80, 0x1b, 0x00, 0x80,
  0x09, 0xf1, 0x00, 0x0c, 0xf3, 0x00, 0x07, 0x0e, 0x00, 0x01, 0xf8, 0x00
};
const static unsigned char icondo[] = {
  0x00, 0x00, 0x3f, 0x00, 0x3f, 0x00, 0x33, 0x00, 0x33, 0x00, 0x3f, 0x00, 0x3f, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char rain[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xe0,
  0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x78, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x1c, 0x00, 0x00,
  0x00, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00,
  0x18, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x30, 0x00,
  0x01, 0xf0, 0x00, 0x00, 0x00, 0x20, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x30, 0x0e,
  0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x08, 0x00,
  0x00, 0x00, 0x00, 0x30, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x0c, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x03, 0xfc, 0x83, 0xb1, 0x3f, 0xf0, 0x00, 0x00,
  0x00, 0x85, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x06, 0x00, 0x00, 0x00, 0x00, 0x03, 0x08, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x80, 0x00,
  0x00, 0x00, 0x00, 0x0c, 0x31, 0x88, 0x00, 0x00, 0x00, 0x00, 0x18, 0x63, 0x18, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xc0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char cloudy[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0xc3, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
  0x0c, 0x0f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x18, 0x30, 0x03, 0x80, 0x00, 0x00, 0x00, 0x10, 0x60, 0x00, 0x80,
  0x00, 0x00, 0x00, 0x30, 0xc0, 0x00, 0x80, 0x00, 0x00, 0x00, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x60, 0x80, 0x00, 0x40, 0x00, 0x00, 0x00, 0xc0, 0x80, 0x07, 0xf8, 0x00, 0x00, 0x01, 0x81,
  0x80, 0x0e, 0x0c, 0x00, 0x00, 0x03, 0x03, 0x80, 0x0c, 0x06, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x06, 0x0c, 0x00, 0x00, 0x02, 0x00, 0x00, 0x04, 0x08, 0x00, 0x00, 0x03, 0x00,
  0x00, 0x04, 0x18, 0x00, 0x00, 0x03, 0x80, 0x00, 0x06, 0x10, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x07,
  0x10, 0x00, 0x00, 0x00, 0x60, 0x00, 0x03, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x03, 0x90, 0x00,
  0x00, 0x00, 0x20, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xc0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00
};
const unsigned char lighting[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0xf8,
  0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x06, 0x00, 0x00,
  0x00, 0x00, 0x18, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
  0x30, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x30, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x30, 0x00,
  0x07, 0xf0, 0x00, 0x00, 0x00, 0x30, 0x00, 0x1c, 0x3c, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x30, 0x06,
  0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x03, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x0e, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x08, 0x00,
  0x00, 0x00, 0x00, 0xe0, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x08, 0x00, 0x00, 0x1f,
  0x00, 0x78, 0x00, 0x08, 0x00, 0x00, 0x1f, 0x00, 0x18, 0x00, 0x08, 0x00, 0x00, 0x1b, 0x00, 0x18,
  0x00, 0x0c, 0x00, 0x00, 0x32, 0x00, 0x18, 0x00, 0x0e, 0x00, 0x00, 0x27, 0x00, 0x18, 0x00, 0x07,
  0x80, 0x3e, 0x67, 0x00, 0x38, 0x00, 0x01, 0xfe, 0x66, 0xfb, 0x7f, 0xe0, 0x00, 0x00, 0x3e, 0xcc,
  0xfb, 0x3f, 0x80, 0x00, 0x00, 0x00, 0xce, 0x1a, 0x00, 0x00, 0x00, 0x00, 0x01, 0x82, 0x1e, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x96, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf6, 0x1c, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x3c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char lighting_rain[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0xe0, 0x00,
  0x00, 0x00, 0x03, 0x80, 0x00, 0x20, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
  0x06, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x3c, 0x00,
  0x00, 0x18, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00,
  0xf0, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x0c, 0x00, 0x0f, 0xfc, 0x00, 0x1c, 0x00,
  0x08, 0x00, 0x18, 0x18, 0x00, 0x0c, 0x00, 0x18, 0x00, 0x18, 0x30, 0x00, 0x0c, 0x00, 0x18, 0x00,
  0x38, 0x70, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x30, 0xc0, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x30, 0xff,
  0x00, 0x1c, 0x00, 0x06, 0x00, 0x60, 0x06, 0x00, 0x38, 0x00, 0x03, 0xc0, 0x60, 0x0c, 0x00, 0xf0,
  0x00, 0x01, 0xff, 0x7c, 0x19, 0xff, 0xe0, 0x00, 0x00, 0x1f, 0x04, 0x37, 0xfe, 0x00, 0x00, 0x00,
  0x00, 0x0c, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x69,
  0x87, 0x18, 0x00, 0x00, 0x00, 0x38, 0xcb, 0x0e, 0x30, 0x00, 0x00, 0x00, 0x31, 0x9e, 0x18, 0x60,
  0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0x8c, 0x41, 0xc7, 0x00, 0x00, 0x00, 0x07, 0x18, 0xe3, 0x8e, 0x00, 0x00, 0x00, 0x0c, 0x31,
  0x87, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char night[] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x10,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x1c,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x1f,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x0f,
  0xc0,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x0f,
  0xc0,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x0e,
  0xe0,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x06,
  0x38,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x06,
  0x38,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x06,
  0x18,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x06,
  0x1c,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x06,
  0x0e,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x06,
  0x06,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x06,
  0x06,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x0e,
  0x06,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x0e,
  0x06,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x1e,
  0x06,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x1c,
  0x06,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x1c,
  0x06,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x38,
  0x06,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x78,
  0x0e,
  0x00,
  0x00,
  0x00,
  0x00,
  0x01,
  0xf0,
  0x0e,
  0x00,
  0x00,
  0x03,
  0x00,
  0x07,
  0xe0,
  0x1c,
  0x00,
  0x00,
  0x01,
  0xff,
  0xff,
  0x80,
  0x1c,
  0x00,
  0x00,
  0x00,
  0xff,
  0xfe,
  0x00,
  0x38,
  0x00,
  0x00,
  0x00,
  0xff,
  0xe0,
  0x00,
  0x78,
  0x00,
  0x00,
  0x00,
  0xf0,
  0x00,
  0x00,
  0xf0,
  0x00,
  0x00,
  0x00,
  0x38,
  0x00,
  0x01,
  0xc0,
  0x00,
  0x00,
  0x00,
  0x3f,
  0x00,
  0x07,
  0xc0,
  0x00,
  0x00,
  0x00,
  0x3f,
  0xc0,
  0x1f,
  0x80,
  0x00,
  0x00,
  0x00,
  0x07,
  0xff,
  0xfe,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0xff,
  0xfc,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x1f,
  0xc0,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
};
const unsigned char clear_sky[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x38, 0x03, 0xc0, 0x1c, 0x00,
  0x00, 0x00, 0x3c, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00,
  0x3e, 0x0f, 0xf0, 0x78, 0x00, 0x00, 0x00, 0x0c, 0x3f, 0xfc, 0x70, 0x00, 0x00, 0x00, 0x00, 0x7f,
  0xfe, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x3f, 0x80,
  0x00, 0x00, 0x00, 0x03, 0xe0, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x03, 0xc0, 0x00, 0x00,
  0x00, 0x03, 0xc0, 0x03, 0xc0, 0x00, 0x00, 0x07, 0xc7, 0xc0, 0x03, 0xc3, 0xe0, 0x00, 0x0f, 0xc7,
  0xc0, 0x03, 0xe7, 0xe0, 0x00, 0x07, 0xc7, 0xc0, 0x03, 0xe3, 0xe0, 0x00, 0x03, 0xc7, 0xc0, 0x03,
  0xc3, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x07, 0xc0, 0x00,
  0x00, 0x00, 0x03, 0xf0, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x3f, 0xfc, 0x30, 0x00, 0x00, 0x00, 0x1e, 0x1f,
  0xf8, 0x78, 0x00, 0x00, 0x00, 0x3e, 0x03, 0xc0, 0x7c, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x3c,
  0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char clear_cloudy[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06,
  0x0c, 0x00, 0x00, 0x00, 0x00, 0x01, 0x86, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x18, 0x00,
  0x00, 0x00, 0x00, 0x60, 0xc0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x30, 0x60, 0x00, 0x00,
  0x00, 0x78, 0x3f, 0x80, 0xe0, 0x00, 0x00, 0x00, 0x38, 0x7f, 0xc1, 0xe0, 0x00, 0x00, 0x00, 0x18,
  0xe0, 0xe3, 0xc0, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x73, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf0, 0x38,
  0x00, 0x00, 0x00, 0x01, 0xf0, 0x78, 0x18, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x3c, 0x18, 0x00, 0x00,
  0x00, 0x03, 0x80, 0x0e, 0x18, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x07, 0x98, 0xf0, 0x00, 0x00, 0x0e,
  0x00, 0x03, 0xfc, 0xf0, 0x00, 0x00, 0x1c, 0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 0x18, 0x00, 0x01,
  0xcf, 0x00, 0x00, 0x00, 0x10, 0x00, 0x03, 0x00, 0xc0, 0x00, 0x00, 0x30, 0x00, 0x02, 0x00, 0xe0,
  0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x70, 0x00, 0x03,
  0xf0, 0x00, 0x00, 0x00, 0x30, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x0e, 0x00, 0x00,
  0x00, 0x00, 0x30, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00,
  0x30, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x06, 0x00,
  0x00, 0x00, 0x03, 0x80, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff,
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char night_cloud[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x3c, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x18, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xc0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x61, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x81, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x81, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x01, 0x81, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0xc1, 0x80, 0x00, 0x00,
  0x00, 0x0c, 0x00, 0x60, 0xc0, 0x40, 0x00, 0x00, 0x18, 0x00, 0x30, 0x71, 0xc0, 0x00, 0x00, 0x18,
  0x00, 0x3f, 0xbf, 0xc0, 0x00, 0x00, 0x10, 0x00, 0x19, 0xc1, 0x80, 0x00, 0x00, 0x10, 0x00, 0x00,
  0x63, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x3c, 0x00,
  0x00, 0x01, 0x80, 0x00, 0x00, 0x10, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x02,
  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00,
  0x00, 0x02, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0xe0,
  0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void setup() {

  Serial.begin(115200);
  Serial.println("Initialized");
  
  // sensors
  dht.begin();
  bmp.begin();
  Wire.begin();
  pinMode(HALL_PIN, INPUT);

  // devices
  int pins[6] = { BUZZER_PIN, LED1, LED2, LED3, LED4, LED5 };
  for(int i = 0; i < pins.size(); i++)
    pinMode(pins[i], OUTPUT);

  // times
  // connectWifi();
  // lightMeter.begin();
  // setupNTPClient();

  // screen
  // setupLCD();
  // getTime();
  // updateTimeLCD();
  // timer_updateTime.setInterval(1000, updateTime);
  // getWeather();
}

void loop() {
  delay(1000);
  // read data from sensors
  float temperature1 = getTemperatureDHT11();
  float temperature2 = getTemperatureBMP180();
  float humidity = getHumidity();
  float insentity = getIntensity();
  float pressure = getPressure();
  bool haveMagnet = haveMagnet();

  // controll devices
  // turnBuzzerOn();
  // turnBuzzerOff();
  // turnLedOn(led1);
  // turnLedOff(led1);
  // turnAllLedOn();
  // turnAllLedOff();
  //  timer_updateTime.run();
  //   if(phut==0&&giay==0){
  //     getWeather();
  //   }
}