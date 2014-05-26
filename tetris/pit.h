#ifndef pit_h
#define pit_h

#include <Arduino.h>
#include <LedControl.h>
#define N 8

class Pit {
	public:
		Pit();
		byte cleanup(LedControl * lc);
		byte data[N];
};

#endif
