#include "game.h"
#include "output-ledlcd.h"

/* 
 * Pin 12 is connected to the DATA IN-pin of the first MAX7221
 * Pin 11 is connected to the CLK-pin of the first MAX7221
 * Pin 3 is connected to the LOAD(/CS)-pin of the first MAX7221 	
 * There will only be a single MAX7221 attached to the arduino 
 */
LedControl lc(12, 11, 3, 1); 
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

OutputLEDLCD output(&lc, &lcd);
Game game(&output);

void setup() {
	randomSeed(analogRead(A0) * analogRead(A1) * analogRead(A2));
	random(100);

	game.start();
}

void loop() {
	game.step();

	if (game.playing) {
		delay(100);
	} else {
		delay(2000);
		game.start();
	}
}
