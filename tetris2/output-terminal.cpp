#include "output-terminal.h"
#include <stdio.h>
#define gotoxy(y,x) printf("\033[%d;%dH", (x), (y))

void OutputTerminal::newGame() {
	printf("\e[1;1H\e[2J");
	gotoxy(0, 0);
	printf("new game\n");
}

void OutputTerminal::setScore(int score) {
	gotoxy(0, 1);
	printf("score: %i\n", score);
}

void OutputTerminal::setPixel(byte x, byte y, byte color) {
	gotoxy(10+2*x, 10+y);
	printf("%i", color);
}

void OutputTerminal::draw(Pit * pit, Piece * piece) {
	Output::draw(pit, piece);
	fflush(stdout);
}
