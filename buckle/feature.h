#ifndef FEATURE_H
#define FEATURE_H

#include <ESP8266WebServer.h>
#include <FastLED.h>
#include "leds.h"

class Feature {
  public:
    virtual void setup() {}
    virtual void get_config(ESP8266WebServer& server) {}
    virtual void set_config(ESP8266WebServer& server) {}
    virtual void loop() {}
};

class Blinker : public Feature {
  public:
    Blinker() {
      pin = 2;  
      state = true;
    }
    void setup() {
      DEBUG_MSG("blinker here");
      pinMode(pin, OUTPUT);
    }

    void loop() {
      state = !state;
      digitalWrite(pin, state);
      delay(100);
    }

  private:
    int pin;
    bool state;
};

class Leds : public Feature {
  public:
    virtual void begin(CRGB* leds) {
      this->leds = leds;
    }

    virtual void get_config(ESP8266WebServer& server) {
      char bytes[NUM_LEDS * 3];
      for (int i=0; i<NUM_LEDS; i++) {
        bytes[3*i+0] = leds[i].r;
        bytes[3*i+1] = leds[i].g;
        bytes[3*i+2] = leds[i].b;
      }

      int content_length = sizeof(bytes);
      server.setContentLength(content_length);
      server.send(200, "application/octet-stream", "");
      server.client().write((const char *) bytes, content_length);
    }

  protected:
    CRGB *leds;

    void clear() {
      for (int i=0; i<NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
      }
    }
};

#endif
