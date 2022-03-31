#define IR_PIN 2
#define BTN_PIN 11

bool wasClicked = false;

void setup() {
  Serial.begin(9600);
  pinMode(IR_PIN, INPUT);
  pinMode(13, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
}
int i = 0;
void loop() {
  bool hasMove = digitalRead(IR_PIN);

  bool btnState = !digitalRead(BTN_PIN);
  if (btnState && !wasClicked) {
    wasClicked = true;
  }
  if (!btnState && wasClicked) wasClicked = false;  
  
  Serial.println(wasClicked);
  digitalWrite(13, hasMove);
}
