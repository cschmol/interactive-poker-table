#define MAX_PLAYERS 8

#include	"poker_game.hpp"
#include	<iterator>


Poker_game::Poker_game () {                            /* constructor */
	n_common_cards=0;
	for(int i=0; i<5; i++) {
		common_cards[i] = -1;           /* initalize the cards with -1 */
	}
	deck.shuffle();                     /* shuffle the deck */
	n_common_cards = 0;                         /* no common cards have been dealt */
}

bool Poker_game::add_player(Poker_player &player) {
	if(players.size()<MAX_PLAYERS) {
		players.push_back(player);
		return true;
	} else {
		cerr << "Maximum number of players reached" << endl;
		return false;
	}
}


void Poker_game::deal_common_cards(int count) {
	for(int i=0; i<count; i++) {                /* deal as many cards as specified */
		common_cards[n_common_cards++ - 1] = deck.draw_card();
	}
}

void Poker_game::start() {
	Poker_action *action;                       /* a player_action is returned here */

	while (players.size() > 1) {                         /* until there are no more players */
		int current_player= (big_blind+1)%players.size(); /* it's the player after BB's turn */
		int highest_better=big_blind;                           /* big blind is the highest better initially */

		unsigned int player_bet = 100;


		//deal player cards
		while ( players.size() > 1 || current_player != highest_better ) {   /* while there are still players */
			action = (players.at(current_player)).poker_action();     /* current player needs to play */
			if(action->action == "fold") {
				players.erase(players.begin()+current_player); /* remove player from round */
			}
			if ( action->action == "check" ) {
				if ( (players.at(current_player)).get_chips() < player_bet ) {
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
			current_player = (current_player+1)%players.size();
		}
		//now determine a winner
		if ( players.size()==1 ) {        /* only 1 player has not folded */
		} else {
			//determine winner by card ranks
		}

		//some logic to advance dealer, small/big blind

	}

}



void Poker_game::deal_player_cards() {

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

