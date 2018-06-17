#ifndef arduino_h
#define arduino_h

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/share/arduino/hardware/arduino/cores/arduino/binary.h"

#define byte unsigned char
#define delay(t) usleep(1000*t)
#define random(max) (random()%max)
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))

#endif
