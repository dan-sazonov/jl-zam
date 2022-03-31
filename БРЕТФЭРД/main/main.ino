#include <Adafruit_Sensor.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <DHT.h>
#include <DHT_U.h>

#define DHT_PIN 2 

DHT dht(DHT_PIN, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();  
  lcd.backlight();
  dht.begin();
}

void loop() {
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  
  if !(isnan(hum) || isnan(dht)) {
    printData(temp, hum);
  }
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
