#include "spriteInteraction.h"
#include "sprite.h"
#include "ball.h"
#include "player.h"

#define PI 3.14159265

/*
* Funkcija određuje u koji dio igrača je lopta udarila i određuje kut pod kojim će se odbiti.
* Trenutno se u obzir uzimaju samo y vrijednosti. Y os je ona prema kojoj se određuje kut
*
* povratna vrijednost je kut
*
*/
double determineAngle (int spriteOnePositionY, int spriteTwoPositionY) {

	double diffAngle = (double) 60 / (PLAYER_HEIGHT / 2); // kolika će biti razlika između 2 različita kuta

	int diffLowY = spriteTwoPositionY - spriteOnePositionY; // razlika između prve točke igrača i lopte
	int diffHighY = spriteOnePositionY + PLAYER_HEIGHT - spriteTwoPositionY; // razlika između druge točke i lopte
	
	//mvprintw (23,0,"diffAngle = %lf,diffLowY = %d, diffHighY = %d", diffAngle, diffLowY, diffHighY);
	if (diffLowY <= PLAYER_HEIGHT / 2) {
		mvprintw (22,0, "diffLowY");
		return (int) diffAngle * (PLAYER_HEIGHT / 2 - diffLowY);
	}
	if (diffHighY <= PLAYER_HEIGHT / 2) {
		mvprintw (22,0, "diffHighY");
		return (int) -diffAngle * (PLAYER_HEIGHT / 2 - diffHighY);
	}

	return ERR;
}

// ovo je poseban slučaj, ne općeniti
// funkcija vraća kut
int simpleSpriteCollision (Sprite *spriteOne, Sprite *spriteTwo, double *ballAngle) {
	int spriteOnePositionX, spriteOnePositionY;
	int spriteTwoPositionX, spriteTwoPositionY;
	Sprite *one = NULL, *two = NULL;	

	switch (spriteOne->id) {
		case 1:				// dodjeljujem igrača varijabli one
		case 2:				// a loptu varijabli two
			one = spriteOne;
			break;
		case 100:
			two = spriteOne;
			break;
	}
	
	
	switch (spriteTwo->id) {
		case 1:				// dodjeljujem igrača varijabli one
		case 2:				// a loptu varijabli two
			one = spriteTwo;
			break;
		case 100:
			two = spriteTwo;
			break;
	}

	if (one == NULL || two == NULL) return 0;	// u slučaju da su oba objekta lopta
							// ili igrač vrati 0


	getSpritePosition (one, &spriteOnePositionX, &spriteOnePositionY);	// igrač
	getSpritePosition (two, &spriteTwoPositionX, &spriteTwoPositionY);	// lopta

	if (one->id == 1) {		
		if (spriteTwoPositionX == spriteOnePositionX + PLAYER_WIDTH  
			&& (spriteOnePositionY <= spriteTwoPositionY 
			&& spriteOnePositionY + PLAYER_HEIGHT >= spriteTwoPositionY)) {
			
			*ballAngle = determineAngle (spriteOnePositionY, spriteTwoPositionY) * PI / 180;
			return 1;
		}
	}

	if (one->id == 2) {		
		if (spriteTwoPositionX + 1 == spriteOnePositionX
			&& (spriteOnePositionY <= spriteTwoPositionY 
			&& spriteOnePositionY + PLAYER_HEIGHT >= spriteTwoPositionY)) {

			*ballAngle = - determineAngle (spriteOnePositionY, spriteTwoPositionY) * PI / 180;
			return 1;
		}
	}
	
	return 0;
}
