#ifndef piece_h
#define piece_h

#include <Arduino.h>
#include "pit.h"

class Piece {
	public:
		Piece();
		void center();
		void pick();
		void action(byte);
		bool fits(Pit *);
		void addTo(Pit *);
		byte color;
		byte shape;
		byte rotation;
		int position;
		int depth;
};

#endif
