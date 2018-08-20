# mqtt-temperature

A simple temperature and humidity sensor publishing messages to a MQTT server. Can be used with ESP12 and DHT sensors.

## Usage

Copy `src/config_sample.h` to `src/config.h` and change your WiFi, MQTT and other configurations. Plug a DHT11 or DHT22 sensor to any digital GPIO port, compile and deploy to the ESP.

Configure your MQTT client to listen to the topic. Example [Home Assistant](https://www.home-assistant.io) configuration:

```yaml
sensor temperature:
  platform: mqtt
  name: "Temperature"
  state_topic: "sensor/temperature"
  qos: 0
  unit_of_measurement: "ºC"

sensor humidity:
  platform: mqtt
  name: "Humidity"
  state_topic: "sensor/humidity"
  qos: 0
  unit_of_measurement: "%"
```

## License

MIT