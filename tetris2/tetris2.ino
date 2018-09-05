#include "game.h"
#include "output-terminal.h"
#include "output-rgbmatrix.h"

#ifdef TERMINAL
OutputTerminal output;
#else
OutputRGBMatrix output;
#endif

Game game(&output);

void setup() {
//	randomSeed(analogRead(A0) * analogRead(A1) * analogRead(A2));
//	random(100);

	game.start();
}

void loop() {
	game.step();

	if (game.playing) {
		delay(150);
	} else {
		delay(1000);
		game.start();
	}
}
