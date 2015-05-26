#include	<iostream>
#include	"card_deck.hpp"
#include	"poker_player.hpp"
#include	"poker_game.hpp"
#include	<ncurses.h>


int main ( int argc, char *argv[] )
{
	std::srand(time(NULL));                                                /* initialize random generator */

	int i;

    initscr();
    clear();
    noecho();
    curs_set(0);
    cbreak();
//    keypad(stdscr, 1);
	box(stdscr, 0, 0);
	
	//Start the poker game here
	Poker_game pg;
	mvwprintw(stdscr, 0, 0, "Starting the setup now");

	getch();
	mvwprintw(stdscr, 0, 0, "asdfasdf");
	refresh();

	refresh();
//	WINDOW *w[4];
//	for(i=0; i<4; i++) {
//		w[i] = newwin(10, COLS, 10+i*LINES/4, 0);
//		box(w[i], 0, 0);
//		wrefresh(w[i]);
//	}
//	getch();
//
//	delwin(stdscr);
//	refresh();

	pg.setup();
	pg.start();
  
	endwin();
    return(0);
}

