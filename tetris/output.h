#ifndef output_h
#define output_h

class Output {
	public:
		virtual void clearPixels();
		virtual void setPixel(byte, byte, bool);
		virtual void setScore(int);
		virtual void newGame();
};

#endif
