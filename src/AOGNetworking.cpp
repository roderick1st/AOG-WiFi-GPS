//#include "AOGNetworking.h"

/*
void initNtrip(){

    pinMode(def_LEDPIN, OUTPUT);

    SystemSettings.AogNtripPort = 2233;
    UdpHandler.listen(SystemSettings.AogNtripPort);

    UdpHandler.onPacket([](AsyncUDPPacket packet){

        digitalWrite(def_LEDPIN, HIGH);
            
                for (unsigned int i = 0; i < packet.length(); i++) //loop through the packet
                {
                    Serial1.write(packet.data()[i]); //send each byte to the F9P        
                } 
        digitalWrite(def_LEDPIN, LOW);
    
    });
}

void SendNmeaToNetwork(char * ptr_nmea){

    UdpHandler.broadcastTo(ptr_nmea, 9999);
    //UdpHandler.broadcastTo(ptr_nmea, 5544);

}

void SendNmeaToUsb(char * ptr_nmea){

    

    Serial.print(ptr_nmea);
    //Serial.print("TimeStamp:"); Serial.println(NOW_IMU.IMU_TimeStamp);

  

}
*/

 