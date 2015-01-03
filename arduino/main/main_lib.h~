#include <stdint.h>
#include <LiquidCrystal.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "ADXL345.h"
#include "HMC5883L.h"
#include "DS1307.h"
#include "eMath.cpp"
#include "math.h"

#define LED_PIN 13
#define BTN_PIN 7

#define mIntensityX 19289 //X intensity in nT
#define mIntensityY 245   //Y intensity in nT
#define mIntensityZ 44961 //Z intensity in nT
#define mGain 92		  //in nT/LSB (100.000 / gain in LSB/Gauss)

#define DEBUG
//#define SETTIME

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

ADXL345 accel;
HMC5883L mag;
DS1307 rtc;
int16_t rawx, rawy, rawz;
double temp, xzlength, yaw, pitch, spitch, cpitch, roll, sroll, croll, lst, ra, dec;
bool blinkState = false;

XYZ aData, mData, aOffset, mOffset;

int16_t xScaleA = 310;
int16_t yScaleA = 310;
int16_t zScaleA = 280;

uint16_t year;
uint8_t month, day, dow, hours, minutes, seconds;
double dayfrac;

void serialSetup();
void rtcSetup();
void lcdSetup();
void sensorSetup();
void calibrate();
void retrieveRaw(XYZ *aData, XYZ *mData);
void retrieveRaw(XYZ *mData);
void displayRetrieveRaw(char n, XYZ *aData, XYZ *mData);
void outputSerialData();
void pause();
void updateRtc();
void readData();
