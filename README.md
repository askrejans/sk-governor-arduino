# sk-governor-arduino

Firmware for Arduino / ESP-01 side for various sensors.

## Implemented fw:

- DHT-11 HTTP JSON response based temperature/humidity sensor. To be deployed on ESP-01.

## Install

### DHT-11
- Add your ip/port/ssid and pwd data. 
- Compile and flash to ESP-01 or compatable Arduino (some modifications will be needed). 
- Once up and running, ip can be cofigured for sk-governor-base and used with the corresponding drivers for temperature and humidity data.

### Requirements

- [ESP8266WiFi](https://github.com/esp8266/Arduino)
- [DHT](https://github.com/adafruit/DHT-sensor-library)

#### Implemented endpoint examples

- /  `{
sensor: "ESP-01 - DHT11 - 1",
temperature: 24,
humidity: 47
}` 
- /temperature  `{
temperature: 24
}`
- /humidity  `{
humidity: 50
}`
