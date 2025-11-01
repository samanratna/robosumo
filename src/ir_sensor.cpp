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

byte start_ir_reading(void) {

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
  
  byte all_ir_bit_pattern = ((byte)reading_front_left << 3) | ((byte)reading_front_right << 2) | ((byte)reading_back_left << 1) | ((byte)reading_back_right);
  // Serial.print("IR Bit Pattern: "); Serial.println(all_ir_bit_pattern, BIN);
  return all_ir_bit_pattern;
}

