int SER_Pin = 5;   //pin 14 on the 75HC595
int RCLK_Pin = 6;  //pin 12 on the 75HC595
int SRCLK_Pin = 7; //pin 11 on the 75HC595

void setup(){
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
  Serial.begin(9600);  
  int registers[] = {LOW,LOW,LOW,
                       LOW,LOW,LOW,
                       LOW,LOW,LOW,
                       LOW,LOW,LOW,
                       LOW,LOW,LOW,LOW};
   writeRegisters(12, registers);
}

void loop(){
  int numOfRegisters = 12;
  for(int i=0; i<=44; i++){
    Serial.println(i);
    int registers[] = {HIGH,HIGH,LOW,
                       LOW,LOW,LOW,
                       LOW,LOW,LOW,
                       LOW,LOW,LOW,
                       LOW,LOW,LOW,LOW};
     registers[1]=HIGH;
     writeRegisters(numOfRegisters, registers);
     delay(100);
  }
}

void writeRegisters(int numOfRegisters, int registers[]){
  digitalWrite(RCLK_Pin, LOW);

  for(int i = numOfRegisters - 1; i >=  0; i--){
    digitalWrite(SRCLK_Pin, LOW);
    digitalWrite(SER_Pin, registers[i]);
    digitalWrite(SRCLK_Pin, HIGH);
  }

  digitalWrite(RCLK_Pin, HIGH);
}  
