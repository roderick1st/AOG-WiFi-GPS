#ifndef GLOBALSTRUCTS_H
#define GLOBALSTRUCTS_H

#include "Definitions.h"

struct GlobalVariables { 
    unsigned long lastMillis;
    unsigned long newMillis;
    unsigned long currentTime; 
    unsigned long previousTime;
    unsigned long hundredthSecond;
    unsigned long tenthSecond;
    unsigned long oneSecond;
    unsigned long lastIMUMesssage;
    bool UseUSB;
    int bootCounter;
};
extern GlobalVariables myGlobalVariables;

struct NMEA_Struct{ //holds data from the parser
    char fixTime[12];
    char latitude[15];
    char latNS[3];
    char longitude[15];
    char lonEW[3];
    char fixQuality[2];
    char numSats[4];
    char HDOP[5];
    char altitude[12];
    char ageDGPS[10];
    char vtgSpeed[10];
};
extern NMEA_Struct NMEAData;

struct ESPNOWData{
    int messageID;
    unsigned long messageTimeStamp;

    char IMU_Roll[6];
    char IMU_Pitch[6];
    char IMU_Heading[6];
    char IMU_Yaw[6];

    char Panda[def_LengthOfPandaString];

    int ntripLen;
};
extern ESPNOWData MyEspNowData;


struct IMUData{
    unsigned long messageTimeStamp;
    char IMU_Roll[6];
    char IMU_Pitch[6];
    char IMU_Heading[6];
    char IMU_Yaw[6];
};
extern IMUData myIMUData[def_numIMUToStore];


#endif