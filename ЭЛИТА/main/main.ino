#define IRPIN 2

void setup() {
  Serial.begin(9600);
  pinMode(IRPIN, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  bool s = digitalRead(IRPIN);
  Serial.println(s);
  digitalWrite(13, s);
}
