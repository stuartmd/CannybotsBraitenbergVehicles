//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Cannybots Blue Brain - Braitenberg Vehicle Demonstration
// Based on CannybotRacer by Wayne Keenan
// Authors:  Stuart Dickson
//
// License: http://opensource.org/licenses/MIT
//
// Version:   1.0  -  14.03.2015  -  Initial Version  (stuartmd@hoardingshinies.com)
//////////////////////////////////////////////////////////////////////////////////////////////////

#define BOT_NAME "BraitenbergVehicle1"               // custom name (16 chars max)

#include <RFduinoGZLL.h>
#include <RFduinoBLE.h>

// Simple, global Response Curve
int RESPONSE_CURVE[] = {2, 600, 0, 1024, 170};

// PIN ASSIGNEMENT
// total of 7 pins available of which any 4 can be defined as PWM
// Photocell sensors
#define SENSOR_L_PIN 2
#define SENSOR_R_PIN 4

// Motor Pins
#define MOTOR_A1_PIN 0	// motor direction
#define MOTOR_A2_PIN 6  // motor speed (PWM)
#define MOTOR_B1_PIN 1	// motor direction
#define MOTOR_B2_PIN 5	// motor speed (PWM)


// DEFINITIONS & ITIALISATION
#define MOTOR_MAX_SPEED 250 // max speed (0..255)
#define SENSOR_THRESHOLD_DEFAULT 750 //to

//IR sensor bias
#define SENSOR_L_BIAS 0
#define SENSOR_R_BIAS 0

int SENSORthreshold = SENSOR_THRESHOLD_DEFAULT;

//set initial reading to zero
int SENSORvalL = 0;
int SENSORvalR = 0;

// motor speeds
int lineSpeed = 0;
int speedA = 0;
int speedB = 0;

void setup() {
  Serial.end();

  // Motor pins
  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);
}

void loop() {

  readSensors(); //read photocell sensors

  speedA = apply_response_curve(SENSORvalL, RESPONSE_CURVE);
  speedB = apply_response_curve(SENSORvalR, RESPONSE_CURVE);

  motorSpeed(speedA, speedB);
}


// READ & PROCESS VALUES FROM PHOTOCELLS
void readSensors() {
  SENSORvalL = analogRead(SENSOR_L_PIN) + SENSOR_L_BIAS; //left looking from behind
  if (SENSORvalL >= 1000)
    SENSORvalL = 1000;

  SENSORvalR = analogRead(SENSOR_R_PIN) + SENSOR_R_BIAS; //centre
  if (SENSORvalR >= 1000)
    SENSORvalR = 1000;

}

// MOTOR DRIVER
void motorSpeed(int _speedA, int _speedB) {

  _speedA = constrain(_speedA, -MOTOR_MAX_SPEED, MOTOR_MAX_SPEED);
  _speedB = constrain(_speedB, -MOTOR_MAX_SPEED, MOTOR_MAX_SPEED);

  digitalWrite(MOTOR_A1_PIN, _speedA >= 0 ? HIGH : LOW) ;
  analogWrite (MOTOR_A2_PIN, abs(_speedA));

  digitalWrite(MOTOR_B1_PIN, _speedB >= 0 ? HIGH : LOW);
  analogWrite (MOTOR_B2_PIN, abs(_speedB));
}
