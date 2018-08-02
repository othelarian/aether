//#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "conf.h"

// PLAN #########################################

/*
1. CONNECT TO SSIDs, with preferences --> IN PROGRESS
2. RECEPTION OF UDP REQUEST
3. SENDING UDP datagram with full informations
4. CONNECT TO THE APP
5. SETUP LED
*/

// GLOBAL VARIABLES #############################

bool getnet = false;
int sel_lvl = 0;
String sel_ssid = "";
String sel_pwd = "";

// HELPERS ######################################

bool scanning() {
    bool res = false;
    int nbn = WiFi.scanNetworks();
    for (int i = 0; i < nbn; i++) {
        String tmp_ssid = WiFi.SSID(i);
        if (tmp_ssid == SSID_01) {
            sel_ssid = SSID_01;
            sel_pwd = PASS_01;
            sel_lvl = 1;
            return true;
        }
        else if (tmp_ssid == SSID_02) {
            sel_ssid = SSID_02;
            sel_pwd = PASS_02;
            sel_lvl = 2;
            res = true;
        }
    }
    return res;
}

// GENERAL PART #################################

void setup() {
    // TEST PURPOSE
    pinMode(LED_BUILTIN, OUTPUT);
    // TEST END
    // setup the wifi
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    // ready to go
    delay(100);
}

void loop() {
    // if not connected, try to connect
    if (!getnet) {
        // TEST PURPOSE
        digitalWrite(LED_BUILTIN, HIGH);
        // TEST END
        getnet = scanning();
        // TEST PURPOSE
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        // TEST END
        if (!getnet) {
            // TEST PURPOSE
            delay(300);
            for (int i = 0; i < 3; i++) {
                digitalWrite(LED_BUILTIN, HIGH);
                delay(300);
                digitalWrite(LED_BUILTIN, LOW);
                delay(300);
            }
            // TEST END
            // delay the next scan in 5 seconds
            delay(5000);
        }
        else {
            // connect to the selected network
            WiFi.begin(sel_ssid.c_str(), sel_pwd.c_str());
            //
            // TODO : setup webserver ?
            // TODO : setup udp ?
            //
        }
    }
    else {
        //
        // TODO : check if we are connected. If not, disconnect and set "getnet" to false
        //
        switch(sel_lvl) {
            case 1:
                //
                digitalWrite(LED_BUILTIN, HIGH);
                delay(300);
                digitalWrite(LED_BUILTIN, LOW);
                delay(300);
                digitalWrite(LED_BUILTIN, HIGH);
                delay(700);
                digitalWrite(LED_BUILTIN, LOW);
                delay(300);
                digitalWrite(LED_BUILTIN, HIGH);
                delay(300);
                digitalWrite(LED_BUILTIN, LOW);
                delay(1200);
                //
                break;
            case 2:
                //
                digitalWrite(LED_BUILTIN, HIGH);
                delay(800);
                digitalWrite(LED_BUILTIN, LOW);
                delay(200);
                digitalWrite(LED_BUILTIN, HIGH);
                delay(800);
                digitalWrite(LED_BUILTIN, LOW);
                delay(1200);
                //
                break;
            //
        }
        //
        //
    }
    //
    /*
    if (WiFi.status() == WL_CONNECTED) {
    */
}
