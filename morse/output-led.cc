#include <Arduino.h>
#include "output-led.h"
#define N 8

#define DELAY_DOT 200
#define DELAY_DASH 3*DELAY_DOT
#define DELAY_GLYPH DELAY_DOT
#define DELAY_LETTER 5*DELAY_DOT

OutputLED::OutputLED(LedControl * lc, float speed) : lc(lc), speed(speed) {
	if (this->lc) { 
		this->lc->shutdown(0, false);
		this->lc->setIntensity(0, 0);
	}
}

void OutputLED::dot() {
	this->on();
	delay(this->speed * DELAY_DOT);
	this->off();
	delay(this->speed * DELAY_GLYPH);
}

void OutputLED::dash() {
	this->on();
	delay(this->speed * DELAY_DASH);
	this->off();
	delay(this->speed * DELAY_GLYPH);
}

void OutputLED::letter() {
	delay(this->speed * DELAY_LETTER);
}

void OutputLED::word() {
}

void OutputLED::on() {
	this->set((1 << N)-1);
}

void OutputLED::off() {
	this->set(0);
}

void OutputLED::set(byte value) {
	if (!this->lc) { return; }
	for (byte i=0;i<N;i++) {
		this->lc->setRow(0, i, value);
	}
}
