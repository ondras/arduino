#include "pit.h"
#include "stdio.h"

Pit::Pit(Weights& weights): weights(&weights) {}

void Pit::clear() {
	for (int x=0;x<WIDTH;x++) { 
		for (int y=0;y<DEPTH;y++) { 
			this->data[x][y] = 0; 
		}
	}
}

byte Pit::cleanup() {
	byte removed = 0, row = 0, tmp, cells_in_row, x;
	byte * col;

	while (row < DEPTH) {
		cells_in_row = 0;
		for (x=0; x<WIDTH; x++) {
			if (this->data[x][row] > 0) { cells_in_row++; }
		}

		if (cells_in_row == WIDTH) { // remove row, move all above
			removed++;
			for (x=0; x<WIDTH; x++) {
				col = this->data[x];
				for (tmp=row; tmp<DEPTH; tmp++) {
					col[tmp] = (tmp+1 == DEPTH ? 0 : col[tmp+1]);
				}
			}

		} else {
			row++;
		}
	}

	return removed;
}

/* compute six values:
  - holes = number of holes (cells with empty cell below them)
  - max_depth = maximum column depth
  - cells = total occupied cells
  - max_slope = maximum of absolute slopes
  - slope = sum of absolute column differences
  - weighted_cells = weighted sum of cells
*/
float Pit::score() {
	int max_depth = 0, cells = 0, holes = 0, slope = 0, max_slope = 0, weighted_cells = 0;

	byte x, y, cells_in_row, depth;
	byte depths[WIDTH];
	memset(depths, 0, sizeof(depths));

	for (y=0; y<DEPTH; y++) {
		depth = y+1;
		cells_in_row = 0;

		for (x=0; x<WIDTH; x++) { // for all columns
			if (this->data[x][y] == 0) { continue; } // skip empty cells
			cells_in_row++;

			cells++; // update cells
			weighted_cells += depth; // update weighted cells
			depths[x] = max(depths[x], depth); // adjust column depths

			if (y && (this->data[x][y-1] == 0)) { holes++; } // look below for a hole
		}

		if (cells_in_row > 0) { max_depth = depth; } // max depth
 	}


 	int diff;
	for (x=0;x<WIDTH-1;x++) {
		diff = abs(depths[x]-depths[x+1]);
		slope += diff;
		max_slope = max(max_slope, diff);
	}

	// experimental weights
	//return 20*holes + 2*max_depth + 1*cells + 1*max_slope + 1*slope + 1*weighted_cells;
	Weights* w = weights;
	return w->holes*holes + w->max_depth*max_depth + w->cells*cells + w->max_slope*max_slope + w->slope*slope + w->weighted_cells*weighted_cells;
}
