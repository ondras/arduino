#include <HID-Project.h>
#include <HID-Settings.h>
#include <TimerOne.h>

#define LEVEL_COUNT 4

//debounce milliseconds
const int debounce = 5;
//Switch Pins
const byte k[4] = { 7, 6, 5, 4 };
//Switch status
boolean s[4] = { 0, 0, 0, 0 };

const char GIT_PULL[] = "git pull";
const char GIT_PUSH[] = "git push";
const char GIT_COMMIT[] = "git commit -am \"\"";
const char GIT_RESET[] = "git reset --hard HEAD";

const KeyboardKeycode kcode[4] = { KEY_LEFT_ARROW,
                                   KEY_DOWN_ARROW,
                                   KEY_UP_ARROW,
                                   KEY_RIGHT_ARROW
                                 };

// pin[xx] on led matrix connected to nn on Arduino (-1 is dummy to make array start at pos 1)
int pins[6] = {
  -1, 18, 19, 20, 21
};

// col[xx] of leds = pin yy on led matrix
int cols[2] = {
  pins[2], pins[1]
};

// row[xx] of leds = pin yy on led matrix
int rows[2] = {
  pins[4], pins[3]
};

const byte led_levels[LEVEL_COUNT] = {0, 1, 5, 10};
byte led_level = LEVEL_COUNT-1;
const byte led_max = 10;
byte led_counter = 0;

void setup() {
  Keyboard.begin();
  setupLeds();
  for (int i = 0; i < 4; i++) {
    pinMode(k[i], INPUT);
    digitalWrite(k[i], 1);
  }
}

void loop() {
  CheckKeys();
  delay(debounce);
}

void pressed_primary(int i) {
  switch (i) {
    case 1:
      Keyboard.print(GIT_PULL);
      Keyboard.write(KEY_RETURN);
    break;
    case 2:
      Keyboard.print(GIT_PUSH);
      Keyboard.write(KEY_RETURN);
    break;
    case 3:
      Keyboard.print(GIT_COMMIT);
      Keyboard.write(KEY_LEFT_ARROW);
    break;
  }
}

void pressed_alt(int i) {
  switch (i) {
    case 1:
      led_level = max(led_level-1, 0);
    break;
    case 2:
      led_level = min(led_level+1, LEVEL_COUNT-1);
    break;
    case 3:
      Keyboard.print(GIT_RESET);
    break;
  }
}

void CheckKeys() {
  bool pressed;
  for (int i = 0; i < 4; i++) {
    pressed = !digitalRead(k[i]);
    if (pressed == s[i]) continue; // not changed
    s[i] = pressed;

    if (!pressed) continue; // only interested in pressed
    if (i == 0) continue; // first only changes state

    if (s[0]) {
      pressed_alt(i);
    } else {
      pressed_primary(i);
    }
  }
}

void setupLeds() {
  // sets the pins as output
  for (int i = 1; i <= 4; i++) {
    pinMode(pins[i], OUTPUT);
  }

  digitalWrite(cols[0], LOW);
  digitalWrite(cols[1], LOW);

  ledOff();
  
  // Set refresh rate (interrupt timeout period)
  Timer1.initialize(100);
  // Set interrupt routine to be called
  Timer1.attachInterrupt(display);
}

void ledOn() {
  digitalWrite(rows[0], HIGH);
  digitalWrite(rows[1], HIGH);
}

void ledOff() {
  digitalWrite(rows[0], LOW);
  digitalWrite(rows[1], LOW);
}

// Interrupt routine
void display() {
  led_counter = (led_counter+1) % led_max;
  if (led_counter < led_levels[led_level]) {
    ledOn();
  } else {
    ledOff();
  }
}
