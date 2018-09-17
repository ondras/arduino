#include "game.h"
#include "output-ledlcd.h"

#define RIGHT  0
#define UP     1
#define DOWN   2
#define LEFT   3
#define SELECT 4
#define NONE   5

/* 
 * Pin 12 is connected to the DATA IN-pin of the first MAX7221
 * Pin 11 is connected to the CLK-pin of the first MAX7221
 * Pin 3 is connected to the LOAD(/CS)-pin of the first MAX7221 	
 * There will only be a single MAX7221 attached to the arduino 
 */
LedControl lc(12, 11, 3, 1); 
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

OutputLEDLCD output(&lc, &lcd);
Game game(&output);

// read the buttons
int read_LCD_button() {
 int adc_key_in = analogRead(0);      // read the value from the sensor 
// Serial.println(adc_key_in);
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return NONE; // We make this the 1st option for speed reasons since it will be the most likely result
 if (adc_key_in < 50)   return RIGHT;  
 if (adc_key_in < 250)  return UP; 
 if (adc_key_in < 450)  return DOWN; 
 if (adc_key_in < 650)  return LEFT; 
 if (adc_key_in < 850)  return SELECT;  
 return NONE;  // when all others fail, return this...
}

int ms = 50;
int last_button = NONE;

void setup() {
//  Serial.begin(9600);
	randomSeed(analogRead(A0) * analogRead(A1) * analogRead(A2));
	random(100);

	game.start();
}

void loop() {
  int button = read_LCD_button();
  if (button != last_button) {
    last_button = button;
    if (button == DOWN && ms > 0) { ms -= 10; }
    if (button == UP && ms < 100) { ms += 10; }
  }

	game.step();

	if (game.playing) {
		delay(ms);
	} else {
		delay(1000);
		game.start();
	}
}
