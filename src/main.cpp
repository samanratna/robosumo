#include <SoftwareSerial.h>
#include <Arduino.h>
SoftwareSerial BTSerial(11, 13); // RX, TX

void setup() {
  Serial.begin(9600);      // For Serial Monitor
  BTSerial.begin(9600);    // For HC-05 communication
  // BTSerial.begin(38400);    // For HC-05 communication
  Serial.println("Bluetooth ready. Type in Serial Monitor or Phone App:");
}

void loop() {
  // Bluetooth → Serial Monitor
  if (BTSerial.available()) {
    char c = BTSerial.read();
    Serial.write(c);
  }

  // Serial Monitor → Bluetooth
  if (Serial.available()) {
    char c = Serial.read();
    BTSerial.write(c);
  }
}
