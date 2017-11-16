#include "sprite.h"

void getSpritePosition (Sprite *sprite, int *x_position, int *y_position) {	// možda nisu potrebne dodatne lokalne varijable, pokušati bez njih
	int x = 0, y = 0;
	getbegyx (sprite->object, y, x);

	*x_position = x;
	*y_position = y;
}

// ova funkcija radi samo s prozorima, treba joj opći oblik za sve objekte, recimo ubaciti još 2 varijable koje će ako su veće od 0
// pokazati da se ne radi o prozoru i tada preskočiti dohvaćanje pozicije prozora
// ili ubaciti te varijable u strukturu
void changeSpritePosition (Sprite *sprite, int offsetX, int offsetY) {
	int x_position = 0, y_position = 0;

	getSpritePosition (sprite, &x_position, &y_position);

	eraseObjectOnScreen (sprite);
	mvwin (sprite->object, y_position + offsetY, x_position + offsetX);
}

void moveSpriteToCenter (Sprite *sprite, int locationX, int locationY) {
	eraseObjectOnScreen (sprite);
	mvwin (sprite->object, locationY, locationX);
} 

void eraseObjectOnScreen (Sprite *sprite) { 	// ova funkcija radi samo s prozorima, treba joj opći oblik za sve objekte
	wborder (sprite->object, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh (sprite->object);
}