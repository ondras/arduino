#include <FastLED.h>
#include "feature.h"
#include "leds.h"

class Brightness : public Feature {
  public:
    void set_config(ESP8266WebServer& server) {
      int b = server.arg("brightness").toInt();
      FastLED.setBrightness(b);
      FastLED.show();
    }

    void get_config(ESP8266WebServer& server) {
      int b = FastLED.getBrightness();
      server.send(200, "text/plain", String(b));
    }
};
