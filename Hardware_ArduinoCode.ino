#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

// LCD setup 
LiquidCrystal_I2C lcd(0x27, 16, 2);  // 

// Ultrasonic sensor pins
const int trigPinWaste = 25;
const int echoPinWaste = 33;
const int trigPinLid = 5;
const int echoPinLid = 18;

// Servo motor pin
Servo servoMotor;
const int servoPin = 14;

// Variables
long durationWaste, distanceWaste;
long durationLid, distanceLid;
int wasteLevel;

void setup() {
  Serial.begin(115200);
  Serial.println("Smart Bin Starting...");
  
  // Set pin modes
  pinMode(trigPinWaste, OUTPUT);
  pinMode(echoPinWaste, INPUT);
  pinMode(trigPinLid, OUTPUT);
  pinMode(echoPinLid, INPUT);
  
  // Attach servo
  servoMotor.attach(servoPin);
  
  // LCD setup
  Wire.begin();
  lcd.init();
  lcd.backlight();
  
  // Display startup message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Bin");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  
  // Initial position of servo (lid closed)
  servoMotor.write(0);

  delay(2000);  // Show startup message for 2 seconds
  Serial.println("Setup complete");
}

void loop() {
  // Measure waste level
  distanceWaste = measureDistance(trigPinWaste, echoPinWaste);
  
  Serial.print("Raw waste distance: ");
  Serial.println(distanceWaste);

  // Map waste level from 30 cm (empty) to 0 cm (full)
  if (distanceWaste < 30) {
    wasteLevel = map(distanceWaste, 0, 30, 100, 0); // 100% is full, 0% is empty
  } else {
    wasteLevel = 0; // If distance is above 30 cm, set it to 0 (empty)
  }

  Serial.print("Calculated waste level: ");
  Serial.print(wasteLevel);
  Serial.println("%");

  // Display waste level on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waste Level:");
  lcd.setCursor(0, 1);
  lcd.print(wasteLevel);
  lcd.print("%");

  // Check if hand is near to open lid (below 20 cm)
  distanceLid = measureDistance(trigPinLid, echoPinLid);
  Serial.print("Lid distance: ");
  Serial.println(distanceLid);

  if (distanceLid < 20) { // Hand detected within 20 cm
    Serial.println("Hand detected, opening lid");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Opening lid...");
    
    // Open lid slowly
    for (int pos = 0; pos <= 85; pos += 4) {
      servoMotor.write(pos);
      delay(20);
    }
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lid open");
    lcd.setCursor(0, 1);
    lcd.print("Closing in 4s");
    delay(4000); // Wait for 4 seconds
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Closing lid...");
    
    // Close lid slowly
    for (int pos = 85; pos >= 0; pos -= 4) {
      servoMotor.write(pos);
      delay(20);
    }
  } else {
    // Ensure the lid is closed if no hand is detected
    servoMotor.write(0);
  }

  delay(500); // Small delay between measurements
}

// Function to measure distance using ultrasonic sensor
long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}