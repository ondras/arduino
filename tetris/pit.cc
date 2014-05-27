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

	if (removed > 0) {
		lc->clearDisplay(0);
		for (index=0; index<N; index++) {
			lc->setRow(0, N-index-1, this->data[index]);
		}
	}

	return removed;
}

float Pit::score() {
	return 0;
}