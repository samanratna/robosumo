const int trigPin = 9;
const int echoPin = 2;  // Must be pin 2 or 3 on Uno (external interrupt)

volatile unsigned long startTime = 0;
volatile unsigned long endTime = 0;
volatile bool measurementDone = false;

const int threshold = 30; // cm
bool thresholdTriggered = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT); // built-in LED as indicator

  Serial.begin(9600);

  // Attach interrupt on ECHO pin
  attachInterrupt(digitalPinToInterrupt(echoPin), echoISR, CHANGE);
}

void loop() {
  // Send a trigger pulse every 100 ms
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  delay(100); // wait before next measurement

  if (measurementDone) {
    unsigned long duration = endTime - startTime;
    int distance = duration * 0.034 / 2;  // convert to cm

    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance <= threshold) {
      thresholdTriggered = true;
    } else {
      thresholdTriggered = false;
    }

    // Act on threshold
    if (thresholdTriggered) {
      digitalWrite(LED_BUILTIN, HIGH); // LED ON when distance <= 30 cm
      Serial.println("⚠️ Threshold reached!");
    } else {
      digitalWrite(LED_BUILTIN, LOW); // LED OFF otherwise
    }

    measurementDone = false; // reset flag
  }
}

void echoISR() {
  if (digitalRead(echoPin) == HIGH) {
    startTime = micros();   // echo pulse started
  } else {
    endTime = micros();     // echo pulse ended
    measurementDone = true; // signal main loop
  }
}
