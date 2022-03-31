#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHT_PIN 2
#define BUTTON_PIN 11
#define LED_PIN 13
 
bool buttonWasUp = true;
bool dispEnabled = false;

DHT dht(DHT_PIN, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  
  dht.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  boolean buttonIsUp = !digitalRead(BUTTON_PIN);
    if (buttonWasUp && !buttonIsUp) {  
      delay(10);
      buttonIsUp = digitalRead(BUTTON_PIN);
    if (!buttonIsUp) {
      dispEnabled = !dispEnabled;
      digitalWrite(LED_PIN, dispEnabled);
    }
  }
  buttonWasUp = buttonIsUp;

  if (isnan(hum) || isnan(temp)) {
    printData(0.00, 0.00);
  } else {
    printData(temp, hum);
  }
  
  delay(2000);
}

int printData(float t, float h) {
  lcd.setCursor(2, 0);
  lcd.print("Temp: ");
  lcd.setCursor(10, 0);
  lcd.print(t);
  lcd.setCursor(15, 0);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.setCursor(10, 1);
  lcd.print(h);
  lcd.setCursor(15, 1);
  lcd.print("%");
}
