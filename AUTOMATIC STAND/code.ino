#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>

MPU6050 mpu;
Servo standServo;

const int servoPin = 9;         // Pin connected to the servo motor
const int platePin = 2;         // Pin connected to the conducting plate
int16_t ax, ay, az;             // Variables for accelerometer readings
int16_t initialAx, initialAy, initialAz; // Initial tilt values

bool standRetracted = false;    // Flag to check if stand is retracted

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  standServo.attach(servoPin);

  // Set up the conducting plate pin
  pinMode(platePin, INPUT_PULLUP);

  // Get the initial tilt values
  mpu.getAcceleration(&initialAx, &initialAy, &initialAz);
  
  // Print the initial values for reference
  Serial.print("Initial X: "); Serial.println(initialAx);
  Serial.print("Initial Y: "); Serial.println(initialAy);
  Serial.print("Initial Z: "); Serial.println(initialAz);

  // Initialize servo to stand down position
  standServo.write(0);
}

void loop() {
  // Check if the stand is already retracted
  if (digitalRead(platePin) == LOW) {
    standRetracted = true;
    Serial.println("Stand already retracted.");
  } else {
    standRetracted = false;
  }

  // Get current tilt values
  mpu.getAcceleration(&ax, &ay, &az);

  // Detect if the scooter is lifted (tilt change)
  if (!standRetracted && abs(ax - initialAx) < 2000 && abs(az - initialAz) < 2000) {
    Serial.println("Scooter lifted, retracting stand...");
    standServo.write(45); // Rotate servo to lift the stand
    delay(1000);          // Wait for the servo to complete the movement

    // Check if the stand is in the rest position
    if (digitalRead(platePin) == LOW) {
      Serial.println("Stand retracted successfully.");
      standRetracted = true;
    }
  }

  delay(500); // Small delay for stable readings
}
