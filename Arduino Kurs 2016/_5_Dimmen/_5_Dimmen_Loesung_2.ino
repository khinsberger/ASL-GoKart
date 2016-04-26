/*
 * Mini-Projekt 4: Dimmen einer LED
 * Loesung
 */

void setup() {
  // Pin deklarieren:
  pinMode(11, OUTPUT);
}

void loop() {
  // Helligkeit der LED mit einer Schleife immer um eins erhöhen
  // Achtung es ist immer eine kleine Pause nach der Helligkeitsänderung nötig
  int i = 0;
  while (i < 256) {
    analogWrite(11, i);
    delay(50);
    i++;
  }
  
  // Helligkeit der LED mit einer Schleife immer um eins erniedrigen
  // Achtung es ist immer eine kleine Pause nach der Helligkeitsänderung nötig
  int j = 0;
  while (j >= 0) {
    analogWrite(11, j);
    delay(50);
    i--;
  }
}
