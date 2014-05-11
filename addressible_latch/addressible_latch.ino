int cl=2;
int data=3;
int en=4;
int one=5;
int two=6;
int four=7;

void setup(){
  Serial.begin(9600);
  pinMode(cl, OUTPUT);
  pinMode(en, OUTPUT);
  pinMode(one, OUTPUT);
  pinMode(two, OUTPUT);
  pinMode(four, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  digitalWrite(cl, LOW);
  digitalWrite(en, HIGH);
  digitalWrite(one, LOW);
  digitalWrite(two, LOW);
  digitalWrite(four, LOW);
  digitalWrite(data, LOW);
  digitalWrite(cl, HIGH);
  delay(5);
  digitalWrite(cl, LOW);
}

void loop(){
  Serial.println("One ");
  setPinHigh(0);
  delay(1000);
  Serial.println("Two ");
  setPinHigh(1);
  delay(1000);
  Serial.println("Three ");
  setPinHigh(2);
  delay(1000);
  Serial.println("Four ");
  setPinHigh(3);
  delay(1000);
/*  Serial.println("Five ");
  setPinHigh(4);
  delay(1000);
  Serial.println("Six ");
  setPinHigh(5);
  delay(1000);
  Serial.println("Seven ");
  setPinHigh(6);
  delay(1000);
  Serial.println("Eight ");
  setPinHigh(7);
  delay(1000); */
  Serial.println("One LOW");
  setPinLow(0);
  delay(1000);
  Serial.println("Two LOW");
  setPinLow(1);
  delay(1000);
  Serial.println("Three LOW");
  setPinLow(2);
  delay(1000);
  Serial.println("Four LOW");
  setPinLow(3);
  delay(1000);
/*  Serial.println("Five LOW");
  setPinLow(4);
  delay(1000);
  Serial.println("Six LOW");
  setPinLow(5);
  delay(1000);
  Serial.println("Seven LOW");
  setPinLow(6);
  delay(1000);
  Serial.println("Eight LOW");
  setPinLow(7);
  delay(1000);*/
}

void setPinHigh(int pinNumber){
  addressPin(pinNumber);
  digitalWrite(data, HIGH);
  digitalWrite(en, LOW);
  delay(5);
  digitalWrite(en, HIGH);
}

void setPinLow(int pinNumber){
  addressPin(pinNumber);
  digitalWrite(data, LOW);
  digitalWrite(en, LOW);
  delay(5);
  digitalWrite(en, HIGH);
}

void addressPin(int pinNumber){
  if(pinNumber%2 == 1){
    Serial.print(1);
    digitalWrite(one, HIGH);
    pinNumber--;
  }else{
    Serial.print(0);
    digitalWrite(one, LOW);
  }
  pinNumber/=2;
  if(pinNumber%2 == 1){
    Serial.print(1);
    digitalWrite(two, HIGH);
    pinNumber--;
  }else{
    Serial.print(0);
    digitalWrite(two, LOW);
  }
  pinNumber/=2;
  if(pinNumber%2 == 1){
    Serial.print(1);
    digitalWrite(four, HIGH);
    pinNumber--;
  }else{
    Serial.print(0);
    digitalWrite(four, LOW);
  }
  Serial.println();
}
