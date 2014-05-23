#include <LedControl.h>
#include <LiquidCrystal.h>

#include "Remote.h"

/* 
 * Now we create a new LedControl. 
 * We use pins 12,11 and 10 on the Arduino for the SPI interface
 * Pin 12 is connected to the DATA IN-pin of the first MAX7221
 * Pin 11 is connected to the CLK-pin of the first MAX7221
 * Pin 10 is connected to the LOAD(/CS)-pin of the first MAX7221  
 * There will only be a single MAX7221 attached to the arduino 
 */

LedControl lc = LedControl(12,11,10,1); 
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

Remote r(&lc);

void setup() {
	lc.shutdown(0, false);
	Serial.begin(9600);

//	lcd.begin(16, 2);
//	lcd.print("hello, world!");

}
/*
			lc.setRow(0, row, value);
		lc.setLed(0, y, x, value);
		*/

int x = 0;
void loop() {
	int data;

	while (1) {
		data = Serial.read();
		if (data == -1) { return; }
		r.processByte(data);

//		lcd.setCursor(x, 1);
  //		lcd.print(data);
		x += 4;
	}
}

