#define TRIG 7
#define ECHO 8
#define BUZZ 3

#define MIN_DIST 3.0
#define MIN_FREQ 131.0
#define MAX_DIST 50.0
#define MAX_FREQ 1048.0

#define GAP 1.059463094

void setup() {
	Serial.begin(9600);
	pinMode(BUZZ, OUTPUT);
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
}

int getPing() {
	digitalWrite(TRIG, LOW); 
	delayMicroseconds(2); 

	digitalWrite(TRIG, HIGH);
	delayMicroseconds(10); 

	digitalWrite(TRIG, LOW);
	return pulseIn(ECHO, HIGH);
}

void loop() {
	float distance = getPing()/58.2;
	if (distance < MIN_DIST || distance > MAX_DIST) {
		noTone(BUZZ);
		return;
	}
	
	float freq = MIN_FREQ + (distance - MIN_DIST) * (MAX_FREQ-MIN_FREQ)/(MAX_DIST-MIN_DIST);

	/* autotune */
//	float lf = log(freq) / log(GAP); 
//	float rlf = round(lf);
//	freq = pow(GAP, rlf);

	tone(BUZZ, freq);
//	Serial.println(distance);
	delay(20);
}
