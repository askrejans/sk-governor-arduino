#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "DHT.h"

IPAddress ip(192, 168, 1, 2);
IPAddress gateway(192, 168, 8, 1);
IPAddress subnet(255, 255, 255, 0);

const char* ssid = "ssid";
const char* password = "passsword";

#define DHTPIN 2
#define DHTTYPE DHT11

ESP8266WebServer server(80);

const int led = 13;

void handleRoot() {
  digitalWrite(led, 1);
  DHT dht(DHTPIN, DHTTYPE);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  server.send(200, "text/plain", "{\"sensor\": \"ESP-01 - DHT11 - 1\", \"temperature\": " + String(t) + ", \"humidity\": " + String(h) + "}");
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/temperature", []() {
    DHT dht(DHTPIN, DHTTYPE);
    int t = dht.readTemperature();
    server.send(200, "text/plain", "{\"temperature\":" + String(t) + "}");
  });

  server.on("/humidity", []() {
    DHT dht(DHTPIN, DHTTYPE);
    int h = dht.readHumidity();
    server.send(200, "text/plain", "{\"humidity\":" + String(h) + "}");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
