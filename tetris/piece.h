#ifndef piece_h
#define piece_h

#include <Arduino.h>
#include <LedControl.h>
#include "pit.h"

class Piece {
	public:
		void center();
		void pick();
		void action(byte);
		bool fits(Pit *);
		void addTo(Pit *);
		void draw(Output *);
		void clear(Output *);
		byte shape;
		byte rotation;
		int position;

	private:
		int depth;
		void draw(Output *, bool value);
};

#endif
