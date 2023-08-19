#include <DHT.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define DHT_PIN D4       // Define the digital pin connected to the DHT sensor (GPIO 4)
#define DHT_TYPE DHT11  // Define the type of sensor (DHT11 or DHT22)
#define PIR_PIN D3      // Define the digital pin connected to the PIR sensor (GPIO 3)
#define RELAY_PIN D1    // Define the digital pin connected to the relay (GPIO 5)

StaticJsonDocument<500> doc;
DHT dht(DHT_PIN, DHT_TYPE);
AsyncWebServer server(80);

bool motionDetected = false;
unsigned long relayStartTime = 0;
const unsigned long relayDuration = 5000; // 5 seconds

void setup() {
  Serial.begin(9600); // Initialize serial communication
  dht.begin();        // Initialize the DHT sensor
  pinMode(PIR_PIN, INPUT);    // Set PIR pin as input
  pinMode(RELAY_PIN, OUTPUT); // Set relay pin as output

  // Connect to Wi-Fi network
  WiFi.begin("Server", "Allow Me");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  // Print IP address
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Route to handle HTTP requests
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><body>";
    html += "<h2>Temperature: " + String(dht.readTemperature()) + " °C</h2>";
    html += "<h2>Humidity: " + String(dht.readHumidity()) + " %</h2>";
    html += "<h2>Motion Detected: " + String(motionDetected ? "Yes" : "No") + "</h2>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  // Start the HTTP server
  server.begin();
}

void loop() {
  float temperature = dht.readTemperature(); // Read temperature in Celsius
  float humidity = dht.readHumidity();       // Read humidity
  
  int motionState = digitalRead(PIR_PIN);  // Read PIR sensor state
  if (motionState == HIGH) {
    if (!motionDetected) {
      motionDetected = true;
      relayStartTime = millis();
      digitalWrite(RELAY_PIN, LOW); // Trigger the relay
    }
  } else {
    motionDetected = false;
    digitalWrite(RELAY_PIN, HIGH); // Turn off the relay
  }

  doc["Temperature"] = String(temperature) + " °C";
  doc["Humidity"] = String(humidity) + " %";
  doc["MotionDetected"] = motionDetected ? "Yes" : "No";

  Serial.println();
  serializeJson(doc, Serial);
  
  doc.clear(); // Clear the JSON object for the next reading
  
  if (motionDetected && (millis() - relayStartTime >= relayDuration)) {
    motionDetected = false;
    digitalWrite(RELAY_PIN, HIGH); // Turn off the relay
  }

  // delay(2000); // Wait for 2 seconds before the next reading
}
