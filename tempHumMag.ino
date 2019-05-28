#include <dht.h>

dht DHT;

#define DHT11_PIN 7

//***** MAGNETIC FIELD *****//
int ANALOG_MAG_PIN = A0; //The analog pin for the analog output of the sensor
int DIGITAL_MAG_PIN = 5; //The digital pin for the digital output of the sensor

int mag_D; //Variable to store the digital reading
int mag_A; //Variable to store the analog reading

void setup(){
  Serial.begin(9600);
  pinMode(ANALOG_MAG_PIN, INPUT); //Make the pin you used an input on the Arduino
  pinMode(DIGITAL_MAG_PIN, INPUT); //Make the pin you used an input on the Arduino
}

void loop()
{
  //***** TEMPERATURE & HUMIDITY *****//
  
  int chk = DHT.read11(DHT11_PIN);
  if (DHT.temperature > -999 || DHT.humidity > -999) {
    Serial.print("Temperature = ");
    Serial.println(DHT.temperature);
    Serial.print("Humidity = ");
    Serial.println(DHT.humidity);
  }

  //***** MAGNETIC FIELD *****//
  mag_A = analogRead(ANALOG_MAG_PIN); //Read the signal from your sensor
  Serial.print("Magnetic Field Strength: "); //Print out the results
  Serial.println(mag_A); //Print the raw analog output
  
  delay(1000);
}
