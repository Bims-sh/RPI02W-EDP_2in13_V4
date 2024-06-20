#include <cstdlib>
#include "lib/Config/DEV_Config.h"
#include "lib/e-Paper/EPD_2in13_V4.h"
#include "lib/GUI/GUI_BMPfile.h"
#include "lib/GUI/GUI_Paint.h"

int main() {
    if (DEV_Module_Init() != 0) {
        printf("Failed to initialize\r\n");
        return -1;
    }

    UBYTE *BlackImage;
    UWORD Imagesize = (EPD_2in13_V4_WIDTH / 8 + 1) * EPD_2in13_V4_HEIGHT;

    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }

    Paint_NewImage(BlackImage, EPD_2in13_V4_WIDTH, EPD_2in13_V4_HEIGHT, 90, WHITE);

    EPD_2in13_V4_Init();
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);

    Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 55, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);

    Paint_DrawLine(20, 10, 70, 60, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(70, 10, 20, 60, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawRectangle(20, 10, 70, 60, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(85, 10, 135, 60, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    Paint_DrawLine(45, 15, 45, 55, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(25, 35, 70, 35, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawCircle(45, 35, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(110, 35, 20, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    Paint_DrawString_EN(140, 15, "waveshare", &Font16, BLACK, WHITE);
    Paint_DrawNum(140, 40, 123456789, &Font16, BLACK, WHITE);

    EPD_2in13_V4_Display_Base(BlackImage);
    DEV_Delay_ms(3000);

    printf("Done!\r\n");

    return 0;
}