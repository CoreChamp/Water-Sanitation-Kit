
int sensorPin = A0;
int BuzzerPin = 4;
void setup()
{ 
  Serial.begin(9600);
  pinMode(BuzzerPin,OUTPUT);
   
}
void loop() {
  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  int turbidity = map(sensorValue, 0, 750, 100, 0);
  delay(100);
  Serial.print(turbidity);
  delay(100);
  if (turbidity < 20) {
    Serial.println("Water Quality Status: It's Clear");
      delay(500); 
  }
  if ((turbidity > 20) && (turbidity < 50)) {
    Serial.println("Water Quality Status: It's Cloudy"); 
    digitalWrite(BuzzerPin,HIGH);
    delay(1000);
    digitalWrite(BuzzerPin,LOW);
    delay(1000);
           
  }
  if (turbidity > 50) {
  digitalWrite(BuzzerPin,HIGH);
  Serial.println("Water Quality Status: It's Dirty");
  delay(500);
  }
}
