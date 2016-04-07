#include "mylib.h"

// State enum definition
enum GBAState {
	START_NODRAW,
	TITLE_SCREEN,
	GAME,
	LOSE,
	WIN
};

enum LevelState {
	LEVEL_NODRAW,
	LEVEL1,
	LEVEL2,
	LEVEL3,
	LEVEL_WIN
};

int main() {
	REG_DISPCNT = BG2_EN | MODE_3;

	//instantiate state variables
	enum GBAState state = TITLE_SCREEN;
	enum GBAState nextState = GAME;
	u16 prevButtonSelect = KEY_DOWN_NOW(BUTTON_SELECT);
	u16 prevButtonStart = KEY_DOWN_NOW(BUTTON_START);
	short bgColor = BLACK;
	short brickColor = YELLOW;
	//short color = WHITE;

	//instantiate level state variables
	int lives = LIVES;
	int redoLevel = 1;
	enum LevelState level = LEVEL1;
	enum LevelState nextLevel = LEVEL1;
	int bricksLeft = 0;
	int r = 0;
	int c = 0;

	//instantiate objects
	BRICK pbounds = {.x = 0, .y = 0, .width = PADDLE_WIDTH, .height = PADDLE_HEIGHT};
	PADDLE paddle = {.bounds = &pbounds, .vx = 0};
	BRICK bbounds = {.x = 0, .y = 0, .width = BALL_WIDTH, .height = BALL_HEIGHT};
	BALL ball = {.bounds = &bbounds, .vx = 0, .vy = 0};
	BRICK** brick_arr = init(r, c, &paddle, &ball, &bgColor);

	while(1) {
		waitForVBlank();
		switch(state) {
		case START_NODRAW:
			if (prevButtonStart == 0 && KEY_DOWN_NOW(BUTTON_START)) {
				state = nextState;
			}
			// if (prevButtonSelect == 0 && KEY_DOWN_NOW(BUTTON_SELECT)) {
			// 	state = nextState;
			// }
			break;
		case TITLE_SCREEN:
			drawImage3(0, 0, TITLE_WIDTH, TITLE_HEIGHT, title_data);
			state = START_NODRAW;
			nextState = GAME;
			break;
		case WIN: ;
			drawImage3(0, 0, TITLE_WIDTH, TITLE_HEIGHT, win_data);
			state = START_NODRAW;
			nextState = GAME;
			level = LEVEL1;
			redoLevel = 1;
			lives = 3;
			break;
		case LOSE: ;
			drawImage3(0, 0, TITLE_WIDTH, TITLE_HEIGHT, gameover_data);
			state = START_NODRAW;
			nextState = GAME;
			level = LEVEL1;
			redoLevel = 1;
			lives = 3;
			break;
		case GAME:

			switch(level) {
			case LEVEL_NODRAW:
				if (/*prevButtonStart == 0 && */KEY_DOWN_NOW(BUTTON_START)) {
					level = nextLevel;
					redoLevel = 1;
				}
				break;
			case LEVEL_WIN: ;
				drawImage3(0, 0, TITLE_WIDTH, TITLE_HEIGHT, level_data);
				level = LEVEL_NODRAW;
				redoLevel = 1;
				break;
			case LEVEL1:
				//initialize
				if (redoLevel) {
					r = 2;
					c = 4;
					nextLevel = LEVEL2;
					brickColor = RED;

					free(brick_arr);
					brick_arr = init(r, c, &paddle, &ball, &bgColor);
					bricksLeft = r*c;
					redoLevel = 0;
				}
				//win checking
				if (bricksLeft <= 0) {
					level = LEVEL_WIN;
				}
				//loss checking
				if (lives <= 0) {
					state = LOSE;
				}
				break;
			case LEVEL2:
				//initialize
				if (redoLevel) {
					r = 3;
					c = 5;
					nextLevel = LEVEL3;
					brickColor = BLUE;

					free(brick_arr);
					brick_arr = init(r, c, &paddle, &ball, &bgColor);
					bricksLeft = r*c;
					redoLevel = 0;
				}
				//win checking
				if (bricksLeft <= 0) {
					level = LEVEL_WIN;
				}
				//loss checking
				if (lives <= 0) {
					state = LOSE;
				}
				break;
			case LEVEL3:
				//initialize
				if (redoLevel) {
					r = 2;
					c = 6;
					brickColor = YELLOW;

					free(brick_arr);
					brick_arr = init(r, c, &paddle, &ball, &bgColor);
					bricksLeft = r*c;
					redoLevel = 0;
				}
				//win checking
				if (bricksLeft <= 0) {
					state = WIN;
				}
				//loss checking
				if (lives <= 0) {
					state = LOSE;
				}
				break;
			}
			if (level != LEVEL_NODRAW && level != LEVEL_WIN) {
				drawColor3(0, 0, 240, 9, &brickColor);
				char str[9];
				sprintf(str, "LIVES: %d", lives);
				drawString(1,180, str, BLACK);
				// if (level == LEVEL_NODRAW) {
				// 	drawString(1,0,"LEVEL_NODRAW", BLACK);
				// }
				// if (level == LEVEL_WIN) {
				// 	drawString(1,0,"LEVEL_WIN", BLACK);
				// }
				if (level == LEVEL1) {
					drawString(1,0,"LEVEL 1", BLACK);
				}
				if (level == LEVEL2) {
					drawString(1,0,"LEVEL 2", BLACK);
				}
				if (level == LEVEL3) {
					drawString(1,0,"LEVEL 3", BLACK);
				}
				// if (state == START_NODRAW) {
				// 	drawString(1,100,"START_NODRAW", BLACK);
				// }
				// if (state == GAME) {
				// 	drawString(1,100,"GAME", BLACK);
				// }
				// if (state == TITLE_SCREEN) {
				// 	drawString(1,100,"TITLE_SCREEN", BLACK);
				// }
				//handle pausing
				if (KEY_DOWN_NOW(BUTTON_SELECT)) {
					state = TITLE_SCREEN;
					redoLevel = 1;
				}

				//handle paddle movement
				if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
					paddle.vx = PADDLE_SPEED;
				} else if (KEY_DOWN_NOW(BUTTON_LEFT)) {
					paddle.vx = -1*PADDLE_SPEED;
				} else {
					paddle.vx = 0;
				}
				if (KEY_DOWN_NOW(BUTTON_UP)) {
					ball.vy = 2;
				}

				//handle brick drawing and ball brick collisions
				for (int i = 0; i < r; i++) {
					for (int j = 0; j < c; j++) {
						if (collide(*ball.bounds, brick_arr[i][j]) && brick_arr[i][j].health > 0) {
							ball.vy *= -1;
							brick_arr[i][j].health = 0;
							drawBrick3(brick_arr[i][j], &bgColor);
							bricksLeft--;
						} else if (brick_arr[i][j].health > 0) {
							drawBrick3(brick_arr[i][j], &brickColor);
						}
					}
				}

				//handle ball wall collisions
				int l = collideWall(&ball);
				if (l) {
					lives--;
					redoLevel = 1;
				}
				//handle ball paddle collisions
				int c = collide(*ball.bounds, *paddle.bounds);
				if (c) {
					int v = (((ball.bounds)->x + (ball.bounds)->width/2) - ((paddle.bounds)->x + (paddle.bounds)->width/2));
					ball.vx = v/5;
					ball.vy *= -1;
				}

				//clean up old paddle and ball positions
				drawBrick3(*paddle.bounds, &bgColor);
				drawBrick3(*ball.bounds, &bgColor);

				//update ball and paddle positions
				(ball.bounds)->y += ball.vy;
				(ball.bounds)->x += ball.vx;
				//handle paddle wall collision
				if (((paddle.bounds)->x + paddle.vx < (240 - PADDLE_WIDTH) && paddle.vx > 0) || ((paddle.bounds)->x + paddle.vx > 0 && paddle.vx < 0)) {
					(paddle.bounds)->x += paddle.vx;
				}

				//draw ball and paddle
				drawPaddle3(*(paddle.bounds), paddle_data);
				drawPaddle3(*(ball.bounds), ball_data);

				break;

			}
		}
		prevButtonSelect = KEY_DOWN_NOW(BUTTON_SELECT);
		prevButtonStart = KEY_DOWN_NOW(BUTTON_START);
	}
	return 0;
}