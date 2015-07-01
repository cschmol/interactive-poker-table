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
#include	<ncurses.h>
//#include 	<stdio.h>
//#include 	<stdlib.h>
#include 	<ncursesw/ncurses.h> 
//#include	<ncurses.h>
#include 	<locale.h> 

//#define NFC
#undef NFC

using namespace std;

int myrandom (int i);

// Get the rank of a hand comprising seven cards, each represented by an
// integer from 0 (resp. Ace of Spades) to 51 (resp. Two of Clubs) inclusive.
// The higher the rank the better the hand. Two hands of equal rank tie.
string card2str(int c);
std::wstring card2unistr(int c);

class Card_deck
{
	public:
		Card_deck () {                           /* constructor */
#ifdef NFC
			cout << "NFC enabled" << endl;
#else
			cout << "NFC disabled" << endl;
#endif
			reset();
			std::srand(unsigned(time(0)));
			return;
		}

		int draw_card() {
#ifdef NFC
			FILE *pipe = popen("explorenfc-basic | grep Title | awk '{print $2}'", "r");
			if(pipe==NULL) {
				cout << "Error opening pipe" << endl;
				exit(1);
			}

			int card;
			char buffer[512];
			while(fgets(buffer, 512, pipe) != NULL) {
				card = atoi(buffer);
			}
			fscanf(pipe, "%d\n", &card);
			cout << "card " << card2str(card) << " drawn" << endl;
			pclose(pipe);
			return card;
#else
			int res = card_deck.back();  /* get the last element */
			card_deck.pop_back();               /* delete it from the vector */
			return res;                         /* and return a copy of it */
#endif
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
