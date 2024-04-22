#include <OneWire.h>
#include <DallasTemperature.h>
#define echoPin 3 
#define trigPin 2 

long duration; // Variable to store time taken to the pulse
               // to reach receiver
int distance; // Variable to store distance calculated using
              // formula


// Data wire is plugged into digital pin 5 on the Arduino
#define ONE_WIRE_BUS 13

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>




#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define NEXT_BUTTON_PIN 12    // Digital pin connected to the "Next" button
#define PREV_BUTTON_PIN 10// Digital pin connected to the "Previous" button

int nextButtonState = 0;
int prevButtonState = 0;
int currentSensor = 1; // Default sensor is temp
int turbiditysensorPin = A0;

const float Gwater = 1.5;   //Good Quality Water Referance Value 
const float Mwater = 0.8;   //Medauim Quality Water Referance Value 


void setup() {
  Serial.begin(9600);
  pinMode(NEXT_BUTTON_PIN, INPUT_PULLUP); // Use internal pull-up resistors
  pinMode(PREV_BUTTON_PIN, INPUT_PULLUP); // Use internal pull-up resistors
  pinMode(trigPin,OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
 // pinMode(smoke, INPUT);


  
  
// Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  //display.display();
  //delay(1000);  // Pause for 2 seconds
  display.clearDisplay();
  displayCurrentSensor();
}





void loop() {
  // Read the button states
  nextButtonState = digitalRead(NEXT_BUTTON_PIN);
  prevButtonState = digitalRead(PREV_BUTTON_PIN);

  if (nextButtonState == LOW) {
    // Move to the next sensor when the "Next" button is pressed
    currentSensor++;
    if (currentSensor > 3) {
      currentSensor = 1;
    }
    displayCurrentSensor();
    delay(500); // Debounce delay
  } else if (prevButtonState == LOW) {
    // Move to the previous sensor when the "Previous" button is pressed
    currentSensor--;
    if (currentSensor < 1) {
      currentSensor = 3;
    }
    displayCurrentSensor();
    delay(500); // Debounce delay
  }
   switch (currentSensor) {
    case 1:
      readtemprature();
      break;
    case 2:
       readturbidity();
      break;
      case 3:
       readhight();
      break;
     
       default:
      break;
  }
}
void displayCurrentSensor() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Sensor: ");
  display.print(currentSensor);
  display.setCursor(0, 1);
  display.print("Reading: ");
  display.print(sensorName(currentSensor));

}
String sensorName(int sensor) {
  switch (sensor) {
    case 1:
      return "DHT11 Temp & Hum";
    case 2:
      return "MQ-2 Air Qual";
      default:
      return "Unknown";
      
  }
}
void readtemprature() {

  sensors.requestTemperatures();
  
 display.clearDisplay();
  display.setCursor(10,1);
  display.setTextSize(2);
  display.print("Innova8");
  delay(100);
   display.setCursor(0,25);
  display.setTextSize(2);
  display.print("Temp: "); 
  delay(100);
  display.setCursor(10,45);
  display.setTextSize(1);
  display.print(sensors.getTempCByIndex(0));
  display.print("  deg C");
  delay(100);
  display.setCursor(10,55);
  display.setTextSize(1);
  display.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  display.print("  deg F");
  delay(100);

  display.display();

}
void readturbidity() {
 int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.println(voltage);


  display.clearDisplay();
  display.setCursor(10,1);
  display.setTextSize(2);
  display.print("innova8");
  delay(100);
 
    if (voltage >= Gwater) {
    Serial.println("Good Quality Water");
//    digitalWrite(buzzer,LOW);
//    digitalWrite(red,LOW);
//    digitalWrite(green,HIGH);
//    digitalWrite(blue,LOW);
    display.setCursor(40,25);
    display.setTextSize(2);
    display.print("Good");
    display.setCursor(25,50);
    display.setTextSize(1);
    display.print("Quality Water");
    delay(100);
  }  if (voltage < Gwater && voltage > Mwater) {
    Serial.println("Medium Quality Water");
//    digitalWrite(buzzer,LOW);
//    digitalWrite(red,LOW);
//    digitalWrite(green,LOW);
//    digitalWrite(blue,HIGH);
    display.setCursor(30,25);
    display.setTextSize(2);
    display.print("Medium");
    display.setCursor(25,50);
    display.setTextSize(1);
    display.print("Quality Water");
    delay(100);
  } if (voltage < Mwater) {
    Serial.println("Bad Quality Water");
//    digitalWrite(buzzer,HIGH);
//    digitalWrite(red,HIGH);
//    digitalWrite(green,LOW);
//    digitalWrite(blue,LOW);
    display.setCursor(43,25);
    display.setTextSize(2);
    display.print("Bad");
    display.setCursor(25,50);
    display.setTextSize(1);
    display.print("Quality Water");
    delay(100);
} 
display.display();
}
void readhight() {
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
                                 // distance using time
 
    Serial.print("HEIGHT: ");
    Serial.print(distance); 
    Serial.println(" cm");
    delay(100);

    display.clearDisplay();
  display.setCursor(10,1);
  display.setTextSize(2);
  display.print("innova8");
  delay(100);
  display.setCursor(0,20);
  display.setTextSize(2);
  display.print("Height: "); 
  delay(100);
  display.setCursor(0,40);
  display.setTextSize(2);
  display.print(distance);
  display.print("cm");
  delay(100);

  display.display();

  delay(2000);
}





  
