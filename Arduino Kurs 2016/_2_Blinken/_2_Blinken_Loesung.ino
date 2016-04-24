/*
*
* Mini-Projekt 1: Blinken einer LED
*
*/

void setup() {
  //Pin Deklaration
  pinMode(11, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
