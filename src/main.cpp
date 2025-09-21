#include <Arduino.h>

// #define TRIG_PIN 9
// #define ECHO_PIN 10

// long duration;
// float distance_cm;

// void setup() {
//   Serial.begin(9600);      // Start serial communication
//   pinMode(TRIG_PIN, OUTPUT);
//   pinMode(ECHO_PIN, INPUT);
// }

  /* Ardumoto Example Sketch
  by: Jim Lindblom`
  date: November 8, 2013
  license: Public domain. Please use, reuse, and modify this 
  sketch!

  Adapted to v20 hardware by: Marshall Taylor
  date: March 31, 2017

  Three useful functions are defined:
    setupArdumoto() -- Setup the Ardumoto Shield pins
    drive([motor], [direction], [speed]) -- Drive [motor] 
      (0 for A, 1 for B) in [direction] (0 or 1) at a [speed]
      between 0 and 255. It will spin until told to stop.
    stopDrive([motor]) -- Stop driving [motor] (0 or 1).

  setupArdumoto() is called in the setup().
  The loop() demonstrates use of the motor driving functions.
*/

// Clockwise and counter-clockwise definitions.
// Depending on how you wired your motors, you may need to swap.
#define FORWARD  0
#define REVERSE 1

// Motor definitions to make life easier:
#define MOTOR_RIGHT 0
#define MOTOR_LEFT 1

// Pin Assignments //
#define DIR_MOTOR_RIGHT 2  // Direction control for motor RIGHT
#define PWM_MOTOR_RIGHT 3  // PWM control (speed) for motor RIGHT

#define DIR_MOTOR_LEFT 4  // Direction control for motor LEFT
#define PWM_MOTOR_LEFT 11 // PWM control (speed) for motor LEFT

#define ONBOARD_LED 13 // On-board LED

void setupArdumoto(void);
void drive(byte motor, byte dir, byte spd);
void stopDrive(byte motor);

void setup()
{
  setupArdumoto(); // Set all pins as outputs
  digitalWrite(ONBOARD_LED, HIGH); // Turn on the on-board LED to show we're running
  Serial.begin(9600); // Start serial communication at 9600 baud
  Serial.println("Ardumoto Example Sketch");
}

void loop()
{
  // Drive motor A (and only motor A) at various speeds, then stop.
  drive(MOTOR_RIGHT, REVERSE, 255); // Set motor A to REVERSE at max
  delay(1000);  // Motor A will spin as set for 1 second
  drive(MOTOR_RIGHT, FORWARD, 127);  // Set motor A to FORWARD at half
  delay(1000);  // Motor A will keep trucking for 1 second 
  stopDrive(MOTOR_RIGHT);  // STOP motor A 

  // Drive motor B (and only motor B) at various speeds, then stop.
  drive(MOTOR_LEFT, REVERSE, 255); // Set motor B to REVERSE at max
  delay(1000);  // Motor B will spin as set for 1 second
  drive(MOTOR_LEFT, FORWARD, 127);  // Set motor B to FORWARD at half
  delay(1000);  // Motor B will keep trucking for 1 second
  stopDrive(MOTOR_LEFT);  // STOP motor B 

  // Drive both
  drive(MOTOR_RIGHT, FORWARD, 255);  // Motor A at max speed.
  // drive(MOTOR_LEFT, FORWARD, 255);  // Motor B at max speed.
  // delay(1000);  // Drive forward for a second
  // // Now go backwards at half that speed:
  // drive(MOTOR_RIGHT, REVERSE, 127);  // Motor A at max speed.
  // drive(MOTOR_LEFT, REVERSE, 127);  // Motor B at max speed.
  // delay(1000);  // Drive forward for a second

  // // Now spin in place!
  // drive(MOTOR_RIGHT, FORWARD, 255);  // Motor A at max speed.
  // drive(MOTOR_LEFT, REVERSE, 255);  // Motor B at max speed.
  // delay(2000);  // Drive forward for a second
  // stopDrive(MOTOR_RIGHT);  // STOP motor A 
  // stopDrive(MOTOR_LEFT);  // STOP motor B 

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


// stopDrive makes a motor stop
void stopDrive(byte motor)
{
  drive(motor, 0, 0);
}

// setupArdumoto initialize all pins
void setupArdumoto()
{
  // All pins should be setup as outputs:
  pinMode(PWM_MOTOR_RIGHT, OUTPUT);
  pinMode(PWM_MOTOR_LEFT, OUTPUT);
  pinMode(DIR_MOTOR_RIGHT, OUTPUT);
  pinMode(DIR_MOTOR_LEFT, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWM_MOTOR_RIGHT, LOW);
  digitalWrite(PWM_MOTOR_LEFT, LOW);
  digitalWrite(DIR_MOTOR_RIGHT, LOW);
  digitalWrite(DIR_MOTOR_LEFT, LOW);
}







// void distance_calculation(void)
// {
//   // Clear the trig pin
//   delayMicroseconds(2);
//   digitalWrite(TRIG_PIN, LOW);
//   delayMicroseconds(2);

//   // Send a 10 µs HIGH pulse
//   digitalWrite(TRIG_PIN, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(TRIG_PIN, LOW);

//   // Read echo pin
//   duration = pulseIn(ECHO_PIN, HIGH);

//   // Convert to distance (cm)
//   distance_cm = (duration * 0.0343) / 2;

//   // Print result
//   Serial.print("Distance: ");
//   Serial.print(distance_cm);
//   Serial.println(" cm");

//   delay(500);
// }
