# smart-door-lock
his project is a smart door lock system based on the ESP32 microcontroller and the MFRC522 RFID reader. It allows access using RFID cards and includes a servo motor to control the door. The system unlocks automatically when someone is inside and uses RFID authentication from outside.
# 🔐 Smart Door Lock System using ESP32, RFID (RC522), and Servo Motor

This project is a smart door lock system that uses an ESP32 microcontroller, an RC522 RFID reader, and a servo motor to control access.

## 📦 Components Used

- ESP32
- RC522 RFID Reader
- Servo Motor
- Ultrasonic Sensor (Optional)
- Jumper Wires
- Breadboard
- Power Supply (e.g. 5V)

## ⚙️ Features

- RFID authentication
- Unlocks door when authorized card is scanned
- Servo motor to open/close lock
- Optional: Ultrasonic sensor to detect presence

## 🛠️ Installation

1. Connect all components as shown in the wiring diagram.
2. Flash the Arduino code to ESP32 using the Arduino IDE.
3. Add your RFID card UIDs in the code to authorize access.

## 📁 Files

- `smart_door_lock.ino` - main Arduino sketch
- `wiring_diagram.png` - circuit diagram (if available)

## 💡 Future Improvements

- Add buzzer or LCD screen
- Store users in EEPROM or online database
- Add mobile app or web interface

## 📸 Preview

*(Insert image or GIF of the working system here)*

## 👤 Author

- Name: Haitam Jarmi  
- GitHub: [github.com/yourusername](https://github.com/yourusername)

---

*This is an educational project. Use responsibly.*
