#include "ir_sensor.h"

// Movement codes
// #define DEFAULT 0
// #define IR_FORWARD 1
// #define IR_BACKWARD 2
// #define IR_RIGHT_FORWARD 3
// #define IR_LEFT_FORWARD 4

void ir_setup() {
  // If sensors are digital type, set them as INPUT
  pinMode(IR1_PIN, INPUT);
  pinMode(IR2_PIN, INPUT);
  pinMode(IR3_PIN, INPUT);
  pinMode(IR4_PIN, INPUT);

  Serial.println("IR Sensor Test Started...");
}

// int ir_test() {
//   // --- Option 1: for DIGITAL output sensors (HIGH/LOW) ---
//   int ir_front_left = digitalRead(IR1_PIN);
//   int ir_back_left = digitalRead(IR2_PIN);
//   int ir_back_right = digitalRead(IR3_PIN);
//   int ir_front_right = digitalRead(IR4_PIN);

//   // --- Option 2: for ANALOG output sensors (distance/reflectance) ---
//   // int ir1 = analogRead(IR1_PIN);
//   // int ir2 = analogRead(IR2_PIN);
//   // int ir3 = analogRead(IR3_PIN);
//   // int ir4 = analogRead(IR4_PIN);

//   // Print values to Serial Monitor
//   Serial.print("ir_front_left: "); Serial.print(ir_front_left);
//   Serial.print(" | ir_back_left: "); Serial.print(ir_back_left);
//   Serial.print(" | ir_back_right: "); Serial.print(ir_back_right);
//   Serial.print(" | ir_front_right: "); Serial.println(ir_front_right);

//   if (ir_front_left == HIGH) {
//     return 1;
//   } else if (ir_front_right == HIGH) {
//     return 1;
//   } else if (ir_back_left == HIGH) {
//     return 2;
//   } else if (ir_back_right == HIGH) {
//     return 2;
//   } else {
//     return 0;
//   }
//   // delay(100); // slow down output for readability
// }
int ir_test() {
  int ir_front_left = digitalRead(IR1_PIN); // Sensor 1
  int ir_back_left  = digitalRead(IR2_PIN); // Sensor 2
  // int ir_back_right = digitalRead(IR3_PIN); // ignored
  // int ir_front_right = digitalRead(IR4_PIN); // ignored

  Serial.print("FL: "); Serial.print(ir_front_left);
  Serial.print(" | BL: "); Serial.println(ir_back_left);

  // --- Logic using only FL and BL ---

  if (ir_front_left && ir_back_left) {
    return DEFAULT;        // Both sensors see obstacle: default
  }
  else if (ir_front_left && !ir_back_left) {
    return IR_FORWARD;    // Front left sees obstacle, back left clear
  }
  else if (!ir_front_left && ir_back_left) {
    return IR_BACKWARD;     // Front left clear, back left sees obstacle
  }
  else { 
    return DEFAULT;        // Both clear
  }
}

