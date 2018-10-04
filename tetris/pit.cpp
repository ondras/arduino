#include "pit.h"

Pit::Pit() {
}

void Pit::clear(Output * output) {
	for (byte i=0;i<N;i++) { this->data[i] = 0; }
	this->draw(output);
}

byte Pit::cleanup(Output * output) {
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

	if (removed > 0 && output != NULL) { this->draw(output); }

	return removed;
}

void Pit::draw(Output * output) {
	output->clearPixels();
	for (byte depth=0; depth<N; depth++) {
		for (byte x=0; x<N; x++) {
			output->setPixel(x, N-depth-1, this->data[depth] & (1 << (N-x-1)));
		}
	}
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

	/* weights computed by a genetic algorithm */
	return 11.8*holes + 0.1*max + -1.1*cells + 0.6*maxslope + 2.2*slope + 0.6*weight;
}
