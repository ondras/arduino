#include <FastLED.h>
#include <FS.h>
#include "feature.h"
#include "leds.h"
#include <game.h>
#include <pit.h>
#include <shapes.h>
#include <output.h>

CRGB COLORS[COLOR_COUNT+1] = {
  CRGB::Black,
  CRGB::Red,
  CRGB::Green,
  CRGB::Blue,
  CRGB::Yellow,
  CRGB::Cyan,
  CRGB::Magenta
};

class Tetris : public Leds, Output {
  public:
    Tetris() : game(Game(*this)) {}

    void setup() override {
      game.start();
    }

    void loop() override {
      game.step();
      if (game.playing) {
        delay(50);
      } else {
        delay(1000);
        game.start();
      }
    }

    void setPixel(byte x, byte y, byte color) {
      set_led(x + y*N, color);
    }
    
    void draw(Pit& pit, Piece& piece) {
      Output::draw(pit, piece);
      FastLED.show();
    }

  private:
    Game game;
};
