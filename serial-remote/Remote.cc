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
		size_t count = 0;
		while (count < MAXLEN && buffer[count] != -1) { count++; }

		buffer[count++] = data;
		if (count == pending) { 
			pending = 0;
			processControlByte(command, true); 
		}
	}
}

void Remote::processControlByte(byte control, bool dataAvailable) {
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
	switch (control & R_LED_OP) {
		case R_LED_OP_CLEAR:
			lc->clearDisplay(0);
		break;

		case R_LED_OP_ONE:
			if (dataAvailable) {
				byte x = (buffer[0] >> 4);
				byte y = buffer[0] & 0xF;
				bool value = control & 1;
				lc->setLed(0, y, x, value);
			} else {
				waitFor(1);
			}
		break;

		case R_LED_OP_ROW:
			if (dataAvailable) {
				lc->setRow(0, control & 0x7, buffer[0]);
			} else {
				return waitFor(1);
			}
		break;

		case R_LED_OP_COL:
			if (dataAvailable) {
				lc->setColumn(0, control & 0x7, buffer[0]);
			} else {
				return waitFor(1);
			}
		break;

		case R_LED_OP_ALL:
			if (dataAvailable) {
				for (size_t i=0; i<N; i++) {
					lc->setRow(0, i, buffer[i]);
				}
			} else {
				return waitFor(N);
			}
		break;

		case R_LED_OP_BRIGHT:
			if (dataAvailable) {
				lc->setIntensity(0, buffer[0]);
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
