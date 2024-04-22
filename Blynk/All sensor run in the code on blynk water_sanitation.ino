#define BLYNK_TEMPLATE_ID "TMPL3GJxfSfdQ"
#define BLYNK_TEMPLATE_NAME "Water Sanitation"
#define BLYNK_AUTH_TOKEN "3ONmpDYd4t9NKe0zPkAQCh7VwyLOU-36"
#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.

char ssid[] = "Innova8";
char pass[] = "innova8.in";


#include <SoftwareSerial.h>
SoftwareSerial EspSerial(11, 12); // RX, TX

WidgetLCD lcd(V2);

// Your ESP8266 baud rate:
#define ESP8266_BAUD 4800

ESP8266 wifi(&EspSerial);

BlynkTimer timer;


#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into digital pin 13 on the Arduino
#define ONE_WIRE_BUS 13

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

//motor status
int motorpin = 6;
int motorstate = 0;

float sensorvalue;
//ULTRASONIC FOR HIGHT
#define echoPin 3 
#define trigPin 2                                           
 
 
long duration; // Variable to store time taken to the pulse
               // to reach receiver
 
int distance; // Variable to store distance calculated using


//turbudity
int sensorPin = A0;


void sendSensor(){

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, sensors.getTempCByIndex(0));
  Blynk.virtualWrite(V5, (sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);

  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "innova8");

  // Send the command to get temperatures
  sensors.requestTemperatures(); 

  //print the temperature in Celsius
  Serial.print("Water Temperature: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print("°C  |  ");
  
  //print the temperature in Fahrenheit
  Serial.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  Serial.println("°F");

  lcd.print(2, 1, "TEMPERATURE:");

  
  delay(500);
}

void sendWATERlevel(){

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
 
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0344 / 2; // Expression to calculate
                               
  Serial.print("HEIGHT: ");
  Serial.print(distance); // Print the output in serial monitor
  Serial.println(" cm");
  lcd.print(0, 1, "HEIGHT:");
  lcd.print(8,1,distance);
  lcd.print(12,1,"cm");
  delay(500);              
}

void sendwaterquality()
{
  int sensorValue = analogRead(sensorPin);
  
  //int turbidity = map(sensorValue, 0, 750, 100, 0);
  
  Blynk.virtualWrite(V0,sensorValue);

  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "innova8"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print") 
  Serial.println(sensorValue);
 
  delay(100);

}
  void setup(void)
{
  // Debug console
  Serial.begin(4800);
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
   Blynk.begin(auth, wifi, ssid, pass);
  pinMode(motorpin,OUTPUT);
  pinMode(trigPin,OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  digitalWrite(motorpin,LOW);
  timer.setInterval(100L, sendSensor);
  timer.setInterval(100L, sendWATERlevel);
  timer.setInterval(100L, sendwaterquality);
  //timer.setInterval(100L, sendmotorStatus);
  sensors.begin();  // Start up the library
  Serial.begin(4800);
  Serial.println("INNOVA8");
    delay(500);
}

void loop() {
  Blynk.run();
  timer.run();
}
