#include <stdio.h>
#include <stdlib.h>
#include "../pit.h"

void setup(void);
void loop(void);

extern Weights weights;

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
