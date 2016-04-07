#include "mylib.h"

u16 *videoBuffer = (u16*) 0x6000000;

void setPixel(int r, int c, short color) {
	videoBuffer[OFFSET(r, c, 240)] = color;
}

void drawChar(int row, int col, char ch, short color)
{
    int r, c;
    for(r=0; r<8; r++)
    {
        for(c=0; c<6; c++)
        {
            if(fontdata_6x8[OFFSET(r, c, 6) + ch*48])
            {
                setPixel(row+r, col+c, color);
            }
        }
    }
}

void drawString(int row, int col, char *str, short color)
{
    while(*str)
    {
        drawChar(row, col, *str++, color);
        col+= 6;
    }
}


void drawImage3(int r, int c, int width, int height, const u16* image) {
    int i;
    for(i=0; i<height; i++)
    {
        DMA[DMA_CHANNEL_3].src = image + i*width;
        DMA[DMA_CHANNEL_3].dst = &videoBuffer[OFFSET(r+i, c, 240)];
        DMA[DMA_CHANNEL_3].cnt = width | DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT | DMA_ON;
    }
}

void drawColor3(int r, int c, int width, int height, short* color) {
    int i;
    for(i=0; i<height; i++)
    {
        DMA[DMA_CHANNEL_3].src = color;
        DMA[DMA_CHANNEL_3].dst = &videoBuffer[OFFSET(r+i, c, 240)];
        DMA[DMA_CHANNEL_3].cnt = width | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED | DMA_ON;
    }
}

void drawBrick3(BRICK in, short* color) {
	drawColor3(in.y, in.x, in.width, in.height, color);
}


void drawPaddle3(BRICK in, const u16* image) {
	drawImage3(in.y, in.x, in.width, in.height, image);
}

void fillScreen3(short* color) {
	DMA[DMA_CHANNEL_3].src = color;
    DMA[DMA_CHANNEL_3].dst = videoBuffer;
    DMA[DMA_CHANNEL_3].cnt = 240*160 |
    						 DMA_SOURCE_FIXED |
                             DMA_DESTINATION_INCREMENT |
                             DMA_ON;
}

void waitForVBlank() {
    while(SCANLINECOUNTER > 160);
    while(SCANLINECOUNTER < 160);
}


BRICK** init(int rows, int num, PADDLE* p, BALL* b, short* color) {
	//short c = BLUE;
	fillScreen3(color);
	initPaddle(p);
	initBall(b);

	int hpad = (240-(num*(BRICK_WIDTH+5)))/2;

	BRICK** brick_arr = (BRICK**)malloc(rows*sizeof(BRICK*));
	for ( int i = 0; i < rows; i++ ) {
		brick_arr[i] = (BRICK*)malloc(num*sizeof(BRICK));
   	}
	for (int i = 0; i < rows; i++) {
		for (int n = 0; n < num; n++) {
			brick_arr[i][n].x = hpad+(n*(BRICK_WIDTH+5));
			brick_arr[i][n].y = 19+(i*(BRICK_HEIGHT+5));
			brick_arr[i][n].width = BRICK_WIDTH;
			brick_arr[i][n].height = BRICK_HEIGHT;
			brick_arr[i][n].health = 1;
			//drawBrick3(brick_arr[i][n], &c);
		}
	}
	return brick_arr;
}

void initPaddle(PADDLE* p) {
	(p->bounds)->x = 120 - PADDLE_WIDTH/2;
	(p->bounds)->y = 160 - PADDLE_HEIGHT;
	p->vx = 0;
}

void initBall(BALL* b) {
	(b->bounds)->x = 120 - BALL_WIDTH/2;
	(b->bounds)->y = 160 - PADDLE_HEIGHT - BALL_HEIGHT - 5;
	b->vx = 0;
	b->vy = 0;
}

int collide(BRICK b, BRICK o) {
	if ((b.y + b.height >= o.y) && (b.y + b.height <= o.y + o.height) ) {
		if ( (b.x <= o.x + o.width) && (b.x + b.width >= o.x) ) {
			return 1;
		}
	}
	return 0;
}

int collideWall(BALL* ball) {
	BRICK b = *(ball->bounds);
	if (b.y <= 0+9) {
		ball->vy *= -1;
	}
	if (b.y >= 160 - BALL_HEIGHT) {
		//lose life
		return 1;
		ball->vy *= -1;
	}
	if (b.x <= 0 || b.x >= 240 - BALL_WIDTH) {
		ball->vx *= -1;
	}
	return 0;
}
