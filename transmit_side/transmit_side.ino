
void setup()  {
  Serial.begin(9600);
  // set the data rate for the SoftwareSerial port
  Serial1.begin(9600);
}



void loop()                     // run over and over again
{
  Serial1.println("hi there");
  delay(1500);
}
