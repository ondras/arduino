#include "morse.h"
#include <Arduino.h>

#define DELAY_STRING 4000

const char * LETTERS[] = {
	".-",     // A
	"-...",   // B
	"-.-.",   // C
	"-..",    // D
	".",      // E
	"..-.",   // F
	"--.",    // G
	"....",   // H
	"..",     // I
	".---",   // J
	"-.-",    // K
	".-..",   // L
	"--",     // M
	"-.",     // N
	"---",    // O
	".--.",   // P
	"--.-",   // Q
	".-.",    // R
	"...",    // S
	"-",      // T
	"..-",    // U
	"...-",   // V
	".--",    // W
	"-..-",   // X
	"-.--",   // Y
	"--.."    // Z
};

const char* NUMBERS[] = {
	"-----",   // 1
	".----",   // 2
	"..---",   // 3
	"...--",   // 4
	"....-",   // 5
	".....",   // 6
	"-....",   // 7
	"--...",   // 8
	"---..",   // 9
	"----."    // 0
};

Morse::Morse(Output * output) : output(output) {}

void Morse::string(String str) {
	bool inWord = false;
	for (int i=0;i<(int) str.length();i++) {
		char ch = str[i];
		if (ch == ' ') {
			if (!inWord) { continue; }
			inWord = false;
			this->output->word();
		} else {
			inWord = true;
			this->letter(ch);
		}
	}
	delay(DELAY_STRING);
}

void Morse::letter(char ch) {
	const char * code;

	if (ch >= 'a' && ch <= 'z') {
		code = LETTERS[ch - 'a'];
	} else if (ch >= 'A' && ch <= 'Z') {
		code = LETTERS[ch - 'A'];
	} else if (ch >= '0' && ch <= '9') {
		code = NUMBERS[ch - '0'];
	} else {
		return;
	}

	for (byte i=0;i<strlen(code);i++) {
		if (code[i] == '.') { 
			this->output->dot(); 
		} else {
			this->output->dash(); 
		}
	}
	this->output->letter();
}