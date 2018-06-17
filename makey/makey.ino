#include "pitches.h"
#define BUZZ 13
#define DELAY_SMALL 10
#define DELAY_MELODY 200

class Pin {
	public:
		Pin(int in, int threshold) : in(in), out(in-A0+6), threshold(threshold), value(0), on(false) {
			pinMode(out, OUTPUT);
		}
		void update() {
			this->value = analogRead(this->in);
			this->on = this->value < 1023-this->threshold;
			digitalWrite(this->out, this->on ? HIGH : LOW);
		}
		bool isOn() {
			return this->on;
		}
		int getValue() {
			return this->value;
		}

	private:
		int in;
		int out;
		int threshold;
		int value;
		bool on;
};

class Melody {
	public:
		Melody(int * def) : def(def), index(0) {

		}
		void step() {
			this->index++;
			if (!this->def[index]) { this->index = 0; }

			if (this->def[index] > 0) {
				tone(BUZZ, this->def[index]);
			} else {
				noTone(BUZZ);
			}
			delay(DELAY_MELODY);
		}
		void reset() {
			this->index = 0;
		}
	private:
		int * def;
		int index;

};

Pin pins[] = {
	Pin(A0, 80),
	Pin(A1, 100),
	Pin(A2, 100)
};

int def[] = {NOTE_A4, -1, NOTE_A3, -1, 0};
Melody song(def);

void setup() {
	pinMode(BUZZ, OUTPUT);
}

int current = 0;

void play(int freq) {
	if (freq == current) { return; }
	current = freq;
	if (freq) {
		tone(BUZZ, freq);
	} else {
		noTone(BUZZ);
	}
}

void loop() {
	int count = sizeof(pins) / sizeof(Pin);
	for (int i=0;i<count;i++) { pins[i].update(); }
	
	if (pins[0].isOn()) {
		song.reset();
		tone(BUZZ, 4096 - 5*pins[0].getValue());
	}  else {
		noTone(BUZZ);
	} 
	delay(DELAY_SMALL);
	
	
	/*
	if (pins[0].isOn()) {
		play(NOTE_C5);
	} else if (pins[1].isOn()) {
		play(NOTE_E5);
	} else if (pins[2].isOn()) {
		play(NOTE_G5);
	} else {
		play(0);
	}*/
/*
	if (pins[0].isOn()) {
		song.reset();
		tone(BUZZ, NOTE_A4);
		delay(DELAY_SMALL);
	} else if (pins[1].isOn()) {
		song.reset();
		tone(BUZZ, 4096 - 4*pins[1].getValue());
		delay(DELAY_SMALL);
	} else if (pins[2].isOn()) {
		song.step();
	} else {
		song.reset();
		noTone(BUZZ);
	}
	*/
}
