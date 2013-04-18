// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
} 
 
 
void loop() 
{ 
  int sensorValue = analogRead(A0);
  Serial.print("Val: ");
  Serial.print(sensorValue);
  Serial.write('\n');
  myservo.write(map(sensorValue, 600, 300, 25, 159));
  delay(20);
} 
