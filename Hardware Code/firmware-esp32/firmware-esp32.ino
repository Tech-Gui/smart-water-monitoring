#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Isaiah";
const char* password = "Tadiwa@20";
const int waterSensorPin = 36;

String serverUrl = "https://one-more-thing-2-0b78fb9fe4b4.herokuapp.com/temperature";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");

   // Set the water sensor pin as an input
  pinMode(waterSensorPin, INPUT);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Specify the URL and method (POST)
    http.begin(serverUrl);

    // Set the Content-Type header to indicate JSON data
    http.addHeader("Content-Type", "application/json");


      // Read the water sensor value
  int waterLevel = analogRead(waterSensorPin);

  // Map the analog reading to a range (you can adjust these values)
  int mappedLevel = map(waterLevel, 0, 4095, 0, 100);

    // Create a JSON object for your data

    String postData = "{\"value\": " + String(mappedLevel) + "}";

    // Send the POST request
    int httpCode = http.POST(postData);

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("HTTP Response: " + payload);
    } else {
      Serial.println("HTTP Error: " + httpCode);
    }

    http.end();
  }

  delay(2000); // Wait for a while before sending the next request
}
