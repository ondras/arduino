#ifndef game_h
#define game_h

#include "ai.h"
#include "pit.h"
#include "piece.h"
#include "output.h"

#define ACTION_DROP			0
#define ACTION_MOVE_L		1
#define ACTION_MOVE_R		2
#define ACTION_ROTATE_L		3
#define ACTION_ROTATE_R 	4
#define ACTION_UNDO_DROP	5

class Game {
	public:
		Game(Output*, Weights*);
		void start();
		void step();
		bool playing;
		int score;

	private:
		AI ai;
		Piece piece;
		Pit pit;
		Output* output;
		void newPiece();
		void gameOver();
};

#endif
