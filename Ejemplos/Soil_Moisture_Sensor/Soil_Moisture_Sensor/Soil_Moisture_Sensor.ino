int sensorPin = A0;
 
void setup() {
  
   Serial.begin(9600);
}
 
void loop() {
  
  int sensorValue = 1023 - analogRead(sensorPin);
  int soil = map(sensorValue, 0, 600, 0, 100);
  
  Serial.print("Humedad: " );                       
  Serial.print(soil);
  Serial.println("%" );   
  delay(1000);         
}
