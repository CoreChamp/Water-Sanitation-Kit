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


#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into digital pin 5 on the Arduino
#define ONE_WIRE_BUS 5

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

void sendSensor(){

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V3, sensors.getTempCByIndex(0));
  Blynk.virtualWrite(V4, (sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);

  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "CORECHAMP");

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

  void setup(void)
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

  sensors.begin();  // Start up the library
  Serial.begin(9600);
  Serial.println("CORECHAMP");
    delay(500);
}

void loop() {
  Blynk.run();
  timer.run();
}
