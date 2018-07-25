//#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "conf.h"

void setup() {
    //
    pinMode(LED_BUILTIN, OUTPUT);
    //
    // TODO : scan for available SSIDs
    // TODO : check each registered SSID
    //
    WiFi.begin(, );
    //
    //
}

void loop() {
    // put your main code here, to run repeatedly:
    if (WiFi.status() == WL_CONNECTED) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(200);
        digitalWrite(LED_BUILTIN, LOW);
        delay(400);
    }
    else {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
    }
}
