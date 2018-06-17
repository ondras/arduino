#define N 3
#define MAX 256

byte pins[N] = {6, 5, 3};
byte rgb[N] = {0, 0, 0};

byte index = 0;
int direction = 1;

void setup() {
	Serial.begin(9600);
	for (byte i=0; i<N; i++) { pinMode(pins[i], OUTPUT); }
}

void write() {
	for (byte i=0; i<N; i++) { analogWrite(pins[i], rgb[i]); }
}

void loop() {
	index = (index + 1 + random(N-1)) % N;
	direction = (rgb[index] ? -1 : 1);

	for (int i=1; i<MAX; i++) {
		rgb[index] += direction;

		write();
		delay(5);
	}
}
