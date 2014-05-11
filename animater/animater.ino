/************************************************************************************************************************************
 * ShiftPWM blocking RGB fades example, (c) Elco Jacobs, updated August 2012.
 *
 * ShiftPWM blocking RGB fades example. This example uses simple delay loops to create fades.
 * If you want to change the fading mode based on inputs (sensors, buttons, serial), use the non-blocking example as a starting point.
 * Please go to www.elcojacobs.com/shiftpwm for documentation, fuction reference and schematics.
 * If you want to use ShiftPWM with LED strips or high power LED's, visit the shop for boards.
 ************************************************************************************************************************************/
 
// ShiftPWM uses timer1 by default. To use a different timer, before '#include <ShiftPWM.h>', add
// #define SHIFTPWM_USE_TIMER2  // for Arduino Uno and earlier (Atmega328)
// #define SHIFTPWM_USE_TIMER3  // for Arduino Micro/Leonardo (Atmega32u4)

// Clock and data pins are pins from the hardware SPI, you cannot choose them yourself if you use the hardware SPI.
// Data pin is MOSI (Uno and earlier: 11, Leonardo: ICSP 4, Mega: 51, Teensy 2.0: 2, Teensy 2.0++: 22) 
// Clock pin is SCK (Uno and earlier: 13, Leonardo: ICSP 3, Mega: 52, Teensy 2.0: 1, Teensy 2.0++: 21)

// You can choose the latch pin yourself.
const int ShiftPWM_latchPin=8;

// ** uncomment this part to NOT use the SPI port and change the pin numbers. This is 2.5x slower **
// #define SHIFTPWM_NOSPI
// const int ShiftPWM_dataPin = 11;
// const int ShiftPWM_clockPin = 13;


// If your LED's turn on if the pin is low, set this to true, otherwise set it to false.
const bool ShiftPWM_invertOutputs = true; 

// You can enable the option below to shift the PWM phase of each shift register by 8 compared to the previous.
// This will slightly increase the interrupt load, but will prevent all PWM signals from becoming high at the same time.
// This will be a bit easier on your power supply, because the current peaks are distributed.
const bool ShiftPWM_balanceLoad = false;

//#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!

// Here you set the number of brightness levels, the update frequency and the number of shift registers.
// These values affect the load of ShiftPWM.
// Choose them wisely and use the PrintInterruptLoad() function to verify your load.
// There is a calculator on my website to estimate the load.

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
int numRegisters = 3;
int numRGBleds = 8;//numRegisters*8/3;
byte leds[8][3] = {
 { 1,0,2 },
 { 7,3,15 },
 { 4,8,5 },
 { 16,6,23 },
 { 9,10,20 },
 { 19,18,11 },
 { 12,14,17 },
 { 22,21,13 }
};
byte rows[8] = {
  2,3,7,6,5,4,10,9  
};


  char ca[] = {
    8, 
      2,2, 255,1,1,
      2,2, 255,1,1,
      2,2, 255,1,1,
      2,2, 255,1,1,
      2,2, 255,1,1,
      2,2, 255,1,1,
      2,2, 255,1,1,
      2,2, 255,1,1,
//----------------------
      2,2, 255,1,1,
      2,2, 255,1,1,
      2,3, 255,1,1,
      2,3, 255,1,1,
      2,4, 255,1,1,
      2,4, 255,1,1,
      2,5, 255,1,1,
      2,5, 255,1,1,
//----------------------
      2,2, 255,1,1,
      2,3, 255,1,1,
      2,4, 255,1,1,
      2,5, 255,1,1,
      2,6, 255,1,1,
      2,7, 255,1,1,
      2,8, 255,1,1,
      2,9, 255,1,1,
//----------------------
      2,6, 255,1,1,
      2,6, 255,1,1,
      2,7, 255,1,1,
      2,7, 255,1,1,
      2,8, 255,1,1,
      2,8, 255,1,1,
      2,9, 255,1,1,
      2,9, 255,1,1,
//----------------------
      2,9, 255,1,1,
      2,9, 255,1,1,
      2,9, 255,1,1,
      2,9, 255,1,1,
      2,9, 255,1,1,
      2,9, 255,1,1,
      2,9, 255,1,1,
      2,9, 255,1,1,
//----------------------
      2,6, 255,1,1,
      2,6, 255,1,1,
      2,7, 255,1,1,
      2,7, 255,1,1,
      2,8, 255,1,1,
      2,8, 255,1,1,
      2,9, 255,1,1,
      2,9, 255,1,1,
//----------------------
      2,2, 255,1,1,
      2,3, 255,1,1,
      2,4, 255,1,1,
      2,5, 255,1,1,
      2,6, 255,1,1,
      2,7, 255,1,1,
      2,8, 255,1,1,
      2,9, 255,1,1,
//----------------------
      2,2, 255,1,1,
      2,2, 255,1,1,
      2,3, 255,1,1,
      2,3, 255,1,1,
      2,4, 255,1,1,
      2,4, 255,1,1,
      2,5, 255,1,1,
      2,5, 255,1,1
  };
String myString = String(ca);

void setup(){
  Serial.begin(115200);
//  myString = String(ca);
  // Sets the number of 8-bit registers that are used.
//  ShiftPWM.SetAmountOfRegisters(numRegisters);

  // SetPinGrouping allows flexibility in LED setup. 
  // If your LED's are connected like this: RRRRGGGGBBBBRRRRGGGGBBBB, use SetPinGrouping(4).
//  ShiftPWM.SetPinGrouping(1); //This is the default, but I added here to demonstrate how to use the funtion
  
//  ShiftPWM.Start(pwmFrequency,maxBrightness);
  for(int r=0; r<8; r++){
    pinMode(rows[r], OUTPUT);
    digitalWrite(rows[r], LOW);
  }
}

void loop(){
  //delay(1000);
  //return;
  byte numberOfFrames = myString.charAt(0) - 1;
  long offset = 1;  
  byte duration=1;
  for(byte f=1; f<=numberOfFrames; f++){
    long frameStart = offset;
    for(byte r=0; r<8; r++){
      byte rowLedCount = myString.charAt(offset++)--;
      offset+= 4*rowLedCount;
    }
    String frame = myString.substring(frameStart, offset);
    Serial.print("calling display from: ");
    Serial.print(frameStart);
    Serial.print(" to ");
    Serial.println(offset);
    displayFrame(duration, frame);
    offset++;
  }
//  for(int f=0; f<4; f++){
//    displayFrame(duration, framed[f]);
//  }
}

void displayFrame(byte duration,String frame){
  byte offset = 0;
  byte pixels[] = {};
  for(byte r=0; r<8; r++){
    pixels[offset] = myString.charAt(offset);
    byte rowByteCount = pixels[offset++]*4;
    for(byte i=0; i<rowByteCount; i++){
      pixels[offset] = myString.charAt(offset++);
      pixels[offset] = myString.charAt(offset++);
      pixels[offset] = myString.charAt(offset++);       
      pixels[offset] = myString.charAt(offset++);
    }
  }
  Serial.println("Showing frame");
  for(byte i=0; i<duration; i++){
    Serial.println("loop");
    offset=0;
    for(byte c=0;c<1;c++){
      byte rowLedCount = pixels[offset++];
      Serial.println(rowLedCount);
/*      for(byte l=1; l<=rowLedCount; l++){
//        Serial.println("L=");
//        Serial.print(l);
//        Serial.println(".");
        //Serial.println(int(pixels[offset++]));
        //setLed(pixels[offset++], pixels[offset++],pixels[offset++],pixels[offset++]);
      }*/
      enableRow(c);
      delay(800);
      disableRow(c);
      setAll(0,0,0);
    }
  }  
  
}

void enableRow(byte row){
  digitalWrite(rows[row], HIGH);
}
void disableRow(byte row){
  digitalWrite(rows[row], LOW);
}


void setAll(byte red, byte green, byte blue){
  for(byte l = 0; l < 8; l++){
   setLed(l, red, green, blue);
  }
}

void setLed(byte led, byte red, byte green, byte blue){
  Serial.print("Setting ");
  Serial.print(led);Serial.println(": ");
/*  Serial.print(red);Serial.print(",");
  Serial.print(green);Serial.print(",");
  Serial.print(blue);Serial.println(",");*/
//  ShiftPWM.SetOne(leds[led][0], red);
//  ShiftPWM.SetOne(leds[led][1], green);
//  ShiftPWM.SetOne(leds[led][2], blue);
}
