#include "morse.h"
#include "output-led.h"
#include <Arduino.h>

LedControl lc(12, 11, 3, 1); 

OutputLED output(&lc, 1);
Morse morse(&output);

void setup() {
	lc.setIntensity(0, 0);
}

void loop() {
	morse.string(String("SOS JAK CYP"));
}
