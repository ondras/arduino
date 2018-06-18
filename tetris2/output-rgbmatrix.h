#include "output.h"
#include <Arduino.h>

class OutputRGBMatrix : public Output {
	public:
		OutputRGBMatrix();
		void setScore(int);
		void newGame();
		void draw(Pit *, Piece *);

	private:
		void setPixel(byte, byte, byte);
};
