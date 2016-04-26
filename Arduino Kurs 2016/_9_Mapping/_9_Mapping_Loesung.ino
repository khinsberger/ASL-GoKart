/*
 * Mini-Projekt 9: LED mit einem Potentiometer steuern
 * Loesung
 */

// Variablen für die Pins initialisieren
const int potiPin = A0;
const int ledPin = 11;

void setup() {
  // Pins deklarieren:
  pinMode(potiPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Wert des Potentiometers auslesen und in einer Variablen speichern
  int potiStatus = analogRead(potiPin);
  // Helligkeit durch "Mapping" berechnen
  int helligkeit = map(potiStatus, 0, 1024, 0, 255);
  // Helligkeit an die LED ausgeben
  analogWrite(ledPin, helligkeit);
}
