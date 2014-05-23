#ifndef Remote_h
#define Remote_h

#include <LedControl.h>
#define MAXLEN	8 // bytes

class Remote {
public:
	Remote(LedControl * lc);
	void processByte(byte data); 

private:
	LedControl * lc;

	size_t pending;
	int buffer[MAXLEN];
	byte command;

	void waitFor(size_t len);
	void processControlByte(byte control, bool dataAvailable);
	void processControlLED(byte control, bool dataAvailable);
	void processControlLCD(byte control, bool dataAvailable);
};

#endif