#include <Adafruit_NeoPixel.h>

// set to pin connected to data input of WS8212 (NeoPixel) strip
#define PIN         0
#define RNDPIN      2

// number of LEDs (NeoPixels) in your strip
// (please note that you need 3 bytes of RAM available for each pixel)
#define NUMPIXELS   7

// max LED brightness (1 to 255) – start with low values!
// (please note that high brightness requires a LOT of power)
#define BRIGHTNESS  250


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // initialize pseudo-random number generator with some random value
  randomSeed(analogRead(RNDPIN));
  pinMode(1, OUTPUT);

  // initialize LED strip
  strip.begin();
  strip.show();
}

double current = 0;

void loop() {
  // use real time to recalculate position of each color spot
  double ms = (double) millis();
  float speed = (1+sin(ms/1000))/2;
  speed = max(speed, 0.2);

  float center = BRIGHTNESS * speed;
  strip.setPixelColor(0, center, center, center);

  current += speed*0.02;
  int currentIndex = long(current) % (NUMPIXELS-1);

  for (int i=0; i<NUMPIXELS-1; i++) {
    int value = (i == currentIndex ? BRIGHTNESS/2 : 0);
    strip.setPixelColor(i+1, value, value, value);
  }

  // send data to LED strip
  strip.show();

  int s = ms/1000;
  digitalWrite(1, (s % 2 ? HIGH : LOW));
}



