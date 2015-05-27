#include	<iostream>
#include	"card_deck.hpp"
#include	"poker_player.hpp"
#include	"poker_game.hpp"
#include	<ncurses.h>
#include	"FiveEval.h"
#include	"SevenEval.h"
#include	<unistd.h>


int main ( int argc, char *argv[] )
{
	std::srand(time(NULL));                                                /* initialize random generator */



    	initscr();
    	clear();
    	noecho();
    	curs_set(0);
    	cbreak();
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);



	//Start the poker game here
	Poker_game pg;

	pg.setup();
	pg.start();
  
	endwin();
    return(0);
}














