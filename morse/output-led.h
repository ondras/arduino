#include <LedControl.h>
#include "output.h"

class OutputLED : public Output {
	public:
		OutputLED(LedControl *, float speed);
		void dot();
		void dash();
		void letter();
		void word();

	private:
		LedControl * lc;
		float speed;
		void on();
		void off();
		void set(byte);
};
