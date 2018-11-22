//#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "conf.h"

// PLAN #########################################

/*
1.  CONNECT TO SSIDs, with preferences           --> DONE
1b. ENABLE REACTING TO BAD PWD NETWORK           --> DONE
2.  RECEPTION OF UDP REQUEST                     --> IN PROGRESS
3.  SENDING UDP datagram with full informations
4.  CONNECT TO THE APP
5.  SETUP LED
*/

// GLOBAL VARIABLES #############################

bool getnet = false;
int sel_lvl = 0;
String sel_ssid = "";
String sel_pwd = "";
bool good_ssid[CONF_NB_RESEAUX];

// HELPERS ######################################

// scanning network and check if there is one in the whitelist available
bool scanning() {
    bool res = false;
    int nbn = WiFi.scanNetworks();
    sel_lvl = CONF_NB_RESEAUX;
    for (int i = 0; i < nbn; i++) {
        String tmp_ssid = WiFi.SSID(i);
        for (int j = 0; j < sel_lvl; j++) {
            if (good_ssid[j] && tmp_ssid == CONF_RESEAUX[j].ssid) {
                sel_lvl = j;
                sel_ssid = CONF_RESEAUX[j].ssid;
                sel_pwd = CONF_RESEAUX[j].pwd;
                res = true;
                break;
            }
        }
    }
    return res;
}

// if there is no connection, this function try to init a new wireless setup
void connecting() {
    // scan for available network, with the conf.h whitelist
    getnet = scanning();
    // if there is no network available
    if (!getnet) { delay(5000); } // delay the next scan in 5 seconds
    else {
        // try to connect to the selected network
        WiFi.begin(sel_ssid.c_str(), sel_pwd.c_str());
        // loop until the esp succeed to connect, or failed
        bool tryconnect = true;
        while (tryconnect) {
            if (WiFi.status() == WL_CONNECT_FAILED) {
                getnet = false;
                good_ssid[sel_lvl] = false;
                delay(1000);
                tryconnect = false;
            }
            else if (WiFi.status() == WL_CONNECTED) {
                tryconnect = false;
            }
            delay(300);
        }
    }
}

// GENERAL PART #################################

void setup() {
    // TEST PURPOSE
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    // TEST END
    // setup some global variables
    for (int i = 0; i < CONF_NB_RESEAUX; i++) { good_ssid[i] = true; }
    // setup the wifi
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    // ready to go
    delay(100);
}

void loop() {
    // if not connected, try to connect
    if (!getnet) { connecting(); }
    else {
        // check if the connection is still up
        if (WiFi.status() == WL_CONNECTION_LOST || WiFi.status() != WL_CONNECTED) { getnet = false; }
        else {
            //
            switch(sel_lvl) {
                case 0:
                    //
                    digitalWrite(LED_BUILTIN, LOW);
                    delay(200);
                    digitalWrite(LED_BUILTIN, HIGH);
                    delay(200);
                    //
                    break;
                case 1:
                    //
                    digitalWrite(LED_BUILTIN, LOW);
                    delay(800);
                    digitalWrite(LED_BUILTIN, HIGH);
                    delay(200);
                    //
                    break;
                //
            }
            //
        }
        //
    }
}
