#include	"card_deck.hpp"


int myrandom (int i) { return std::rand()%i;}

string card2str(int c) {
	std::stringstream buffer;
	if(c<0) {
		return "undefined";
	} else {
		switch (c%4) {
			case 0:
				buffer	<< "Spade ";
				break;
			case 1:
				buffer	<< "Hearts ";
				break;
			case 2:
				buffer	<< "Diamonds ";
				break;
			case 3:
				buffer	<< "Clubs ";
				break;
			default:
				break;
		}

		switch (c/4) {
			case 0:
				buffer	<< "Ace";
				break;
			case 1:
				buffer	<< "King";
				break;
			case 2:
				buffer	<< "Queen";
				break;
			case 3:
				buffer	<< "Valet";
				break;
			case 4:
				buffer	<< "King";
				break;
			default:
				buffer	<<  15 - (c/4);
				break;
		}
	}
	
	return buffer.str();
}
