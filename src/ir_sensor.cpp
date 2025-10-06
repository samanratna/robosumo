#include "ir_sensor.h"

// Movement codes
#define DEFAULT 0
#define FORWARD 1
#define BACKWARD 2
#define RIGHT_FORWARD 3
#define LEFT_FORWARD 4

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
  int ir_front_left  = digitalRead(IR1_PIN); // Sensor 1
  int ir_back_left   = digitalRead(IR2_PIN); // Sensor 2
  int ir_back_right  = digitalRead(IR3_PIN); // Sensor 3
  // int ir_front_right = digitalRead(IR4_PIN); // ignored

  Serial.print("FL: "); Serial.print(ir_front_left);
  Serial.print(" | BL: "); Serial.print(ir_back_left);
  Serial.print(" | BR: "); Serial.println(ir_back_right);

  // --- Logic without front-right sensor ---

  // Case 1: Default (1 1 1)
  if (ir_front_left && ir_back_left && ir_back_right) {
    return DEFAULT;
  }

  // Case 2: Forward (1 1 0) or (1 0 1) or (1 0 0)
  else if ((ir_front_left && ir_back_left && !ir_back_right) ||
           (ir_front_left && !ir_back_left && ir_back_right) ||
           (ir_front_left && !ir_back_left && !ir_back_right)) {
    return FORWARD;
  }

  // Case 3: Backward (0 1 1)
  else if (!ir_front_left && ir_back_left && ir_back_right) {
    return BACKWARD;
  }

  // Case 4: Right + Forward (0 0 1)
  else if (!ir_front_left && !ir_back_left && ir_back_right) {
    return RIGHT_FORWARD;
  }

  // Case 3: Backward (0 1 0)
  else if( !ir_front_left && ir_back_left && !ir_back_right) {
    return LEFT_FORWARD;
  }

  // Default fallback
  else {
    return DEFAULT;
  }
}
