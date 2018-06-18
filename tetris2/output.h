#ifndef output_h
#define output_h

#include <Arduino.h>
#include "pit.h"
#include "piece.h"

class Output {
	public:
		virtual void setScore(int);
		virtual void newGame();
		virtual void draw(Pit *, Piece *);

	private:
		virtual void drawPit(Pit *);
		virtual void drawPiece(Piece *);
		virtual void setPixel(byte, byte, byte);
};

#endif
