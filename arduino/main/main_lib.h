#include <stdint.h>
#include <LiquidCrystal.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "ADXL345.h"
#include "HMC5883L.h"

#define LED_PIN 13
#define BTN_PIN 7

#define mIntensityX 19289 //X intensity in nT
#define mIntensityY 245   //Y intensity in nT
#define mIntensityZ 44961 //Z intensity in nT
#define mGain 92		  //in nT/LSB (100.000 / gain in LSB/Gauss)

#define DEBUG

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

ADXL345 accel;
HMC5883L mag;
int16_t rawx, rawy, rawz;
double x, y, z, roll, pitch;
bool blinkState = false;

int16_t xOffsetA, yOffsetA, zOffsetA, xOffsetM, yOffsetM, zOffsetM;

int16_t xScaleA = 310;
int16_t yScaleA = 310;
int16_t zScaleA = 280;


void serialSetup();
void lcdSetup();
void sensorSetup();
void calibrate();
void pause();

void readData();
