#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "main_lib.cpp"
#include <LiquidCrystal.h>
#include "Wire.h"


void setup() {
	serialSetup();
	lcdSetup();
	sensorSetup();
	calibrate();
}

void loop() {
	readData();
	delay(50);
}