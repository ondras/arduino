#include <Adafruit_NeoPixel.h>

#define PIN         0
#define NUMPIXELS   7

#define MAX_R 1
#define MAX_G 0.5
#define MAX_B 0

#define COLOR(intensity) intensity*MAX_R, intensity*MAX_G, intensity*MAX_B

// max LED brightness (1 to 255) – start with low values!
// (please note that high brightness requires a LOT of power)
#define BRIGHTNESS  250

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(1, OUTPUT);

  strip.begin();
  strip.show();
}

double current = 0;

void loop() {
  double ms = (double) millis(); // double 0..many
  float bright = (1+sin(ms/1500))/2; // float 0..1
  bright = (0.1+bright*0.9) * 250; // 25..250

  strip.setPixelColor(0, COLOR(bright));

  int currentIndex = long(ms/1000) % (NUMPIXELS-1);

  for (int i=0; i<NUMPIXELS-1; i++) {
    float value = (i == currentIndex ? 1 : 0.25);
    strip.setPixelColor(i+1, COLOR(bright * value));
  }

  strip.show();

  int s = ms/1000;
  digitalWrite(1, (s % 2 ? HIGH : LOW));
}



