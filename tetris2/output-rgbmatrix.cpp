#include "output-rgbmatrix.h"
#include "shapes.h"
#include <Arduino.h>

#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>

// #define DATA_PIN 13 // corresponds to Wemos pin D7
// #define DATA_PIN 2 // corresponds to Wemos pin D4, built-in LED
#define DATA_PIN 0 // corresponds to Wemos pin D3
#define NUM_LEDS 64

CRGB COLORS[COLOR_COUNT+1] = {
	CRGB::Black,
	CRGB::Red,
	CRGB::Green,
	CRGB::Blue,
	CRGB::Yellow,
	CRGB::Cyan,
	CRGB::Magenta
};
CRGB leds[NUM_LEDS];

OutputRGBMatrix::OutputRGBMatrix() {
	FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
	FastLED.setBrightness(80);
}

void OutputRGBMatrix::newGame() {}
void OutputRGBMatrix::setScore(int score) {}

byte xy_to_index(byte x, byte y) {
	bool odd = y % 2;
	byte index = WIDTH*y;
	/*
	if (y % 2) {
		index += x;
	} else {
		index += WIDTH-x-1;
	}
	*/
	index += x;
	return index;
}

void OutputRGBMatrix::setPixel(byte x, byte y, byte color) {
	byte index = xy_to_index(x, y);
	leds[index] = COLORS[color];
}

void OutputRGBMatrix::draw(Pit& pit, Piece& piece) {
	Output::draw(pit, piece);
	FastLED.show();
}
