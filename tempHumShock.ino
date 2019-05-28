#include <dht.h>

dht DHT;

#define DHT11_PIN 7

//Henry's Bench
//KY-002 Shock Sensor Tutorial

int shockPin = 10; // Use Pin 10 as our Input
int shockVal = HIGH; // This is where we record our shock measurement
boolean bAlarm = false;

unsigned long lastShockTime; // Record the time that we measured a shock

int shockAlarmTime = 250; // Number of milli seconds to keep the shock alarm high
int tempHumidityInterval = 1000; // Number of milli seconds to keep the shock alarm high
boolean shouldRecord = true;
int recordTime = 0;

void setup(){
  Serial.begin(9600);
  pinMode (shockPin, INPUT) ; // input from the KY-002
}

void loop()
{
  if (shouldRecord) {
    shouldRecord = false;
    recordTime = millis();
    int chk = DHT.read11(DHT11_PIN);
    if (DHT.temperature > -999 || DHT.humidity > -999) {
      Serial.print("Temperature = ");
      Serial.println(DHT.temperature);
      Serial.print("Humidity = ");
      Serial.println(DHT.humidity);
    }
  }
  if (millis()-recordTime > tempHumidityInterval) {
    shouldRecord = true;
  }


  shockVal = digitalRead (shockPin) ; // read the value from our sensor
  
  if (shockVal == LOW) // If we're in an alarm state
  {
    lastShockTime = millis(); // record the time of the shock
    // The following is so you don't scroll on the output screen
    if (!bAlarm){
      Serial.println("Shock Alarm");
      bAlarm = true;
    }
  }
  else
  {
    if( (millis()-lastShockTime) > shockAlarmTime  &&  bAlarm){
      Serial.println("no alarm");
      bAlarm = false;
    }
  }

//  delay(500);
}
