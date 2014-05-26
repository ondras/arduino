#ifndef pit_h
#define pit_h

#include <Arduino.h>
#define N 8

class Pit {
	public:
		Pit();
		byte cleanup();
		byte data[N];
};

#endif
