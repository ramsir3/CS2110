#include <stdlib.h>
#include <stdio.h>
#include "ball.h"
#include "paddle.h"
#include "title.h"
#include "win.h"
#include "gameover.h"
#include "level.h"

typedef unsigned short u16;
typedef unsigned int u32;

//DMA
typedef struct {
	const volatile void *src;
	volatile void *dst;
	volatile u32 cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER*) 0x40000B0)
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

#define REG_DISPCNT *(u16*) 0x4000000
#define BG2_EN (1 << 10)
#define MODE_3 3
#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006

//Colors

#define RGB(r,g,b) ((r)|((g)<<5)|((b)<<10))
#define RED RGB(31,0,0)
#define GREEN RGB(0,31,0)
#define BLUE RGB(0,0,31)
#define CYAN RGB(0,31,31)
#define MAGENTA RGB(31,0,31)
#define YELLOW RGB(31,31,0)
#define BLACK 0
#define WHITE RGB(31,31,31)


#define OFFSET(r,c,nc) ((r)*(nc)+(c))

extern u16 *videoBuffer;

//Text
extern const unsigned char fontdata_6x8[12288];

// *** Input =========================================================

// Buttons

#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

#define BUTTONS *(unsigned int *)0x4000130

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

#define LIVES (3)

typedef struct {
	int x;
	int y;
	int width;
	int height;
	int health;
} BRICK;

#define BRICK_WIDTH (30)
#define BRICK_HEIGHT (10)

typedef struct {
	BRICK* bounds;
	int vx;
} PADDLE;

#define PADDLE_SPEED (3)

typedef struct {
	BRICK* bounds;
	int vx;
	int vy;
} BALL;

/* drawImage3
* A function that will draw an arbitrary sized image
* onto the screen (with DMA).
* @param r row to draw the image
* @param c column to draw the image
* @param width width of the image
* @param height height of the image
* @param image Pointer to the first element of the image.
*/
void drawImage3(int r, int c, int width, int height, const u16* image);
void drawColor3(int r, int c, int width, int height, short* color);
void drawBrick3(BRICK brick, short* color);
void drawPaddle3(BRICK in, const u16* image);
BRICK** init(int rows, int num, PADDLE* p, BALL* b, short* color);
void fillScreen3(short* color);
void waitForVBlank();
void initPaddle(PADDLE* p);
void initBall(BALL* b);
int collide(BRICK b, BRICK o);
int collideWall(BALL* ball);
void setPixel(int r, int c, short color);
void drawChar(int row, int col, char ch, short color);
void drawString(int row, int col, char *str, short color);