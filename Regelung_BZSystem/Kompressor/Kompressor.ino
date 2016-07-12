
int druckSensorPin = A0;           //the pin that the Sensor is attached to
int druckSensor = 0;              // der Druck am Kompressorausgang
int druckLeitung = 1000;  // der gewünschte Druck in kP nach dem Kompressor (O2 Leitung zur Brennstoffzelle)
int maxDruck = 1200;     //bei diesem Wert wird der Kompressor komplett abgeschalten
int minDruck = 800;      // bei diesem Wert wird Kompressor auf maximale Leistung geschalten
//max und min sind Masnahmen, damit der Kompressor nicht immer an und aus geht bei jeder kleinsten veränderung
int mosfetPinKompressor = 1;    //PWM Pin für Kompressor Steuerung an den Mosfet Ground 
int kompressorWert = 0;
int mosfetWert = 0;       // wird von kompWert umgerechnet damit der Kompressor immer läuft, z.B. Wert 20 könnte zu klein sein

void setup() 
{

  pinMode(druckSensorPin, INPUT);
  pinMode(mosfetPinKompressor, OUTPUT);

  //aufbauen des gewünschten Startdrucks vor Systemstart
  while(analogRead(druckSensorPin) < druckLeitung)
  {
   kompressorWert = 255;
  }
  Serial.begin(9600);
}


void loop()
    {
      druckSensor = analogRead(druckSensorPin);
      Serial.println("Druck in Leitung: Kompressor OUT: ");
      Serial.print(druckSensor);
      
      mosfetWert = map(kompressorWert, 35, 173,0,255); //173< kompWert <35 kann nicht umgesetz werden
       // Wert wird an den Mosfet gegeben
       analogWrite(mosfetPinKompressor, mosfetWert);
       
         
       //Falls der Druck zu niedrig, Kompressor Wert hoch
        if ( analogRead(druckSensorPin) < druckLeitung)
        {
         kompressorWert++; 
           }
       //Falls der Druck zu hoch, Kompressor Wert runter
        if ( analogRead(druckSensorPin) > druckLeitung)
        {
         kompressorWert--;
           }
        if(analogRead(druckSensorPin) > maxDruck)
        {
         mosfetWert = 0;
           }
        if(analogRead(druckSensorPin) < minDruck)
        {
          mosfetWert = 255;
           }
      
       delay(10);
       
     }

