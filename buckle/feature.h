#ifndef FEATURE_H
#define FEATURE_H

#include <ESP8266WebServer.h>

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

#endif
