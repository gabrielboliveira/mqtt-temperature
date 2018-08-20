#define DEBUG_ENABLED true
#define FLASH_BUILTIN_LED true
#define READING_DELAY 10000 // reading delay in milliseconds

// Wifi: SSID and password
const PROGMEM char* WIFI_SSID = "Wifi-SSID";
const PROGMEM char* WIFI_PASSWORD = "wifi-password";

// MQTT: ID, server IP, port, username and password
#define MQTT_VERSION MQTT_VERSION_3_1_1
const PROGMEM char* MQTT_CLIENT_ID = "esp-dht-22";
const PROGMEM char* MQTT_SERVER_IP = "mqtt-server";
const PROGMEM uint16_t MQTT_SERVER_PORT = 1883;
const PROGMEM char* MQTT_USER = "mqtt-user";
const PROGMEM char* MQTT_PASSWORD = "mqtt-password";
const PROGMEM char* MQTT_HUMIDITY_TOPIC = "sensor/temperature";
const PROGMEM char* MQTT_TEMPERATURE_TOPIC = "sensor/humidity";

// DHT sensor
#define DHTPIN 14       // which digital pin we're connected to
#define DHTTYPE DHT22   // DHT22 or DHT11
