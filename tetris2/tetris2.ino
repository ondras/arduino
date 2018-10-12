#include <tetris.h>
#include "output-rgbmatrix.h"

#ifdef BENCH
	#include <stdio.h>
	#include <limits.h>
	#define MAX_GAMES 100
	Output output;
	int total_score = 0;
	int min_score = INT_MAX;
	int max_score = 0;
	int games = 0;
#elif TERM
	OutputTerminal output;
#else
	OutputRGBMatrix output;
#endif


//Weights weights { .holes = 20, .max_depth = 2, .cells = 1, .max_slope = 1, .slope = 1, .weighted_cells = 1 };
//Weights weights { .holes = 11.8, .max_depth = 0.1, .cells = -1.1, .max_slope = 0.6, .slope = 2.2, .weighted_cells = 0.6 };
//Game game(&output, weights);
Game game(output);

void setup() {
//	randomSeed(analogRead(A0) * analogRead(A1) * analogRead(A2));
#ifdef BENCH
	srandom(games);
#endif
	game.start();
}

void loop() {
	game.step();

	if (game.playing) {
#ifndef BENCH
		delay(100);
#endif
	} else {
#ifdef BENCH
		games++;
		total_score += game.score;
		min_score = min(min_score, game.score);
		max_score = max(max_score, game.score);
#else
		delay(1000);
#endif

#ifdef BENCH
		if (games > MAX_GAMES) {
			printf("total: %i, min: %i, max: %i\n", total_score, min_score, max_score);
//			printf("%i\n", total_score);
			exit(0);
		} else {
			setup();
		}
#else
		setup();
#endif
	}
}

#if defined(BENCH) || defined(TERM)

int main(int argc, char** argv) {
#ifdef BENCH
	if (argc < 7) {
		printf("USAGE: %s holes max_depth cells max_slope slope weighted_cells\n", argv[0]);
		exit(1);
	}

	weights.holes = atof(argv[1]);
	weights.max_depth = atof(argv[2]);
	weights.cells = atof(argv[3]);
	weights.max_slope = atof(argv[4]);
	weights.slope = atof(argv[5]);
	weights.weighted_cells = atof(argv[6]);
#endif

	setup();
	while (true) { loop(); }
}

#endif
