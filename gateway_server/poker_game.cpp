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
	rounds = 0;
	Poker_action *action;                       /* a player_action is returned here */

	while (players.size() > 1) {                         /* until there are no more players */
		round_players = players;                         /* all active players participate in the round */
		int current_player= (big_blind+1)%round_players.size(); /* it's the player after BB's turn */
		int highest_better=big_blind;                           /* big blind is the highest better initially */

		unsigned int player_bet = 100;


		//deal player cards
		while ( round_players.size() > 1 || current_player == highest_better ) {   /* while there are still players */
			action = (round_players.at(current_player)).poker_action();     /* current player needs to play */
			if(action->action == "fold") {
				round_players.erase(round_players.begin()+current_player); /* remove player from round */
			}
			if ( action->action == "check" ) {
				if ( (round_players.at(current_player)).get_chips() < player_bet ) {
					cout << "You cannot check now, only fold/call/raise" << endl;
				} else {
					//take some chips away from player
				}
			}
			if ( action->action == "call" ) {
				//check if player has enough chips, else splitpot logic
				//deduct chips from player
			}
			if ( action->action == "raise" ) {
				//mark current player as the biggest better
				//deduct chips from player
			}
		}
		//now determine a winner
		if ( round_players.size()==1 ) {        /* only 1 player has not folded */
		} else {
			//determine winner by card ranks
		}

		cout << "Round " << ++rounds << "finished now" << endl;
		//maybe print stats about this round

		//some logic to advance dealer, small/big blind

	}

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
