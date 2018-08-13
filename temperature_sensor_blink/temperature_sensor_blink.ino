// Robo India Tutorial 
// Digital Output on LED 
// Hardware: NodeMCU Blynk Board


#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"           // including the library of DHT11 temperature and humidity sensor
#include <SimpleTimer.h>   //including the library of SimpleTimer
#define DHTTYPE DHT11      // DHT 11

#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE); 
SimpleTimer timer;
char auth[] = "e81b7b37dd324c60b67fa752dd074e1e";            // You should get Auth Token in the Blynk App.
                                           // Go to the Project Settings (nut icon).

char ssid[] = "nishant";    // Your WiFi credentials.
char pass[] = "12345678";  // Set password to "" for open networks.
float t;                                   // Declare the variables 
float h;
int r1=12;


void setup()
{
  pinMode(r1,OUTPUT);
    Serial.begin(9600);// Debug console
    Blynk.begin(auth, ssid, pass);
    dht.begin();
    timer.setInterval(2000, sendUptime);
}

void sendUptime()
{
  
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  if(t>30)
  {
    digitalWrite(r1,LOW);
  }
  else
  {
    digitalWrite(r1,HIGH);
}
  Serial.println("Humidity and temperature\n\n");
  Serial.print("Current humidity = ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(t); 
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  
}

void loop()
{
  Blynk.run();
  timer.run();
}

