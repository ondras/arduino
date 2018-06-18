#include "game.h"
#include "output-terminal.h"
#include "output-rgbmatrix.h"

OutputRGBMatrix output;
//OutputTerminal output;
Game game(&output);

void setup() {
//	randomSeed(analogRead(A0) * analogRead(A1) * analogRead(A2));
//	random(100);

	game.start();
}

void loop() {
	game.step();

	if (game.playing) {
		delay(100);
	} else {
		delay(2000);
		game.start();
	}
}
