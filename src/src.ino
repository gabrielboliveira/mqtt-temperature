#include <ESP8266WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>
#include <DHT.h>
#include "config.h"

#define LED_BUILTIN 2

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

void setup () {
#if DEBUG_ENABLED
  Serial.begin(115200);
#endif

  setup_wifi();
  client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);

  // Start sensor
  dht.begin();

#if FLASH_BUILTIN_LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
#endif
}

void setup_wifi () {
  delay(10);

#if DEBUG_ENABLED
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
#endif

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

#if DEBUG_ENABLED
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
#endif
}

void reconnect () {
  // Loop until we're reconnected
  while (!client.connected()) {
#if DEBUG_ENABLED
    Serial.print("Attempting MQTT connection...");
#endif
    
    // Attempt to connect
    if (! client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
#if DEBUG_ENABLED
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
#endif
      // Wait 5 seconds before retrying
      delay(5000);
    } else {
#if DEBUG_ENABLED
      Serial.println("connected");
#endif
    }
  }
}

bool checkBound (float newValue, float prevValue, float maxDiff) {
  return !isnan(newValue) &&
         (newValue < prevValue - maxDiff || newValue > prevValue + maxDiff);
}

long lastReading = 0;

void loop () {
  if (!client.connected()) {
    reconnect();
  }
  
  client.loop();

  long now = millis();

  // Every READING_DELAY gets a new reading
  if (now - lastReading > READING_DELAY) {
    lastReading = now;

    checkAndPublish();
  }
}

void checkAndPublish () {
#if FLASH_BUILTIN_LED
  digitalWrite(LED_BUILTIN, LOW);
#endif
  
  float newTemp = dht.readTemperature();
  float newHum = dht.readHumidity();
 
  if (! isnan(newTemp)) {
#if DEBUG_ENABLED
    Serial.print("New temperature: ");
    Serial.println(String(newTemp, 2).c_str());
#endif

    client.publish(MQTT_TEMPERATURE_TOPIC, String(newTemp, 2).c_str(), true);
  }
  
  if (! isnan(newHum)) {
#if DEBUG_ENABLED
    Serial.print("New humidity: ");
    Serial.println(String(newHum, 2).c_str());
#endif

    client.publish(MQTT_HUMIDITY_TOPIC, String(newHum, 2).c_str(), true);
  } 

#if FLASH_BUILTIN_LED
  digitalWrite(LED_BUILTIN, HIGH);
#endif
}


