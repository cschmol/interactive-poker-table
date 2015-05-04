#include	<iostream>
#include	"card_deck.hpp"
#include	"poker_player.hpp"


int main ( int argc, char *argv[] )
{
	poker_card pc;

	std::srand(time(NULL));                     /* initialize random generator */

	Card_deck cards;
	while ( !cards.empty() ) {
		pc = cards.draw_card();
		cout << "Card: " << pc.suit << pc.number <<endl;
	}
	return 0;
}
