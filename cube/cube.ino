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

#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!

// Here you set the number of brightness levels, the update frequency and the number of shift registers.
// These values affect the load of ShiftPWM.
// Choose them wisely and use the PrintInterruptLoad() function to verify your load.
// There is a calculator on my website to estimate the load.

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
int numRegisters = 3;
int numRGBleds = 8;//numRegisters*8/3;
int leds[8][3] = {
 { 1,0,2 },
 { 7,3,15 },
 { 4,8,5 },
 { 16,6,23 },
 { 9,10,20 },
 { 19,18,11 },
 { 12,14,17 },
 { 22,21,13 }
};
int cascade[21][3] = {
  {32,32,255},
  {64,0,224},
  {96,0,192},
  {128,0,160},
  {160,0,128},
  {192,0,96},
  {224,0,64},
  {255,32,32},
  {224,64,0},
  {192,96,0},
  {160,128,0},
  {128,160,0},
  {96,192,0},
  {64,224,0},
  {32,255,32},
  {0,224,64},
  {0,192,96},
  {0,160,128},
  {0,128,160},
  {0,96,192},
  {0,64,224},
};
int rows[8] = {
  2,3,7,6,5,4,10,9  
};
int row=0;
void setup(){
  // Sets the number of 8-bit registers that are used.
  ShiftPWM.SetAmountOfRegisters(numRegisters);

  // SetPinGrouping allows flexibility in LED setup. 
  // If your LED's are connected like this: RRRRGGGGBBBBRRRRGGGGBBBB, use SetPinGrouping(4).
  ShiftPWM.SetPinGrouping(1); //This is the default, but I added here to demonstrate how to use the funtion
  
  ShiftPWM.Start(pwmFrequency,maxBrightness);
  for(int r=0; r<8; r++){
    pinMode(rows[r], OUTPUT);
    digitalWrite(rows[r], LOW);
  }
}

void loop(){
  for(int i=0; i<800; i++){
    for(int c=0;c<8;c++){
      int col = c - int(i/100);
      if(col < 0){
        col+=8;
      }
      int col2 = col-1;
      if(col2 < 0){
        col2+=8;
      }
      int col3 = col-2;
      if(col3 < 0){
        col3+=8;
      }
      setLed(col, 205,255,0);
      setLed(col2, 0,255,255);
      setLed(col3, 255,0,255);
      enableRow(c);
      delay(1);
      disableRow(c);
      setLed(col, 0,0,0);
      setLed(col2, 0,0,0);
      setLed(col3, 0,0,0);
    }
  }
 //rainbow(); 
}

void rainbow(){
  for(int i=0; i < 2199; i++){
    int l = int(i/100);
    enableRow(row);
    for(int e=0; e<8; e++){
      int c = l - e - row;
      if(c < 0){
        c += 21;
      }
      setLed(e, cascade[c][0], cascade[c][1], cascade[c][2]);
    }
    if(i%2 == 0){
      disableRow(row);
      row++;
      if(row > 7){
        row = 0;
      }
    }
  }
}

void enableRow(int row){
  digitalWrite(rows[row], HIGH);
}
void disableRow(int row){
  digitalWrite(rows[row], LOW);
}


void setAll(int red, int green, int blue){
  for(int l = 0; l < 8; l++){
   setLed(l, red, green, blue);
  } 
}

void setLed(int led, int red, int green, int blue){
  ShiftPWM.SetOne(leds[led][0], red);
  ShiftPWM.SetOne(leds[led][1], green);
  ShiftPWM.SetOne(leds[led][2], blue);
}

void rgbLedRainbow(int numRGBLeds, int delayVal, int numCycles, int rainbowWidth){
  // Displays a rainbow spread over a few LED's (numRGBLeds), which shifts in hue. 
  // The rainbow can be wider then the real number of LED's.

  ShiftPWM.SetAll(0);
  for(int cycle=0;cycle<numCycles;cycle++){ // loop through the hue shift a number of times (numCycles)
    for(int colorshift=0;colorshift<360;colorshift++){ // Shift over full color range (like the hue slider in photoshop)
      for(int led=0;led<numRGBLeds;led++){ // loop over all LED's
        int hue = ((led)*360/(rainbowWidth-1)+colorshift)%360; // Set hue from 0 to 360 from first to last led and shift the hue
        ShiftPWM.SetHSV(led, hue, 255, 255); // write the HSV values, with saturation and value at maximum
      }
      delay(delayVal); // this delay value determines the speed of hue shift
    } 
  }  
}
