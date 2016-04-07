#include "mylib.h"
#include "rle.h"

void drawDecompressedImage(const u16* data);

int main(void)
{
    //REG_DISPCNT = 1027;
    REG_DISPCNT = BG2_ENABLE | MODE3;

    // Call this function with rle2 and rle1 these are harder test cases for you to ensure it works.
    drawDecompressedImage(rle3);

    while(1);
}

/*
    Draws an RLE encoded image decompressed onto the videoBuffer.
    Remember you may only call setPixel when the run length is 2 or less
    You must use DMA if the run length is 3 or greater! (Heavy penalty if you don't follow these rules)
*/
void drawDecompressedImage(const u16* data) {
	int x = 0;
	int y = 0;
	int a = sizeof(data);
	int b = sizeof(data[0]);
    for (int i = 0; i < a/b; i+=2) {
    	if (data[i] >= 3) {
    		//drawColor3(y, x, data[i], data[i+1]);
    		DMA[DMA_CHANNEL_3].src = &(data[i+1]);
    		DMA[DMA_CHANNEL_3].dst = &videoBuffer[x+(240*y)];
    		DMA[DMA_CHANNEL_3].cnt = data[i] | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED | DMA_ON;
    		x += data[i];
	    	if (x >= 240) {
	    		y += x/240;
				x = x%240;
			}
    	} else {
    		for (int j = 0; j < data[i]; j++) {
    			setPixel(x, y, data[i+1]);
    			x++;
		    	if (x >= 240) {
		    		y += x/240;
					x = x%240;
				}
    		}
    	}
    }
}
