#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHT_PIN 2
#define BUTTON_PIN 9
#define LED_PIN 13

DHT dht(DHT_PIN, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

boolean buttonWasUp = true;
boolean ledEnabled = false;
unsigned long timing;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  dht.begin();
  lcd.init();
  lcd.backlight();
}
int i = 0;
void loop() {
  Serial.println(i++);


  boolean buttonIsUp = !digitalRead(BUTTON_PIN);
  if (buttonWasUp && !buttonIsUp) {
    buttonIsUp = digitalRead(BUTTON_PIN);
    if (digitalRead(BUTTON_PIN)) {
      ledEnabled = !ledEnabled;
      while (digitalRead(BUTTON_PIN)) {}
      digitalWrite(13, ledEnabled);
    }
  }
  buttonWasUp = buttonIsUp;


  if (millis() - timing > 2000) {
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    if (isnan(hum) || isnan(temp)) {
      printData(0.00, 0.00);
    } else {
      printData(temp, hum);
    }
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