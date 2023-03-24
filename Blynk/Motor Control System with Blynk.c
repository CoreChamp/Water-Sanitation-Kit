/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPLAQTecbqy"
#define BLYNK_TEMPLATE_NAME "corechamp"
#define BLYNK_AUTH_TOKEN "EAQVIFIeZ_1IMYe8ktPaq_iRwdJQCADy"

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


int motorpin = 6;
int motorstate = 0;

int redPin =7;
int greenPin = A2;
int bluePin = A3;

void sendSensor()
{
  motorstate = digitalRead(motorpin);

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  
  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "CORECHAMP"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")

  Serial.println(motorstate);
  Serial.print('\n');
  delay(1000);
  
  if(motorstate == 1){
  lcd.print(0, 2, "Motor is On");  
  Serial.println("Motor is On");
  digitalWrite(redPin,LOW);
  digitalWrite(greenPin,HIGH);
  digitalWrite(bluePin,LOW);
  delay(100);
  }
  else{
    lcd.print(1, 2, "Motor is Off");
    Serial.println("Motor is Off");
    digitalWrite(redPin,HIGH);
    digitalWrite(greenPin,LOW);
    digitalWrite(bluePin,LOW);
    delay(100);
  }
}

void setup()
{
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

}

void loop()
{
  Blynk.run();
  timer.run();
}
