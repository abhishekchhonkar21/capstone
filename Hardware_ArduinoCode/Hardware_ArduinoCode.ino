#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi credentials
#define WIFI_SSID "EACCESS"
#define WIFI_PASSWORD "hostelnet"

// Firebase credentials
#define API_KEY "AIzaSyAny42AW3Tq0XPPtY46LYVRyLRExJY6rjg"
#define DATABASE_URL "https://smartbin-ee19f-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "kIpv5eQfS3dE5wkHihOd9m0mQuUpHDzbqmSeIc2M"

// Firebase database path
String firebasePath = "/wasteBin/readings";

// LCD setup 
LiquidCrystal_I2C lcd(0x27, 16, 2);

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
unsigned long previousMillis = 0;
const long interval = 30000; // Send data every 30 seconds

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
  lcd.print("Connecting WiFi");

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  
  // Initial position of servo (lid closed)
  servoMotor.write(0);

  lcd.clear();
  lcd.print("System Ready!");
  delay(2000);
  Serial.println("Setup complete");
}

void loop() {
  // Measure waste level
  distanceWaste = measureDistance(trigPinWaste, echoPinWaste);
  
  // Map waste level from 30 cm (empty) to 0 cm (full)
  if (distanceWaste < 30) {
    wasteLevel = map(distanceWaste, 0, 30, 100, 0);
  } else {
    wasteLevel = 0;
  }

  // Display waste level on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waste Level:");
  lcd.setCursor(0, 1);
  lcd.print(wasteLevel);
  lcd.print("%");

  // Send data to Firebase every 30 seconds
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Create a JSON object
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["wasteLevel"] = wasteLevel;
    jsonDoc["timestamp"] = String(currentMillis);

    // Convert JSON object to string
    String jsonString;
    serializeJson(jsonDoc, jsonString);

    // Send data to Firebase
    sendToFirebase(jsonString);
  }

  // Check if hand is near to open lid
  distanceLid = measureDistance(trigPinLid, echoPinLid);

  if (distanceLid < 10) {
    Serial.println("Hand detected, opening lid");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Opening lid...");
    
    // Open lid slowly
    for (int pos = 0; pos <= 80; pos += 2) {  // Smaller steps and limit angle
    servoMotor.write(pos);
  
    if (pos > 60) {
      delay(40);  // Slow down near the end
    } else {
      delay(20);  // Normal speed at the beginning
      }
    }

    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lid open");
    lcd.setCursor(0, 1);
    lcd.print("Closing in 5sec");
    delay(4000);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Closing lid...");
    
    // Close lid slowly
    for (int pos = 85; pos >= 0; pos -= 4) {
      servoMotor.write(pos);
      delay(20);
    }
  } else {
    servoMotor.write(0);
  }

  delay(500);
}

// Function to measure distance using ultrasonic sensor
long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

// Function to send data to Firebase using HTTP POST
void sendToFirebase(String jsonString) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(DATABASE_URL) + firebasePath + ".json?auth=" + FIREBASE_AUTH;

    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonString);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Data sent to Firebase");
      Serial.println(response);
    } else {
      Serial.print("Error sending data: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}