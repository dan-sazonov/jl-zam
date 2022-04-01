#define IR_PIN 2
#define BTN_PIN 11
#define LED_PIN 6
#define PHOTO_PIN A1
#define POT_PIN A0

bool ledState = false;
bool lastPir = false;
bool flag = false;

void setup() {
  Serial.begin(9600);
  pinMode(IR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);
  pinMode(PHOTO_PIN, INPUT);
  pinMode(POT_PIN, INPUT);
}

void loop() {
  bool hasMove = digitalRead(IR_PIN);
  int photo = analogRead(PHOTO_PIN);
  int potSignal = analogRead(POT_PIN);
  
  if (lastPir != hasMove) {
    ledState = hasMove;
    lastPir = hasMove;
  }

  bool btnState = digitalRead(11);
  if (btnState && !flag) {
    flag = true;
    ledState = !ledState;
  }
  if (!btnState && flag) flag = false;

  byte maxBright = map(potSignal, 0, 1023, 1, 255);

  byte bright = map(photo, 0, 1023, maxBright, 5);
  bright = constrain(bright, 0, 255);
  ledOn(bright);
}

byte ledOn(byte bright) {
  if (!ledState) bright = 0;
  analogWrite(LED_PIN, bright);
}
