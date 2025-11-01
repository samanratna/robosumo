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


int ir_test() {

  reading_front_right = digitalRead(IR_PIN_FRONT_RIGHT);
  reading_front_left  = digitalRead(IR_PIN_FRONT_LEFT);
  reading_back_right = digitalRead(IR_PIN_BACK_RIGHT);
  reading_back_left = digitalRead(IR_PIN_BACK_LEFT);

  // Serial.print(reading_front_left); Serial.print("------"); Serial.print(reading_front_right);
  // Serial.println("");
  // Serial.print(" || ");
  // Serial.print(" || ");
  // Serial.println("");
  // Serial.print(reading_back_left); Serial.print("------"); Serial.print(reading_back_right);
  // Serial.println("");
  // Serial.println("");
}

byte start_ir_reading(void) {
  
  byte all_ir_bit_pattern = ((byte)reading_front_left << 3) | ((byte)reading_front_right << 2) | ((byte)reading_back_left << 1) | ((byte)reading_back_right);
  Serial.print("IR Bit Pattern: "); Serial.println(all_ir_bit_pattern, BIN);

  return all_ir_bit_pattern;

  // // cases for front movement
  // if (all_ir_bit_pattern == 0b1100 || all_ir_bit_pattern == 0b1101 || all_ir_bit_pattern == 0b1110) {
  //   // Opponent detected in front
  //   forward(150);
  // }



  // if (all_ir_bit_pattern == 0b0000) {
  //   // No opponent detected
  //   stop();
  // }
  // else if (all_ir_bit_pattern == 0b1100 || all_ir_bit_pattern == 0b1000 || all_ir_bit_pattern == 0b0100) {
  //   // Opponent detected in front
  //   forward(150);
  // }
  // else if (all_ir_bit_pattern == 0b0011 || all_ir_bit_pattern == 0b0001 || all_ir_bit_pattern == 0b0010) {
  //   // Opponent detected at back
  //   backward(150);
  // }
  // else if (all_ir_bit_pattern == 0b1001 || all_ir_bit_pattern == 0b1000) {
  //   // Opponent detected at front-right
  //   right(150);
  // }
  // else if (all_ir_bit_pattern == 0b0110 || all_ir_bit_pattern == 0b0100) {
  //   // Opponent detected at front-left
  //   left(150);
  // }
}

