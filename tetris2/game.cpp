#include "game.h"
#include "piece.h"

Game::Game(Output* output, Weights* weights) : playing(false), output(output), pit(Pit(weights)), score(0) {}

void Game::start() {
	this->score = 0;
	this->playing = true;

	this->output->newGame();
	this->pit.clear();

	this->newPiece();
	this->output->draw(&this->pit, &this->piece);
}

void Game::step() {
	if (!this->playing) { return; }

	byte action = this->ai.act(&this->piece, &this->pit);

	Piece old = this->piece;
	this->piece.action(action);

	if (this->piece.fits(&this->pit)) { // normal movement
	} else { // cannot move, finish pit and get new piece
		old.addTo(&this->pit);
		byte removed = this->pit.cleanup();
		if (removed > 0) {
			this->score += (1 << (removed-1));
			this->output->setScore(this->score);
		}

		this->newPiece();
		if (!this->piece.fits(&this->pit)) { this->gameOver(); }
	}

	this->output->draw(&this->pit, &this->piece);
}

void Game::newPiece() {
	this->piece = Piece();
	this->ai.newPiece(&this->piece, &this->pit);
}

void Game::gameOver() {
	this->playing = false;
}
