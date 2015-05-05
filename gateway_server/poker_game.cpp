#define MAX_PLAYERS 8

#include	"poker_game.hpp"
#include	<iterator>

bool Poker_game::add_player(Poker_player &player) {
	if(players.size()<MAX_PLAYERS) {
		players.push_back(player);
		return true;
	} else {
		cerr << "Maximum number of players reached" << endl;
		return false;
	}
}

void Poker_game::start() {
	dealer = 0;
	small_blind = (dealer+1) % players.size();
	big_blind = (small_blind+1) % players.size();
}

void Poker_game::player_cards() {
	//deal 2 cards to every player
}

void Poker_game::flop() {
	//deal 3 common cards
}

void Poker_game::turn() {
	//deal 1 card
}

void Poker_game::river() {
	//deal 1 card
}

void Poker_game::betting_round () {


}

void Poker_game::list_players() {
	vector<Poker_player>::iterator it;

	//cout << "Listing Players now" << endl;
	for(it=players.begin(); it!=players.end(); ++it) {
		it -> print_info();
		cout << endl;
	}
}
