#ifndef POKER_PLAYER_HPP
#define POKER_PLAYER_HPP

#include	<string>
#include	<vector>
#include	<iostream>


using namespace std;

typedef struct {
	string action;
	unsigned int new_high_bet;
} Poker_action;


class Poker_player
{
	public:
		Poker_player(string n, unsigned int c);           /* constructor */
		
		string get_name ();                               /* getter method */
		void set_name (string value);                     /* setter method */
		unsigned int get_chips ();                        /* getter method */
		void set_chips ( unsigned int c );                /* setter method */
		unsigned int get_bet();                           /* getter method */
		void set_bet ( unsigned int b );                  /* setter method */
		void set_card (int index, int card);

		void reset_fold() {
			has_folded=false;
		}

		bool folded();

		void print_info();                                /* print info about player */
		Poker_action *poker_action(unsigned int new_bet); /* player needs to chose an action */

	private:
		string name;
		unsigned int chips;                     /* current chips of the player */
		unsigned int bet;                       /* current bet of the player */
		bool has_folded;                        /* has the player folded yet */
		int hand_cards[2];                      /* the players hand cards */

};

#endif
