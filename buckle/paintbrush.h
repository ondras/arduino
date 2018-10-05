#define PAINTBRUSH_FILE "/paintbrush.dat"
#define N 8

#include "feature.h"
#include <FastLED.h>
#include <FS.h>

class Paintbrush : public Feature {
  public:
    Paintbrush(CRGB* leds) : leds(leds) {
      if (!SPIFFS.exists(PAINTBRUSH_FILE)) {
        File file = SPIFFS.open(PAINTBRUSH_FILE, "w");
        for (int i=0; i<N*N; i++) {
          file.write('0');
        }
        file.close();
      }
    }
    void setup() {
      File file = SPIFFS.open(PAINTBRUSH_FILE, "r");
      byte rgb[3];
      for (int i=0; i<N*N; i++) {
        file.read(rgb, sizeof(rgb));
        setLed(i, rgb[0], rgb[1], rgb[2]);
      }
      FastLED.show();
    }

    void config(ESP8266WebServer& server) {
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

      setLed(offset/3, r, g, b);
      FastLED.show();

    }

  private:
    CRGB *leds;
    void setLed(int index, byte r, byte g, byte b) {
      leds[index] = CRGB(r, g, b);
    }
};
