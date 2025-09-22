#include <Arduino.h>

#define TRIG_PIN 9
#define ECHO_PIN 2

long duration;
float distance_cm;

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


/// @brief Arduino setup function
void setup()
{
  motorsInit();
  ultrasonicSensorInit();

  pinMode(ONBOARD_LED, OUTPUT);
  digitalWrite(ONBOARD_LED, HIGH); // Show peripherals initialized

  Serial.begin(9600); // Start serial communication
  Serial.println("Starting main codebase here...");
}


/// @brief Arduino main loop function
void loop()
{
  // moveBackward(64); // Move backward at speed 64
  // moveForward(64);  // Move forward at speed 64
  
  // Get distance by polling
  float distance = getDistance();

  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");

  // Threshold check
  if (distance <= threshold) {
    thresholdTriggered = true;
  } else {
    thresholdTriggered = false;
  }

  // Act on threshold
  if (thresholdTriggered) {
    digitalWrite(LED_BUILTIN, HIGH); // LED ON when distance <= 30 cm
    Serial.println("⚠️ Threshold reached!");
    moveForward(64); // scale motor speed
  } else {
    digitalWrite(LED_BUILTIN, LOW); // LED OFF otherwise
    moveBackward(64);
  }

  delay(100); // Wait before next measurement
}


// drive drives 'motor' in 'dir' direction at 'spd' speed
void drive(byte motor, byte dir, byte spd)
{
  if (motor == MOTOR_RIGHT) {
    digitalWrite(DIR_MOTOR_RIGHT, dir);
    analogWrite(PWM_MOTOR_RIGHT, spd);
  }
  else if (motor == MOTOR_LEFT) {
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
  stopDrive(MOTOR_LEFT);   // STOP left motor 
}


// initialize ultrasonic sensor
void ultrasonicSensorInit(void)
{
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}


// get distance from ultrasonic sensor (polling mode)
float getDistance(void)
{
  // Clear the trig pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send a 10 µs HIGH pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo pin duration using polling
  duration = pulseIn(ECHO_PIN, HIGH, 30000UL); // timeout = 30 ms (~5 m range)

  // Convert to distance (cm)
  float calculated_distance = (duration * 0.0343) / 2;
  return calculated_distance;
}
