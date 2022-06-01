#include <Arduino.h>
#include "Definitions.h"
#include "init.h"
#include "GlobalStructs.h"
#include <NMEAParser.h>
#include "myTimers.h"
#include <Preferences.h>

NMEAParser<2> parser;
NMEA_Struct NMEAData;
GlobalVariables myGlobalVariables;
ESPNOWData MyEspNowData;
IMUData myIMUData[def_numIMUToStore];
Preferences prefs;

byte ntripMess[256];
int ntripMessLen = 0;


void setup() {

  recordBootCount();

  pinMode(def_LEDPIN, OUTPUT);

  Serial.begin(115200); //output to serial terminal USB

  Serial1.begin(115200, SERIAL_8N1, def_F9P_RX1, def_F9P_TX1); //connect to the F9P

  delay(100);

  Serial.println("AOG-WiFi-GPS");

  initMacAddress();
  initESPNOW();
  initNMEAParser();
}

void loop() {

  Clock_Tick();

}




