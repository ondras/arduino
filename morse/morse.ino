#include "morse.h"
#include <LedControl.h>
#include <Arduino.h>

#define N 8
#define SPEED 1
#define DELAY 200*SPEED

LedControl lc(12, 11, 3, 1); 
String code;

void led_set(bool value) {
	for (byte i=0;i<N;i++) {
		lc.setRow(0, i, value ? (1 << N)-1 : 0);
	}
}
void setup() {
	lc.setIntensity(0, 0);
	lc.shutdown(0, false);
	code = morse("SOS JAK CYP");
}

void loop() {
	int len = code.length();
	char ch;
	for (int i=0;i<len;i++) {
		ch = code[i];
		switch (ch) {
			case '.':
				led_set(true);
				delay(DELAY);
				led_set(false);
				delay(DELAY);
			break;
			case '-':
				led_set(true);
				delay(3*DELAY);
				led_set(false);
				delay(DELAY);
			break;
			case '/':
				delay(4*DELAY);
			break;
		}
	}
}

