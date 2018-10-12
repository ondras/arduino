#include "ai.h"
#include "game.h"
#include "shapes.h"

byte AI::act(Piece& piece, Pit& pit) {
	// rotate if necessary
	if (piece.rotation != this->targetRotation) { return ACTION_ROTATE_R; }

	// move left/right if necessary
	int posDiff = piece.position - this->targetPosition;
	if (posDiff != 0) {
		return (posDiff > 0 ? ACTION_MOVE_L : ACTION_MOVE_R);
	}

	// just drop
	return ACTION_DROP;
}

void AI::newPiece(Piece& piece, Pit& pit) {
	/* failsafe defaults */
	this->targetPosition = piece.position;
	this->targetRotation = piece.rotation;

	float bestScore = -1, score;
	int minPosition, maxPosition;
	Pit tmpPit(*(pit.weights));
	Piece tmpPiece = piece;

	for (byte rotation = 0; rotation < SHAPE_ROTATIONS; rotation++) {
		tmpPit = pit;
		tmpPiece.rotation = rotation;

		/* find left limit */
		tmpPiece.center();
		while (tmpPiece.fits(tmpPit)) { tmpPiece.action(ACTION_MOVE_L); }
		minPosition = tmpPiece.position + 1;

		/* find right limit */
		tmpPiece.center();
		while (tmpPiece.fits(tmpPit)) { tmpPiece.action(ACTION_MOVE_R); }
		maxPosition = tmpPiece.position - 1;

		if (minPosition > maxPosition) { continue; }

		/* try all positions */
		for (int position = minPosition; position <= maxPosition; position++) {
			tmpPiece.center();
			tmpPiece.position = position;
			tmpPit = pit;

			while (tmpPiece.fits(tmpPit)) { tmpPiece.action(ACTION_DROP); }
			tmpPiece.action(ACTION_UNDO_DROP); /* revert the last drop */

			tmpPiece.addTo(tmpPit);
			tmpPit.cleanup();
			score = tmpPit.score();

			if (bestScore == -1 || score < bestScore) {
				bestScore = score;
				this->targetPosition = position;
				this->targetRotation = rotation;
			}
		}
	}
}
