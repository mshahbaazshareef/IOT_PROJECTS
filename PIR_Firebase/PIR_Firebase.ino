
/*
 code written by Mohammed Shahbaaz Shareef, explanations/tutorial can be found on my medium blog
*/
// required libraries
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
// required libraries
// Set these to run example.
#define FIREBASE_HOST "test-1741a.firebaseio.com" //please remove http and / from firebase url
#define FIREBASE_AUTH "GpW1hx87op8YrVbHCe37OFveQuI1QE0VucW0ZWOK" // paste secret key here
#define WIFI_SSID "ssid here "
#define WIFI_PASSWORD "wifi password here"


String myString; // sending integer data as string ,sensor data can also be send as integer
String motion = "detected";   // string which stores state - motion/no motion
String nomotion="nomotion";
int sdata = 0; // PIR sensor  value will be stored in sdata.
int Status = 12;  // Digital pin D6
int sensor = 13;  // Digital pin D7

void setup() {
Serial.begin(9600);
  pinMode(sensor, INPUT);   // declare sensor as input
  pinMode(Status, OUTPUT);  // declare LED as output
  int val = 0;  
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
      {
    Serial.print(".");
    delay(500);
      }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 
}
void loop() {
sdata = digitalRead(sensor);
myString = String(sdata); 
Serial.println(myString);//printing string to verify whether sensor is working or not  
Firebase.setString("Variable/Value",myString);//A string will be sent to real time database under variable /value (user need not create this in advance)
delay(1000); 
    long state = digitalRead(sensor);
    if(state == HIGH) {

      digitalWrite (Status, HIGH);
      Serial.println("Motion detected!");
      Serial.println(state);
      Firebase.setString("state/alert",motion);//A string will be sent to real time database under state- alert -ex -  motion , no motion 
      delay(1000);
    }
    else {
      digitalWrite (Status, LOW);
      Serial.println("Motion absent!");
       Firebase.setString("state/alert",nomotion);
      delay(1000);
      }
}
