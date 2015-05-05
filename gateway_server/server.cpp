#include	<iostream>
#include	"card_deck.hpp"
#include	"poker_player.hpp"
#include	"poker_game.hpp"


int main ( int argc, char *argv[] )
{
	poker_card pc;

	std::srand(time(NULL));                     /* initialize random generator */

	Poker_game game;
	game.start();


	return 0;
}
