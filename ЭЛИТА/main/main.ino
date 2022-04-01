#define IR_PIN 2
#define BTN_PIN 11
#define LED_PIN 6

bool ledState = false;
bool lastPir = false;
bool flag = false;

void setup() {
  Serial.begin(9600);
  pinMode(IR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);
}

void loop() {
  bool hasMove = digitalRead(IR_PIN);

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

  digitalWrite(13, ledState);


  
  ledOn(255);
}

byte ledOn(byte bright) {
  if (!ledState) bright = 0;
  analogWrite(LED_PIN, bright);
}
