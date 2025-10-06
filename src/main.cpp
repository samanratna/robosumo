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
#include "distance_sensor.h"

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

void loop() {
  int distance_reading = ultrasonic_checkObstacle();
  int ir_reading = ir_test();

  // === Step 1: If ultrasonic detects obstacle ===
  if (distance_reading != NONE) {
    switch (distance_reading) {
      case OBSTACLE_FRONT:
        Serial.println("Ultrasonic: Target in FRONT → Moving forward...");
        while (true) {
          forward(200);
          delay(100);

          // Continuously check IR sensors while approaching
          int ir_check = ir_test();
          if (ir_check == IR_FORWARD) {
            Serial.println("IR: Close obstacle detected at FRONT → Stop!");
            backward(100);
            delay(100);
            break;
          }

          delay(50);
        }
        break;

      case OBSTACLE_BACK:
        Serial.println("Ultrasonic: Target in BACK → Moving backward...");
        while (true) {
          backward(200);
          delay(100);
          int ir_check = ir_test();
          if (ir_check == IR_BACKWARD) {
            Serial.println("IR: Close obstacle detected at BACK → Stop!");
            forward(100);
            delay(100);
            break;
          }
          delay(50);
        }
        break;

      case OBSTACLE_LEFT:
        Serial.println("Ultrasonic: Target on LEFT → Moving left...");
        while (true) {
          left(200);
          delay(100);
          int ir_check = ir_test();
          if (ir_check == IR_LEFT) {
            Serial.println("IR: Close obstacle detected on LEFT → Stop!");
            right(255);
            delay(100);
            forward(100);
            delay(100);
            break;
          }
          delay(50);
        }
        break;

      case OBSTACLE_RIGHT:
        Serial.println("Ultrasonic: Target on RIGHT → Moving right...");
        while (true) {
          right(200);
          delay(100);
          int ir_check = ir_test();
          if (ir_check == IR_RIGHT) {
            Serial.println("IR: Close obstacle detected on RIGHT → Stop!");
            backward(100);
            break;
          }
          delay(50);
        }
        break;
    }
  }

  // === Step 2: If no ultrasonic detection, scan with IR ===
  else if (ir_reading != DEFAULT) {

    if (ir_reading == IR_BACKWARD) {
      Serial.println("Obstacle detected in back!");
      forward(100);
    } 
    else if (ir_reading == IR_FORWARD) {
      Serial.println("Obstacle detected at front!");
      backward(100);
    } 
    else if (ir_reading == IR_LEFT) {
      Serial.println("Obstacle detected on the left!");
      right(255);
      delay(100);
      forward(100);
      delay(100);
    }
    else if (ir_reading == IR_RIGHT) {
      Serial.println("Obstacle detected on the right!");
      backward(100);
    } else {
      Serial.println("Unknown IR reading.");
      right(255);
      delay(100);
      forward(100);
      delay(100);
    }




    // switch (ir_reading) {
    //   case IR_FORWARD:
    //     Serial.println("IR: Obstacle at FRONT → Moving forward!");
    //     backward(200);
    //     break;

    //   case IR_BACKWARD:
    //     Serial.println("IR: Obstacle at BACK → Moving backward!");
    //     forward(200);
    //     break;

    //   case IR_LEFT:
    //     Serial.println("IR: Obstacle on LEFT → Turning left!");
    //     right(200);
    //     break;

    //   case IR_RIGHT:
    //     Serial.println("IR: Obstacle on RIGHT → Turning right!");
    //     left(200);
    //     break;
    // }
  }

  // === Step 3: No detections at all → keep scanning ===
  else {
    Serial.println("No obstacle detected — rotating to find one...");
    right(150);
  }
  delay(100);
}


// void loop()
// {

//   int ir_reading = ir_test();

//   if (ir_reading == DEFAULT) {
//     Serial.println("No obstacle detected.");
//     right(255);
//     delay(100);
//     forward(100);
//     delay(100);
//   } 
//   else if (ir_reading == IR_BACKWARD) {
//     Serial.println("Obstacle detected in back!");
//     forward(100);
//   } 
//   else if (ir_reading == IR_FORWARD) {
//     Serial.println("Obstacle detected at front!");
//     backward(100);
//   } 
//   else if (ir_reading == IR_LEFT) {
//     Serial.println("Obstacle detected on the left!");
//     right(255);
//     delay(100);
//     forward(100);
//     delay(100);
//   }
//   else if (ir_reading == IR_RIGHT) {
//     Serial.println("Obstacle detected on the right!");
//     backward(100);
//   } else {
//     Serial.println("Unknown IR reading.");
//     right(255);
//     delay(100);
//     forward(100);
//     delay(100);
//   }


//   int distance_reading = ultrasonic_checkObstacle();


// }

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