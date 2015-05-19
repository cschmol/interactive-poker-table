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
	//this is only 1 round

	deal_player_cards();                             /* deal player cards */
	cout	<< "Pre-flop betting" << endl;
	cout	<< "----------------" << endl;
	print_info();

	betting_round();

	print_info();


	flop();                                     /* deal the flop */
	cout	<< "Post-flop betting" << endl;
	cout	<< "----------------" << endl;
	betting_round();

	turn();                                     /* deal the turn */
	cout	<< "Post-turn betting" << endl;
	cout	<< "----------------" << endl;
	betting_round();

	river();                                    /* deal the river */
	cout	<< "Post-river betting" << endl;
	cout	<< "----------------" << endl;
	betting_round();

	//determine a winner
	//blinds logic
}

void Poker_game::deal_player_cards() {
	cout << "Dealing player cards" << endl;
}

void Poker_game::flop() {
	cout << "Dealing flop" << endl;
	//deal 3 common cards
}

void Poker_game::turn() {
	cout << "Dealing turn" << endl;
	//deal 1 card
}

void Poker_game::river() {
	//deal 1 card
	cout << "Dealing river" << endl;
}

void Poker_game::betting_round () {
	Poker_action *action;                       /* a player_action is returned here */

	//some logic needed here
	dealer=0;
	small_blind=1;
	big_blind=2;

	current_player= (big_blind+1)%players.size(); /* it's the player after BB's turn */
	int highest_better=big_blind;                 /* big blind is the highest better initially */

	(players.at(small_blind)) . set_bet(50);
	(players.at(small_blind)) . set_chips((players.at(small_blind) . get_chips() - 50));
	(players.at(big_blind)) . set_bet(100);
	(players.at(big_blind)) . set_chips((players.at(big_blind) . get_chips() - 100));

	int i;
	//set each players has_folded to 0, so that every player can play again
	for ( i = 0; i < players.size(); i += 1 ) {
		(players.at(i)) . reset_fold();
	}

	int n_players = players.size();
	int high_bet = 100;

	cout << endl;

	//deal player cards
	while ( n_players > 1 && current_player != highest_better ) {            /* while there are still players */
		if(!(players.at(current_player)).folded()) {                              /* only when this player has not folded yet */
//			cout << endl;
			action = (players.at(current_player)).poker_action(high_bet);                 /* current player needs to play */
			cout << "Action: " << action->action;

			if(action->action == "fold") {
				n_players--;                /* player marked as fold in member variable */

			} else if ( action->action == "check" ) { /* no action required here */

			} else if ( action->action == "call" ) { /* no action required here */

			} else if ( action->action == "raise" ) {
				high_bet = (players.at(current_player)).get_bet(); /* set the bet to be what this player has raised */
				highest_better = current_player; /* mark player as the highest better */
				cout	<< "Player raised" << endl;
			}

			else {
				cout << "Invalid action, please repeat" << endl;
				continue;                                                         /* do not change the current player */
			}
			cout << endl;
		}
		current_player = (current_player+1)%players.size(); /* readjust the current player */
		cout << "Highest bidder: " << highest_better << endl;
		cout << "High_bet: " << high_bet << endl;
		cout << "Still " << n_players << " in the game" << endl;
	}

	cout << "One round is done now" << endl;

	return;

}

void Poker_game::print_info (  ) {
	int i;
	cout	<< "Info about the game" << endl;
	cout	<< "Still " << players.size() << " players in the game" << endl;
	for ( i = 0; i < players.size(); i += 1 ) {
//		cout << i << ": " << (players.at(i)) . get_name() << endl;
		(players.at(i)) . print_info();
	}

	return ;
}		/* -----  end of method Poker_game::print_info  ----- */

