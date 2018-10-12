#include "output.h"
#include "shapes.h"

void Output::draw(Pit& pit, Piece& piece) {
	this->drawPit(pit);
	this->drawPiece(piece);
}

void Output::drawPit(Pit& pit) {
	for (int y=0; y<DEPTH; y++) {
		for (int x=0; x<WIDTH; x++) {
			this->setPixel(x, DEPTH-y-1, pit.data[x][y]);
		}
	}
}

void Output::drawPiece(Piece& piece) {
	int x, y, i, j;
	bool bit;

	for (j=0;j<SHAPE_SIZE;j++) {
		byte row = SHAPES[piece.shape][piece.rotation][j];
		for (i=0;i<SHAPE_SIZE;i++) {
			bit = row & (1 << (SHAPE_SIZE-i-1));
			if (!bit) { continue; }

			// to pit coords
			x = piece.position + i;
			y = piece.depth - j;
			if (x < 0 || x >= WIDTH) { continue; }
			if (y < 0 || y >= DEPTH) { continue; }

			this->setPixel(x, DEPTH-y-1, piece.color);
		}
	}
}

void Output::setScore(int score) {}
void Output::newGame() {}
void Output::setPixel(byte x, byte y, byte color) {}