#ifndef POKER_GAME_HPP
#define POKER_GAME_HPP

#include	"poker_player.hpp"
#include	"card_deck.hpp"
#include	<algorithm>
#include	<vector>

class Poker_game
{
	public:
		Poker_game () { }                            /* constructor */

		bool add_player(Poker_player &player);

		void start();                           /* players added, start game */

		void player_cards();
		//void flop();
		//void turn();
		//void river();
		void setup();
		void deal_player_cards();
		void deal_common_cards(int count);
        void output();
		void betting_round();

	protected:

	private:
		Card_deck deck;                         /* card deck for the game */
		vector<Poker_player> players;           /* all players that are still competing */
		//vector<Poker_player> round_players;     /* all players that participate in that round */

		int dealer, small_blind, big_blind;
		int rounds;                         /* how many rounds have been played */
		int common_cards[5];
		int n_common_cards;
		int current_player;


};

#endif
