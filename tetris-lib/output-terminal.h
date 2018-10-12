#include "output.h"
#include <Arduino.h>

class OutputTerminal : public Output {
	public:
		void setScore(int);
		void newGame();
		void draw(Pit&, Piece&);

	private:
		void setPixel(byte, byte, byte);
};
