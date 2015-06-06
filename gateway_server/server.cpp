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




	//Start the poker game here
	Poker_game pg;

	pg.setup();
	//pg.start();
	pg.draw();
  	getch();
	endwin();
    return(0);
}














