#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHT_PIN 2   // пин к которому подключен dht
#define BUTTON_PIN 11   // пин к которму подключена сенснорная кнопка

// инициализируем классы для работы с библиотеками
DHT dht(DHT_PIN, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// инициализируем глобальные переменные:
bool buttonWasUp = true;    // была ли нажата кнопка
bool dispEnabled = false;   // активен ли дисплей
bool shownAlert = false;    // было ли показано уведомление
unsigned long timing;

void setup() {
  pinMode(BUTTON_PIN, INPUT);

  dht.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  bool buttonIsUp = !digitalRead(BUTTON_PIN);   // считываем сигнал с пина кнопки
  if (buttonWasUp && !buttonIsUp) {
    buttonIsUp = digitalRead(BUTTON_PIN);
    if (digitalRead(BUTTON_PIN)) {
      dispEnabled = !dispEnabled;   // если кнопка была нажата, меняем значение флага
      while (digitalRead(BUTTON_PIN)) {}
      dispWorking(dispEnabled);   // меняем состояние дисплея по нажатию на кнопку
    }
  }
  buttonWasUp = buttonIsUp;   // сохраняем в переменную текущее состояние кнопки

  if (millis() - timing > 2000) {
    // опрашиваем каждые 2 секунды dht. чаще нельзя
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    if (!(isnan(hum) || isnan(temp))) {
      if ((temp > 24.0 || hum < 40.0) && !shownAlert) {   // если некомфортные значения и уведомление еще не было показано...
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("OPEN THE WINDOW!");    // показываем уведомление
        shownAlert = true;  // меняем значение флага
      } else if (shownAlert) {
        printData(temp, hum);   // если уведомление уже было показано, а значения не комфортные, выводим их
        shownAlert = false;
      } else printData(temp, hum);    // если значения нормальные, выводим их
    } else printData(0.0, 0.0);   // если не удалось считать данные, выводим нули
    timing = millis();    // обновляем счетчик таймера
  }
}

int printData(float t, float h) {
  lcd.clear();

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
