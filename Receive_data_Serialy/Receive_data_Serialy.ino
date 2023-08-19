#include <ArduinoJson.h>

StaticJsonDocument<500> doc;
int a = 0;

void setup() {
  Serial.begin(9600);
  //  doc["count"] = a;
  //  doc["name"] = "Arduino json";



}

void loop() {

  if (Serial.available()) {
    deserializeJson(doc, Serial);
    int marks = doc["marks"];
    Serial.println(marks);
  }

  //  a = a + 1;
  //  doc["marks"] = a;
  //  delay(1000);
}
