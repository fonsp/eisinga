#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Wire.h"


void setup() {
	Serial.begin(9600);
	
	/*Wire.begin();
	while(true) {
		byte error, address;
		int nDevices;
		Serial.println("Scanning..");
		nDevices = 0;
		for(address = 1; address < 127; address++)
		{
			Wire.beginTransmission(address);
			error = Wire.endTransmission();
			if(error == 0)
			{
				Serial.print("Device at: 0x");
				if(address < 16)
				{
					Serial.print("0");
				}
				Serial.println(address,HEX);
				nDevices++;
			} else if(error == 4)
			{
				Serial.print("Error at: 0x");
				if(address < 16)
				{
					Serial.print("0");
				}
				Serial.println(address,HEX);
				nDevices++;
			}
		}
		Serial.println("---");
		delay(5000);
	}*/
	
	while(Serial.available() < 2) {
		Serial.write('@');
		delay(1000);
	}
	delay(100);
	
	int16_t mLength;
	mLength = Serial.read();
	mLength = mLength << 8;
	mLength += Serial.read();
	
	//mLength = 16;
	
	delay(100);
	
	Serial.print(mLength);
	
	Wire.begin();
	
	uint16_t n;
	char buff[16];
	
	for(n = 0; n < mLength / 16; n++) {
		Serial.write('$');
		while(Serial.available() < 16) {
			delay(1);
		}
		
		Serial.readBytes(buff, 16);
		Wire.beginTransmission(0x50);
		
		Wire.write(int((n * 16) >> 8)); // MSB
		Wire.write(int((n * 16) & 0xFF)); // LSB
		uint8_t c;
		for(c = 0; c < 16; c++) {
			Wire.write(buff[c]);
		}
		
		Wire.endTransmission();
	}
	
	delay(500);
	
	/*for(n = 0; n < mLength / 16; n++) {
		Wire.beginTransmission(0x50);
		Wire.write(int((n * 16) >> 8)); // MSB
		Wire.write(int((n * 16) & 0xFF)); // LSB
		Wire.endTransmission();
		Wire.requestFrom(0x50, 16);
		uint8_t c;
		for(c = 0; c < 16; c++) {
			if(Wire.available()) {
				Serial.write(Wire.read());
			}
		}
	}*/
	
	Serial.write('#');
}

void loop() {
	digitalWrite(13, HIGH);
	delay(50);
	digitalWrite(13, LOW);
	delay(50);
}
