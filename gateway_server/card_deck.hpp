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

typedef struct card {
	char suit;
	int number;
} poker_card;


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
			std::random_shuffle(card_deck.begin(), card_deck.end()); /* shuffle the deck */
			return;
		}
		void reset() {
		}

		/* ====================  DATA MEMBERS  ======================================= */
	protected:

	private:
		std::vector<poker_card> card_deck;

}; /* -----  end of class Card_deck  ----- */

