#include "LedControl.h"

#include "game.h"

/* 
 * Pin 12 is connected to the DATA IN-pin of the first MAX7221
 * Pin 11 is connected to the CLK-pin of the first MAX7221
 * Pin 10 is connected to the LOAD(/CS)-pin of the first MAX7221 	
 * There will only be a single MAX7221 attached to the arduino 
 */
LedControl lc = LedControl(12,11,10,1); 
Game game(&lc);

void setup() {
	Serial.begin(9600);

	lc.shutdown(0, false);
	lc.setIntensity(0, 0);

	randomSeed(analogRead(A0) * analogRead(A1) * analogRead(A2));
	random(100);

	game.start();
}


void loop() {
	delay(100);
	game.step();
}
