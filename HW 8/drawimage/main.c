// Draw an image from bmptoc
// Name: Ramamurthy Siripuram

// If you want to test this with one of your own images, you may do so by
// including the appropriate header file. However, when you submit this file,
// it must contain ONLY #include "diddy.h" or else our grader will not work
// and you will not receive credit for this file.
#include "title.h"

#define REG_DISPCNT *(unsigned short*) 0x4000000
#define MODE_3 3
#define BG2_EN (1 << 10)

unsigned short *videoBuffer = (unsigned short*) 0x6000000;

void drawImage3(int x, int y, int width, int height, const unsigned short *image) {

	// TODO Draw the image with the top left corner at (x,y).
	// Recall that the GBA screen is 240 pixels wide, and 160 tall.
	// The videoBuffer is a 1-dimensional array of these pixels.
	// For example, to set pixel (37,21) to white:
	//   videoBuffer[21 * 240 + 37] = 0x7FFF;

	for (int i = 0; i < 240; i++) {
		for (int j = 0; j < 160; j++) {
			if ( !(i < x || j < y || i >= x + width || j >= y + height) ) {
				videoBuffer[(240 * j) + i] = image[(width * (j - y)) + (i - x)];
			}
		}
	}

}

int main() {

	// 1. TODO Set REG_DISPCNT appropriately for drawing in mode 3.
	// Use the #define fields near the top of this file to accomplish this.



	// 2. TODO Call your drawing function using parameters from the header.
	// You can use whatever you want for X and Y. If you use a high X and the width
	// goes beyond the edge of the screen, it will wrap around onto the next line.
	// This is normal.
	// You may test your own images with calls to drawImage3 here using the
	// appropriate fields from your header, but when you submit this file it
	// must contain ONLY a valid call using the diddy.h parameters, or else
	// our grader will not work and you will not receive credit for this file.



	// 3. (already done) wait forever after drawing.
	REG_DISPCNT = MODE_3 | BG2_EN;
	drawImage3(0,0,TITLE_WIDTH,TITLE_HEIGHT,title_data);
	while(1);
	return 0;
}

