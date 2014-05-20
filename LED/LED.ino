//we have to include the libary 
#include "LedControl.h"

/* 
 * Now we create a new LedControl. 
 * We use pins 12,11 and 10 on the Arduino for the SPI interface
 * Pin 12 is connected to the DATA IN-pin of the first MAX7221
 * Pin 11 is connected to the CLK-pin of the first MAX7221
 * Pin 10 is connected to the LOAD(/CS)-pin of the first MAX7221 	
 * There will only be a single MAX7221 attached to the arduino 
 */
LedControl lc=LedControl(12,11,10,1); 

int x = 0;
int y = 0;
#define N 8


void setup() {
	lc.shutdown(0, false);

	lc.setIntensity(0, 0);

	lc.setLed(0, N/2, N/2, true);
	lc.setLed(0, N/2 - 1, N/2, true);
	lc.setLed(0, N/2, N/2 - 1, true);
	lc.setLed(0, N/2 - 1, N/2 - 1, true);
}


void loop() {
	lc.setLed(0, x, y, false);

	if (y == 0) { /* first row */
		x++;

		if (x == N) {
			x--;
			y++;
		}

	} else if (y == N-1) { /* last row */
		x--;
		if (x < 0) {
			x++;
			y--;
		}

	} else {
		if (x == 0) { /* first column */
			y--;
		} else { /* last column */
			y++;
		}

	}

	lc.setLed(0, x, y, true);
	delay(100);
}
