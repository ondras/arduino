#include "feature.h"
#include "leds.h"
#include <FastLED.h>

const bool MASK[NUM_LEDS] = {
  0, 1, 1, 0, 0, 1, 1, 0,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  0, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};

CRGBPalette16 palette;

class Heart : public Leds {
  public:
    void begin(CRGB* leds) {
      Leds::begin(leds);

      fill_solid(palette, 16, CRGB::Red);
      palette[0] = CRGB::Pink;
      palette[4] = CRGB::Orange;
      palette[8] = CRGB::Magenta;
      palette[12] = CRGB::Yellow;    
    }
    void loop() {
      double time = millis();
      int index = int(time/500) % 256;
      CRGB color = ColorFromPalette(palette, index);
      for (int i=0; i<NUM_LEDS; i++) {
        leds[i] = (MASK[i] ? color : CRGB::Black);
      }
      FastLED.show();
      FastLED.delay(30);
    }
};
