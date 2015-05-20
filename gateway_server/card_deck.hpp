#ifndef CARD_DECK_HPP
#define CARD_DECK_HPP

#include	<iostream>
#include	<string>
#include	<algorithm>
#include	<vector>
#include	<ctime>
#include	<cstdlib>
#include 	<sstream>
#include	<fstream>

using namespace std;

int myrandom (int i);

class Card_deck
{
	public:
		Card_deck () {                           /* constructor */
			cout << "Card_deck created" << endl;
			reset();
			std::srand(unsigned(time(0)));
			return;
		}

		int draw_card() {
			int res = card_deck.back();  /* get the last element */
			card_deck.pop_back();               /* delete it from the vector */
			return res;                         /* and return a copy of it */

		}
		void shuffle() {
			cout << "Shuffling deck now" << endl;
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
