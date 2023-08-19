#include <ArduinoJson.h>

StaticJsonDocument<500> doc;
int a = 0;

void setup() {
  Serial.begin(9600);
  doc["marks"] = a;
  doc["name"] = "Nodemcu";

}

void loop() {

  
  serializeJson(doc, Serial);
  Serial.println();
  a = a + 1;
  doc["marks"] = a;
  delay(1000);
}
