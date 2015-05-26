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
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
//    keypad(stdscr, 1);
	box(stdscr, 0, 0);
	
	//Start the poker game here
	Poker_game pg;
	mvwprintw(stdscr, 0, 0, "Starting the setup now");

	refresh();
	pg.setup();
	pg.start();
  
	endwin();
    return(0);
}

