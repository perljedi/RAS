#include <FourWD.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_9DOF.h>

/* Assign a unique ID to the sensors */
Adafruit_9DOF                dof   = Adafruit_9DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
FourWD rover(3,4,5,6);

void setup(){
  Serial.begin(115200);
  initSensors();
  delay(500);
  getHeading();
}

void loop(){
  float start_heading = getHeading();
  float current_heading = getHeading();
  float headingMod = start_heading - current_heading;
  
  while(abs(headingMod) < 90){
    rover.turnLeft();
    current_heading = getHeading();
    headingMod = start_heading - current_heading;
    Serial.print(start_heading);
    Serial.print(" - ");
    Serial.print(current_heading);
    Serial.print(" = ");
    Serial.println(headingMod);
  }
  rover.stop();
  Serial.println("Complete");
  delay(3000);
  start_heading = getHeading();
  current_heading = getHeading();
  headingMod = start_heading - current_heading;
  
  while(abs(headingMod) < 90){
    rover.turnRight();
    current_heading = getHeading();
    headingMod = start_heading - current_heading;
    Serial.print(start_heading);
    Serial.print(" - ");
    Serial.print(current_heading);
    Serial.print(" = ");
    Serial.println(headingMod);
  }
  rover.stop();
  Serial.println("Complete");
  delay(3000);
}

void initSensors()
{
  if(!accel.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
    while(1);
  }
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
}

float getHeading(){
  sensors_event_t accel_event;
  sensors_event_t mag_event;
  sensors_vec_t   orientation;

  accel.getEvent(&accel_event);
  dof.accelGetOrientation(&accel_event, &orientation);
  mag.getEvent(&mag_event);
  dof.magTiltCompensation(SENSOR_AXIS_Z, &mag_event, &accel_event);
  dof.magGetOrientation(SENSOR_AXIS_Z, &mag_event, &orientation);

  return orientation.heading;
}
