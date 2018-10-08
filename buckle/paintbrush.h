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

    void setup() {
      File file = SPIFFS.open(PAINTBRUSH_FILE, "r");
      byte rgb[3];
      for (int i=0; i<N*N; i++) {
        file.read(rgb, sizeof(rgb));
        leds[i].setRGB(rgb[0], rgb[1], rgb[2]);
      }
      FastLED.show();
    }

    void set_config(ESP8266WebServer& server) {
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
      
      leds[offset/3].setRGB(r, g, b);
      FastLED.show();
    }
};
