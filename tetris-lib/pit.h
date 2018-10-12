#ifndef pit_h
#define pit_h

#include <Arduino.h>
#define WIDTH 8
#define DEPTH 8

typedef struct {
	float holes, max_depth, cells, max_slope, slope, weighted_cells;
} Weights;

class Pit {
	public:
		Pit(Weights&);
		byte cleanup();
		void clear();
		float score();
		byte data[WIDTH][DEPTH];
		Weights* weights;
};

#endif
