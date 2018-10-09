#define PAINTBRUSH_FILE "/paintbrush.dat"

#include "feature.h"
#include "leds.h"
#include <FastLED.h>
#include <FS.h>

unsigned char EMPTY[] = { 0, 0, 0 };

class Paintbrush : public Leds {
  public:
    void begin(CRGB* leds) {
      Leds::begin(leds);

      if (!SPIFFS.exists(PAINTBRUSH_FILE)) {
        File file = SPIFFS.open(PAINTBRUSH_FILE, "w");
        for (int i=0; i<N*N; i++) {
          size_t written = file.write(EMPTY, sizeof(EMPTY));
        }
        file.close();
      }
    }

    void setup() override {
      load_file(PAINTBRUSH_FILE);
      FastLED.show();
    }

    void set_config(ESP8266WebServer& server) override {
      int offset = server.arg("offset").toInt();
      byte r = server.arg("r").toInt();
      byte g = server.arg("g").toInt();
      byte b = server.arg("b").toInt();

      File file = SPIFFS.open(PAINTBRUSH_FILE, "r+");
      file.seek(offset, SeekSet);
      file.write(r);
      file.write(g);
      file.write(b);
      file.close();
      
      set_led(offset/3, CRGB(r, g, b));
      FastLED.show();
    }
};
