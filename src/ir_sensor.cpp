#include "ir_sensor.h"

void ir_setup() {
  // If sensors are digital type, set them as INPUT
  pinMode(IR1_PIN, INPUT);
  pinMode(IR2_PIN, INPUT);
  pinMode(IR3_PIN, INPUT);
  pinMode(IR4_PIN, INPUT);

  Serial.println("IR Sensor Test Started...");
}

int ir_test() {
  // --- Option 1: for DIGITAL output sensors (HIGH/LOW) ---
  int ir_front_left = digitalRead(IR1_PIN);
  int ir_back_left = digitalRead(IR2_PIN);
  int ir_back_right = digitalRead(IR3_PIN);
  int ir_front_right = digitalRead(IR4_PIN);

  // --- Option 2: for ANALOG output sensors (distance/reflectance) ---
  // int ir1 = analogRead(IR1_PIN);
  // int ir2 = analogRead(IR2_PIN);
  // int ir3 = analogRead(IR3_PIN);
  // int ir4 = analogRead(IR4_PIN);

  // Print values to Serial Monitor
  Serial.print("ir_front_left: "); Serial.print(ir_front_left);
  Serial.print(" | ir_back_left: "); Serial.print(ir_back_left);
  Serial.print(" | ir_back_right: "); Serial.print(ir_back_right);
  Serial.print(" | ir_front_right: "); Serial.println(ir_front_right);

  if (ir_front_left == HIGH) {
    return 1;
  } else if (ir_front_right == HIGH) {
    return 1;
  } else if (ir_back_left == HIGH) {
    return 2;
  } else if (ir_back_right == HIGH) {
    return 2;
  } else {
    return 0;
  }
  // delay(100); // slow down output for readability
}
