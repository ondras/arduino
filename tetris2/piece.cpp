#include "piece.h"
#include "game.h"
#include "shapes.h"

#include <stdio.h>

Piece::Piece() {
	this->color = 1 + random(COLOR_COUNT);
	this->shape = random(SHAPE_COUNT);
	this->rotation = 0;
	this->center();
}

void Piece::center() {
	this->depth = DEPTH;
	this->position = (WIDTH-SHAPE_SIZE)/2;
}

bool Piece::fits(Pit * pit) {
	int x, y, i, j;
	bool bit;

	for (j=0;j<SHAPE_SIZE;j++) {
		y = this->depth - j;
		if (y >= DEPTH) { continue; }

		byte row = SHAPES[this->shape][this->rotation][j];

		for (i=0;i<SHAPE_SIZE;i++) {
			bit = row & (1 << (SHAPE_SIZE-i-1));
			if (!bit) { continue; }

			x = this->position + i;

			if (x < 0 || x >= WIDTH) { return false; }
			if (y < 0) { return false; }
			if (pit->data[x][y] > 0) { return false; }
		}
	}

	return true;
}

void Piece::action(byte action) {
	switch (action) {
		case ACTION_DROP:
			this->depth--;
		break;

		case ACTION_UNDO_DROP:
			this->depth++;
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

void Piece::addTo(Pit * pit) {
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
			if (y >= DEPTH) { continue; } /* out of the pit */

			pit->data[x][y] = this->color;
		}
	}
}
