#include "distance_sensor.h"

void ultrasonic_setup() {
  pinMode(US1_TRIG, OUTPUT);
  pinMode(US2_TRIG, OUTPUT);
  pinMode(US3_TRIG, OUTPUT);
  pinMode(US4_TRIG, OUTPUT);

  pinMode(US1_ECHO, INPUT);
  pinMode(US2_ECHO, INPUT);
  pinMode(US3_ECHO, INPUT);
  pinMode(US4_ECHO, INPUT);

  Serial.println("Ultrasonic sensors initialized...");
}

long getDistanceCM(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000UL); // 30 ms timeout (~5m)
  if (duration == 0) return -1;

  return duration / 58; // convert microseconds to cm
}

int ultrasonic_checkObstacle() {
  long d_front = getDistanceCM(US1_TRIG, US1_ECHO);
  long d_back  = getDistanceCM(US2_TRIG, US2_ECHO);
  long d_left  = getDistanceCM(US3_TRIG, US3_ECHO);
  long d_right = getDistanceCM(US4_TRIG, US4_ECHO);

  Serial.print("Front: "); Serial.print(d_front);
  Serial.print(" | Back: "); Serial.print(d_back);
  Serial.print(" | Left: "); Serial.print(d_left);
  Serial.print(" | Right: "); Serial.println(d_right);

  if (d_front > 0 && d_front < OBSTACLE_THRESHOLD_CM) return OBSTACLE_FRONT;
  if (d_back  > 0 && d_back  < OBSTACLE_THRESHOLD_CM) return OBSTACLE_BACK;
  if (d_left  > 0 && d_left  < OBSTACLE_THRESHOLD_CM) return OBSTACLE_LEFT;
  if (d_right > 0 && d_right < OBSTACLE_THRESHOLD_CM) return OBSTACLE_RIGHT;

  return NONE;
}
