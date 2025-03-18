# SmartBin: IoT-Based Waste Management System

## Overview
SmartBin is an IoT-powered smart waste management system designed to improve waste collection efficiency, especially in Tier 2 and Tier 3 cities. It utilizes ESP32 microcontrollers, ultrasonic sensors, and cloud-based data storage to provide real-time monitoring of public dustbins. The system integrates automated lid control, real-time data transmission, and a web-based reporting platform for waste management authorities and the public.

<img width="684" alt="Screenshot 2025-03-18 at 10 15 42 AM" src="https://github.com/user-attachments/assets/1ae2e33e-4ea0-46af-bef2-74fc6d3b79b0" />

## Features
- **Real-Time Bin Monitoring**: Ultrasonic sensors measure waste levels and send live data to Firebase.
- **Automated Lid Control**: A servo motor opens the lid when motion is detected.
- **Web-Based Management Portal**: Allows authorities to track bin status, schedule collections, and address complaints.
- **Community Reporting System**: Residents can report overflowing bins or uncollected waste.
- **LCD Display**: Provides real-time bin status information.
- **Efficient Power Management**: Uses a buck converter for stable voltage regulation.

## System Architecture
The system consists of the following components:
1. **ESP32 Microcontroller**: Processes sensor data and communicates with the cloud.
2. **Ultrasonic Sensors**: Measure bin fill levels and detect user interaction.
3. **Servo Motor**: Opens and closes the bin lid automatically.
4. **LCD Display**: Displays bin status locally.
5. **Wi-Fi Connectivity**: Sends data to Firebase for remote access.
6. **Management Website**: Allows authorities to monitor bins and manage waste collection.
7. **Battery Pack & LM2596 Buck Converter**: Ensures stable power supply.

<img width="884" alt="Screenshot 2025-03-18 at 10 14 19 AM" src="https://github.com/user-attachments/assets/4ad991c1-488f-412d-ac01-7a2c7a0cc6a0" />

## Installation and Setup
### Hardware Requirements
- ESP32 Microcontroller
- HC-SR04 Ultrasonic Sensors (x2)
- Tower Pro Micro Servo Motor
- LM2596 Buck Converter
- LCD Display
- Battery Pack (3xAAA)
- Breadboard & Jumper Wires
- 
<img width="622" alt="Screenshot 2025-03-18 at 10 14 56 AM" src="https://github.com/user-attachments/assets/656c9bf1-804b-4b6d-987d-baca84d3c943" />

### Software Requirements
- Arduino IDE
- Firebase Realtime Database
- HTML, CSS, and JavaScript (for Web Portal)

## Usage
1. **Automated Bin Monitoring**: The system continuously updates bin fill levels in real-time.
2. **Automatic Lid Operation**: The bin opens automatically when a user approaches.
3. **Web Dashboard for Authorities**: View bin statuses, assign collection tasks, and monitor waste trends.
4. **Public Reporting**: Residents can report waste issues, promoting community participation.

## Future Enhancements
- Integration with AI for predictive waste collection.
- Mobile app for real-time alerts.
- GPS tracking for collection vehicles.

## Report Link

https://drive.google.com/file/d/18nze9UTDU2O8N1w0vOLJywK2bV0nm8fH/view?usp=sharing
