#include "Remote.h"
#include "RemoteProtocol.h"
#include <Arduino.h>
#include <LedControl.h>

#define N		8

Remote::Remote(LedControl * lc) : lc(lc), pending(0) {}

void Remote::processByte(byte data) {
	if (pending == 0) {
		processControlByte(data, false);
	} else {
		Serial.println("got data byte");
		size_t count = 0;
		while (count < MAXLEN && buffer[count] != -1) { count++; }
		Serial.println("count");
		Serial.println(count);

		buffer[count++] = data;
		if (count == pending) { 
			pending = 0;
			processControlByte(command, true); 
		}
	}
}

void Remote::processControlByte(byte control, bool dataAvailable) {
	Serial.println("processing control byte");
	command = control;
	switch (control & R_DEVICE) {
		case R_DEVICE_LED:
			processControlLED(control, dataAvailable);
		break;

		case R_DEVICE_LCD:
			processControlLCD(control, dataAvailable);
		break;
	}
}

void Remote::processControlLED(byte control, bool dataAvailable) {
	Serial.println("processing control byte led");
	switch (control & R_LED_OP) {
		case R_LED_OP_CLEAR:
			lc->clearDisplay(0);
		break;

		case R_LED_OP_ONE:
			if (dataAvailable) {
				Serial.println("data here");
				byte x = (buffer[0] >> 4);
				byte y = buffer[0] & 0xF;
				bool value = control & 1;
				Serial.println("x");
				Serial.println(x);
				Serial.println("y");
				Serial.println(y);
				Serial.println("value");
				Serial.println(value);
				lc->setLed(0, y, x, value);
			} else {
				Serial.println("waiting for one");
				waitFor(1);
			}
		break;

		case R_LED_OP_ROW:
			if (dataAvailable) {

			} else {
				return waitFor(1);
			}
		break;

		case R_LED_OP_COL:
			if (dataAvailable) {

			} else {
				return waitFor(1);
			}
		break;

		case R_LED_OP_ALL:
			if (dataAvailable) {

			} else {
				return waitFor(N);
			}
		break;

		case R_LED_OP_BRIGHT:
			if (dataAvailable) {

			} else {
				return waitFor(1);
			}
		break;
	}
}

void Remote::processControlLCD(byte control, bool dataAvailable) {
}

void Remote::waitFor(size_t len) {
	pending = len;
	for (int i=0;i<MAXLEN;i++) { buffer[i] = -1; }
}
