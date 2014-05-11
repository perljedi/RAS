#include <FourWD.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
FourWD rover(4,7,2,8);

String buffer;
char sep = 58;
byte rSPin  = 5;
byte rSpeed = 0;
byte lSPin  = 6;
byte lSpeed = 0;

void setup()  {
  Serial.begin(9600);
  pinMode(rSPin, OUTPUT);
  pinMode(lSPin, OUTPUT);
  analogWrite(rSPin, rSpeed);
  analogWrite(lSPin, lSpeed);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  buffer="";
}



void loop()                     // run over and over again
{
  int incoming = mySerial.available();  
  while(mySerial.available() > 0)
  {
    char next = (char) mySerial.read();
    if(String(next).equals(":")){
//      Serial.println(buffer);
      enactCommand(buffer);
      buffer="";
    }else{
      buffer = buffer + String(next);
    }
  }
  delay(10);
}

void enactCommand(String command){
  if(command.equals("RL")){
    analogWrite(lSPin, 255);
    analogWrite(rSPin, 255);
    rover.rotateLeft();
  }else if(command.equals("RR")){
    analogWrite(lSPin, 255);
    analogWrite(rSPin, 255);
    rover.rotateRight();
  }else{
    byte ind = command.indexOf("|");
    if(ind > 0){
      int x = command.substring(0, ind++).toInt();
      int y = command.substring(ind).toInt();
      if(x == 0 && y == 0){
        rover.stop();  
      }else{
        int fspeed;
        if(y == 0){
          if(x > 0){
            rover.rotateRight();
            fspeed = map(y, 0, 512, 58, 255);
          }else{
            fspeed = map(y, 0, -512, 58, 255);
            rover.rotateLeft();
          }
        }else{
          if(y < 0){
            rover.forward();
            fspeed = map(y, 0, -512, 58, 255);
            if(fspeed == 256){
               fspeed--;
            } 
          }else if(y > 0){
            rover.reverse();
            fspeed = map(y, 0, 512, 58, 255);
            if(fspeed == 256){
              fspeed--;
            }
          }
          int lspeed, rspeed;
          if(abs(x) > abs(y)){
            fspeed = map(abs(x), 0, 512, 58, 255);
          }
          if(x > 0){
            int portion = map(x, 0, 512, 85,15);
            lspeed = fspeed * portion / 100;
            rspeed = fspeed;
          }else if(x<0){
            int portion = map(x, 0, -512, 85,15);
            rspeed = fspeed * portion / 100;
            lspeed = fspeed;
          }else{
            lspeed = fspeed;
            rspeed = fspeed; 
          }
          Serial.print(lspeed);Serial.print(":");Serial.print(rspeed);Serial.print("|");
          analogWrite(lSPin, lspeed);
          analogWrite(rSPin, rspeed);
        }
      }
    }else{
     rover.stop(); 
    }
  }
}
