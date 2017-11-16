#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_HEIGHT 8
#define PLAYER_WIDTH 3
#define PLAYER_BORDER 0 	// for function box()

// srediti slučaj s početnim pozicijama
#define PLAYER_START_X(player_id, width) ((player_id) == 1 ? 2 : width - 5)	
#define PLAYER_START_Y(height) (((height) - (PLAYER_HEIGHT)) / 2)

#define PLAYER_DIRECTION_UP -1
#define PLAYER_DIRECTION_DOWN 1

#endif