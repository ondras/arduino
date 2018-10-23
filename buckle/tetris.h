#include <FastLED.h>
#include <FS.h>
#include <tetris.h>
#include "feature.h"
#include "leds.h"

CRGB COLORS[COLOR_COUNT+1] = {
  CRGB::Black,
  CRGB::Red,
  CRGB::Green,
  CRGB::Blue,
  CRGB::Yellow,
  CRGB::Cyan,
  CRGB::Magenta
};

class Tetris : public Feature, Output {
  public:
    Tetris() : game(Game(*this)) {}

    void setup() override {
      game.start();
    }

    void loop() override {
      game.step();
      if (game.playing) {
        delay(delay_ms);
      } else {
        delay(1000);
        game.start();
      }
    }

    void set_config(ESP8266WebServer& server) {
      delay_ms = server.arg("delay").toInt();
    }

    void get_config(ESP8266WebServer& server) {
      server.send(200, "text/plain", String(delay_ms));
    }

    void setPixel(byte x, byte y, byte color) {
      set_led(x + y*N, COLORS[color]);
    }
    
    void draw(Pit& pit, Piece& piece) {
      Output::draw(pit, piece);
      FastLED.show();
    }

  private:
    Game game;
    int delay_ms = 80;
};
