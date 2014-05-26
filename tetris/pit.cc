#include <Arduino.h>
#include "pit.h"

Pit::Pit() {
	for (byte i=0;i<N;i++) { this->data[i] = 0; }
}

byte Pit::cleanup() {

}
