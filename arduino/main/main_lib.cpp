#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "main_lib.h"
#include <LiquidCrystal.h>
#include "Wire.h"

void serialSetup() {
	#ifdef DEBUG
	Serial.begin(9600);
	Serial.println("Per aspera ad astra");
	//Serial.println("EISINGA, Fons van der Plas")
	#endif
	Wire.begin();
}

void rtcSetup() {
	#ifdef DEBUG
	Serial.println("Initializing RTC connection...");
	#endif
	rtc.initialize();
	rtc.setClockRunning(true);
	#ifdef DEBUG
	Serial.println(rtc.testConnection() ? "DS1307 connection successful" : "DS1307 connection failed");
	#ifdef SETTIME
	Serial.setTimeout(20000); // 20 sec
	Serial.println("Unix time in dec s:");
	Serial.flush();
	while(Serial.available() < 10); {
		delay(10);
	}
	char inputArray[10];
	uint32_t inputT = 0;
	Serial.readBytes(inputArray, 10);
	for(int i = 0; i < 10; i++) {
		inputT += inputArray[i] - '0';
		if(i != 9) {
			inputT *= 10;
		}
	}
	Serial.println(inputT);
	rtc.setDateTime(DateTime(inputT));
	delay(100);
	/*Serial.println(rtc.getYear());
	Serial.println(rtc.getMonth());
	Serial.println(rtc.getDay());
	Serial.println(rtc.getHours24());
	Serial.println(rtc.getMinutes());*/
	#endif
	Serial.println("Current epoch:");
	Serial.println(rtc.getDateTime().unixtime());
	#endif
}

void updateRtc() {
	lst = 18.697374558 + 24.06570982441908 * (rtc.getDateTime().dayFrac() + 0.5);
		
	#ifdef DEBUG
	delay(500);
	Serial.print("GMST: ");
	Serial.println(lst - 24.0 * int(lst / 24.0));
	Serial.print("Dayfrac: ");
	Serial.println(rtc.getDateTime().dayFrac());
	#endif
	lst -= 24.0 * int(lst / 24.0);
	lst += longitude / 15.0;
	lst -= 24.0 * int(lst / 24.0);
	#ifdef DEBUG
	Serial.print("LST: ");
	Serial.println(lst);
	#endif
	lst *= PI / 12.0;
}

void lcdSetup() {
	pinMode(LCD_PIN, OUTPUT);
	pinMode(BTN_PIN, INPUT);
	digitalWrite(LCD_PIN, HIGH);
	
	lcd.begin(16, 2);
	lcd.print("EISINGA");
	lcd.setCursor(0,1);
	lcd.print("Initialzing...");
	delay(300);
}

void sensorSetup() {
	#ifdef DEBUG
	Serial.println("Initializing other I2C devices...");
	#endif
	
	accel.initialize();
	mag.initialize();
	
	#ifdef DEBUG
	Serial.println("Testing device connections...");
	Serial.println(accel.testConnection() ? "ADXL345 connection successful" : "ADXL345 connection failed");
	Serial.println(mag.testConnection() ? "HMC5883L connection successful" : "HMC5883 connection failed");
	Wire.beginTransmission(0x50);
	Serial.println(Wire.endTransmission() == 0 ? "AT24C256 connection successful" : "AT24C256 connection failed");
	#endif
	
	accel.setRange(3);
	accel.setFullResolution(255);
	accel.setOffset(0, 0, 0);
}

void calibrate() {
	delay(200);
	
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("Press to calib");
	pause();
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("...");
	
	double dataVec[4];
	double xtx[4][4];
	double xty[4];
	
	for(int ix = 0; ix < 4; ix++) {
		for(int iy = 0; iy < 4; iy++) {
			xtx[ix][iy] = 0.0;
		}
		xty[ix] = 0.0;
	}
	
	while(digitalRead(BTN_PIN) == HIGH) {
		retrieveRaw(&mData, 20.0);
		
		dataVec[0] = mData.x;
		dataVec[1] = mData.y;
		dataVec[2] = mData.z;
		dataVec[3] = 1.0;
		
		double xtxtemp[4][4];
		
		Matrix.Multiply(dataVec, dataVec, 4, 1, 4, (double*)xtxtemp);
		Matrix.Add((double*)xtxtemp, (double*)xtx, 4, 4, (double*)xtx);
		
		Matrix.Scale(dataVec, 4, 1, mData.x * mData.x + mData.y * mData.y + mData.z * mData.z);
		Matrix.Add(dataVec, xty, 4, 1, xty);
		
		delay(100);
	}
	
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print(Matrix.Invert((double*)xtx, 4) == 1 ? "Calib complete" : "Calib failed");
	Matrix.Multiply((double*)xtx, xty, 4, 4, 1, dataVec);
	
	mOffset.x = 0.5 * dataVec[0];
	mOffset.y = 0.5 * dataVec[1];
	mOffset.z = 0.5 * dataVec[2];
	
	aOffset = XYZ(13.5, 13.0, -1.5); //TODO: calibrate
	
	lcd.clear();
		
	#ifdef DEBUG
	Serial.println("Calibration complete: ");
	Serial.print("mOff: ");
	Serial.print(mOffset.x); Serial.print(", ");
	Serial.print(mOffset.y); Serial.print(", ");
	Serial.println(mOffset.z);
	#endif
}

void readData() {
	retrieveRaw(&aData, &mData, 100.0);
	
	digitalWrite(LCD_PIN, LOW);
	
	aData = XYZ::Subtract(aData, aOffset);
	mData = XYZ::Subtract(mData, mOffset);
	
	temp = mData.x;
	mData.x = mData.y;
	mData.y = temp;
	mData.z = -mData.z;
	
	roll = atan2(-aData.y, aData.z);
	
	temp = sqrt(aData.x * aData.x + aData.y * aData.y + aData.z * aData.z);
	xzlength = sqrt(aData.y * aData.y + aData.z * aData.z);
	
	pitch = atan(aData.x / xzlength);
	
	spitch = aData.x / temp;
	cpitch = xzlength / temp;
	
	sroll = -aData.y / xzlength;
	croll = aData.z / xzlength;
	
	temp = sqrt(mData.x * mData.x + mData.y * mData.y + mData.z * mData.z);
	mData.x /= temp;
	mData.y /= temp;
	mData.z /= temp;
	
	yaw = compassDeclination / 57.29577951308233 + atan2(
		(mData.z * sroll) - (mData.y * croll), 
		(mData.x * cpitch) + (mData.y * spitch * sroll) + (mData.z * spitch * croll));
	
	/*dec = asin(spitch * sin(latitude / 57.29577951308233) + cpitch * cos(latitude / 57.29577951308233) * cos(yaw));
	ra = lst - asin(-sin(yaw) * cpitch / cos(dec));*/
	dec = asin(spitch * sin(latitude / 57.29577951308233) + cpitch * cos(latitude / 57.29577951308233) * cos(yaw));
	ra = lst + atan2(sin(yaw), spitch * cos(latitude / 57.29577951308233) / cpitch - cos(yaw) * sin(latitude / 57.29577951308233));
	
	dec *= 57.29577951308233; // 180.0/PI
	ra *= 3.819718634205488;  //  12.0/PI
	
	ra -= double(int(ra / 24.0) * 24.0);
	
	uint16_t sdec = max(0, min(65534, int32_t((dec + 90.0) * 65536.0 / 180.0)));
	uint16_t sra  = max(0, min(65534, int32_t( ra          * 65536.0 /  24.0)));
	
	#ifdef DISPLAY_COORDS
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print(yaw * 57.29577951308233);
	//lcd.print(sra);
	lcd.setCursor(8,0);
	lcd.print(",");
	lcd.print(pitch * 57.29577951308233);
	//lcd.print(sdec);
	lcd.setCursor(0,1);
	lcd.print(ra);
	lcd.setCursor(8,1);
	lcd.print(",");
	lcd.print(dec);
	
	delay(50);
	digitalWrite(LCD_PIN, HIGH);
	pause();
	#else
	delay(50);
	digitalWrite(LCD_PIN, HIGH);
	#endif
	
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("...");
	
	///
	uint16_t pointer = 711;
	
	for(uint16_t i = 0; i < 357; i++) { //TODO: put dec before ran & rax
		uint16_t decin, ranin, raxin, pointin;
		Wire.beginTransmission(0x50);
		Wire.write(int((i * 8) >> 8));   // MSB
		Wire.write(int((i * 8) & 0xFF)); // LSB
		Wire.endTransmission();
		Wire.requestFrom(0x50, 8);
		
		while(Wire.available() < 8) {
			delay(1);
		}
		
		ranin = Wire.read();
		ranin *= 256;
		ranin += Wire.read();
		
		raxin = Wire.read();
		raxin *= 256;
		raxin += Wire.read();
		
		decin = Wire.read();
		decin *= 256;
		decin += Wire.read();
		
		pointin = Wire.read();
		pointin *= 256;
		pointin += Wire.read();
		
		/*lcd.clear();
		lcd.setCursor(0,0);
		lcd.print(ranin);
		lcd.setCursor(8,0);
		lcd.print(",");
		lcd.print(raxin);
		lcd.setCursor(0,1);
		lcd.print(decin);
		lcd.setCursor(8,1);
		lcd.print(",");
		lcd.print(pointin);
		pause();*/
		
		if(sdec < decin) {
			continue; //TODO: check per 2 bytes
		}
		if(sra < ranin) {
			continue;
		}
		if(sra >= raxin) {
			continue;
		}
		pointer = pointin;
		break;
	}
	///
	
	lcd.setCursor(0,0);
	printCstName(2856 + pointer);
}

void retrieveRaw(XYZ *aData, XYZ *mData, double n) {
	accel.getAcceleration(&rawx, &rawy, &rawz);
	int32_t xAccum, yAccum, zAccum;
	xAccum = yAccum = zAccum = 0;
	for(int i = 0; i < int(n); i++) {
		delay(5);
		accel.getAcceleration(&rawx, &rawy, &rawz);
		xAccum += rawx;
		yAccum += rawy;
		zAccum += rawz;
	}
	
	*aData = XYZ(double(xAccum) / n, double(yAccum) / n, double(zAccum) * 0.93571 / n); //TODO: calibrate
	
	xAccum = yAccum = zAccum = 0;
	
	mag.getHeading(&rawx, &rawy, &rawz);
	for(int i = 0; i < int(n); i++) {
		delay(5);
		mag.getHeading(&rawx, &rawy, &rawz);
		xAccum += rawx;
		yAccum += rawy;
		zAccum += rawz;
	}
	*mData = XYZ(double(xAccum) / n, double(yAccum) / n, double(zAccum) / n);
}

void retrieveRaw(XYZ *mData, double n) {
	int32_t xAccum, yAccum, zAccum;
	xAccum = yAccum = zAccum = 0;
	mag.getHeading(&rawx, &rawy, &rawz);
	for(int i = 0; i < int(n); i++) {
		delay(5);
		mag.getHeading(&rawx, &rawy, &rawz);
		xAccum += rawx;
		yAccum += rawy;
		zAccum += rawz;
	}
	*mData = XYZ(double(xAccum) / n, double(yAccum) / n, double(zAccum) / n);
}

void pause() {
	while(digitalRead(BTN_PIN) == HIGH) {
		delay(10);
	}
	delay(200);
}

void printCstName(uint16_t pointer)
{
	Wire.beginTransmission(0x50);
	Wire.write(int((pointer) >> 8));   // MSB
	Wire.write(int((pointer) & 0xFF)); // LSB
	Wire.endTransmission();
	Wire.requestFrom(0x50, 1);
	delay(5);
	uint8_t c = Wire.read();
	Wire.requestFrom(uint8_t(0x50), c);
	for(; c > 0; c--) {
		if(Wire.available()) {
			lcd.write(Wire.read());
		}
	}
}

void outputSerialData() {
	retrieveRaw(&aData, &mData, 20.0);
	
	byte a[4];
	int32_t n;
	
	n = int32_t(mData.x);
	memcpy(a, &n, sizeof(n));
	Serial.write(a, 4);
	n = int32_t(mData.y);
	memcpy(a, &n, sizeof(n));
	Serial.write(a, 4);
	n = int32_t(mData.z);
	memcpy(a, &n, sizeof(n));
	Serial.write(a, 4);
	
	Serial.write(255);
	Serial.write(255);
	Serial.write(255);
}
