#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int sensorWert = 0;

LiquidCrystal_I2C lcd(0x27, 20,4);

void setup() {
  // Gassensor
  Serial.begin(9600);
  pinMode (A0, INPUT);
  
  // LCD
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("C02 Partikel Anzeige");
  lcd.setCursor(0,1);
  lcd.print("starte Sensor...");
  delay(2000);
}

void loop() {
  sensorWert = analogRead(A0);
  
  //LCD
  lcd.setCursor(0,1);
  lcd.print("Raw: ");
  lcd.print(sensorWert * 4);
  lcd.print(" ");

  lcd.setCursor(0,2);
  if (sensorWert >= 90){
    lcd.print("Status: Lüften!!!");
  }else{
    lcd.print("Status: Alles Ok");
  }
  // Grenzwert 90ppm 
  delay(1000);
}
