#ifndef ai_h
#define ai_h

#include <Arduino.h>
#include "piece.h"
#include "pit.h"

class AI {
	public:
		byte act(Piece&, Pit&);
		void newPiece(Piece&, Pit&);
	private:
		byte targetRotation;
		int targetPosition;
};

#endif
