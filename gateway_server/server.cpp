#include	<iostream>
#include	"card_deck.hpp"
#include	"poker_player.hpp"
#include	"poker_game.hpp"


int main ( int argc, char *argv[] )
{
	std::srand(time(NULL));                                                /* initialize random generator */


	Poker_player christophe("Chris", 1000);
	Poker_player nina("Nina", 1000);
	Poker_player fojer("Fojer", 1000);
	Poker_player claire("Claire", 1000);

	Poker_game pg;

	pg.add_player(christophe);
	pg.add_player(nina);
	pg.add_player(fojer);
	pg.add_player(claire);

	pg.start();


	return 0;
}
