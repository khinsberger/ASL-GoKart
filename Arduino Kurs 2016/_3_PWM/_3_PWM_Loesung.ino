/*
 * Mini-Projekt 3: Helligkeit einer LED steuern
 * Loesung
 */

void setup() {
  // Pin deklaration:
  pinMode(11,OUTPUT);
}

void loop() {
  // LED auf die volle Helligkeit und eine Sekunde warten:
  analogWrite(11, 255);
  delay(1000);
  // LED auf die halbe Helligkeit und eine Sekunde warten:
  analogWrite(11, 127);
  delay(1000);
  // LED aus und eine Sekunde warten:
  analogWrite(11, 0);
  delay(1000);
}
