//Buzzer
void turnBuzzerOn() {
  digitalWrite(buzzerPin, HIGH);
  Serial.println("Buzzer has been turned on");
}

void turnBuzzerOff() {
  digitalWrite(buzzerPin, LOW);
  Serial.println("Buzzer has been turned off");
}
//End buzzer

//Leds
const int ledPins[5] = { LED1, LED2, LED3, LED4, LED5 };

void turnAllLedOn() {
  for (int i = 0; i < ledPins.size(); i++)
    digitalWrite(ledPins[i], HIGH);
  Serial.println("All leds have been turned on!");
}

void turnLedOn(int led1) {
  digitalWrite(led1, HIGH);
  Serial.println("Led1 has been turned on!");
}

void turnLedOn(int led1, int led2) {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  Serial.println("Led: 1, 2 have been turned on!");
}

void turnLedOn(int led1, int led2, int led3) {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  Serial.println("Led: 1, 2, 3 have been turned on!");
}

void turnLedOn(int led1, int led2, int led3, int led4) {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  Serial.println("Led: 1, 2, 3, 4 have been turned on!");
}

void turnLedOn(int led1, int led2, int led3, int led5) {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  Serial.println("Led: 1, 2, 3, 4, 5 have been turned on!");
}

void turnAllLedOff() {
  for (int i = 0; i < ledPins.size(); i++)
    digitalWrite(ledPins[i], LOW);
  Serial.println("All leds have been turned ff!");
}

void turnLedOff(int led1) {
  digitalWrite(led1, LOW);
  Serial.println("Led1 has been turned off!");
}

void turnLedOff(int led1, int led2) {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  Serial.println("Led: 1, 2 have been turned off!");
}

void turnLedOff(int led1, int led2, int led3) {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  Serial.println("Led: 1, 2, 3 have been turned off!");
}

void turnLedOff(int led1, int led2, int led3, int led4) {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  Serial.println("Led: 1, 2, 3, 4 have been turned off!");
}

void turnLedOff(int led1, int led2, int led3, int led5) {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  Serial.println("Led: 1, 2, 3, 4, 5 have been turned off!");
}
//End leds

