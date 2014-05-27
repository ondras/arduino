#include "game.h"
#include <Arduino.h>

Game::Game(LedControl * lc) : lc(lc), playing(false), score(0) {
}

void Game::start() {
	this->playing = true;
	this->newPiece();
}

void Game::step() {
	if (!this->playing) { return; }

	byte action = this->ai.act(&this->piece, &this->pit);

	Piece old = this->piece;
	this->piece.action(action);

	if (this->piece.fits(&this->pit)) { /* normal movement */
		old.clear(this->lc);
		this->piece.draw(this->lc);
	} else { /* cannot move, finish pit and get new piece */
		old.addTo(&this->pit);
		byte removed = this->pit.cleanup(this->lc); /* FIXME score */
		for (byte i=0;i<removed;i++) {
			this->score += 100 * (1 << i);
		}

		this->newPiece();
		if (!this->piece.fits(&this->pit)) { this->gameOver(); }
	}
}

void Game::newPiece() {
	this->piece.pick();
	this->piece.draw(lc);
	this->ai.newPiece(&this->piece, &this->pit);
}

void Game::gameOver() {
	this->playing = false;
}