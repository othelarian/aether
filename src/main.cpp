//#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>

#include "structures.h"
#include "conf.h"

// PLAN #########################################

/*
1.  CONNECT TO SSIDs, with preferences           --> DONE
1b. ENABLE REACTING TO BAD PWD NETWORK           --> DONE
3.  SENDING UDP DATAGRAM                         --> DONE
3b. PARSING DATAGRAM WITH USEFUL INFOS           --> IN PROGRESS
4.  HANDLE INFO REQUEST                          --> IN PROGRESS
5.  SETUP LED                                    --> DONE
6.  HANDLE SETUP LEDS COLOR                      --> SOON
7.  BUILTIN PRESETS                              --> EVOLUTION
*/

// GLOBAL VARIABLES #############################

bool getnet = false;
int sel_lvl = 0;
Def_Reseau sel_reseau = {"", ""};
bool good_ssid[CONF_NB_RESEAUX];
ESP8266WebServer server(LOCAL_SERVER_PORT);
WiFiUDP udp;
char replyPacket[] = "AEx"+AETHER_CODE;
CRGB leds[LED_QTY];

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
                sel_reseau.ssid = CONF_RESEAUX[j].ssid;
                sel_reseau.pwd = CONF_RESEAUX[j].pwd;
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
    if (!getnet) { delay(2000); } // delay the next scan in 5 seconds
    else {
        // try to connect to the selected network
        WiFi.begin(sel_reseau.ssid.c_str(), sel_reseau.pwd.c_str());
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

// insert IP address in udp message
void parsingAddr() {
    //
    // TODO : parse the IP address
    //
}

// SERVER HANDLERS ##############################

void get_beatheart() {
    server.send(200, "text/plain", "beat");
}

void get_info() {
    //
    String message;
    //
    // TODO : send info
    //
    message = "touch the info";
    //
    // TODO : check AETHER_CODE
    //
    // TODO : resend type
    // TODO : send number of leds
    // TODO : send if builtin presets available
    //
    server.send(200, "text/plain", message);
}

void set_leds() {
    //
    // TODO : setup all the leds
    //
}

void set_led() {
    //
    // TODO : setup one led
    //
}

void configure_preset() {
    //
    // TODO : configure a selected preset
    //
}

void launch_preset() {
    //
    // TODO : launch a selected preset
    //
}

// GENERAL PART #################################

void setup() {
    // setup some global variables
    for (int i = 0; i < CONF_NB_RESEAUX; i++) { good_ssid[i] = true; }
    // setup the wifi
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    // setup server
    server.on("/alive", get_beatheart);
    server.on("/info", get_info);
    server.on("/led", set_led);
    server.on("/leds", set_leds);
    server.on("/configure", configure_preset);
    server.on("/launch", launch_preset);
    // setup udp message
    replyPacket[2] = AETHER_TYPE;
    // setup leds
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLOR_ORDER>(leds, LED_QTY).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(LED_BRIGHTNESS);
    for (int i = 0;i<LED_QTY;i++) { leds[i] = CRGB::Black; }
    FastLED.show();
    // ready to go
    delay(100);
}

void loop() {
    // if not connected, try to connect
    if (!getnet) {
        leds[0] = CRGB::Red;
        for (int i = 1;i<LED_QTY;i++) { leds[i] = CRGB::Black; }
        FastLED.show();
        delay(400);
        connecting();
        if (getnet) { leds[0] = CRGB::Yellow; FastLED.show(); }
        delay(400);
        parsingAddr();
        leds[0] = CRGB::Green;
        FastLED.show();
        delay(400);
    }
    else {
        // check if the connection is still up
        if (WiFi.status() == WL_CONNECTION_LOST || WiFi.status() != WL_CONNECTED) { getnet = false; }
        else {
            //
            udp.beginPacket("255.255.255.255", SENDING_UDP_PORT);
            udp.write(replyPacket);
            udp.endPacket();
            //
            leds[0] = CRGB::Blue;
            FastLED.show();
            //
            delay(1000);
            //
            leds[0] = CRGB::Black;
            FastLED.show();
            //
            delay(1000);
            //
        }
    }
}
