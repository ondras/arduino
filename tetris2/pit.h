#ifndef pit_h
#define pit_h

#include <Arduino.h>
#define WIDTH 8
#define DEPTH 8

class Pit {
	public:
		byte cleanup();
		void clear();
		float score();
		byte data[WIDTH][DEPTH];
};

#endif
