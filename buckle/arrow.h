#include "feature.h"
#include "leds.h"
#include <FastLED.h>

const bool ARROW_MASK[NUM_LEDS] = {
  0,0,0,1,1,0,0,0,
  0,0,1,1,1,1,0,0,
  0,1,1,1,1,1,1,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
};

class Arrow : public Leds {
  public:
    void setup() override {
      clear();
      FastLED.show();
    }

    void set_config(ESP8266WebServer& server) override {
      orientation = server.arg("orientation").toInt();
      byte r = server.arg("r").toInt();
      byte g = server.arg("g").toInt();
      byte b = server.arg("b").toInt();
      CRGB rgb(r, g, b);
      for (int i=0; i<NUM_LEDS; i++) {
        set_led(i, (ARROW_MASK[i] ? rgb : CRGB::Black));
      }
      FastLED.show();
    }
};
