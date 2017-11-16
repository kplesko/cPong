#ifndef NCURSES_WIN_FUNCTIONS_H
#define NCURSES_WIN_FUNCTIONS_H

void initNcurses ();
	
void exitNcurses ();

void getWindowDimensions (WINDOW *win, int *height, int *width);

#endif