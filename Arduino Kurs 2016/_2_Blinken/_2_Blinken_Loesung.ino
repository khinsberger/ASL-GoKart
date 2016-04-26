/*
* Mini-Projekt 2: Blinken einer LED
* Loesung
*/

void setup() {
  //Pin Deklaration
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
