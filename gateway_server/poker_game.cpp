#define MAX_PLAYERS 8

#include	"poker_game.hpp"
#include	<iterator>
#include	<string>

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
	betting_round();
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
	string player_action;
	string::size_type pos;

	int raise_amount;
	int players = 4;

	//int current_player = (big_blind+1)%round_players.size();          /* player after BB has to play */
	int current_player = 1;
	int highest_bidder = big_blind;                                     /* in the beginning, the big blind ist the highest bet */
	while ( current_player != highest_bidder ) {                        /* until all players are on the same level or fold */
		cout << "Need action from player " << current_player << endl;
		cin >> player_action;

		pos = player_action.find(" ");
		if(pos != string::npos) {                                       /* there is a ' ' in the string, thus the player raises */
			if(player_action.substr(0, pos-1) != "raise") {
				cout << "Invalid command" << endl;                      /* stupid player :) */
			}
			//raise_amount = std::stoi(player_action.substr(pos));
			raise_amount = atoi(player_action.substr(pos).c_str());
			cout << "Player wants to raise " << raise_amount << endl;



		} else {                                                        /* there is no space, thus either call check or fold */

			if (player_action == "fold") {                              /* fold */
				cout << "Player folds" << endl;
				//round_players.remove(current_player);

			} else if (player_action == "check") {                      /* check */
				cout << "Player checks" << endl;
				//check if player has betted the same as highest bidder

			} else if (player_action == "call") {                       /* call */
				cout << "Player calls" << endl;
				//check if player has enough chips to call
				//nothing else to do here

			} else {                                                    /* not a valid command */
				cout << "Invalid command" << endl;                      /* stupid player :) */
			}
		}


		current_player = (current_player++) % round_players.size();
		cout << current_player << players << endl;
	}

}
