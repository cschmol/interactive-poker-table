#ifndef POKER_PLAYER_HPP
#define POKER_PLAYER_HPP

#include	<string>
#include	<vector>
#include	<iostream>
#include	<fstream>
#include	"card_deck.hpp"

using namespace std;

typedef struct {
	string action;
	unsigned int new_high_bet;
	unsigned int new_player_chips;
} Poker_action;


class Poker_player
{
	public:
		Poker_player(string n, unsigned int c);

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

		//card accessors
		void set_card (int index, int card);                /* set the players poker cards */
		int get_card (int index);                           /* get the players poker cards */

		bool make_bet(unsigned int c);

		void print_info();                                  /* print info about player */
		Poker_action *poker_action(unsigned int new_bet);   /* player needs to chose an action */

	private:
		string name;
		unsigned int chips;
		unsigned int bet;
		bool has_folded;
		int hand_cards[2];

};

#endif
