#define DEBUG_MSG Serial.println
#define FEATURE_COUNT 7
#define FASTLED_ALLOW_INTERRUPTS 0

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <FastLED.h>
#include "leds.h"
#include "feature.h"
#include "paintbrush.h"
#include "heart.h"
#include "image.h"
#include "arrow.h"
#include "tetris.h"

CRGB leds[NUM_LEDS];
ESP8266WebServer server(80);

Feature * current_feature;
String current_feature_name;

Blinker blinker;
Feature noop;
Paintbrush paintbrush;
Heart heart;
Image image;
Arrow arrow;
Tetris tetris;

Feature * FEATURES[FEATURE_COUNT] = { &noop, &blinker, &paintbrush, &heart, &image, &arrow, &tetris };
String NAMES[FEATURE_COUNT] = { "noop", "blinker", "paintbrush", "heart", "image", "arrow", "tetris" };

void setup() {
  Serial.begin(115200);
  bool result = WiFi.softAP("esp-ap");
  DEBUG_MSG(String("AP ") + result);

  result = SPIFFS.begin();
  DEBUG_MSG(String("SPIFFS ") + result);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  DEBUG_MSG(String("Brightness ") + BRIGHTNESS);

  paintbrush.begin(leds);
  heart.begin(leds);
  image.begin(leds);
  arrow.begin(leds);
  tetris.begin(leds);

  server.serveStatic("/", SPIFFS, "/index.html");
  server.serveStatic("/index.css", SPIFFS, "/index.css");
  server.serveStatic("/index.js", SPIFFS, "/index.js");
  server.on("/feature", HTTP_GET, onGetFeature);
  server.on("/feature", HTTP_POST, onPostFeature);
  server.on("/config", HTTP_GET, onGetConfig);
  server.on("/config", HTTP_POST, onPostConfig);
  server.begin();

  set_feature(String("noop"));
}

void set_feature(const String& feature) {
  int index = -1;
  for (int i=0; i<FEATURE_COUNT; i++) {
    if (NAMES[i] == feature) { index = i; }  
  }
  if (index == -1) { index = 0; }

  current_feature_name = NAMES[index];
  current_feature = FEATURES[index];
  current_feature->setup();
  server.send(200, "text/plain", "Oll Korrect");
}

void onGetFeature() {
  server.send(200, "text/plain", current_feature_name);
}

void onPostFeature() {
  set_feature(server.arg("feature"));
}

void onGetConfig() {
  if (current_feature) { 
    current_feature->get_config(server);
  } else {
    server.send(404, "text/plain", "No feature");
  }
}

void onPostConfig() {
  if (current_feature) { 
    current_feature->set_config(server);
    server.send(200, "text/plain", "Oll Korrect");
  } else {
    server.send(404, "text/plain", "No feature");
  }
}

void loop() {
  server.handleClient();
  if (current_feature) { current_feature->loop(); }
}
