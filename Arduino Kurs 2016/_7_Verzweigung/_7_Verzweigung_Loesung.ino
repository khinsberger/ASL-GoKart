/*
 * Mini-Projekt 7: Button auslesen
 * Loesung
 */

// Variablen für die Pins initialisieren
const int buttonPin = 13;
const int ledPin = 12;

void setup() {
  // Pins deklarieren:
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Status des Tasters auslesen und in einer Variablen speichern
  int buttonStatus = digitalWrite(buttonPin);
  // Wenn der Taster gedrückt ist LED anmachen sonst aus
  if (buttonStatus == 1) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
