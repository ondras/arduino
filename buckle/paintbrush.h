#include "feature.h"
#include <FS.h>
#define PAINTBRUSH_FILE "/paintbrush.dat"
#define N 8

class Paintbrush : public Feature {
  public:
    Paintbrush() {
      if (!SPIFFS.exists(PAINTBRUSH_FILE)) {
        File file = SPIFFS.open(PAINTBRUSH_FILE, "w");
        for (int i=0; i<N*N; i++) {
          file.write('0');
        }
        file.close();
      }
    }
    void setup() {
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
    }
};
