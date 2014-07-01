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

const char * NUMBERS[] = {
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

const char * CH = "----";

const char * _morseLetter(const char ch, const char next) {
	if ((ch == 'c' || ch == 'C') && (next == 'h' || next == 'H')) {
		return CH;
	} else if (ch >= 'a' && ch <= 'z') {
		return LETTERS[ch - 'a'];
	} else if (ch >= 'A' && ch <= 'Z') {
		return LETTERS[ch - 'A'];
	} else if (ch >= '0' && ch <= '9') {
		return NUMBERS[ch - '0'];
	} else {
		return NULL;
	}
}

String morse(String in) {
	String out, part;
	char ch, next;
	bool inWord = false;

	int len = in.length();
	for (int i=0;i<len;i++) {
		ch = in[i];

		if (ch == ' ') {
			if (!inWord) { continue; }
			inWord = false;
			out += "/";
		} else {
			inWord = true;
			next = (i+1 < len ? in[i+1] : 0);
			part = _morseLetter(ch, next);
			if (part) { 
				out += part + "/"; 
				if (part == CH) { i++; }
			}
		}
	}

	out += "//"; /* word, message */
	
	return out;
}

String morse(const char * in) {
	return morse(String(in));
}
