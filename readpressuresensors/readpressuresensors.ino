// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 5:
  int sensorValue5 = analogRead(A0);
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
  Serial.println("");
  
}
