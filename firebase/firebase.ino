#include <IOXhop_FirebaseESP32.h>

#include <WiFi.h>

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#include <M5StickCPlus.h>
#include "secrets.h"


#define LED_BUILTIN 10
bool fireStatus = false;
bool prevStatus = false;

void setup()
{
    Serial.begin(115200);
    WiFi.begin(SECRET_SSID, SECRET_PASS);
    Serial.println("Connecting To");
    Serial.println(SECRET_SSID);
    while (WiFi.status()!= WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    M5.begin();
    Firebase.begin(SECRET_HOST, SECRET_API_KEY);
    Firebase.setBool("LED_STATUS", false);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    fireStatus = Firebase.getBool("LED_STATUS");
    prevStatus = fireStatus;
}

void loop()
{
    fireStatus = Firebase.getBool("LED_STATUS");
    if(fireStatus != prevStatus) {
        if(fireStatus) digitalWrite(LED_BUILTIN, LOW);
        else digitalWrite(LED_BUILTIN, HIGH);
        prevStatus = fireStatus;
    }
}
