#include "output-ledlcd.h"

OutputLEDLCD::OutputLEDLCD(LedControl * lc, LiquidCrystal * lcd) : 
	lc(lc), lcd(lcd), score(0), bestScore(0), game(0), bestGame(0) {

	if (this->lc) { 
		this->lc->shutdown(0, false);
		this->lc->setIntensity(0, 0);
	}
	if (this->lcd) {
		this->lcd->begin(16, 2);
	}
}

void OutputLEDLCD::clearPixels() {
	if (this->lc != NULL) { this->lc->clearDisplay(0); }
}

void OutputLEDLCD::setPixel(byte x, byte y, bool value) {
	if (this->lc != NULL) { this->lc->setLed(0, y, x, value); }
}

void OutputLEDLCD::setScore(int score) {
	this->score = score;
	if (this->score > this->bestScore) {
		this->bestScore = this->score;
		this->bestGame = this->game;
	}
	this->draw();
}


void OutputLEDLCD::newGame() {
	this->game++;
	this->setScore(0);
}

void OutputLEDLCD::draw() {
	if (!this->lcd) { return; }

	this->lcd->clear();

	char buf[20];
	sprintf(buf, "Now:  %3d (#%d)", this->score, this->game);
	this->lcd->setCursor(0, 0);
	this->lcd->print(buf);

	sprintf(buf, "Best: %3d (#%d)", this->bestScore, this->bestGame);
	this->lcd->setCursor(0, 1);
	this->lcd->print(buf);
}
