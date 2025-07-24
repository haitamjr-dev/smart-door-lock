#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>

// ESP32 hardware SPI pins for MFRC522
#define SS_PIN    2
#define RST_PIN   22
#define SCK_PIN   18
#define MISO_PIN  19
#define MOSI_PIN  23

// Ultrasonic sensor pins
#define TRIG_PIN  5
#define ECHO_PIN  4

// Servo motor pin
#define SERVO_PIN 25

// Servo angles
const int OPEN_ANGLE  = 90;
const int CLOSE_ANGLE = 0;

// Authorized RFID UID (example: 0x35, 0x15, 0xA5, 0xAC)
byte authorizedUID[4] = {0x35, 0x15, 0xA5, 0xAC};

MFRC522 rfid(SS_PIN, RST_PIN);
Servo doorServo;

void setup() {
  Serial.begin(115200);
  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, SS_PIN);
  rfid.PCD_Init();

  doorServo.setPeriodHertz(50);
  doorServo.attach(SERVO_PIN, 500, 2400);  // Standard servo pulse range
  doorServo.write(CLOSE_ANGLE);            // Start with door closed

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("Smart Door Lock system ready!");
}

void loop() {
  // Serial.println("Loop start");

  // Check RFID from outside FIRST
  if (checkRFIDEntry()) {
    openDoor();
    delay(2000);
    return; // Skip ultrasonic this loop if RFID triggered
  }

   //Check ultrasonic from inside
   if (checkInsideExit()) {
     openDoor();
    delay(2000);
  }
}

// Returns true if authorized RFID card is detected
bool checkRFIDEntry() {
 //  Serial.println("Checking RFID...");
  if (!rfid.PICC_IsNewCardPresent()) {
   // Serial.println("No new RFID card present.");
    return false;
  }
  if (!rfid.PICC_ReadCardSerial()) {
    // Serial.println("RFID card detected, but could not read serial.");
    return false;
  }

  Serial.print("🎫 Card UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  if (isAuthorized(rfid.uid.uidByte)) {
    Serial.println("✅ Access granted");
    rfid.PICC_HaltA();
    return true;
  } else {
    Serial.println("❌ Access denied");
    rfid.PICC_HaltA();
    return false;
  }
}

// Returns true if someone detected inside
bool checkInsideExit() {
  long duration, distance;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000); // Timeout 30ms for reliability
  distance = duration * 0.034 / 2;

  // Serial.print("Ultrasonic distance: ");
  Serial.println(distance);

  if (distance > 0 && distance < 20) { // 20cm threshold
    Serial.println("🚶 Detected movement from inside");
    return true;
  }
  return false;
}

// Check UID against authorized list
bool isAuthorized(byte *uid) {
  for (byte i = 0; i < 4; i++) {
    if (uid[i] != authorizedUID[i])
      return false;
  }
  return true;
}

// Servo door control
void openDoor() {
  Serial.println("🔓 Opening door");
  doorServo.write(OPEN_ANGLE);
  delay(3000); // Door remains open for 3 seconds
  Serial.println("🔒 Closing door");
  doorServo.write(CLOSE_ANGLE);
}