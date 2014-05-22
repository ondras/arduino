#include "LedControl.h"

/* 
 * Now we create a new LedControl. 
 * We use pins 12,11 and 10 on the Arduino for the SPI interface
 * Pin 12 is connected to the DATA IN-pin of the first MAX7221
 * Pin 11 is connected to the CLK-pin of the first MAX7221
 * Pin 10 is connected to the LOAD(/CS)-pin of the first MAX7221  
 * There will only be a single MAX7221 attached to the arduino 
 */
LedControl lc = LedControl(12,11,10,1); 

#define N 8

void setup() {
	lc.shutdown(0, false);
	Serial.begin(9600);
}

void processControlData(int data) {
	if (data & B10000000) { /* row/column */
		if (data & B1000000) { /* row */
			int row = (data >> 3) & B111;
			int count = data & B111;
			int value = 0;
			for (int i=0;i<count;i++) {
				value += 1 << (7-i);
			}
			lc.setRow(0, row, value);
		} else { /* column */

		}
	} else { /* individual led */
		int x = (data >> 4) & B111;
		int y = (data >> 1) & B111;
		bool value = data & B1;
		lc.setLed(0, y, x, value);
	}

}

void loop() {
	int data;

	while (1) {
		data = Serial.read();
		if (data == -1) { return; }
		processControlData(data);
	} 
}

