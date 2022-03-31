#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHT_PIN 2
#define BUTTON_PIN 11

DHT dht(DHT_PIN, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool buttonWasUp = true;
bool dispEnabled = false;
unsigned long timing;

void setup() {
  pinMode(BUTTON_PIN, INPUT);

  dht.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  bool buttonIsUp = !digitalRead(BUTTON_PIN);
  if (buttonWasUp && !buttonIsUp) {
    buttonIsUp = digitalRead(BUTTON_PIN);
    if (digitalRead(BUTTON_PIN)) {
      dispEnabled = !dispEnabled;
      while (digitalRead(BUTTON_PIN)) {}
      dispWorking(dispEnabled);
    }
  }
  buttonWasUp = buttonIsUp;

  if (millis() - timing > 2000) {
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    if (isnan(hum) || isnan(temp)) printData(0.00, 0.00);
    else printData(temp, hum);
  }
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

void dispWorking(bool state) {
  if (state) {
    lcd.display();
    lcd.backlight();
  }
  else {
    lcd.noDisplay();
    lcd.noBacklight();
  }
}
