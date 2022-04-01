#define BUTTON_PIN  11
#define LED_PIN     13
 
boolean buttonWasUp = true;  // была ли кнопка отпущена?
boolean ledEnabled = false;  // включен ли свет?
 
void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}
 
void loop()
{
  Serial.println(digitalRead(BUTTON_PIN));
}
