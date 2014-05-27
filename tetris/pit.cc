#include "pit.h"

Pit::Pit() {
	for (byte i=0;i<N;i++) { this->data[i] = 0; }
}

byte Pit::cleanup(LedControl * lc) {
	byte removed = 0, index = 0, tmp;

	while (index < N) {
		if (this->data[index] == (1 << N) - 1) { /* remove row, move all above */
			removed++;
			for (tmp=index; tmp<N; tmp++) {
				this->data[tmp] = (tmp+1 == N ? 0 : this->data[tmp+1]);
			}
		} else {
			index++;
		}
	}

	if (lc != NULL && removed > 0) {
		lc->clearDisplay(0);
		for (index=0; index<N; index++) {
			lc->setRow(0, N-index-1, this->data[index]);
		}
	}

	return removed;
}

float Pit::score() {
	/* compute six values:
	  - max = maximum column depth
	  - cells = total occupied cells
	  - weight = weighted sum of cells
	  - holes = number of holes (cells with empty cell below them)
	  - slope = sum of absolute column differences
	  - maxslope = maximum of absolute slopes
	*/
	int max = 0, cells = 0, holes = 0, slope = 0, maxslope = 0, weight = 0;
	byte mask, diff, x;

	byte depths[N];
	memset(depths, 0, sizeof(depths));

	for (int depth=0; depth<N; depth++) {
		byte row = this->data[depth];
		if (!row) { continue; } /* skip empty */

		max = depth+1; /* maximum depth */

		for (x=0; x<N; x++) { /* for all columns */
			mask = 1 << x;
			if (!(row & mask)) { continue; } /* skip empty cells */

			cells++; /* update cells */
			weight += (depth+1); /* update weighted cells */
			depths[x] = max(depths[x], depth+1); /* adjust column depths */

			if (depth && !(this->data[depth-1] & mask)) { holes++; } /* look below for a hole */
		}
	}


	for (x=0;x<N-1;x++) {
		diff = abs(depths[x]-depths[x+1]);
		slope += diff;
		maxslope = max(maxslope, diff);
	}

	/* experimental weights */
	return 20*holes + 2*max + 1*cells + 1*maxslope + 1*slope + 1*weight;
}

