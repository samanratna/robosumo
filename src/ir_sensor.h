#ifndef IRSENSOR_H
#define IRSENSOR_H

#include <Arduino.h>

// Pin definitions
// IR sensor pins (latest mapping)
// const int IR1_PIN = A0;
// const int IR2_PIN = A1;
// const int IR3_PIN = A2;
// const int IR4_PIN = A3;

// Pin definitions
#define IR1_PIN A0
#define IR2_PIN A1
#define IR3_PIN A2
#define IR4_PIN A3

// void initIRSensors();
// int readIRSensor(int index);
void ir_setup(void);
int ir_test(void);

#endif
