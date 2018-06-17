#include "output-rgbmatrix.h"
#include <stdio.h>

void OutputRGBMatrix::newGame() {
	printf("new game\n");
}
void OutputRGBMatrix::setScore(int score) {
	printf("score: %i\n", score);
}
void OutputRGBMatrix::setPixel(byte x, byte y, byte color) {
}
