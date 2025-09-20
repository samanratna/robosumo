#define TRIG_PIN 9
#define ECHO_PIN 10

long duration;
float distance_cm;

void setup() {
  Serial.begin(9600);      // Start serial communication
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Clear the trig pin
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send a 10 µs HIGH pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo pin
  duration = pulseIn(ECHO_PIN, HIGH);

  // Convert to distance (cm)
  distance_cm = (duration * 0.0343) / 2;

  // Print result
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500);
}
