#ifndef POKER_GAME_HPP
#define POKER_GAME_HPP

#include	"poker_player.hpp"
#include	"card_deck.hpp"
#include	<algorithm>
#include	<vector>





class Poker_game
{
	public:
		Poker_game ();                          /* constructor */

		bool add_player(Poker_player &player);

		void start();                           /* players added, start game */
		void round();                           /* corresponds to 1 round of poker */
		void setup();
		void deal_common_cards(int count);

		void deal_player_cards();
		void flop();
		void turn();
		void river();

		void betting_round();

		void print_info();                      /* print info about the game */


	protected:

	private:
		Card_deck deck;                                     /* card deck for the game */
		vector<Poker_player> players;                       /* all players that are still competing */

		int dealer, small_blind, big_blind, current_player; /* indexes for special players */
		int common_cards[5];
		int n_small_blind, n_big_blind;         /* worth of small and big blind */

		unsigned int n_common_cards;                        /* holds the number of cards currently on the table */
		int high_bet;                                       /* set the bet to the big blind */
		int highest_better;
		unsigned int pot;                                   /* amount of chips in the pot */

};

#endif
