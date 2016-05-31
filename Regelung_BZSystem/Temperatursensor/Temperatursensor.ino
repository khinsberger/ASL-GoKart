int Volt = 0;
int value = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(A3, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:


value = analogRead(A3);
Volt = map(value,0,1024,0,5000);
Serial.print("Volt in mV:");
Serial.println(Volt);
Serial.print("X:");
Serial.println(analogRead(A3));
delay(500);


}
