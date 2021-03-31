#include <iostream>

extern "C" {
#include "libs/IT8951/Config/DEV_Config.h"
#include "libs/IT8951/e-Paper/EPD_IT8951.h"
}

int main() {
    if(DEV_Module_Init()!=0) {
        DEV_Module_Exit();
        throw std::runtime_error("Could not initialize bcm2835.");
    }

    const uint16_t vcom = 1.48 * 1000;
    IT8951_Dev_Info deviceInfo = EPD_IT8951_Init(vcom);
    uint32_t initTargetMemoryAddress = deviceInfo.Memory_Addr_L | (deviceInfo.Memory_Addr_H << 16);

    EPD_IT8951_Init_Refresh(deviceInfo, initTargetMemoryAddress);
    EPD_IT8951_Sleep();

    DEV_Delay_ms(5000);
    DEV_Module_Exit();
}
