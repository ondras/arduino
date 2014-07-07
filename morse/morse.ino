#include "morse.h"
#include <LedControl.h>
#include <Arduino.h>

#define N 8
#define SPEED 1
#define DELAY 200*SPEED
#define BLINK(length) led_set(true); delay(length*DELAY); led_set(false); delay(DELAY)
#define LIMIT 150

/*
 * Pin 12 is connected to the DATA IN-pin of the first MAX7221
 * Pin 11 is connected to the CLK-pin of the first MAX7221
 * Pin 10 is connected to the LOAD(/CS)-pin of the first MAX7221 	
 * There will only be a single MAX7221 attached to the arduino 
 */
LedControl lc(12, 11, 10, 1); 
String code;
int index = 0;

void led_set(bool value) {
	for (byte i=0;i<N;i++) {
		lc.setRow(0, i, value ? (1 << N)-1 : 0);
	}
}
void setup() {
	lc.setIntensity(0, 0);
	lc.shutdown(0, false);
	code = morse("tajny kod");
}

void loop() {
	if (analogRead(A0) > LIMIT) {
		index = 0;
		return;
	}

	char ch = code[index];
	switch (ch) {
		case '.': BLINK(1); break;
		case '-': BLINK(3); break;
		case '/': delay(4*DELAY); break;
	}

	index++;
	if (index >= code.length()) { index = 0; }
}
