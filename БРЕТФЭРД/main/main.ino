#include <LiquidCrystal_I2C.h>
#include <Wire.h> 

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();  
  lcd.backlight();

}

void loop() {
  printData(12.34, 42.13);
}

int printData(float t, float h) {
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.setCursor(10,0);
  lcd.print(t);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.setCursor(10,1);
  lcd.print(h);
  lcd.print("%");
}
