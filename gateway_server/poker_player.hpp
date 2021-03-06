#ifndef POKER_PLAYER_HPP
#define POKER_PLAYER_HPP

#include	<string>
#include	<vector>
#include	<iostream>
#include	<fstream>

#include	<sys/types.h>
#include	<sys/socket.h>
#include	<string.h>

//#include	<ncurses.h>
#include 	<ncursesw/ncurses.h> 


#include	"card_deck.hpp"
#include	"socket.hpp"

#include	"SevenEval.h"
#include	"FiveEval.h"

using namespace std;

typedef struct {
	string action;
	unsigned int new_high_bet;
	unsigned int new_player_chips;
} Poker_action;

class Socket;


class Poker_player
{
	public:
		Poker_player(string n, unsigned int c);
		Poker_player(string n, unsigned int c, int sock,WINDOW *parentwin);
		
		~Poker_player();

		//name accessors
		string get_name ();
		void set_name (string value);

		//chips accessors
		unsigned int get_chips ();
		void set_chips ( unsigned int c );
		unsigned int deduct_chips(unsigned int c);          /* deduct the amount of chips specified */
                                                            /* if player has less chips, return the amount of chips */
		//bet accessors
		unsigned int get_bet();
		void set_bet ( unsigned int b );

		//fold accessors
		void reset_fold();                                  /* set has_folded to false */
		bool folded();                                      /* return has_folded */
		void fold();

		//card accessors
		void set_card (int index, int card);                /* set the players poker cards */
		int get_card (int index);                           /* get the players poker cards */

		//prop accessors
		void set_prob(double prob);
		double get_prob();


		WINDOW *get_wnd();
		void set_wnd(WINDOW *w);

		bool make_bet(unsigned int c);

		void print_info(int line, int n_cards, int *comm_cards);
//		void print_info(int line);                                  /* print info about player */
		Poker_action *poker_action(unsigned int new_bet);   /* player needs to chose an action */

		void print_hello();
		void draw(bool active);


	private:
		string name;
		unsigned int chips;
		unsigned int bet;
		bool has_folded;
		int hand_cards[2];
		double winprob;

		/*-----------------------------------------------------------------------------
		 *  socket variables
		 *-----------------------------------------------------------------------------*/

		int cli_socket;                         /* socket of the new connection */
		Socket *sock;


		/*-----------------------------------------------------------------------------
		 *  ncurses varialbes
		 *-----------------------------------------------------------------------------*/
		WINDOW *wnd;
		//int wnd_x,wnd_y;		//coordinates of player window

		/*-----------------------------------------------------------------------------
		 *  Hands evaluator
		 *-----------------------------------------------------------------------------*/


};

#endif
