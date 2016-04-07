#include "mylib.h"

u16* videoBuffer = (u16*) 0x6000000;

void setPixel(int x, int y, u16 color)
{
    videoBuffer[y * 240 + x] = color;
}

void drawColor3(int r, int c, int run, u16 color) {
    DMA[DMA_CHANNEL_3].src = &color;
    DMA[DMA_CHANNEL_3].dst = &videoBuffer[OFFSET(r, c, 240)];
    DMA[DMA_CHANNEL_3].cnt = run | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED | DMA_ON;
}


void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}
