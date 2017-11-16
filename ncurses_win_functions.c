#include <ncurses.h>

#include "ncurses_win_functions.h"

// koristiti argument koji će pokazati koje elemente netko želi inicijalizirati u ncurses modu
void initNcurses () {
	initscr ();
}

void exitNcurses () {
	endwin ();
}

void getWindowDimensions (WINDOW *win, int *height, int *width) {
	int max_x, max_y;	// provjeri trebaju li lokalne varijable uopće

	getmaxyx (win, max_y, max_x);

	*height = max_y;
	*width = max_x;
}