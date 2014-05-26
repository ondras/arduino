#ifndef game_h
#define game_h

#include <LedControl.h>
#include "ai.h"
#include "pit.h"
#include "piece.h"

#define ACTION_DROP		0
#define ACTION_MOVE_L	1
#define ACTION_MOVE_R	2
#define ACTION_ROTATE_L	3
#define ACTION_ROTATE_R 4

class Game {
	public:
		Game(LedControl *);
		void start();
		void step();

	private:
		AI ai;
		Piece piece;
		Pit pit;
		LedControl * lc;
		int score;
		bool playing;
		void newPiece();
		void gameOver();
};

#endif
