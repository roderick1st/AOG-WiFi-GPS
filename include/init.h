#ifndef INIT_H
#define INIT_H

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include "GlobalStructs.h"
#include "Operations.h"
#include <NMEAParser.h>
#include "Definitions.h"
#include <Preferences.h>
#include <nvs_flash.h>

//extern esp_now_peer_info_t peerInfo;
extern NMEAParser<2> parser;
extern Preferences prefs;


void initMacAddress();
void initESPNOW();
void initNMEAParser();
void recordBootCount();
void ClearFlash();

#endif