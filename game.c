#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#include "ball.h"
#include "sprite.h"
#include "player.h"
#include "spriteInteraction.h"
#include "ncurses_win_functions.h"

#define PI 3.14159265

#define WAIT 50000

Sprite playerLeft;
Sprite playerRight;
Sprite ball;

int charCommand = 0;

// u ncurses_win_functions omogući dohvaćanje veličine prozora itd.
int winHeight = 0;
int winWidth = 0;

int ballDirectionLeftRight = 0;
int ballDirectionUpDown = 0;
double ballAngle = 0;

void init () {
	initNcurses ();

	getWindowDimensions (stdscr, &winHeight, &winWidth);

	ball = (Sprite) {
		.id = 100,
		.name = "Ball",
		.object = newwin (BALL_HEIGHT, BALL_WIDTH, BALL_START_Y (winHeight), 
			BALL_START_X (winWidth)),
		.positionY = BALL_START_Y (winHeight)
	};
	ballDirectionLeftRight = BALL_DIRECTION_LEFT;

	playerLeft = (Sprite) {
		.id = 1,
		.name = "Player 1",
	};
	playerLeft.object = newwin (PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_START_Y (winHeight), 
			PLAYER_START_X (playerLeft.id, winWidth));	// zamijeni brojke s varijablama
	
	playerRight = (Sprite) {
		.id = 2,
		.name = "Player 2",
	};
	playerRight.object = newwin (PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_START_Y (winHeight), 
			PLAYER_START_X (playerRight.id, winWidth));
}

void loadContent () {

}

void draw () {	
	refresh();

	wborder(ball.object, ' ', ' ', ' ', ' ', ' ', ' ', ' ', BALL_SIGN);
	box (playerLeft.object, 0, 0);					// nacrtaj igrače
	box (playerRight.object, 0, 0);

	wrefresh (ball.object);
	wrefresh (playerLeft.object);
	wrefresh (playerRight.object);

}

void update () {				// sredi upravljanje tako da se oba igrača mogu pokretati istovremeno
				 		// i da ne ometaju jedan drugoga
	int ballPositionX = 0, ballPositionY = 0;
	getSpritePosition (&ball, &ballPositionX, &ballPositionY);

	if (simpleSpriteCollision (&playerLeft, &ball, &ballAngle)) {
		ballDirectionLeftRight = -ballDirectionLeftRight;
		ballDirectionUpDown = (ballAngle == 0) ? ballDirectionUpDown : -1;
	}

	if (simpleSpriteCollision (&playerRight, &ball, &ballAngle)) {	
		ballDirectionLeftRight = -ballDirectionLeftRight;
		ballDirectionUpDown = (ballAngle == 0) ? ballDirectionUpDown : 1;
	}
	
	if (ball.positionY <= 2 || ball.positionY + 2 >= winHeight) {
		ballDirectionUpDown = -ballDirectionUpDown;
	}

	if (ballPositionX - 1 <= 0 || ballPositionX + 1 >= winWidth) {
		moveSpriteToCenter (&ball, BALL_START_X (winWidth), BALL_START_Y (winHeight));		
		ball.positionY = BALL_START_Y (winHeight);
		ballDirectionLeftRight = -ballDirectionLeftRight;
		ballDirectionUpDown = 0;
		ballAngle = 0;
		return;
	}
 	/*mvprintw (2, 0, "                                     ");
	mvprintw (0, 0, "double positionY = %lf, int positionY = %d, ballAngle = %lf", ball.positionY, ballPositionY, ballAngle*180/PI);
	mvprintw (2, 0, "ballDirection = %d", ballDirectionUpDown);*/
	ball.positionY = ball.positionY + ballDirectionUpDown * tan(ballAngle);
	changeSpritePosition (&ball, ballDirectionLeftRight, round(ball.positionY - ballPositionY));
	wborder(ball.object, ' ', ' ', ' ', ' ', ' ', ' ', ' ', BALL_SIGN);	// nacrtaj loptu
	wrefresh (ball.object);

	// promijeni biblioteku za unos, izbaci getch
	switch (charCommand = getch ()) {		// učitaj iz datoteke controlne tipke
		case ERR:
			usleep (WAIT);
			break;
		case 'w':
			usleep (WAIT);
			changeSpritePosition (&playerLeft, 0, PLAYER_DIRECTION_UP);			
			break;
		case 's':
			usleep (WAIT);
			changeSpritePosition (&playerLeft, 0, PLAYER_DIRECTION_DOWN);
			break;
		case KEY_UP:
			usleep (WAIT);
			changeSpritePosition (&playerRight, 0, PLAYER_DIRECTION_UP);
			break;
		case KEY_DOWN:
			usleep (WAIT);
			changeSpritePosition (&playerRight, 0, PLAYER_DIRECTION_DOWN);
			break;
		
		default:
			usleep (WAIT);
	}
}

void exitGame () {
	delwin (playerLeft.object);
	delwin (playerRight.object);
	delwin (ball.object);
	delwin (ball.object);
}

int main (void) {
	init ();	// pokušati sve inicijalizacije prebaciti u druge funkcije i datoteke
	noecho ();
	cbreak ();
	keypad (stdscr, TRUE);
	nodelay (stdscr, TRUE);
	curs_set (0);

	while (charCommand != 'q') {
		draw ();
		update ();
	}

	exitGame ();
	exitNcurses ();
	return 0;
}