#include "morse.h"
#include <LiquidCrystal.h>
#include <Arduino.h>

#define PIN_R 3
#define PIN_G 11
#define PIN_B 12
#define LED(r, g, b) digitalWrite(PIN_R, r); digitalWrite(PIN_G, g); digitalWrite(PIN_B, b)

#define SPEED 1
#define DELAY 200*SPEED
#define BLINK(length) LED(1,0,0); delay(length*DELAY); LED(0,0,0); delay(DELAY)
#define THRESHOLD 800

String code = "//.../----/..//";
int index = 0;
bool hibernation = true;

String textOn1  = " Cpt. Kosmodisk";
String textOn2  = " Hibernation ON";
String textOff1 = " Cpt. Kosmodisk";
String textOff2 = " Hibernation OFF";

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void write_text() {
	lcd.clear();
	if (hibernation) {
		lcd.setCursor(0, 0);
		lcd.print(textOn1);
		lcd.setCursor(0, 1);
		lcd.print(textOn2);
	} else {
		lcd.setCursor(0, 0);
		lcd.print(textOff1);
		lcd.setCursor(0, 1);
		lcd.print(textOff2);
	}
}

void setup() {
	pinMode(PIN_R, OUTPUT);
	pinMode(PIN_G, OUTPUT);
	pinMode(PIN_B, OUTPUT);
	lcd.begin(16, 2);
	write_text();
}

void loop() {	
	if (analogRead(0) < THRESHOLD) {
		hibernation = !hibernation;
		write_text();
		index = 0;
		while (analogRead(0) < THRESHOLD) { delay(20); }
		
		if (hibernation) {
			LED(0,0,0);
		} else {
			LED(0,1,0);
		}
	}
	
	if (hibernation) {
		char ch = code[index];
		switch (ch) {
			case '.': BLINK(1); break;
			case '-': BLINK(3); break;
			case '/': delay(4*DELAY); break;
		}

		index++;
		if (index >= code.length()) { index = 0; }
	}
}
