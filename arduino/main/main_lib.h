#include <stdint.h>
#include <LiquidCrystal.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "ADXL345.h"
#include "HMC5883L.h"
#include "DS1307.h"
#include "eMath.cpp"
#include "math.h"

#define LCD_PIN 13
#define BTN_PIN 7

#define compassDeclination 0.94 // in degrees towards East, visit www.ngdc.noaa.gov/geomag-web/#declination
#define longitude 5.225587
#define latitude 51.642934

#define DEBUG
#define DISPLAY_COORDS

#ifdef DEBUG
//#define SETTIME
#endif

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

ADXL345 accel;
HMC5883L mag;
DS1307 rtc;
int16_t rawx, rawy, rawz;
double temp, xzlength, yaw, pitch, spitch, cpitch, roll, sroll, croll, lst, ra, dec;

XYZ aData, mData, aOffset, mOffset;

int16_t xScaleA = 263;
int16_t yScaleA = 262;
int16_t zScaleA = 280;

uint16_t year;
uint8_t month, day, dow, hours, minutes, seconds;
double dayfrac;

void serialSetup();
void rtcSetup();
void updateRtc();
void lcdSetup();
void sensorSetup();
void calibrate();
void readData();
void retrieveRaw(XYZ *aData, XYZ *mData, double n);
void retrieveRaw(XYZ *mData, double n);
void pause();
void printCstName(uint16_t pointer);
void outputSerialData();
