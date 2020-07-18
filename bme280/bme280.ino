#include "config.h"

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS 10

#define MQTT_DEBUG
#define MQTT_ERROR

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883

Adafruit_BME280 bme; // I2C
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_FEED_TEMPERATURE);
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_FEED_HUMIDITY);


// connect to adafruit io via MQTT
void connect() {
  Serial.print(F("WiFi: Connecting to "));
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi: connected"));
  Serial.println(F("WiFi IP address: "));
  Serial.println(WiFi.localIP());

  Serial.print(F("MQTT: Connecting to Adafruit IO... "));
  int8_t ret;
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    if (ret >= 0) mqtt.disconnect();
    Serial.println();
    Serial.println(F("MQTT: Retrying connection..."));
    delay(5000);
  }

  Serial.println();
  Serial.println(F("MQTT: Adafruit IO Connected!"));
}

void setup() {
  Serial.begin(9600);
  Serial.println(F("Initializing"));

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                  Adafruit_BME280::SAMPLING_X1, // temperature
                  Adafruit_BME280::SAMPLING_X1, // pressure
                  Adafruit_BME280::SAMPLING_X1, // humidity
                  Adafruit_BME280::FILTER_OFF   );


  delay(100);
  connect();
}

void loop() {
  if (!mqtt.ping(3)) {
    if (!mqtt.connected()) { connect(); }
  }

  bme.takeForcedMeasurement();
  float temp = bme.readTemperature();
  Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.println(" *C");
  temperature.publish(temp);

  float hum = bme.readHumidity();
  Serial.print("Humidity = ");
  Serial.print(hum);
  Serial.println(" %");
  humidity.publish(hum);


  /*
      Serial.print("Pressure = ");
      Serial.print(bme.readPressure());
      Serial.println(" Pa");

      Serial.print("Approx altitude = ");
      Serial.print(bme.readAltitude(1013.25)); // this should be adjusted to your local forcase
      Serial.println(" m");

      Serial.println();
  */
  delay(DELAY);
}
