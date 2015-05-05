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
		Poker_player ();

		inline unsigned int
			get_chips (  )
			{
				return chips;
			}

		inline string
			get_name (  )
			{
				return name;
			}

		inline void
			set_name ( int value )
			{
				name	= value;
				return ;
			}

		void
			set_chips ( unsigned int c )
			{
				chips = c;
				return ;
			}

		inline void
			set_chips ( int value )
			{
				chips	= value;
				return ;
			}

		void print_info();

		Poker_action *get_action();


	protected:

	private:
		string name;
		unsigned int chips;
		/* array<int, 2> hand_cards; */         /* somehow that does not work */
		vector<int> hand_cards;


};

#endif
