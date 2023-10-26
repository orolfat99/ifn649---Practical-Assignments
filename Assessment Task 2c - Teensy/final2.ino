// const int waterPin = 11;
#include "DHT.h"
#define DHTPIN 21
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


const int soilPin = 20;
int transistorPin = 14;
const int sunPin = 15;


  // the setup() method runs once, when the sketch starts

// HC-05 setup
#define rxPin 7 // Teensy pin 7 <--> HC-05 Tx
#define txPin 8 // Teensy pin 8 <--> HC-05 Rx

void  setup() {
  // initialize the digital pin as an output.
  // pinMode(waterPin, OUTPUT);
  pinMode(transistorPin, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600); // Default communication rate of the Bluetooth module
  Serial.println(F("DHT-11 all setted"));
  dht.begin();

}

void loop() {
  int sunLightValue = analogRead(sunPin);
  int soilValue = analogRead(soilPin);

  // float h = dht.readHumidity();
  // float t = dht.readTemperature();

  const float h = 59.00;
  const float t = 32.0;

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));

  if (t >= 30){
    Serial.print("Weather is very hot");
    // Serial1.print("Weather_is_hot");
  } else {
    Serial.println("Weather is ok!");
  }


  Serial.print(" Soil : ");
  Serial.println(soilValue);

  Serial.print("Sun : ");
  Serial.println(sunLightValue);

  if (sunLightValue < 10) {
    Serial.println("Sun light - Dark");
    delay(5000);
  } else if (sunLightValue < 200) {
    Serial.println("Sun light - Dim");
    delay(5000);
  } else if (sunLightValue < 500) {
    Serial.println("Sun light - Light");
    delay(5000);
  } else {
    Serial.println("Sun light - Bright");
    // Serial1.println("Sun_light_Bright");
    delay(5000);
  }


  if (soilValue >= 600) {

    Serial.println("Soil is good");
    Serial1.println("Soil_is_good");
    // digitalWrite(waterPin, HIGH);  // set the LED on
    delay(30000);
    //digitalWrite(waterPin, LOW);   // set the LED off
    digitalWrite(transistorPin, LOW); // Turn the transistor ON
    delay(120000);  // wait for a secon

  } else {

    Serial.println("Soil is dry");
    Serial1.println("Soil_is_dry");
    // digitalWrite(waterPin, HIGH);  // set the LED on
    digitalWrite(transistorPin, HIGH); // Turn the transistor ON

    if (sunLightValue> 900 || t>30){
      Serial.print("Water motor work 10 seconds");
      delay(5000);                 // wait for a second
      
    } else {
      Serial.print("Water motor work 5 seconds");
      delay(5000);
      
    }

    // digitalWrite(waterPin, LOW);  // set the LED on
    digitalWrite(transistorPin, LOW); // Turn the transistor ON
    delay(5000); 
    // 1000 one second
    // 120000 2 miuntes
    // 180000 3 miuntes

  }
}