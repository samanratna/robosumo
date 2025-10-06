#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

// === Ultrasonic sensor pin definitions ===
#define US1_TRIG 6   // FRONT
#define US1_ECHO 2

#define US2_TRIG 5   // BACK
#define US2_ECHO 3

#define US3_TRIG 4   // LEFT
#define US3_ECHO 12

#define US4_TRIG 11  // RIGHT
#define US4_ECHO 13

// === Constants ===
#define OBSTACLE_THRESHOLD_CM 30

// Return identifiers
#define OBSTACLE_FRONT  1
#define OBSTACLE_BACK   2
#define OBSTACLE_LEFT   3
#define OBSTACLE_RIGHT  4
#define NONE   0

// === Function declarations ===
void ultrasonic_setup();
long getDistanceCM(int trigPin, int echoPin);
int ultrasonic_checkObstacle();   // returns FRONT/BACK/LEFT/RIGHT/NONE

#endif
