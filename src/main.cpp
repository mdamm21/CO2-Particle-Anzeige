#include <Arduino.h>

// put function declarations here:
int sensorWert = 0;

void setup() {
  pinMode (A0, INPUT);
}

void loop() {
  sensorWert = analogRead(A0);
  Serial.println(sensorWert); // dann hier display code
  delay(100);
}