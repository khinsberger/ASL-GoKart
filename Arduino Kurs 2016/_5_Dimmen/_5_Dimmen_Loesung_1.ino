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
  for (int i = 0; i < 256; i++) {
    analogWrite(11, i);
    delay(50);
  }
  
  // Helligkeit der LED mit einer Schleife immer um eins erniedrigen
  // Achtung es ist immer eine kleine Pause nach der Helligkeitsänderung nötig
  for (int i = 255; i >= 0; i--) {
    analogWrite(11, i);
    delay(50);
  }
}
