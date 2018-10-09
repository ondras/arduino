#include "feature.h"
#include "leds.h"
#include <FastLED.h>
#include <FS.h>

class Image : public Leds {
  public:
    void setup() override {
      clear();
      bool ok = load_file("/flag.dat");
      Serial.println(String("LOAD FILE ") + ok);
      FastLED.show();
    }
};
