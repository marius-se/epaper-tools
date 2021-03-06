#include <iostream>

extern "C" {
#include "libs/IT8951/Config/DEV_Config.h"
#include "libs/IT8951/e-Paper/EPD_IT8951.h"
#include "libs/IT8951/GUI/GUI_Paint.h"
}

void clear() {
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

void magic() {
    if(DEV_Module_Init()!=0) {
        DEV_Module_Exit();
        throw std::runtime_error("Could not initialize bcm2835.");
    }
    const uint16_t vcom = 1.48 * 1000;
    IT8951_Dev_Info deviceInfo = EPD_IT8951_Init(vcom);
    uint32_t initTargetMemoryAddress = deviceInfo.Memory_Addr_L | (deviceInfo.Memory_Addr_H << 16);
    uint8_t bitsPerPixel = 4;
    uint8_t a2Mode = 6; // specific for 10.3 inch epaper display

    uint8_t* refreshFrameBuffer = nullptr;

    uint16_t Display_Area_Width = deviceInfo.Panel_W;
    uint16_t Display_Area_Height = deviceInfo.Panel_H;

    uint16_t Display_Area_Sub_Width = Display_Area_Width / 5;
    uint16_t Display_Area_Sub_Height = Display_Area_Height / 5;

    uint32_t imageSize = ((deviceInfo.Panel_W * bitsPerPixel % 8 == 0) ? (deviceInfo.Panel_W * bitsPerPixel / 8 ) : (deviceInfo.Panel_W * bitsPerPixel / 8 + 1)) * deviceInfo.Panel_H;
    refreshFrameBuffer = (uint8_t *)malloc(imageSize);
    //refreshFrameBuffer = new uint8_t(imageSize);

    Paint_NewImage(refreshFrameBuffer, deviceInfo.Panel_W, deviceInfo.Panel_H, 0, BLACK);
    Paint_SetBitsPerPixel(bitsPerPixel);
    Paint_Clear(WHITE);

    const uint16_t stoneSizeInPixel = 100;
    const uint8_t gameSize = 13;
    const uint16_t boardSizeInPixel = (gameSize - 1) * stoneSizeInPixel;
    const uint16_t displayWidth = 1872;
    const uint16_t displayHeight = 1404;

    const uint16_t startPointX = (displayWidth / 2) - (boardSizeInPixel / 2);
    const uint16_t startPointY = (displayHeight / 2) - (boardSizeInPixel / 2);

    for (int x = 0; x <= boardSizeInPixel; x += stoneSizeInPixel) {
        Paint_DrawLine(startPointX + x, startPointY, startPointX + x, startPointY + boardSizeInPixel, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    }
    for (int y = 0; y <= boardSizeInPixel; y += stoneSizeInPixel) {
        Paint_DrawLine(startPointX, startPointY + y, startPointX + boardSizeInPixel, startPointY + y, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    }

/*
    Paint_DrawCircle(300, 300, 50, BLACK, DOT_PIXEL_3X3, DRAW_FILL_EMPTY);
    Paint_DrawCircle(300, 300, 49, WHITE, DOT_PIXEL_3X3, DRAW_FILL_FULL);

    Paint_DrawCircle(300, 400, 50, BLACK, DOT_PIXEL_3X3, DRAW_FILL_FULL);

    Paint_DrawCircle(400, 300, 50, BLACK, DOT_PIXEL_3X3, DRAW_FILL_EMPTY);
    Paint_DrawCircle(400, 300, 49, WHITE, DOT_PIXEL_3X3, DRAW_FILL_FULL);
*/
    //EPD_IT8951_Init_Refresh(deviceInfo, initTargetMemoryAddress);
    //EPD_IT8951_4bp_Refresh(refreshFrameBuffer, 0, 0, Display_Area_Width, Display_Area_Height, false, initTargetMemoryAddress, false);
    //EPD_IT8951_1bp_Refresh(refreshFrameBuffer, 0, 0, Display_Area_Width, Display_Area_Height, a2Mode, initTargetMemoryAddress, false);
    EPD_IT8951_4bp_Refresh(refreshFrameBuffer, 0, 0, Display_Area_Width, Display_Area_Height, false, initTargetMemoryAddress, false);
    delete refreshFrameBuffer;

    EPD_IT8951_Sleep();
    DEV_Delay_ms(5000);
    DEV_Module_Exit();
}

int main() {
    magic();
}
