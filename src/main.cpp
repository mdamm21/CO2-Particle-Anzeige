#include <Arduino.h>

int sensorWert = 0;

void setup() {
  Serial.begin(9600);
  pinMode (A0, INPUT);
  // digital pins für LCD Display
}

void loop() {
  sensorWert = analogRead(A0);
  Serial.println(sensorWert); // Grenzwert evtl 105ppm 
  delay(1000);
}