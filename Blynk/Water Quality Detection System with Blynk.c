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

int sensorPin = A0;
int BuzzerPin = 4;
int redPin =7;
int greenPin = A2;
int bluePin = A3;

void sendSensor(){

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  int sensorValue = analogRead(sensorPin);
  int turbidity = map(sensorValue, 0, 750, 100, 0);
  
  Blynk.virtualWrite(V3,turbidity);

  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "CORECHAMP"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print") 
  Serial.println(sensorValue);
 
  delay(100);
  Serial.print(turbidity);
  delay(100);
  if (turbidity < 20) {
    Serial.println("Water Quality Status: It's Clear");
    lcd.print(0, 1, "STATUS: CLEAR");
    digitalWrite(redPin,LOW);
    digitalWrite(greenPin,HIGH);
    digitalWrite(bluePin,LOW);
    delay(500); 
  }
  if ((turbidity > 20) && (turbidity < 50)) {
    Serial.println("Water Quality Status: It's Cloudy");
    lcd.print(0, 1, "STATUS: CLOUDY"); 
    digitalWrite(redPin,LOW);
    digitalWrite(greenPin,LOW);
    digitalWrite(bluePin,HIGH);
    delay(100);
    digitalWrite(BuzzerPin,HIGH);
    delay(1000);
    digitalWrite(BuzzerPin,LOW);
    delay(1000);
           
  }
  if (turbidity > 50) {
  digitalWrite(BuzzerPin,HIGH);
  Serial.println("Water Quality Status: It's Dirty");
  lcd.print(0, 1, "STATUS: DIRTY");
  digitalWrite(redPin,HIGH);
  digitalWrite(greenPin,LOW);
  digitalWrite(bluePin,LOW);
  delay(500);
  }
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

  Serial.begin(9600);
  pinMode(BuzzerPin,OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  Blynk.run();
  timer.run();
}
