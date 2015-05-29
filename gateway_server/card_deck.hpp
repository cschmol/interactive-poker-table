#ifndef CARD_DECK_HPP
#define CARD_DECK_HPP

#include	<iostream>
#include	<string>
#include	<algorithm>
#include	<vector>
#include	<array>
#include	<ctime>
#include	<cstdlib>
#include 	<sstream>
#include	<fstream>
#include	"SevenEval.h"
#include	"FiveEval.h"

using namespace std;

int myrandom (int i);

// What do the integers mean?
// Get the rank of a hand comprising seven cards, each represented by an
// integer from 0 (resp. Ace of Spades) to 51 (resp. Two of Clubs) inclusive.
// The higher the rank the better the hand. Two hands of equal rank tie.
string card2str(int c);

class Card_deck
{
	public:
		Card_deck () {                           /* constructor */
			reset();
			return;
		}

		int draw_card() {
			int res = card_deck.back(); /* get the last element */
			card_deck.pop_back();       /* delete it from the vector */
			return res;                 /* and return a copy of it */

		}
		void shuffle() {
			std::random_shuffle(card_deck.begin(), card_deck.end(), myrandom); /* shuffle the deck */
			return;
		}
		void reset() {
			card_deck.clear();                  /* clear the vector first */
			
			for ( int i=0; i<52; i++) {
				card_deck.push_back(i);         /* push card to the deck */
			}
			shuffle();
		}

	bool empty() {
		return card_deck.empty();
	}

	protected:

	private:
		std::vector<int> card_deck;             /* integer vector for the cards */

};

#endif
