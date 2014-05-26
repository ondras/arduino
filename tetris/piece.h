#ifndef piece_h
#define piece_h

#include <Arduino.h>
#include <LedControl.h>
#include "pit.h"

class Piece {
	public:
		void pick();
		void action(byte);
		bool fits(Pit *);
		void addTo(Pit *);
		void draw(LedControl *);
		void clear(LedControl *);

	private:
		byte shape;
		byte rotation;
		int position;
		int depth;
		void draw(LedControl *, bool value);
};

#endif
