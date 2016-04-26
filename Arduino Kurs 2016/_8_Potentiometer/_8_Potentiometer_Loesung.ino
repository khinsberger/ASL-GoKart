/*
 * Mini-Projekt 8: Potentiometer auslesen
 * Loesung
 */

// Variable für den Pin initialisieren
const int potiPin = A0;

void setup() {
  // Pin deklarieren:
  pinMode(potiPin, INPUT);

  //Seriellen Monitor initialisieren:
  Serial.begin(9600);
}

void loop() {
  // Wert des Potentiometers auslesen und in einer Variablen speichern
  int potiStatus = analogRead(potiPin);
  // Variable an den Seriellen Monitor weitergeben
  Serial.println(potiStatus);
}
