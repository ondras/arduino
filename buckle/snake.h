#include "feature.h"
#include "leds.h"
#include <FastLED.h>

byte indexToX(byte index) { return index % N; }
byte indexToY(byte index) { return index / N; }
byte xyToIndex(byte x, byte y) { return x + N*y; }

byte distance(byte index1, byte index2) {
  byte x1 = indexToX(index1);
  byte x2 = indexToX(index2);
  byte y1 = indexToY(index1);
  byte y2 = indexToY(index2);

  byte dx = abs(x1-x2);
  byte dy = abs(y1-y2);
  return dx+dy;
}

class Snake : public Feature {
  public:
    void setup() override {
      start();
    }

    void loop() override {
      orientation = compute_orientation();
      
      int new_head = step(state, head, orientation);
      if (new_head == -1) {
        delay(1000);
        start();
        draw();
      } else {
        head = new_head;
        if (head == target) { target = next_target(); }
        draw();
        delay(200);
      }
    }

  private:
    byte state[N*N];
    byte head;
    byte orientation;
    byte target;

    void start() {
      for (byte i=0; i<N*N; i++) { state[i] = 0; }
      head = 0;
      orientation = 1;
      state[head] = 1;
      target = next_target();
    }

    byte next_target() {
      byte available_count = 0;
      byte available[N*N];

      for (byte i=0; i<N*N; i++) {
        if (state[i] != 0) { continue; }
        available[available_count] = i;
        available_count++;
      }

      byte index = random(available_count);
      return available[index];
    }

    byte compute_orientation() {
      byte candidates[3] = {
        orientation,
        (orientation + 4 - 1)%4, // left
        (orientation + 4 + 1)%4  // right
      };

      int best_score = -999;
      byte best_orientation = orientation;

      for (int i=0; i<3; i++) {
        int s = score(candidates[i]);
        if (s > best_score) {
          best_score = s;
          best_orientation = candidates[i];
        }
      }
      return best_orientation;
    }

    int step(byte * state, byte head, byte orientation) {
      byte length = state[head];
      
      int new_head = move_head(head, orientation);
      if (new_head == -1) { return -1; }
      
      if (new_head == target) {
        length++;
      } else {
        for (int i=0; i<N*N; i++) {
          byte value = state[i];
          if (value == 0) { continue; }
          state[i] = value-1;
        }
        if (state[new_head] > 0) { return -1; }
      }
      
      state[new_head] = length;
      return new_head;
    }

    int move_head(byte index, byte orientation) {
      byte x = indexToX(index);
      byte y = indexToY(index);
      
      switch (orientation) {
        case 0: if (y == 0) return -1; y--; break;
        case 1: if (x == N-1) return -1; x++; break;
        case 2: if (y == N-1) return -1; y++; break;
        case 3: if (x == 0) return -1; x--; break;
      }
      
      x = (x+N)%N;
      y = (y+N)%N;
      
      return xyToIndex(x, y);
    }

    void draw() {
      for (byte i=0; i<N*N; i++) {
        set_led(i, color(i));
      }
      FastLED.show();
    }

    CRGB color(byte i) {
      if (i == target) { return CRGB::Red; }
      if (i == head) { return CRGB::Yellow; }
      if (state[i] == 0) { return CRGB::Black; }
      
      float max = state[head]-1;
      float green = (float)state[i] / max;
      return CRGB(0, 255*green, 0);
    }

    int score(byte orientation) {
      byte tmp_state[N*N];
      for (byte i=0; i<N*N; i++) { tmp_state[i] = state[i]; }

      int new_head = step(tmp_state, head, orientation);
      if (new_head == -1) { return -999; }

      return -distance(new_head, target);
    }
};
