#include <FourWD.h>

const int enable=8;
const int rf=2;
const int rr=3;
const int lf=4;
const int lr=5;
FourWD rover(rf,rr,lf,lr);

void setup() {
  pinMode(enable, OUTPUT);
  digitalWrite(enable, LOW);
  Serial.begin(9600); 
}

void loop() {
  delay(1000);
  rover.forward();
  delay(1000);
  rover.reverse();
  delay(1000);
  rover.turnLeft();
  delay(1000);
  rover.turnRight();
  delay(1000);
  rover.rotateLeft();
  delay(1000);
  rover.rotateRight();
}

