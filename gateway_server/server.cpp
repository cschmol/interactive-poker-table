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

//	Card_deck x;
//	x.shuffle();
//	while(!x.empty()) {
//		int i = x.draw_card();
//		cout << i << ". Card: " << card2str(i) << endl;
//	}
//	cout << "-------" << endl;
//	x.reset();
//	x.shuffle();
//	while(!x.empty()) {
//		int i = x.draw_card();
//		cout << i << ". Card: " << card2str(i) << endl;
//	}
//	exit(0);

	Poker_player *pl1 = new Poker_player("Christophe", 1000);
	int rounds = 200;
	int common_cards[5] = {};
	int n_common_cards = 0;
	while(rounds--) {
		Card_deck cd;
		common_cards[0] = cd.draw_card();
		common_cards[1] = cd.draw_card();
		common_cards[2] = cd.draw_card();
//		pl1->set_card(0, cd.draw_card());
//		pl1->set_card(1, cd.draw_card());
		pl1->set_card(0, 1);
		pl1->set_card(1, 2);
		cout << "Starting round " << rounds << "with cards " << card2str(pl1->get_card(0)) << " || " << card2str(pl1->get_card(1)) << endl;
		cout << "Odds: " << pl1->winning_odds(10000, n_common_cards, common_cards) << endl;
	}
	exit(0);

	initscr();
	clear();
	noecho();
	curs_set(0);
	cbreak();
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);

	clear();
	curs_set(0);

	//Start the poker game here
	Poker_game pg;

	pg.setup();
	pg.start();
  
	endwin();
    return(0);
}














