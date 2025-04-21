# QR-Based Smart Parking System

A prototype smart parking solution that streamlines parking slot assignment, entry, and exit using QR codes, computer vision, and LoRa-based communication for secure and efficient multi-level parking management.

---

## Features

- **Automated Slot Assignment:** Assigns parking slots in a linear order (A1, A2, B1, B2) as vehicles arrive.
- **QR Code Generation:** Generates and displays a unique QR code for each vehicle and slot at entry.
- **Multi-Level Support:** Supports two parking levels (A and B), each with two slots.
- **Contactless Entry/Exit:** ESP32-CAM devices scan and decode QR codes at both entry and exit points.
- **LoRa Communication:** ESP32-CAM transmits slot and action data wirelessly to Arduino controllers using LoRa.
- **Servo-Controlled Gates:** Arduino opens/closes entry and exit flaps, as well as individual slot flaps, based on commands.
- **Real-Time Slot Management:** Ensures slots are opened only for valid QR codes and are closed upon exit.

---

## System Overview

1. **Entry Process:**
   - IR sensor detects vehicle at entry.
   - Python script assigns the next available slot and generates a QR code with the slot ID.
   - QR code is displayed for the driver.
2. **Parking Process:**
   - At the parking level, the driver scans the QR code at the ESP32-CAM kiosk.
   - ESP32-CAM decodes the QR, verifies the slot, and sends an "ENTRY" command with the slot ID to Arduino via LoRa.
   - Arduino opens the entry flap and the assigned slot flap.
3. **Exit Process:**
   - At exit, the driver scans the same QR at another ESP32-CAM.
   - ESP32-CAM sends an "EXIT" command with the slot ID to Arduino via LoRa.
   - Arduino opens the exit flap and closes the respective slot flap, marking it as available.

---

## Tech Stack

- **Python:** QR code generation, IR sensor interfacing, OpenCV for display.
- **ESP32-CAM:** QR code scanning/decoding, LoRa communication.
- **Arduino:** LoRa receiver, servo control for gates and slots.
- **Hardware:** IR sensors, ESP32-CAM modules, LoRa modules, Arduino board, servo motors, display screen.

---

## Setup Instructions

1. **Hardware Connections:**
   - Connect IR sensor to the entry system (e.g., Raspberry Pi or PC GPIO).
   - Connect ESP32-CAM modules at each parking level entry and exit.
   - Connect LoRa modules to ESP32-CAM and Arduino.
   - Connect servo motors to Arduino for entry/exit gates and slot flaps.

2. **Software Installation:**
   - Install Python libraries:
     ```
     pip install qrcode opencv-python gpiozero
     ```
   - Upload provided ESP32-CAM and Arduino codes to respective boards.
   - Ensure LoRa modules are set to the same frequency and sync word.

3. **Running the System:**
   - Start the Python script on the entry controller.
   - Power on ESP32-CAM and Arduino modules.
   - System is ready for operation; follow the entry and exit workflow.

---

## File Structure

- `parking_control.py` – Python script for IR detection and QR code generation/display.
- `entry_scanner.ino` – ESP32-CAM code for scanning QR at parking entry.
- `exit_scanner.ino` – ESP32-CAM code for scanning QR at parking exit.
- `parking_controller.ino` – Arduino code for LoRa reception and servo control.

---

## How It Works

- Vehicles are assigned slots in order: A1 → A2 → B1 → B2....
- Each car receives a unique QR code tied to its slot.
- Only the correct slot and gate open for each valid QR scan, ensuring managed and secure parking.
- Slots are marked available again only after exit scan and flap closure.

---

## Contribution

Feedback, issues, and contributions are welcome! Please open an issue or pull request in the repository.


