
#include "myTimers.h"

void Clock_Tick(){

    ReadGPSSerial();
    ReadSerial();

    myGlobalVariables.newMillis = millis();

    unsigned long timePassed = myGlobalVariables.newMillis - myGlobalVariables.lastMillis;

    myGlobalVariables.lastMillis = myGlobalVariables.newMillis;

    myGlobalVariables.currentTime = myGlobalVariables.currentTime + timePassed;

    if((myGlobalVariables.currentTime - myGlobalVariables.previousTime) >= 10){ //1/100th of a second
        
        myGlobalVariables.previousTime = myGlobalVariables.currentTime;
        hundredthSecond();

    }

}

void hundredthSecond(){
    
    myGlobalVariables.hundredthSecond++;

    if(myGlobalVariables.hundredthSecond >= 10){
        
        myGlobalVariables.hundredthSecond = 0;
        tenthSecond();

    }

}

void tenthSecond(){

    myGlobalVariables.tenthSecond++;

    if(myGlobalVariables.tenthSecond >= 10){
        
        myGlobalVariables.tenthSecond = 0;
        oneSecond();

    }

}


void oneSecond(){

    //make everything 0 if we loose imu data

    if((myGlobalVariables.currentTime - myGlobalVariables.lastIMUMesssage) > 2000){
        strlcpy(MyEspNowData.IMU_Heading, "0", sizeof(MyEspNowData.IMU_Heading));
        strlcpy(MyEspNowData.IMU_Pitch, "0", sizeof(MyEspNowData.IMU_Pitch));
        strlcpy(MyEspNowData.IMU_Roll, "0", sizeof(MyEspNowData.IMU_Roll));
        strlcpy(MyEspNowData.IMU_Yaw, "0", sizeof(MyEspNowData.IMU_Yaw));
        HandleIMURecv();
    }
}