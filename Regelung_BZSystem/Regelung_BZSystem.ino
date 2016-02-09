/*
 * 
 * Regelung BZ System
 * 
 * Regelung des Brennstoffzellensytems der Gruppe GoKart mit Brennstoffzellenantrieb 
 * des Aerospace Labs Herrenberg. Einlesen der Sensoren (Temperatur, Durchfluss, Not-Aus),
 * Ansteuerung der Aktoren (Magnetventile, Ventilator, Kompressor, Wasserpumpe) und Aufbau 
 * eines User Interfaces über Warnleuchten.
 * 
 * Pinbelegung:
 * -- Sensoren --
 * Pin A0: Temperatur
 * Pin 2: Durchfluss
 * Pin 22: Not-Aus
 * 
 * -- Aktoren --
 * Pin 23: Magnetventil Zulauf H2 (ZH)
 * Pin 24: Magnetventil Ablauf H2 (AH)
 * Pin 25: Magnetventil Ablauf O2 (ZO)
 * Pin 3: Ventilator
 * Pin 4: Kompressor
 * Pin 8: Wasserpumpe
 * 
 * -- User Interface --
 * Pin 5: Warnleuchte Temperatur zu hoch (TH)
 * Pin 6: Warnleuchte Temperatur zu niedrig (TN)
 * Pin 7: Warnleuchte kein Durchfluss (D)
 * 
 * Created 8th December 2015
 * By AerospaceLab Herrenberg
 * Modified 15th December 2015
 * By AerospaceLab Herrenberg
 * Modified 22nd December 2015
 * By AerospaceLab Herrenberg
 * Modified 19th Janurary 2016
 * By Aerospacelab Herrenberg
 */

/*
 * Bibliotheken Import
 */
// Mathe Bibliothek zur Nutzung des Logarithmus
#include <math.h>


/*
 * Deklarieren der Pins
 */
// Analoge Inputs
const int temperaturPin         = A0;
// Digitale Inputs
const int durchflussPin         = 2;
const int notAusPin             = 22;;
// Digitale Outputs
const int magnetventilPin_ZH    = 23;
const int magnetventilPin_AH    = 24;
const int magnetventilPin_ZO    = 25;
// PWM Output
const int ventilatorPin         = 3;
const int kompressorPin         = 4;
const int wasserpumpePin        = 8;
// User Interface
const int warnleuchtenPin_TH    = 5;
const int warnleuchtenPin_TN    = 6;
const int warnleuchtenPin_D     = 7;


/*
 * Deklarieren der globalen Variablen
 */
double temperatur = 0;
double durchfluss = 0;
volatile int nbTopsFan;
int Ventilator_vel;

/*
 * Initialisieren der globalen Parameter
 */
const int R2 = 10000;




void setup() {
  // Analoge Inputs
  pinMode(temperaturPin, INPUT);
  // Digitale Inputs
  pinMode(notAusPin, INPUT);
  pinMode(durchflussPin, INPUT);
  // Digitale Outputs
  pinMode(magnetventilPin_ZH, OUTPUT);
  pinMode(magnetventilPin_AH, OUTPUT);
  pinMode(magnetventilPin_ZO, OUTPUT);
  // PWM Output
  pinMode(ventilatorPin, OUTPUT);
  pinMode(wasserpumpePin, OUTPUT);
  pinMode(kompressorPin, OUTPUT);
  pinMode(warnleuchtenPin_TH, OUTPUT);
  pinMode(warnleuchtenPin_TN, OUTPUT);
  pinMode(warnleuchtenPin_D, OUTPUT);
  Serial.begin(9600);

  attachInterrupt(0, rpm, RISING);


  Serial.println("Brennstoffzellen System Regelung");
  Serial.println("AerospaceLab Herrenberg");
  Serial.println("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  Serial.println("Serielle Kommunikation initialisiert");
  Serial.println("Initiale Daten:");

  getTemperatur();
  Serial.print("Temperatur: ");
  Serial.print(temperatur);
  Serial.println(" deg C");
  setWasserpumpe(255);
  setVentilator(255);
  while(durchfluss <= 0.1) {
    nbTopsFan = 0;
    sei();    // Aktivieren
    delay(500);
    cli();    // Deaktivieren;
    durchfluss = nbTopsFan/6.425;
    Serial.print("Durchfluss: ");
    Serial.print(durchfluss);
    Serial.println("l/min");
    if(durchfluss > 0.1) {
      setVentile(1, 1);
      setVentile(2, 1);
      setVentile(3, 1);
      break;
    }
  }
}

void loop() {  //Durchflusskontrolle und Kompensierung
  nbTopsFan = 0;
  sei();    // Aktivieren
  delay(500);
  cli();    // Deaktivieren;
  durchfluss = nbTopsFan/6.425;
  if(durchfluss < 0.1) {                  
    setWasserpumpe(255);
    nbTopsFan = 0;
    sei();    // Aktivieren
    delay(500);
    cli();    // Deaktivieren;
    durchfluss = nbTopsFan/6.425;
    if(durchfluss < 0.1) {
      setVentile(1, 0);               //alle Ventile aus
      setVentile(2, 0);
      setVentile(3, 0);
      setKompressor(0);               //Pumpen aus außer Wasserpumpe
      setWarnleuchten(3); 
    }
  }

        Serial.print("Durchfluss: ");
        Serial.println(durchfluss);

        Serial.print("Temperatur: ");
        Serial.println(temperatur);

  
  getTemperatur();
  double diff = temperatur - 70.0;
  double reg = diff / 5.0;
  Ventilator_vel = Ventilator_vel * ( 1 + reg);
  setWasserpumpe(Ventilator_vel);
  if(temperatur > 75) {
    setVentile(1, 0);            //alle Ventile aus
    setVentile(2, 0);
    setVentile(3, 0);
    setKompressor(0);            //Pumpen aus außer Wasserpumpe
    setWarnleuchten(3);
  }
    
  if(notAusPin == 1) {
    setVentile(1, 0);            //alle Ventile aus
    setVentile(2, 0);
    setVentile(3, 0);
    setKompressor(0);            //Pumpen aus außer Wasserpumpe
    setWarnleuchten(3);          // Warnleuchte
  }
}

/*
 * Funktion um die Temperatur des Wasserkreislaufes zu bestimmen
 */
void getTemperatur() {
  double value = analogRead(temperaturPin);
  double volt = map(value, 0, 1023, 0, 5000);
  double widerstand = (R2/(volt/5000))-R2;
  temperatur=92.439-27.929*log(widerstand/1000);
}

/*
 * Funktion um die Durchflussmenge des Wasserkreislaufes zu bestimmen
 */
void rpm() {
  nbTopsFan++;
}

/*
 * Funktion um die Drehgeschwindigkeit der Ventilatoren zu setzen
 * INPUT:
 * nbr (int): Geschwindigkeit des Ventilators
 */
void setVentilator(int vel) {
  analogWrite(ventilatorPin, vel);
}

/*
 * Funktion um die Magnetventile auf ein oder aus zu setzen
 * INPUT:
 * nbr (int): Nummer des zu ansteuernden Magnetventils
 */
void setVentile(int nbr, int state) {
  // Ventil_ZH nbr=1
  if(nbr == 1 && state == 0) {
      digitalWrite(magnetventilPin_ZH, LOW); 
  }
  else if(nbr == 1 && state == 1) {
    digitalWrite(magnetventilPin_ZH, HIGH);
  }
  // Ventil_AH nbr=2
  if(nbr == 2 && state == 0) {
    digitalWrite(magnetventilPin_AH, LOW);
  }
  else if(nbr == 2 && state == 1){
    digitalWrite(magnetventilPin_AH, HIGH);
  }
  // Ventil_ZO nbr=3
  if(nbr == 3 && state == 0) {
    digitalWrite(magnetventilPin_ZO, LOW);
  }
  else if(nbr == 3 && state == 1) {
    digitalWrite(magnetventilPin_ZO, HIGH);
  }
    


  }

/*
 * Funktion um die Pumpstärke der Wasserpumpe zu setzen
 */
void setWasserpumpe(int vel) {
  analogWrite(wasserpumpePin, vel);
}

/*
 * Funktion um die Kompressorstärke zu setzen
 */
void setKompressor(int vel) {
  analogWrite(kompressorPin, vel);
  
}

/*
 * Funktion um die Warnleuchten anzusteuern
 * INPUT:
 * nbr (int): Nummer der zu ansteuernden LED
 */
void setWarnleuchten(int nbr) {
  if(nbr == 1) {
    digitalWrite(warnleuchtenPin_TH, HIGH);
  }
  if(nbr == 2) {
    digitalWrite(warnleuchtenPin_TN, HIGH);
  }
  if(nbr == 3) {
    digitalWrite(warnleuchtenPin_D, HIGH);
  }
}
