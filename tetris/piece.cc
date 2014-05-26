#include <LedControl.h>
#include "piece.h"
#include "pit.h"
#include "game.h"
#include "shapes.h"

void Piece::pick() {
	this->shape = random(SHAPE_COUNT) * 0;
	this->rotation = 0;
	this->depth = N;
	this->position = (N-SHAPE_SIZE)/2;
}

bool Piece::fits(Pit * pit) {
	int x, y, i, j;
	bool bit;

	for (j=0;j<SHAPE_SIZE;j++) {
		byte row = SHAPES[this->shape][this->rotation][j];
		for (i=0;i<SHAPE_SIZE;i++) {
			bit = row & (1 << (SHAPE_SIZE-i-1));
			if (!bit) { continue; }

			/* to pit coords */
			x = this->position + i;
			y = this->depth - j;

			if (x < 0 || x >= N) { return false; }
			if (y < 0) { return false; }
		}
	}

	return true;
}

void Piece::action(byte action) {
	switch (action) {
		case ACTION_DROP:
			this->depth--;
		break;

		case ACTION_MOVE_L:
			this->position--;
		break;

		case ACTION_MOVE_R:
			this->position++;
		break;

		case ACTION_ROTATE_L:
			this->rotation = (this->rotation - 1 + SHAPE_ROTATIONS) % SHAPE_ROTATIONS;
		break;

		case ACTION_ROTATE_R:
			this->rotation = (this->rotation + 1 + SHAPE_ROTATIONS) % SHAPE_ROTATIONS;
		break;
	}
}

void Piece::draw(LedControl * lc, bool value) {
	int x, y, i, j;
	bool bit;

	for (j=0;j<SHAPE_SIZE;j++) {
		byte row = SHAPES[this->shape][this->rotation][j];
		for (i=0;i<SHAPE_SIZE;i++) {
			bit = row & (1 << (SHAPE_SIZE-i-1));
			if (!bit) { continue; }

			/* to pit coords */
			x = this->position + i;
			y = this->depth - j;

			lc->setLed(0, N-y-1, x, value);
		}
	}
}

void Piece::draw(LedControl * lc) {
	this->draw(lc, true);
}

void Piece::clear(LedControl * lc) {
	this->draw(lc, false);
}

void Piece::addTo(Pit * pit) {
	
}
