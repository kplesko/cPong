#ifndef SPRITE_H
#define SPRITE_H

#include <ncurses.h>

typedef struct sprite {
	int id;
	char *name;
	
	double positionX;
	double positionY;	// što ako objekt nije prozor, je li moguće napraviti sve pomoću prozora, 
			// je li efikasno ili je pametnije koristiti bilo što drugo
			// još elemenata poput char **object koji će biti imaginarna reprezentacija
	WINDOW *object; // this structure contains height, width and x,y position
} Sprite;

void getSpritePosition (Sprite *sprite, int *x_position, int *y_position);

void changeSpritePosition (Sprite *sprite, int offsetX, int offsetY);

void moveSpriteToCenter (Sprite *sprite, int locationX, int locationY);

void eraseObjectOnScreen (Sprite *sprite);

#endif