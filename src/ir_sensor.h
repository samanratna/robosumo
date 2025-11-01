#ifndef IRSENSOR_H
#define IRSENSOR_H

#include <Arduino.h>

// Pin definitions
// IR sensor pins (latest mapping)
// const int IR1_PIN = A0;
// const int IR2_PIN = A1;
// const int IR3_PIN = A2;
// const int IR4_PIN = A3;

// Movement codes
#define DEFAULT 0
#define IR_FORWARD 1
#define IR_BACKWARD 2
#define IR_LEFT 3
#define IR_RIGHT 4

// Pin definitions
#define IR_PIN_FRONT_RIGHT A1
#define IR_PIN_FRONT_LEFT A0
#define IR_PIN_BACK_RIGHT A2
#define IR_PIN_BACK_LEFT A3

// void initIRSensors();
// int readIRSensor(int index);
void ir_setup(void);
int ir_test(void);

#endif
