#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <Arduino.h>
#include "GlobalStructs.h"
//#include <WiFi.h>
//#include "AOGNetworking.h"
#include <NMEAParser.h>
//#include <esp_now.h>
#include <esp_now.h>

extern NMEAParser<2> parser;
extern byte ntripMess[256];
extern int ntripMessLen;

void ReadGPSSerial();
void ReadSerial();
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
void HandleTimeRecv();
void HandleIMURecv();
void VTG_Handler();
void GGA_Handler();
int matchIMU();
void BuildNmea(int ImuReading);
void CalculateChecksum();
void SendPandaToNOW();
void SendPandaToUsb();
void HandleNtrip(int ntripEnd);
//void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);


#endif