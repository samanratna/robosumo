#include <Arduino.h>

#define TRIG_PIN 9
#define ECHO_PIN 2

long duration;
float distance_cm;

volatile unsigned long startTime = 0;
volatile unsigned long endTime = 0;
volatile bool measurementDone = false;

const int threshold = 30; // cm
bool thresholdTriggered = false;

// Clockwise and counter-clockwise definitions
#define FORWARD  0
#define REVERSE 1

// Motor definitions
#define MOTOR_RIGHT 1
#define MOTOR_LEFT 0

// Pin Assignments //
#define DIR_MOTOR_RIGHT 4  // Direction control for motor RIGHT
#define PWM_MOTOR_RIGHT 11  // PWM control (speed) for motor RIGHT

#define DIR_MOTOR_LEFT 10  // Direction control for motor LEFT
#define PWM_MOTOR_LEFT 3 // PWM control (speed) for motor LEFT

#define ONBOARD_LED 13 // On-board LED


// Function Prototypes
void motorsInit(void);
void ultrasonicSensorInit(void);
void drive(byte motor, byte dir, byte spd);
void stopDrive(byte motor);
void rotateRight(byte spd);
void rotateLeft(byte spd);
void moveForward(byte spd);
void moveBackward(byte spd);
float getDistance(void);
void echoISR(void);


/// @brief Arduino setup function
void setup()
{
  motorsInit();
  ultrasonicSensorInit();

  digitalWrite(ONBOARD_LED, HIGH); // Turn on the on-board LED to show all the peripherals are initialized

  Serial.begin(9600); // Start serial communication at 9600 baud

  // Attach interrupt on ECHO pin
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), echoISR, CHANGE);

  Serial.println("Starting main codebase here...");
}


/// @brief Arduino main loop function
void loop()
{
  // Drive motor A (and only motor A) at various speeds, then stop.
  // rotateRight(64);
  // delay(2000);
  // rotateLeft(64);
  // delay(2000);
  // moveForward(64);
  // delay(2000);
  // moveBackward(64);
  // delay(2000);
  // stopDrive(MOTOR_RIGHT);
  // stopDrive(MOTOR_LEFT);
  // delay(1000);

  // getObstacle = findObstacle();

  // if (getObstacle)
  // {
  //   moveForward(64); // Move forward if no obstacle is detected
  // }

  // float calculated_distance;


  // Clear the trig pin
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send a 10 µs HIGH pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  delay(100); // wait before next measurement
  // Serial.println("Measuring distance...");

  if (measurementDone) {
    // Serial.println("Measurement done, processing...");
    unsigned long duration = endTime - startTime;
    int distance = duration * 0.034 / 2;  // convert to cm

    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance <= threshold) {
      thresholdTriggered = true;
    } else {
      thresholdTriggered = false;
    }


    /*
    30 -> 127
    0 -> 64
    */
    // Act on threshold
    if (thresholdTriggered) {
      // Serial.println("Threshold triggered action!");
      digitalWrite(LED_BUILTIN, HIGH); // LED ON when distance <= 30 cm
      Serial.println("⚠️ Threshold reached!");
      moveForward(64 + (2*distance));
    } else {
      digitalWrite(LED_BUILTIN, LOW); // LED OFF otherwise
      stopDrive(MOTOR_RIGHT);
      stopDrive(MOTOR_LEFT);
    }

    measurementDone = false; // reset flag
  } else {
    Serial.println("Waiting for measurement to complete...");
  }


}


// drive drives 'motor' in 'dir' direction at 'spd' speed
void drive(byte motor, byte dir, byte spd)
{
  if (motor == MOTOR_RIGHT)
  {
    digitalWrite(DIR_MOTOR_RIGHT, dir);
    analogWrite(PWM_MOTOR_RIGHT, spd);
  }
  else if (motor == MOTOR_LEFT)
  {
    digitalWrite(DIR_MOTOR_LEFT, dir);
    analogWrite(PWM_MOTOR_LEFT, spd);
  }  
}


//  motor stop
void stopDrive(byte motor)
{
  drive(motor, 0, 0);
}


// rotate right
void rotateRight(byte spd)
{
  drive(MOTOR_RIGHT, REVERSE, spd);
  drive(MOTOR_LEFT, FORWARD, spd);
}


// rotate left
void rotateLeft(byte spd)
{
  drive(MOTOR_RIGHT, FORWARD, spd);
  drive(MOTOR_LEFT, REVERSE, spd);
}


// forward
void moveForward(byte spd)
{
  drive(MOTOR_RIGHT, FORWARD, spd);
  drive(MOTOR_LEFT, FORWARD, spd);
}


// backward
void moveBackward(byte spd)
{
  drive(MOTOR_RIGHT, REVERSE, spd);
  drive(MOTOR_LEFT, REVERSE, spd);
}


// motorsInit initialize all pins
void motorsInit()
{
  // All pins should be setup as outputs:
  pinMode(PWM_MOTOR_RIGHT, OUTPUT);
  pinMode(DIR_MOTOR_RIGHT, OUTPUT);
  
  pinMode(PWM_MOTOR_LEFT, OUTPUT);
  pinMode(DIR_MOTOR_LEFT, OUTPUT);

  stopDrive(MOTOR_RIGHT);  // STOP right motor
  stopDrive(MOTOR_LEFT);  // STOP left motor 

}


// initialize ultrasonic sensor
void ultrasonicSensorInit(void)
{
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}


// get distance from ultrasonic sensor
float getDistance(void)
{
  float calculated_distance;
  // Clear the trig pin
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send a 10 µs HIGH pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo pin
  duration = pulseIn(ECHO_PIN, HIGH);

  // Convert to distance (cm)
  calculated_distance = (duration * 0.0343) / 2;

  delay(50);

  return calculated_distance;
}


// Interrupt Service Routine for echo pin
void echoISR() {
  // Serial.println("Echo HIGH detected, starting timer...");
  if (digitalRead(ECHO_PIN) == HIGH) {
    startTime = micros();   // echo pulse started
  } else {
    endTime = micros();     // echo pulse ended
    measurementDone = true; // signal main loop
  }
}