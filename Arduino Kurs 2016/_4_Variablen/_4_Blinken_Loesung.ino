/*
* Mini-Projekt 4: Variablen
* Loesung
*/

const int ledPin = 13;

void setup() {
  //Pin Deklaration
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}
