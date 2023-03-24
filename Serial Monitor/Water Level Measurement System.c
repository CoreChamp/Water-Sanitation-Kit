#define echoPin 3 
#define trigPin 2                                          
 
 
long duration; // Variable to store time taken to the pulse
               // to reach receiver
 
int distance; // Variable to store distance calculated using
              // formula
 
void setup()
{
    pinMode(trigPin,OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
 
    // Serial Communication is starting with 9600 of
    // baudrate speed
    Serial.begin(9600);
 
    // The text to be printed in serial monitor
    Serial.println("CORECHAMP");
    delay(500);
}
 
void loop()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); // wait for 2 ms to avoid
                          // collision in serial monitor
 
    digitalWrite(trigPin,HIGH); // turn on the Trigger to generate pulse
    delayMicroseconds(10);      // keep the trigger "ON" for 10 ms to generate
                                // pulse for 10 ms.
 
    digitalWrite(trigPin,LOW); // Turn off the pulse trigger to stop
                               // pulse generation
 
    // If pulse reached the receiver echoPin
    // become high Then pulseIn() returns the
    // time taken by the pulse to reach the
    // receiver
 
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.0344 / 2; // Expression to calculate
                                 // distance using time
 
    Serial.print("Water Level: ");
    Serial.print(distance); // Print the output in serial monitor
    Serial.println(" cm");
    delay(100);
}
