#include	<iostream>
#include	"card_deck.hpp"
#include	"poker_player.hpp"
#include	"poker_game.hpp"
#include	<ncurses.h>
#include	"FiveEval.h"
#include	"SevenEval.h"


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

	
	//Start the poker game here
	Poker_game pg;

	Poker_player pl("christophe", 100);
	pl.set_card(0, 23);
	pl.set_card(1, 33);

	int cards[] = {10, 20};

//	pl.print_info(10, 2, cards);

	pg.setup();
	pg.start();
  
	endwin();
    return(0);
}














