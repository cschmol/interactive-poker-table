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
//	std::srand(time(NULL));                                                /* initialize random generator */

	SevenEval *se;                              /* rank evaluator */
	se = new SevenEval;

	if(se==NULL) {
		cout << "se=NULL" << endl;
		exit(1);
	}

	int opt;
	bool flag_help=false,
		 flag_server=false,
		 flag_demo=false;

	cout << "pid: " << getpid() << endl;

	while ((opt = getopt(argc, argv, "dhs")) != -1) {
		switch (opt) {
			case 'h':
				cout << "flag_help" << endl;
				flag_help = true;
				break;
			case 's':
				cout << "flag_server" << endl;
				flag_server = true;
				break;
			case 'd':
				cout << "flag_demo" << endl;
				flag_demo = true;
				break;
			default:
				flag_help=true;
				break;
		}
	}


	
	if(flag_help) {
		cout << "Usage: ./server -s" << endl;
	}


	//use this test case, when a command-line argument is specified
	if(flag_demo) {
		cout << "demo" << endl;
		Poker_player *pl1 = new Poker_player("Christophe", 1000);
		pl1->set_evaluator(se);
		int rounds = 200;
		int common_cards[5] = {};
		int n_common_cards = 3;
		while(rounds--) {
			Card_deck cd;

			common_cards[0] = cd.draw_card();
			common_cards[1] = cd.draw_card();
			common_cards[2] = 1;

			//use these cards as a test case
			pl1->set_card(0, cd.draw_card());
			pl1->set_card(1, cd.draw_card());

			//print out winning odds
			cout << pl1->winning_odds(10000, n_common_cards, common_cards);
			cout << " with cards " << card2str(pl1->get_card(0)) << " || " << card2str(pl1->get_card(1)) << endl;
		}
		exit(0);
	}

	if(flag_server) {
		initscr();                              /* init screen session */
		clear();                                /* clear the screen initially */
		noecho();                               /* do not echo the typed characters */
		curs_set(0);                            /* set cursor to the beginning */
		cbreak();
//		start_color();
//		init_pair(1, COLOR_YELLOW, COLOR_BLACK);
//		init_pair(2, COLOR_BLACK, COLOR_WHITE);


		Poker_game pg(se);
		pg.setup();                             /* start the setup here */
		pg.start();                             /* start the game */
	  
		endwin();
		exit(0);
	}

    return(0);
}














