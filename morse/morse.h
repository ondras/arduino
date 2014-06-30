#ifndef morse_h
#define morse_h

#include <Arduino.h>
#include "output.h"

class Morse {
	public:
		Morse(Output *);
		void string(String);
		void letter(char);

	private:
		Output * output;
};

#endif
