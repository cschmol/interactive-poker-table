#ifndef POKER_PLAYER_HPP
#define POKER_PLAYER_HPP

#include	<string>
#include	<vector>
#include	<iostream>


using namespace std;

typedef struct {
	string action;
	unsigned int amount;
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

		void print_info();                                /* print info about player */
		Poker_action *poker_action(); /* player needs to chose an action */

	private:
		string name;
		unsigned int chips;
		unsigned int bet;             /* how many chips has the player moved to the pot */
	    /* array<int, 2> hand_cards; */                      /* somehow that does not work */
		vector<int> hand_cards;

};

#endif
