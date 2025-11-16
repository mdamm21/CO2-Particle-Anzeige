#include <Arduino.h>

int sensorWert = 0;

void setup() {
  pinMode (A0, INPUT);
  // digital pins für LCD Display
}

void loop() {
  sensorWert = analogRead(A0);
  Serial.println(sensorWert); // gerade noch wichtig um experimentell den eigentlichen grenzwert zu finden 
  delay(100);
  if (sensorWert >= 150){ // 150 ist erstmal willkürlich
    // display sag "Lüften"
  } else {
    // display chill 
  }
}