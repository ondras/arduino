#define DEBUG_MSG Serial.println
#define FEATURE_COUNT 2

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include "feature.h"

ESP8266WebServer server(80);
Feature * current_feature;

Blinker blinker;
Feature noop;

Feature * FEATURES[FEATURE_COUNT] = { &noop, &blinker };
String NAMES[FEATURE_COUNT] = { "noop", "blinker" };

void setup() {
  Serial.begin(115200);
  boolean result = WiFi.softAP("esp-ap");
  DEBUG_MSG(String("AP ") + result);
  result = SPIFFS.begin();
  DEBUG_MSG(String("SPIFFS ") + result);

  server.serveStatic("/", SPIFFS, "/index.html");
  server.on("/feature", HTTP_POST, onFeature);
  server.on("/config", HTTP_POST, onConfig);
  server.begin();

//  setFeature(String("blinker"));
}

void setFeature(const String& feature) {
  int index = -1;
  for (int i=0; i<FEATURE_COUNT; i++) {
    if (NAMES[i] == feature) { index = i; }  
  }
  if (index == -1) { index = 0; }

  current_feature = FEATURES[index];
  current_feature->setup();
  server.send(200, "text/plain", "Oll Korrect");
}

void onFeature() {
  String feature = server.arg("feature");
  DEBUG_MSG("onFeature " + feature);
  setFeature(feature);
}

void onConfig() {
  DEBUG_MSG("onConfig");
  if (current_feature) { 
    current_feature->config(server);
    server.send(200, "text/plain", "Oll Korrect");
  } else {
    server.send(404, "text/plain", "No feature");
  }
}

void loop() {
  server.handleClient();
  if (current_feature) { current_feature->loop(); }
}
