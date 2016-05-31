int ventilZustand = 0;
int ventilPin = 1;

void setup() 
{
  pinMode(ventilPin, OUTPUT);
  
}

void loop() 
{
 digitalWrite(ventilPin, ventilZustand);
 ventilZustand = HIGH;
  
}
