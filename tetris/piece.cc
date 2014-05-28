#include "piece.h"
#include "game.h"
#include "shapes.h"

void Piece::pick() {
	this->shape = random(SHAPE_COUNT);
	this->rotation = 0;
	this->center();
}

void Piece::center() {
	this->depth = N;
	this->position = (N-SHAPE_SIZE)/2;
}

bool Piece::fits(Pit * pit) {
	int x, y, i, j;
	bool bit;

	for (j=0;j<SHAPE_SIZE;j++) {
		y = this->depth - j;
		if (y >= N) { continue; }

		byte row = SHAPES[this->shape][this->rotation][j];

		for (i=0;i<SHAPE_SIZE;i++) {
			bit = row & (1 << (SHAPE_SIZE-i-1));
			if (!bit) { continue; }

			x = this->position + i;

			if (x < 0 || x >= N) { return false; }
			if (y < 0) { return false; }
			if (pit->data[y] & (1 << (N-x-1))) { return false; }
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

void Piece::draw(Output * output, bool value) {
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

			output->setPixel(x, N-y-1, value);
		}
	}
}

void Piece::draw(Output * output) {
	this->draw(output, true);
}

void Piece::clear(Output * output) {
	this->draw(output, false);
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
			if (y >= N) { continue; } /* out of the pit */

			pit->data[y] |= (1 << (N-x-1));
		}
	}
}
