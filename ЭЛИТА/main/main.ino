#define IR_PIN 2    // пин датчика движения
#define BTN_PIN 11    // пин кнопки
#define LED_PIN 6   // пин светодиода
#define PHOTO_PIN A1    // пин фоторезистора
#define POT_PIN A0    // пин потенциометра

bool ledState = false;    // состояние светодиода (вкл/выкл)
bool lastPir = false;   // прошлое состояние датчика движения
bool flag = false;    // фалг кнопки с ее прошлым состоянием

void setup() {
  pinMode(IR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(PHOTO_PIN, INPUT);
  pinMode(POT_PIN, INPUT);
}

void loop() {
  bool hasMove = digitalRead(IR_PIN);   // считываем, было ли движение
  int photo = analogRead(PHOTO_PIN);    // считываем сигнал с фоторезистора
  int potSignal = analogRead(POT_PIN);    // считываем сигнал с потенциометра

  if (lastPir != hasMove) {
    ledState = hasMove;   // если состояние движения изменилось, меняем состояние светодиода
    lastPir = hasMove;    // и обновляем флаг
  }

  bool btnState = digitalRead(BTN_PIN);   // считываем сигнал с кнопки
  if (btnState && !flag) {
    flag = true;    // если кнопка была нажата, меняем заначение флага
    ledState = !ledState;   // и инвертируем состояние светодиода
  }
  if (!btnState && flag) flag = false;    // если кнопка была отпущена, меняем значение флага  

  byte maxBright = map(potSignal, 0, 1023, 1, 255);  // вычисляем максимальную яркость, преобразовываем диапазон 0...1023 в 1..255
  byte bright = map(photo, 0, 1023, maxBright, 5);    // вычисляем нужную яркость, преобразовываем диапазон 0...1023 в диапазон от 5 до максимального значения
  // поскольку исходному значению 0 должна соответствовать максимальная яркость, аргументы нового диапазона указаны в обратном порядке
  bright = constrain(bright, 0, 255);   // для надежности обрезаем диапазон
  
  ledOn(bright);    // запускаем светодиод с определенной яркостью
}

byte ledOn(byte bright) {
  if (!ledState) bright = 0;    // если статус 0, яркость ставим 0
  analogWrite(LED_PIN, bright);
}
