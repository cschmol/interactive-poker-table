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

	int i;

//	cout << "PID: " << getpid() << endl;
//	sleep(10);

    initscr();
    clear();
    noecho();
    curs_set(0);
    cbreak();
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);

//	SevenEval se;
//	int x = se.GetRank(1, 2, 3, 4, 5, 6, 7);
//	cout << x << endl;

	//Start the poker game here
	Poker_game pg;
//
//	Poker_player pl("christophe", 100);
//	pl.set_card(0, 23);
//	pl.set_card(1, 33);
//
//	int cards[] = {10, 20, 30};
//
//	pl.print_info(1, 3, cards);
//
//	getch();
//
	pg.setup();
	pg.start();
  
	endwin();
    return(0);
}














