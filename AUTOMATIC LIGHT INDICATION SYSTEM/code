#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpuLeft(0x68);  // Left handle sensor
MPU6050 mpuRight(0x69); // Right handle sensor

const int leftRelayPin = 7;    // Relay for left handle
const int rightRelayPin = 8;   // Relay for right handle
const int leftButtonPin = 2;   // Push button for left handle
const int rightButtonPin = 3;  // Push button for right handle

int16_t axLeft, ayLeft, azLeft;
int16_t axRight, ayRight, azRight;

int16_t initialAxLeft, initialAxRight;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize MPU6050 sensors
  mpuLeft.initialize();
  mpuRight.initialize();

  // Initialize pins
  pinMode(leftRelayPin, OUTPUT);
  pinMode(rightRelayPin, OUTPUT);
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);

  // Set relays off initially
  digitalWrite(leftRelayPin, LOW);
  digitalWrite(rightRelayPin, LOW);

  // Get initial X-axis values
  mpuLeft.getAcceleration(&initialAxLeft, &ayLeft, &azLeft);
  mpuRight.getAcceleration(&initialAxRight, &ayRight, &azRight);

  // Print initial values
  Serial.print("Initial left sensor X-axis: ");
  Serial.println(initialAxLeft);
  Serial.print("Initial right sensor X-axis: ");
  Serial.println(initialAxRight);
}

void loop() {
  // Reading push buttons
  bool leftButtonPressed = digitalRead(leftButtonPin) == LOW;
  bool rightButtonPressed = digitalRead(rightButtonPin) == LOW;

  // Reading current X-axis data from sensors
  mpuLeft.getAcceleration(&axLeft, &ayLeft, &azLeft);
  mpuRight.getAcceleration(&axRight, &ayRight, &azRight);

  // Calculate X-axis change percentage for left sensor
  float leftChangePercent = abs((float)(axLeft - initialAxLeft) / initialAxLeft) * 100;
  float rightChangePercent = abs((float)(axRight - initialAxRight) / initialAxRight) * 100;

  // Left handle logic
  if (leftButtonPressed) {
    digitalWrite(leftRelayPin, HIGH);
    Serial.println("Left relay ON");
  }

  if (digitalRead(leftRelayPin) == HIGH && leftChangePercent >= 60.0) {
    digitalWrite(leftRelayPin, LOW);
    Serial.println("Left relay OFF due to X-axis change");
  }

  // Right handle logic
  if (rightButtonPressed) {
    digitalWrite(rightRelayPin, HIGH);
    Serial.println("Right relay ON");
  }

  if (digitalRead(rightRelayPin) == HIGH && rightChangePercent >= 60.0) {
    digitalWrite(rightRelayPin, LOW);
    Serial.println("Right relay OFF due to X-axis change");
  }

  delay(100); // Small delay to debounce buttons
}
