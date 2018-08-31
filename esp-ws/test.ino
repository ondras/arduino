
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
/*
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
*/
#define NUM_LEDS 64
#define DATA_PIN 13

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ400);


class CRGB {
	public :
		CRGB();
		static CRGB White;
		static CRGB Red;
		static CRGB Green;
		static CRGB Blue;
		static CRGB Black;
};
CRGB::CRGB() {}


ESP8266WebServer server(80);
CRGB leds[NUM_LEDS];
int count = 32;
CRGB color = CRGB::White;

void reply(String text) {
	Serial.println(text);
	server.send(200, "text/html", text);
}

void handleRoot() {
	String response = "";

	String i = server.arg("i");
	String b = server.arg("b");
	String c = server.arg("c");

	if (b != "") {
//		FastLED.setBrightness(b.toInt());
		response += "b set to " + b;
	} else {
		response += "b unchanged";
	}

	if (c == "") { c = String("x"); }

	if (i != "") { count = i.toInt(); }

	switch (c[0]) {
		case 'r':
			color = CRGB::Red;
			response += "c set to red";
		break;
		case 'g':
			color = CRGB::Green;
			response += "c set to green";
		break;
		case 'b':
			color = CRGB::Blue;
			response += "c set to blue";
		break;
		case 'w':
			color = CRGB::White;
			response += "c set to white";
		break;
		default:
			response += "c unchanged";
		break;
	}

	reply(response);
}


void setup() {
	delay(1000);
	Serial.begin(115200);
	Serial.println();

/*
	FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
	FastLED.setBrightness(32);
	Serial.println("LEDs added");
*/
	
	strip.begin();
	strip.setBrightness(8);

	Serial.print("Configuring access point...");
	WiFi.softAP("esp8266");

	server.on("/", handleRoot);
	server.begin();
	Serial.println("HTTP server started");
}

int idx=0;

void loop() {
	server.handleClient();
/*
	for (int i=0; i<NUM_LEDS; i++) {
		leds[i] = (i < count ? color : CRGB::Black);
	}
	FastLED.show();
*/
	for (int i=0; i<NUM_LEDS; i++) {
		if (i < 32) {
			strip.setPixelColor(i, 255, 255, 255);
		} else {
			strip.setPixelColor(i, 0, 0, 0);
		}
	}
	strip.show();
/*
	strip.setPixelColor(idx, 0, 255, 0);
	strip.setPixelColor((idx-1+NUM_LEDS) % NUM_LEDS, 0, 0, 0);
	idx = (idx+1) % NUM_LEDS;
	strip.show();
	delay(300);
*/
}
