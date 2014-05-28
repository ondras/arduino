#ifndef pit_h
#define pit_h

#include <Arduino.h>
#include "output.h"
#define N 8

class Pit {
	public:
		Pit();
		void draw(Output *);
		byte cleanup(Output *);
		void clear(Output *);
		float score();
		byte data[N];
};

#endif
