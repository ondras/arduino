#include <LedControl.h>
#include <LiquidCrystal.h>
#include "output.h"

class OutputLEDLCD : public Output {
	public:
		OutputLEDLCD(LedControl *, LiquidCrystal *);
		void clearPixels();
		void setPixel(byte, byte, bool);
		void setScore(int);
		void newGame();

	private:
		void draw();
		LedControl * lc;
		LiquidCrystal * lcd;
		int score;
		int bestScore;
		int game;
		int bestGame;
};
