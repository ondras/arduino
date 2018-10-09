#ifndef LEDS_H
#define LEDS_H

#define LED_PIN 0 // corresponds to Wemos pin D3
#define NUM_LEDS 64
#define N 8
#define BRIGHTNESS 60

int fix_index(int index, byte orientation) {
  byte x1 = index % N;
  byte y1 = index / N;
  byte x2, y2;

  switch (orientation % 4) {
    case 1: // cw
      x2 = N-y1-1;
      y2 = x1;
    break;

    case 2:
      x2 = N-x1-1;
      y2 = N-y1-1;
    break;

    case 3: // ccw
      x2 = y1;
      y2 = N-x1-1;
    break;

    default:
      x2 = x1;
      y2 = y1;
    break;
  }

  return x2 + y2*N;
}

#endif
