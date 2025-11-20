#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20,4);

int sensorWert = 0;
int grenzWert = 420;
int ppmWert = 0;

const int MIN_PPM = 400;
const int MAX_PPM = 2000;

unsigned long lastScreenUpdate = 0;
unsigned long lastScreenToggle = 0;
bool blinkstate = false; 

void drawCenteredText(uint8_t row, const String &text){
  int len = text.length();
  int startCol = (20 - len) / 2;
  if (startCol < 0) startCol = 0;

  lcd.setCursor(0, row);
  lcd.print("                    "); // 20 x Leerzeichen

  lcd.setCursor(startCol, row);
  lcd.print(text);
}



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
  lcd.print(ppmWert);
  lcd.print(" ");

  lcd.setCursor(0,2);

  if (sensorWert >= grenzWert){
    lcd.print("Status: Lüften!!!");
  }else{
    lcd.print("Status: Alles Ok");
  }
  
  delay(1000);
}
