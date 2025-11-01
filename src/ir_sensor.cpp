#include "ir_sensor.h"

// Movement codes
// #define DEFAULT 0
// #define IR_FORWARD 1
// #define IR_BACKWARD 2
// #define IR_RIGHT_FORWARD 3
// #define IR_LEFT_FORWARD 4

int reading_front_right;
int reading_front_left;
int reading_back_right;
int reading_back_left;


void ir_setup() {
  // If sensors are digital type, set them as INPUT
  pinMode(IR_PIN_FRONT_RIGHT, INPUT);
  pinMode(IR_PIN_FRONT_LEFT, INPUT);
  pinMode(IR_PIN_BACK_RIGHT, INPUT);
  pinMode(IR_PIN_BACK_LEFT, INPUT);
}

void ir_read() {
  int reading_front_right = digitalRead(IR_PIN_FRONT_RIGHT);
  int reading_front_left  = digitalRead(IR_PIN_FRONT_LEFT);
  int reading_back_right = digitalRead(IR_PIN_BACK_RIGHT);
  int reading_back_left = digitalRead(IR_PIN_BACK_LEFT);
}

int ir_test() {

  // Serial.print(reading_front_left); Serial.print("------"); Serial.print(reading_front_right);
  // Serial.println("");
  // Serial.print(" || ");
  // Serial.print(" || ");
  // Serial.println("");
  // Serial.print(reading_back_left); Serial.print("------"); Serial.print(reading_back_right);
  // Serial.println("");
  // Serial.println("");

  // case (reading_front_left + reading_front_right + reading_back_left + reading_back_right) {
  //   case 0:
  //     Serial.println("No line detected");
  //     return DEFAULT;
  //   case 1:
  //     Serial.println("Move Forward");
  //     return IR_FORWARD;
  //   case 2:
  //     Serial.println("Move Backward");
  //     return IR_BACKWARD;
  //   case 3:
  //     Serial.println("Turn Right");
  //     return IR_RIGHT;
  //   case 4:
  //     Serial.println("Turn Left");
  //     return IR_LEFT;
  //   default:
  //     Serial.println("No valid movement detected");
  //     return DEFAULT;
  // }
}

