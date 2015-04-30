#ifndef CARD_DECK_HPP
#define CARD_DECK_HPP
/*
 * =====================================================================================
 *
 *       Filename:  card_deck.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015-04-30 09:48:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Christophe Schmol (cs), christophe_schmol@yahoo.de
 *        Company:  RWTH Aachen University
 *
 * =====================================================================================
 */

#include	<iostream>

#include	<algorithm>
#include	<vector>
#include	<ctime>
#include	<cstdlib>

using namespace std;

const char suits[] = {'D', 'H', 'S', 'C'};

typedef struct card {
	char suit;
	int number;
} poker_card;

int myrandom (int i);

/*
 * =====================================================================================
 *        Class:  Card_deck
 *  Description:  
 * =====================================================================================
 */
class Card_deck
{
	public:
		/* ====================  LIFECYCLE     ======================================= */
		Card_deck () {                           /* constructor */
			cout << "Card_deck created" << endl;
			reset();
			std::srand(unsigned(time(0)));
			return;
		}

		/* ====================  ACCESSORS     ======================================= */

		/* ====================  MUTATORS      ======================================= */

					/* ====================  OPERATORS     ======================================= */
		poker_card draw_card() {
			poker_card res = card_deck.back();  /* get the last element */
			card_deck.pop_back();               /* delete it from the vector */
			return res;                         /* and return a copy of it */
			
		}
		void shuffle() {
			cout << "Shuffling deck now" << endl;
			std::random_shuffle(card_deck.begin(), card_deck.end(), myrandom); /* shuffle the deck */
			return;
		}
		void reset() {
			poker_card pc;
			card_deck.clear();                  /* clear the vector first */
			
			for ( int suit=0; suit<4; suit++) {
				for ( int number=1; number<14; number++) {
					pc.suit = suits[suit];
					pc.number = number;
					card_deck.push_back(pc);
				}
			}
			shuffle();

		}

		/* ====================  DATA MEMBERS  ======================================= */
	protected:

	private:
		std::vector<poker_card> card_deck;

}; /* -----  end of class Card_deck  ----- */

#endif
