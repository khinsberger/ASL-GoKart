/*
 * Mini-Projekt 6: Button auslesen
 * Loesung
 */

// Variable für den Pin initialisieren
const int buttonPin = 13;

void setup() {
  // Pin deklarieren:
  pinMode(buttonPin, INPUT);

  //Seriellen Monitor initialisieren:
  Serial.begin(9600);
}

void loop() {
  // Status des Tasters auslesen und in einer Variablen speichern
  int buttonStatus = digitalWrite(buttonPin);
  // Variable an den Seriellen Monitor weitergeben
  Serial.println(buttonStatus);
}
