// Include the firebase library for ESP32
#include <IOXhop_FirebaseESP32.h>
// Include the built in WiFi library for ESP32
#include <WiFi.h>

// Include the ArduinoJson library for parsing JSON
#include <ArduinoJson.h>

// Include the secrets.h file for the WiFi SSID Password, Firebase Host, and Firebase API Key
#include "secrets.h"

// Define the port the the builtin LED
#define LED_BUILTIN 10
// Define the Firebase status variable and previous status variable
bool fireStatus = false;
bool prevStatus = false;

void setup()
{
    // Begin the Serial connection
    Serial.begin(115200);
    // Connect to WiFi using the secrets.h file
    WiFi.begin(SECRET_SSID, SECRET_PASS);
    Serial.println("Connecting To");
    Serial.println(SECRET_SSID);
    // Wait for WiFi to connect
    while (WiFi.status()!= WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    // Begin the Firebase connection using the secrets.h file
    Firebase.begin(SECRET_HOST, SECRET_API_KEY);
    // Set the LED status to false
    Firebase.setBool("LED_STATUS", false);
    // Set the LED pin as an output
    pinMode(LED_BUILTIN, OUTPUT);
    // Turn the led off
    digitalWrite(LED_BUILTIN, HIGH);
    // Update the fireStatus variable with the current status from Firebase
    fireStatus = Firebase.getBool("LED_STATUS");
    prevStatus = fireStatus;
}

void loop()
{
    // Update the fireStatus variable with the current status from Firebase
    fireStatus = Firebase.getBool("LED_STATUS");
    // If the status has changed...
    // This is done to prevent unnecessary writes to the LED 
    if(fireStatus != prevStatus) {
        // If the status is true turn the led on
        if(fireStatus) digitalWrite(LED_BUILTIN, LOW);
        // Else trun the led off
        else digitalWrite(LED_BUILTIN, HIGH);
        // Update the previous status variable
        prevStatus = fireStatus;
    }
}
