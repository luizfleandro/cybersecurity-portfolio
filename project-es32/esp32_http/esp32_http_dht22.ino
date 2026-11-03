#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// Wi-Fi credentials (replace with your own network)
const char* WIFI_SSID  = "YOUR_WIFI_SSID";
const char* WIFI_PASS  = "YOUR_WIFI_PASSWORD";

// Server endpoint (replace with your computer's local IP address)
const char* SERVER_URL = "http://YOUR_SERVER_IP:8080/temperatura";

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! ESP32 IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from sensor");
  } else {
    HTTPClient http;
    http.begin(SERVER_URL);
    http.addHeader("Content-Type", "text/plain");
    int responseCode = http.POST(String(t));
    Serial.printf("temp=%.1f humidity=%.1f response=%d\n", t, h, responseCode);
    http.end();
  }

  delay(5000);
}