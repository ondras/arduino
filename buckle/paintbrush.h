#define PAINTBRUSH_FILE "/paintbrush.dat"
#define N 8

#include "feature.h"
#include <FastLED.h>
#include <FS.h>

unsigned char EMPTY[] = { 0, 0, 0 };

class Paintbrush : public Feature {
  public:
    void begin(CRGB* leds) {
      this->leds = leds;
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
        setLed(i, rgb[0], rgb[1], rgb[2]);
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

      setLed(offset/3, r, g, b);
      FastLED.show();
    }

    void get_config(ESP8266WebServer& server) {
      File file = SPIFFS.open(PAINTBRUSH_FILE, "r");
      size_t sent = server.streamFile(file, "application/octet-stream");
      file.close();
    }

  private:
    CRGB *leds;
    void setLed(int index, byte r, byte g, byte b) {
      leds[index] = CRGB(r, g, b);
    }
};
