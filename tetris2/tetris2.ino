#include "game.h"
#include "pit.h"
#include "output-terminal.h"
#include "output-rgbmatrix.h"
#include "output.h"

#ifdef BENCH
#include <stdio.h>
Output output;
#elif TERM
OutputTerminal output;
#else
OutputRGBMatrix output;
#endif

int total_score = 0;
int games = 0;

Weights weights { .holes = 20, .max_depth = 2, .cells = 1, .max_slope = 1, .slope = 1, .weighted_cells = 1 };
Game game(&output, &weights);

void setup() {
//	randomSeed(analogRead(A0) * analogRead(A1) * analogRead(A2));
	srandom(games+10);
	game.start();
}

void loop() {
	game.step();

	if (game.playing) {
		#ifndef FAST
		delay(150);
		#endif
	} else {
		games++;
		total_score += game.score;
		#ifndef FAST
		delay(1000);
		#endif

		#ifdef BENCH
		if (games > 100) {
			printf("%i", total_score);
			exit(0);
		} else {
			setup();
		}
		#else
		setup();
		#endif
	}
}
