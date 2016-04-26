/*
 * Mini-Projekt 10: Temperatursensor auslesen
 */

// Variable für den Pin initialisieren
const int tempPin = A0;

void setup() {
  // Pin deklarieren:
  pinMode(tempPin, INPUT);
  //Seriellen Monitor initialisieren:
  Serial.begin(9600);
}

void loop() {
  // Wert des Temperatursensors auslesen und in einer Variablen speichern
  int tempWert = analogRead(tempPin);
  // Variable in Millivolt von 0 bis 5000 umrechnen
  int mVolt = map(tempWert, 0, 1023, 0, 5000);
  // Temperatur mit Formel berechnen
  double temp = (mVolt - 500.0) / 10.0;
  // Temperatur am seriellen Monitor ausgeben
  Serial.println(temp);
  // 5 Sekunden warten
  delay(5000);
}
