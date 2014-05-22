#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int value;
int x = 0;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.setCursor(x, 0);
}


void loop() {

  int avail = Serial.available();
  if (!avail) { return; }

//  lcd.clear();

  while (avail--) {
    value = Serial.read();
    lcd.print(value);
    x += 4;
    lcd.setCursor(x, 0);
  }

  delay(200);
}

