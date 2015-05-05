#ifndef POKER_PLAYER_HPP
#define POKER_PLAYER_HPP

#include	<string>
#include	<vector>
#include	<iostream>

using namespace std;


class Poker_player
{
	public:
		Poker_player(string n, unsigned int c) {
			name 	= n;
			chips 	= c;
		}

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
			set_name (string value)
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
		void poker_action();                    /* player needs to chose an action */

	protected:

	private:
		string name;
		unsigned int chips;
		/* array<int, 2> hand_cards; */         /* somehow that does not work */
		vector<int> hand_cards;

};

#endif
