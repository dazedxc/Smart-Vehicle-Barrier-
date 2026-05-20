#include <ESP32Servo.h>

#define TRIG_PIN 2
#define ECHO_PIN 3
#define SERVO_PIN 4

Servo gateServo;

long duration;
float distance;

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  gateServo.attach(SERVO_PIN);

  // Gate starts CLOSED
  gateServo.write(0);
f
  Serial.println("Smart Parking Toll System Ready");
}

void loop() {

  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo signal
  duration = pulseIn(ECHO_PIN, HIGH);

  // Convert to distance (cm)
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Vehicle detected within 15 cm
  if (distance > 0 && distance <= 15) {

    Serial.println("Vehicle Detected -> Opening Gate");

    // OPEN GATE
    gateServo.write(45);

    // Keep gate open for 5 seconds
    delay(3000);

    // CLOSE GATE
    Serial.println("Closing Gate");
    gateServo.write(0);

    // Small delay to avoid repeated triggering
    delay(1000);
  }

  delay(200);
}