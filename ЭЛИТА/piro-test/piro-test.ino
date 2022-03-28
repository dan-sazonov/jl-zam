#define piro 8
#define mosfet 9
#define foto A0

void setup() {

  pinMode (piro, INPUT);
  pinMode (mosfet, OUTPUT);
}
void loop() {

  if ((analogRead (foto) < 250) && (digitalRead(piro) == HIGH))
  {
    analogWrite(mosfet, 25);
  }
  else if ((analogRead (foto) < 200) && (digitalRead(piro) == HIGH))
  {
    analogWrite(mosfet, 20);
  }
  else if ((analogRead (foto) < 150) && (digitalRead(piro) == HIGH))
  {
    analogWrite(mosfet, 15);
  }
  else if ((analogRead (foto) < 100) && (digitalRead(piro) == HIGH))
  {
    analogWrite(mosfet, 10);
  }
  else if ((analogRead (foto) < 50) && (digitalRead(piro) == HIGH))
  {
    analogWrite(mosfet, 5);
  }
  else if (digitalRead (piro) == LOW)
  {
    digitalWrite (mosfet, LOW);
  }
}
