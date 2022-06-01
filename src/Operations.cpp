#include "Operations.h"

void ReadGPSSerial(){
    if(Serial1.available()){
        parser << Serial1.read();
    }
}

void ReadSerial(){
    if(myGlobalVariables.UseUSB){
        if(Serial.available()){

            byte mybyte;

            while(Serial.available()){
                mybyte = Serial.read();
                Serial1.write(mybyte);
            }
        }
    }
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    memcpy(&MyEspNowData, incomingData, sizeof(MyEspNowData));

    switch(MyEspNowData.messageID){
        case 1:
            HandleTimeRecv();
        break;

        case 3:
            myGlobalVariables.lastIMUMesssage = myGlobalVariables.currentTime;
            HandleIMURecv();
        break;

        case 20:
            HandleNtrip(20);
        break;
    }
}

void HandleTimeRecv(){

    Serial.print("Time: "); Serial.print(myGlobalVariables.currentTime);
    Serial.print("  |  Boot Count:"); Serial.println(myGlobalVariables.bootCounter);
    myGlobalVariables.currentTime = MyEspNowData.messageTimeStamp;

}

void HandleIMURecv(){

    for(int loopData = def_numIMUToStore-1; loopData > 0; loopData--){
        myIMUData[loopData] = myIMUData[loopData - 1];
    }

    myIMUData[0].messageTimeStamp = MyEspNowData.messageTimeStamp;
    strlcpy(myIMUData[0].IMU_Heading, MyEspNowData.IMU_Heading, sizeof(myIMUData[0].IMU_Heading));
    strlcpy(myIMUData[0].IMU_Pitch, MyEspNowData.IMU_Pitch, sizeof(myIMUData[0].IMU_Pitch));
    strlcpy(myIMUData[0].IMU_Roll, MyEspNowData.IMU_Roll, sizeof(myIMUData[0].IMU_Roll));
    strlcpy(myIMUData[0].IMU_Yaw, MyEspNowData.IMU_Yaw, sizeof(myIMUData[0].IMU_Yaw));
}

void VTG_Handler(){
    parser.getArg(4, NMEAData.vtgSpeed);
}

void GGA_Handler() //Rec'd GGA
{
    //find the matching IMU reading
    int IMUReading = matchIMU();

    // fix time
    parser.getArg(0, NMEAData.fixTime);

    // latitude
    parser.getArg(1, NMEAData.latitude);
    parser.getArg(2, NMEAData.latNS);

    // longitude
    parser.getArg(3, NMEAData.longitude);
    parser.getArg(4, NMEAData.lonEW);

    // fix quality
    parser.getArg(5, NMEAData.fixQuality);

    // satellite #
    parser.getArg(6, NMEAData.numSats);
    
    // HDOP
    parser.getArg(7, NMEAData.HDOP);
    
    // altitude
    parser.getArg(8, NMEAData.altitude);
    
    // time of last DGPS update
    parser.getArg(12, NMEAData.ageDGPS);

    BuildNmea(IMUReading); //build the string
}

int matchIMU(){
    unsigned long gpsTime = myGlobalVariables.currentTime - def_gpsReadingDelay;

    for(int imuTimes = 0; imuTimes < def_numIMUToStore; imuTimes++){
        if(myIMUData[imuTimes].messageTimeStamp <= gpsTime){
            //Serial.print("imu reading: "); Serial.println(imuTimes);
            return imuTimes;
        }
    }

    return 0;
}

void BuildNmea(int ImuReading){
    strlcpy(MyEspNowData.Panda, "", sizeof(MyEspNowData.Panda));

    strlcat(MyEspNowData.Panda, "$PANDA,", sizeof(MyEspNowData.Panda));

    strlcat(MyEspNowData.Panda, NMEAData.fixTime, sizeof(MyEspNowData.Panda));
    strlcat(MyEspNowData.Panda, ",", sizeof(MyEspNowData.Panda));

    strlcat(MyEspNowData.Panda, NMEAData.latitude, sizeof(MyEspNowData.Panda));
    strlcat(MyEspNowData.Panda, ",", sizeof(MyEspNowData.Panda));

    strlcat(MyEspNowData.Panda, NMEAData.latNS, sizeof(MyEspNowData.Panda));
    strlcat(MyEspNowData.Panda, ",", sizeof(MyEspNowData.Panda));

    strlcat(MyEspNowData.Panda, NMEAData.longitude, sizeof(MyEspNowData.Panda));
    strlcat(MyEspNowData.Panda, ",", sizeof(MyEspNowData.Panda));

    strlcat(MyEspNowData.Panda, NMEAData.lonEW, sizeof(MyEspNowData.Panda));
    strlcat(MyEspNowData.Panda, ",", sizeof(MyEspNowData.Panda));

    // 6
    strlcat(MyEspNowData.Panda, NMEAData.fixQuality, sizeof(MyEspNowData.Panda));
    strlcat(MyEspNowData.Panda, ",", sizeof(MyEspNowData.Panda));

    strlcat(MyEspNowData.Panda, NMEAData.numSats, sizeof(MyEspNowData.Panda));
    strlcat(MyEspNowData.Panda, ",", sizeof(MyEspNowData.Panda));

    strlcat(MyEspNowData.Panda, NMEAData.HDOP, sizeof(MyEspNowData.Panda));
    strlcat(MyEspNowData.Panda, ",", sizeof(MyEspNowData.Panda));

    strlcat(MyEspNowData.Panda, NMEAData.altitude, sizeof(MyEspNowData.Panda));
    strlcat(MyEspNowData.Panda, ",", sizeof(MyEspNowData.Panda));

    //10
    strlcat(MyEspNowData.Panda, NMEAData.ageDGPS, sizeof(MyEspNowData.Panda));
    strlcat(MyEspNowData.Panda, ",", sizeof(MyEspNowData.Panda));

    //11
    strlcat(MyEspNowData.Panda, NMEAData.vtgSpeed, sizeof(MyEspNowData.Panda));
    strlcat(MyEspNowData.Panda, ",", sizeof(MyEspNowData.Panda));

    //12
    strlcat(MyEspNowData.Panda, myIMUData[ImuReading].IMU_Heading, sizeof(MyEspNowData.Panda));
    strlcat(MyEspNowData.Panda, ",", sizeof(MyEspNowData.Panda));

    //13
    strlcat(MyEspNowData.Panda, myIMUData[ImuReading].IMU_Roll, sizeof(MyEspNowData.Panda));
    strlcat(MyEspNowData.Panda, ",", sizeof(MyEspNowData.Panda));

    //14
    strlcat(MyEspNowData.Panda, myIMUData[ImuReading].IMU_Pitch, sizeof(MyEspNowData.Panda));
    strlcat(MyEspNowData.Panda, ",", sizeof(MyEspNowData.Panda));

    //15
    strlcat(MyEspNowData.Panda, myIMUData[ImuReading].IMU_Yaw, sizeof(MyEspNowData.Panda));
    strlcat(MyEspNowData.Panda, "0", sizeof(MyEspNowData.Panda));

    strlcat(MyEspNowData.Panda, "*", sizeof(MyEspNowData.Panda));

    CalculateChecksum();

    strlcat(MyEspNowData.Panda, "\r\n", sizeof(MyEspNowData.Panda));

    SendPandaToNOW();
    SendPandaToUsb();
    //SendNmeaToNetwork(NMEAData.nmea);
}

void CalculateChecksum(){

    const char* asciiHex = "0123456789ABCDEF"; 

    int16_t sum = 0;
    int16_t inx = 0;
    char tmp;

    // The checksum calc starts after '$' and ends before '*'
    for (inx = 1; inx < def_LengthOfPandaString; inx++)
    {
        tmp = MyEspNowData.Panda[inx];

        // * Indicates end of data and start of checksum
        if (tmp == '*')
        {
            break;
        }

        sum ^= tmp;    // Build checksum
    }

    byte chk = (sum >> 4);
    char hex[2] = { asciiHex[chk], 0 };
    strlcat(MyEspNowData.Panda, hex, sizeof(MyEspNowData.Panda));

    chk = (sum % 16);
    char hex2[2] = { asciiHex[chk], 0 };
    strlcat(MyEspNowData.Panda, hex2, sizeof(MyEspNowData.Panda));
}

void SendPandaToNOW(){

    if(!myGlobalVariables.UseUSB){

        MyEspNowData.messageID = 2;

        uint8_t broadcastAddress[] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x01}; //ethernet bridge

        esp_now_peer_info_t peerInfo = {};

        memcpy(&peerInfo.peer_addr, broadcastAddress, 6);
        if (!esp_now_is_peer_exist(broadcastAddress))
        {
            esp_now_add_peer(&peerInfo);
        }

        esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&MyEspNowData, sizeof(MyEspNowData));
    }

}

void SendPandaToUsb(){

    if(myGlobalVariables.UseUSB){
        Serial.print(MyEspNowData.Panda); 
    }
   
}

void HandleNtrip(int ntripEnd){

    for (int loopData = 0; loopData < MyEspNowData.ntripLen; loopData++){          
            Serial1.write((byte)MyEspNowData.Panda[loopData]);
    }

}