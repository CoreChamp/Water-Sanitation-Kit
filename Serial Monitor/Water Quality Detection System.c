
int sensorPin = A0;
int BuzzerPin = 4;
int redPin =7;
int greenPin = A2;
int bluePin = A3;
void setup()
{ 
  Serial.begin(9600);
  pinMode(BuzzerPin,OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.println("CORECHAMP");
   
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
    digitalWrite(redPin,LOW);
    digitalWrite(greenPin,HIGH);
    digitalWrite(bluePin,LOW);
    delay(500); 
  }
  if ((turbidity > 20) && (turbidity < 50)) {
    Serial.println("Water Quality Status: It's Cloudy"); 
    digitalWrite(redPin,LOW);
    digitalWrite(greenPin,LOW);
    digitalWrite(bluePin,HIGH);
    digitalWrite(BuzzerPin,HIGH);
    delay(1000);
    digitalWrite(BuzzerPin,LOW);
    delay(1000);
           
  }
  if (turbidity > 50) {
  digitalWrite(BuzzerPin,HIGH);
  Serial.println("Water Quality Status: It's Dirty");
  digitalWrite(redPin,HIGH);
  digitalWrite(greenPin,LOW);
  digitalWrite(bluePin,LOW);  
  delay(500);
  }
}
