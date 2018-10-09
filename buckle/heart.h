#include "feature.h"
#include "leds.h"
#include <FastLED.h>

const bool HEART_MASK[NUM_LEDS] = {
  0,1,1,0,0,1,1,0,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,0,0,0,0,0,
};

const int hue_min = 240;
const int hue_max = 5;

class Heart : public Leds {
  public:
    void loop() override {
      double time = millis();
      fract8 fraction = triwave8(time/30);
      int hue = map8(fraction, hue_min, hue_max);

      CRGB rgb = CHSV(hue, 255, 255);
      for (int i=0; i<NUM_LEDS; i++) {
        set_led(i, (HEART_MASK[i] ? rgb : CRGB::Black));
      }
      FastLED.show();
      FastLED.delay(20);
    }
};
