#ifndef POKER_GAME_HPP
#define POKER_GAME_HPP

#include	"poker_player.hpp"
#include	"card_deck.hpp"
#include	<algorithm>

class Poker_game
{
	public:
		Poker_game ();                             /* constructor */
		bool add_player(Poker_player &player);
		void list_players();

		void start();                           /* players added, start game */

		void player_cards();
		void flop();
		void turn();
		void river();

		void betting_round();

	protected:

	private:
		Card_deck deck;                         /* card deck for the game */
		vector<Poker_player> players;           /* participating players */
		vector<Poker_player> round_players;

		

		//pointers to players
		unsigned int dealer, small_blind, big_blind;

		

};

#endif
