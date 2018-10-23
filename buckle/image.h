#include "feature.h"
#include "leds.h"
#include <FastLED.h>
#include <FS.h>

class Image : public Feature {
  public:
    void set_config(ESP8266WebServer& server) {
      String file = String("/") + server.arg("image") + String(".dat");
      clear();
      bool ok = load_file(file);
      FastLED.show();
    }
};
