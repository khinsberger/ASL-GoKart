/*
 * Mini-Projekt 11: Servo-Motor ansteuern
 * Loesung
 */

// Servo Bibliothek einbinden
#include <Servo.h>

// Servo initialisieren
Servo servo;

// Variable für den Potentiometer Pin und den Servo Pin initialisieren
const int potiPin = A0;
const int servoPin = 11;

void setup() {
  // Servo verbinden
  servo.attach(servoPin);
  // Pin deklarieren
  pinMode(potiPin, INPUT);
}

void loop() {
  // Wert des Potentiometers auslesen und in einer Variablen speichern
  int potiStatus = analogRead(potiPin);
  // Variable in Grad für den Servo von 0 bis 180 umrechnen 
  int grad = map(potiStatus, 0, 1023, 0, 180);
  // Gradzahl an den Servo schreiben
  servo.write(grad);
}
