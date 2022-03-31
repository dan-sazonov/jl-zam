#define BUTTON_PIN  3
#define LED_PIN     13
 
boolean buttonWasUp = true;
boolean ledEnabled = false;
 
void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
}
 
void loop()
{
  Serial.println(digitalRead(BUTTON_PIN));
  boolean buttonIsUp = !digitalRead(BUTTON_PIN);
  if (buttonWasUp && !buttonIsUp) {
    delay(10);
    buttonIsUp = digitalRead(BUTTON_PIN);
    if (!buttonIsUp) {
      ledEnabled = !ledEnabled;
      digitalWrite(LED_PIN, ledEnabled);
    }
  }
  buttonWasUp = buttonIsUp;
}
