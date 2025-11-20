#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20,4);

int sensorWert = 0;
int grenzWert = 110;
int ppmWert = 0;

const int MIN_PPM = 400;
const int MAX_PPM = 2000;

unsigned long lastScreenUpdate = 0;
unsigned long lastScreenToggle = 0;
bool blinkState = false; 

void drawCenteredText(uint8_t row, const String &text){
  int len = text.length();
  int startCol = (20 - len) / 2;
  if (startCol < 0) startCol = 0;

  lcd.setCursor(0, row);
  lcd.print("                    "); // 20 x Leerzeichen

  lcd.setCursor(startCol, row);
  lcd.print(text);
}

void drawGauge(int ppm){
  int filledBars = map(ppm, MIN_PPM, MAX_PPM, 0, 20);
  if (filledBars < 0) filledBars = 0;
  if (filledBars > 20) filledBars = 20;

  lcd.setCursor(0,2);

  for (int i = 0; i < 20; i++){
    if (i < filledBars){
      bool isBlinkSegment = (ppm >= grenzWert) && (i >= filledBars - 2);
      if (isBlinkSegment && !blinkState) {
        lcd.print(" ");
      } else {
        lcd.write(byte(255)); // Vollblock
      }
    } else {
      lcd.print(" ");
    }
    
  }
  
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

  lcd.clear();
}

void loop() {
  unsigned long now = millis();

  if (now - lastScreenToggle >= 400) {
    blinkState = !blinkState;
    lastScreenToggle = now;
  }

  if (now - lastScreenUpdate >= 250) {
    lastScreenUpdate = now;

    sensorWert = analogRead(A0);

    ppmWert = map(sensorWert, 0, 1023, 400, 5000);

    // Debug auf Serial
    Serial.print("Raw: ");
    Serial.print(sensorWert);
    Serial.print("  ppm: ");
    Serial.println(ppmWert);

    // Zeile 0: Titel
    drawCenteredText(0, "CO2-Messung");

    // Zeile 1: ppm groß & mittig
    String ppmText = String(ppmWert) + " ppm";
    drawCenteredText(1, ppmText);

    // Zeile 2: Tacho/Balken
    drawGauge(ppmWert);

    // Zeile 3: Status
    lcd.setCursor(0, 3);
    lcd.print("                    "); // Zeile löschen

    lcd.setCursor(0, 3);
    if (sensorWert >= grenzWert) {
      lcd.print(" Status: Lueften!!!  ");
    } else {
      lcd.print("  Status: Alles OK   ");
    }
  }
}