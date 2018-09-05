#include "output-terminal.h"
#include "shapes.h"

#include <stdio.h>

#define gotoxy(y,x) printf("\033[%d;%dH", (x), (y))
#define C_BLK  "\x1B[30m"
#define C_RED  "\x1B[31m"
#define C_GRN  "\x1B[32m"
#define C_YEL  "\x1B[33m"
#define C_BLU  "\x1B[34m"
#define C_MAG  "\x1B[35m"
#define C_CYN  "\x1B[36m"
#define C_WHT  "\x1B[37m"
#define RESET  "\x1B[0m"

const char * COLORS[COLOR_COUNT+1] = {
	C_BLK,
	C_RED,
	C_GRN,
	C_BLU,
	C_YEL,
	C_CYN,
	C_MAG
};

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
	printf("%so" RESET, COLORS[color]);
}

void OutputTerminal::draw(Pit * pit, Piece * piece) {
	Output::draw(pit, piece);
	fflush(stdout);
}
