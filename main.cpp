#include <iostream>

#include "./libs/IT8951/Config/DEV_Config.h"
#include "./libs/IT8951/e-Paper/EPD_IT8951.h"

IT8951_Dev_Info deviceInfo;
uint16_t panelWidth;
uint16_t panelHeight;
uint32_t initTargetMemoryAddress;
char* lutVersion;
uint8_t a2Mode;

int main() {
    if(DEV_Module_Init()!=0){
        DEV_Module_Exit();
        throw std::runtime_error("Could not initialize bcm2835.");
    }

    const uint16_t vcom = 1.48 * 1000;
    deviceInfo = EPD_IT8951_Init(vcom);
    panelWidth = deviceInfo.Panel_W;
    panelHeight = deviceInfo.Panel_H;
    initTargetMemoryAddress = deviceInfo.Memory_Addr_L | (deviceInfo.Memory_Addr_H << 16);
    lutVersion = (char*)deviceInfo.LUT_Version;

    if (strcmp(lutVersion, "M841_TFA5210") == 0 ){
        //10.3inch e-Paper HAT(1872,1404)
        a2Mode = 6;
    } else {
        DEV_Module_Exit();
        EPD_IT8951_Sleep();
        throw std::runtime_error("Unsupported E Paper display.");
    }

    EPD_IT8951_Init_Refresh(deviceInfo, initTargetMemoryAddress);
    EPD_IT8951_Sleep();

    DEV_Delay_ms(5000);
    DEV_Module_Exit();
}
