/*
 * Mini-Projekt 12: LCD ansteuern
 * Loesung
 */

// LCD Bibliothek einbinden
#include <LiquidCrystal.h>

// LCD initialisieren
LiquidCrystal lcd(12,11,5,4,3,2);

// Variable für den Pin initialisieren

void setup() {
  // LCD verbinden
  lcd.begin(2,16);
}

void loop() {
  // Text ausgeben
  lcd.print("Blub");
  // Irgendeine Variable mit einer Zahl definieren
  int blub = 2;
  // Cursor in die zweite Reihe setzen
  lcd.setCursor(1,0);
  // Variable ausgeben
  lcd.print(blub);
}
