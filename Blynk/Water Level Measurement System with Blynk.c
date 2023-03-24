#define BLYNK_TEMPLATE_ID "TMPLAQTecbqy"
#define BLYNK_TEMPLATE_NAME "corechamp"
#define BLYNK_AUTH_TOKEN "12VdYlEtCSGYq6buJWmmYKwy7EKDtX6n"

#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.

char ssid[] = "Enter Wifi Name";
char pass[] = "Enter Password";

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(11, 12); // RX, TX

WidgetLCD lcd(V2);

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

BlynkTimer timer;

#define echoPin 3 
#define trigPin 2                                           
 
 
long duration; // Variable to store time taken to the pulse
               // to reach receiver
 
int distance; // Variable to store distance calculated using
              // formula

void sendSensor(){

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V3, distance);

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

  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "CORECHAMP"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")                               
 
  Serial.print("LEVEL: ");
  Serial.print(distance); // Print the output in serial monitor
  Serial.println(" cm");
  lcd.print(0, 1, "LEVEL:");
  lcd.print(8,1,distance);
  lcd.print(12,1,"cm");
  delay(100);              
}

void setup() {
  // Debug console
  Serial.begin(9600);
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
   Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);

  pinMode(trigPin,OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
 
  // Serial Communication is starting with 9600 of
    // baudrate speed
  Serial.begin(9600);
 
  // The text to be printed in serial monitor
  Serial.println("CORECHAMP");
  delay(500);
}

void loop() {
  Blynk.run();
  timer.run();
}
