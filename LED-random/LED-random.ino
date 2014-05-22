#include "LedControl.h"

#define N 8
#define LEN 4
#define DELAY 50

/*
 * Pin 12 is connected to the DATA IN-pin of the first MAX7221
 * Pin 11 is connected to the CLK-pin of the first MAX7221
 * Pin 10 is connected to the LOAD(/CS)-pin of the first MAX7221 	
 * There will only be a single MAX7221 attached to the arduino 
 */
LedControl lc=LedControl(12,11,10,1); 

class Point {
	public:
		int x;
		int y;
		Point * next;
		Point(int x, int y): x(x), y(y), next(NULL) {}

		~Point() {
			off();
		}

		void on() {
			lc.setLed(0, x, y, true);
		}
		void off() {
			lc.setLed(0, x, y, false);
		}
};

void setup() {
	lc.shutdown(0, false);
	lc.setIntensity(0, 15);
}

Point tail(0, 0);

void loop() {
	Point * ptr = &tail;
	int len = 0;

	/* find last point */
	while (ptr->next != NULL) { 
		ptr = ptr->next; 
		len++;
	}

	/* insert new one */
	ptr->next = new Point(random(N), random(N));
	ptr->next->on();
	len++;

	/* remove old from tail */
	while (len > LEN) {
		ptr = tail.next;
		tail.next = ptr->next;
		delete ptr;
		len--;
	}

	delay(DELAY);
}
