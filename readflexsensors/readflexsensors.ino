/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 5:
  int sensorValue5 = analogRead(A5);
  // print out the value you read:
  Serial.print(sensorValue5);
  //delay(100);        // delay in between reads for stability
  Serial.print("\t");
   
   // read the input on analog pin 4:
  int sensorValue4 = analogRead(A4);
  // print out the value you read:
  Serial.print(sensorValue4);
  //delay(100);        // delay in between reads for stability

  Serial.print("\t");
  
   // read the input on analog pin 3:
  int sensorValue3 = analogRead(A3);
  // print out the value you read:
  Serial.print(sensorValue3);
  //delay(100);        // delay in between reads for stability

  Serial.print("\t");
  
   // read the input on analog pin 2:
  int sensorValue2 = analogRead(A2);
  // print out the value you read:
  Serial.print(sensorValue2);
  //delay(100);        // delay in between reads for stability

  Serial.print("\t");
  
   // read the input on analog pin 1:
  int sensorValue1 = analogRead(A1);
  // print out the value you read:
  Serial.print(sensorValue1);
  //delay(100);        // delay in between reads for stability

  Serial.print("\t");
  
   // read the input on analog pin 0:
  int sensorValue0 = analogRead(A0);
  // print out the value you read:
  Serial.print(sensorValue0);
  delay(100);        // delay in between reads for stability
Serial.println("");
}
