    /* Ardumoto Example Sketch
  by: Jim Lindblom
  date: November 8, 2013
  license: Public domain. Please use, reuse, and modify this 
  sketch!

  Adapted to v20 hardware by: Marshall Taylor
  date: March 31, 2017
  
  Three useful functions are defined:
    setupArdumoto() -- Setup the Ardumoto Shield pins
    driveArdumoto([motor], [direction], [speed]) -- Drive [motor] 
      (0 for A, 1 for B) in [direction] (0 or 1) at a [speed]
      between 0 and 255. It will spin until told to stop.
    stopArdumoto([motor]) -- Stop driving [motor] (0 or 1).

  setupArdumoto() is called in the setup().
  The loop() demonstrates use of the motor driving functions.
*/
#include <Arduino.h>
#include "ir_sensor.h" // Include the IR sensor code

// Clockwise and counter-clockwise definitions.
// Depending on how you wired your motors, you may need to swap.
#define FORWARD  0
#define REVERSE 1

// Motor definitions to make life easier:
#define MOTOR_A 0
#define MOTOR_B 1

// Pin Assignments //
//Default pins:
// #define DIRA 2 // Direction control for motor A
// #define PWMA 3  // PWM control (speed) for motor A
// #define DIRB 4 // Direction control for motor B
// #define PWMB 11 // PWM control (speed) for motor B

////Alternate pins:
#define DIRA 8 // Direction control for motor A
#define PWMA 9 // PWM control (speed) for motor A
#define DIRB 7 // Direction control for motor B
#define PWMB 10 // PWM control (speed) for motor B

void driveArdumoto(byte motor, byte dir, byte spd);
void setupArdumoto();
void stopArdumoto(byte motor);

void forward(byte spd);
void backward(byte spd);
void left(byte spd);
void right(byte spd);
void stop(void);

void setup()
{
  Serial.begin(9600);
  setupArdumoto(); // Set all pins as outputs
  ir_setup();
}

void loop()
{

  int ir_reading = ir_test();

  if (ir_reading == 1) { // If obstacle detected in front
    Serial.println("Obstacle in front! Backing up...");
    backward(100); // Back up
    delay(500); // for half a second
    stop();
    delay(100); // Pause
    right(100); // Turn right
    delay(100); // for a bit
    stop();
    delay(100); // Pause
  } 
  else if (ir_reading == 2) { // If obstacle detected at back
    Serial.println("Obstacle at back! Moving forward...");
    forward(100); // Move forward
    delay(500); // for half a second
    stop();
    delay(100); // Pause
    left(100); // Turn left
    delay(100); // for a bit
    stop();
    delay(100); // Pause
  } 
  else { // No obstacle detected, move forward
    Serial.println("Path clear! Moving right...");
    forward(150); // Move forward
    delay(100); // for half a second
    stop();
    delay(100); // Pause
    left(255); // Turn left
    delay(100); // for a bit
  }

  // forward(255); // Drive forward at max speed
  // delay(300); // for 1 second

  // backward(255); // Drive backward at max speed
  // delay(300); // for 1 second

  // left(255); // Turn left at max speed
  // delay(300); // for 1 second

  // right(255); // Turn right at max speed
  // delay(300); // for 1 second

  // stop(); // Stop motors
  delay(300); // for 1 second
}

void forward(byte spd)
{
  driveArdumoto(MOTOR_A, FORWARD, spd);  // Motor A at max speed.
  driveArdumoto(MOTOR_B, FORWARD, spd);  // Motor B at max speed.
}

void backward(byte spd)
{
  driveArdumoto(MOTOR_A, REVERSE, spd);  // Motor A at max speed.
  driveArdumoto(MOTOR_B, REVERSE, spd);  // Motor B at max speed.
}

void left(byte spd)
{
  driveArdumoto(MOTOR_A, REVERSE, spd);  // Motor A at max speed.
  driveArdumoto(MOTOR_B, FORWARD, spd);  // Motor B at max speed.
}

void right(byte spd)
{
  driveArdumoto(MOTOR_A, FORWARD, spd);  // Motor A at max speed.
  driveArdumoto(MOTOR_B, REVERSE, spd);  // Motor B at max speed.
}

void stop()
{
  stopArdumoto(MOTOR_A);  // STOP motor A 
  stopArdumoto(MOTOR_B);  // STOP motor B 
}

// driveArdumoto drives 'motor' in 'dir' direction at 'spd' speed
void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == MOTOR_A)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  else if (motor == MOTOR_B)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }  
}

// stopArdumoto makes a motor stop
void stopArdumoto(byte motor)
{
  driveArdumoto(motor, 0, 0);
}

// setupArdumoto initialize all pins
void setupArdumoto()
{
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}