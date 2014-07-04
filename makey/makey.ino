class IOPair {
	public:
		IOPair(int in, int threshold) : in(in), out(in-A0+6), threshold(threshold) {
			pinMode(out, OUTPUT);
		}
		void update() {
			int value = analogRead(this->in);
			digitalWrite(this->out, value < 1023-this->threshold ? HIGH : LOW);
		}

	private:
		int in;
		int out;
		int threshold;
};

IOPair pairs[] = { 
	IOPair(A0, 2),
	IOPair(A1, 30),
	IOPair(A2, 300)
};

void setup() {
}

void loop() {
	int count = sizeof(pairs) / sizeof(IOPair);
	for (int i=0;i<count;i++) {
		pairs[i].update();
	}
}
