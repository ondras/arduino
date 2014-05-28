#include "game.h"
#include <Arduino.h>

Game::Game(Output * output) : playing(false), output(output), score(0) {
}

void Game::start() {
	this->score = 0;
	this->playing = true;

	this->output->newGame();
	this->pit.clear(this->output);

	this->newPiece();
}

void Game::step() {
	if (!this->playing) { return; }

	byte action = this->ai.act(&this->piece, &this->pit);

	Piece old = this->piece;
	this->piece.action(action);

	if (this->piece.fits(&this->pit)) { /* normal movement */
		old.clear(this->output);
		this->piece.draw(this->output);
	} else { /* cannot move, finish pit and get new piece */
		old.addTo(&this->pit);
		byte removed = this->pit.cleanup(this->output);
		if (removed > 0) {
			this->score += (1 << (removed-1));
			this->output->setScore(this->score);
		}

		this->newPiece();
		if (!this->piece.fits(&this->pit)) { this->gameOver(); }
	}
}

void Game::newPiece() {
	this->piece.pick();
	this->piece.draw(this->output);
	this->ai.newPiece(&this->piece, &this->pit);
}

void Game::gameOver() {
	this->playing = false;
}
