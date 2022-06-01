#include "init.h"

void initVariables(){
    myGlobalVariables.UseUSB = def_UseUSB;
}

void initMacAddress(){

    WiFi.mode(WIFI_AP_STA);

    uint8_t newMac[] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x02};

    esp_wifi_set_mac(WIFI_IF_STA, &newMac[0]);
    Serial.print("New Mac address : "); Serial.println(WiFi.macAddress());

}


void initESPNOW(){

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        ESP.restart();
    } else {
        esp_now_register_recv_cb(OnDataRecv);
        //esp_now_register_send_cb(OnDataSent);
    }

 
}


void initNMEAParser(){
    //parser.setErrorHandler(parserErrorHandler);
    parser.addHandler("G-GGA", GGA_Handler);
    parser.addHandler("G-VTG", VTG_Handler);
}

void recordBootCount(){
    prefs.begin("crashdata", false);
    myGlobalVariables.bootCounter = prefs.getInt("boot_cnt", 0);
    myGlobalVariables.bootCounter++;
    prefs.putInt("boot_cnt", myGlobalVariables.bootCounter);
    prefs.end();
}



void ClearFlash() {
    nvs_flash_erase(); // erase the NVS partition and...
    nvs_flash_init(); // initialize the NVS partition.

    while(true);
}
