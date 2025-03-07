# SmartBin: IoT-Based Waste Management System

## Overview
SmartBin is an IoT-powered smart waste management system designed to improve waste collection efficiency, especially in Tier 2 and Tier 3 cities. It utilizes ESP32 microcontrollers, ultrasonic sensors, and cloud-based data storage to provide real-time monitoring of public dustbins. The system integrates automated lid control, real-time data transmission, and a web-based reporting platform for waste management authorities and the public.

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

## Installation and Setup
### Hardware Requirements
- ESP32 Microcontroller
- HC-SR04 Ultrasonic Sensors (x2)
- Tower Pro Micro Servo Motor
- LM2596 Buck Converter
- LCD Display
- Battery Pack (3xAAA)
- Breadboard & Jumper Wires

### Software Requirements
- Arduino IDE
- Firebase Realtime Database
- HTML, CSS, and JavaScript (for Web Portal)

### Steps to Set Up
1. **Assemble the Hardware**: Connect ESP32 with sensors, servo motor, LCD, and power components.
2. **Flash the ESP32 Code**:
   - Install the ESP32 board in Arduino IDE.
   - Upload the firmware containing Firebase and sensor logic (code provided in `src/` folder).
3. **Set Up Firebase**:
   - Create a Firebase project.
   - Set up the Realtime Database and obtain API credentials.
   - Update the credentials in the ESP32 firmware.
4. **Deploy the Web Portal**:
   - Host the website on Firebase Hosting or a local server.
   - Configure it to fetch and display data from Firebase.

## Usage
1. **Automated Bin Monitoring**: The system continuously updates bin fill levels in real-time.
2. **Automatic Lid Operation**: The bin opens automatically when a user approaches.
3. **Web Dashboard for Authorities**: View bin statuses, assign collection tasks, and monitor waste trends.
4. **Public Reporting**: Residents can report waste issues, promoting community participation.

## Future Enhancements
- Integration with AI for predictive waste collection.
- Mobile app for real-time alerts.
- GPS tracking for collection vehicles.


