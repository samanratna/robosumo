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
// #include "distance_sensor.h"

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

// delay variations
int delay_after_movement = 200; // Time (in milliseconds) to drive motors in loop()
int delay_after_stop = 200; // Time (in milliseconds) to drive motors in loop()

// speed variations
int speedSet = 130; // Speed setting (0-255) for motors in loop()

// ir global variables
byte ir_bit_pattern;

void driveArdumoto(byte motor, byte dir, byte spd);
void setupArdumoto();
void stopArdumoto(byte motor);

void test_motors(void);
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
  // ultrasonic_setup();
}

void loop()
{
  ir_test();
  // delay(500);
  byte ir_bit_pattern = start_ir_reading();

  // cases for front movement
  if (ir_bit_pattern == 0b1100 || ir_bit_pattern == 0b1101 || ir_bit_pattern == 0b1110) {
    // Opponent detected in front
    forward(speedSet + 40);
    delay(delay_after_movement);
    stop();
    delay(delay_after_stop);
  }

  // cases for back movement
  else if (ir_bit_pattern == 0b0011 || ir_bit_pattern == 0b0111 || ir_bit_pattern == 0b1011) {
    // Opponent detected in back
    backward(speedSet);
    delay(delay_after_movement+30);
    stop();
    delay(delay_after_stop);
  }

  // cases for right movement
  else if (ir_bit_pattern == 0b0101 || ir_bit_pattern == 0b0110 || ir_bit_pattern == 0b1001) {
    // Opponent detected on right
    right(speedSet);
    delay(delay_after_movement);
    stop();
    delay(delay_after_stop);
  }

  // cases for left movement
  else if (ir_bit_pattern == 0 || ir_bit_pattern == 0b1010) {
    // Opponent detected on left
    left(speedSet);
    delay(delay_after_movement);
    stop();
    delay(delay_after_stop);
  }

  // cases for left + forward movement
  else if (ir_bit_pattern == 0b0010 || ir_bit_pattern == 0b1000) {
    // Opponent detected on left + front
    left(speedSet);
    delay(delay_after_movement);
    forward(speedSet);
    delay(delay_after_movement);
    stop();
    delay(delay_after_stop);
  }

  // cases for right + forward movement
  else if (ir_bit_pattern == 0b0001 || ir_bit_pattern == 0b0100) {
    // Opponent detected on right + front
    right(speedSet);
    delay(delay_after_movement);
    forward(speedSet);
    delay(delay_after_movement);
    stop();
    delay(delay_after_stop);
  }

  // case to find the opponent if no IR signal is detected
  else if (ir_bit_pattern == 0b1111) {
    // No opponent detected
    right(speedSet);
    delay(delay_after_movement);
    forward(speedSet);
    delay(delay_after_movement);
    // forward(speedSet);
    // delay(delay_after_movement - 50);
    // left(speedSet);
    // delay(delay_after_movement);
    // stop();
    // delay(delay_after_stop);
  }

}


// Test driving each motor individually
void test_motors()
{
  forward(speedSet);
  delay(delay_after_movement);
  stop();
  delay(delay_after_stop);

  backward(speedSet);
  delay(delay_after_movement);
  stop();
  delay(delay_after_stop);

  left(speedSet);
  delay(delay_after_movement);
  stop();
  delay(delay_after_stop);

  right(speedSet);
  delay(delay_after_movement);
  stop();
  delay(delay_after_stop);
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