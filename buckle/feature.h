#ifndef FEATURE_H
#define FEATURE_H

#include <ESP8266WebServer.h>
#include <FastLED.h>
#include <FS.h>
#include "leds.h"

class Feature {
  public:
    virtual void setup() {}
    virtual void loop() {}
    virtual void get_config(ESP8266WebServer& server) {}
    virtual void set_config(ESP8266WebServer& server) {}
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

    virtual void get_config(ESP8266WebServer& server) override {
      char bytes[NUM_LEDS * 3];
      Serial.println("get_config");
      for (int i=0; i<NUM_LEDS; i++) {
        CRGB rgb = get_led(i);
        Serial.println(rgb);
        bytes[3*i+0] = rgb.r;
        bytes[3*i+1] = rgb.g;
        bytes[3*i+2] = rgb.b;
      }

      int content_length = sizeof(bytes);
      server.setContentLength(content_length);
      server.send(200, "application/octet-stream", "");
      server.client().write((const char *) bytes, content_length);
    }

  protected:
    CRGB *leds;
    byte orientation = 0;

    void clear() {
      fill_solid(leds, NUM_LEDS, CRGB::Black);
    }

    void set_led(int i, CRGB rgb) {
      i = fix_index(i);
      leds[i] = rgb;
    }

    CRGB get_led(int i) {
      i = fix_index(i);
      return leds[i];
    }

    int fix_index(int i) {
      return ::fix_index(i, orientation);
    }

    bool load_file(String name) {
      if (!SPIFFS.exists(name)) { return false; }

      File file = SPIFFS.open(name, "r");
      byte rgb[3];
      for (int i=0; i<N*N; i++) {
        file.read(rgb, sizeof(rgb));
        set_led(i, CRGB(rgb[0], rgb[1], rgb[2]));
      }
      return true;
    }
};

#endif
