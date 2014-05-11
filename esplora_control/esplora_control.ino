#include <Esplora.h>
int centerX;
int centerY;

void setup()
{
  Serial.begin(9600);       // initialize serial communication with your computer
  centerX = Esplora.readJoystickX();        // read the joystick's X position
  centerY = Esplora.readJoystickY();        // read the joystick's Y position
  Serial1.begin(9600);
}

void loop()
{
if(! Esplora.readButton(SWITCH_LEFT)){
    Serial1.print("RL:");
  }else if(! Esplora.readButton(SWITCH_RIGHT)){
    Serial1.print("RR:"); 
  }else{
    int xValue, yValue;  
    if(! Esplora.readButton(SWITCH_UP)){
      xValue = 0;
      yValue = -512;
    }else   if(! Esplora.readButton(SWITCH_DOWN)){
      xValue = 0;
      yValue = 512;
    }else {
      xValue = Esplora.readJoystickX() - centerX;        // read the joystick's X position
      yValue = Esplora.readJoystickY() - centerY;        // read the joystick's Y position
    }
    if(xValue == 0){
      Serial1.print("N");                        // print the X value
    }else {
      Serial1.print(xValue);
    }
    Serial1.print("|");                       // print a tab character and a label for the Y value
    if(yValue == 0){
      Serial1.print("N");                        // print the X value
    }else{
      Serial1.print(yValue);
    }
    Serial1.print(':');
  }
  Serial1.flush();
  delay(10);                                  // a short delay before moving again
}
