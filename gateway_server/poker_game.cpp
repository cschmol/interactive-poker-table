#include	"poker_game.hpp"
#include	<iterator>

#define MAX_PLAYERS 8


Poker_game::Poker_game () {                            /* constructor */
	n_common_cards=0;
	for(int i=0; i<5; i++) {
		common_cards[i] = -1;           /* initalize the cards with -1 */
	}
	//deck.shuffle();                     /* shuffle the deck */
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

void Poker_game::round() {                          /* corresponds to 1 round of poker */
	//this is only 1 round

	pot = 0;
	
	//set the big&small blind's bets accordingly
	small_blind -> deduct_chips ( n_small_blind );
	big_blind -> deduct_chips ( n_big_blind );

	small_blind -> set_bet ( n_small_blind );
	big_blind -> set_bet ( n_big_blind );

	//add the blinds to the pot
	pot += n_small_blind;
	pot += n_big_blind;

	deal_player_cards();                             /* deal player cards */
	betting_round();
	print_info();
	if(++current_player == players.end()) {
		current_player = players.begin();
	}

	flop();                                     /* deal the flop */
	betting_round();
	print_info();
	if(++current_player == players.end()) {
		current_player = players.begin();
	}

	turn();                                     /* deal the turn */
	betting_round();
	print_info();
	if(++current_player == players.end()) {
		current_player = players.begin();
	}

	river();                                    /* deal the river */
	betting_round();
	print_info();


	//determine a winner
	unsigned int winner;                                 /* do that by hand now */
	print_info();
	do {
		cout << "Please determine a winner by hand: ";
		cin >> winner;
	} while (winner > players.size());

	cout << "Player " << winner << " has won" << endl;
	cout	<< "He wins a pot of " << pot << endl;
	(players.at(winner)) .set_chips( (players.at(winner)) . get_chips() + pot );
	pot = 0;


	//blinds logic
}

void Poker_game::start() {
	std::vector<Poker_player>::iterator it;
//	cout	<< "Starting the poker game now" << endl;
	dealer=players.begin();
	small_blind = dealer+1;
	big_blind = small_blind+1;
	current_player = big_blind+1;

	while(players.size() > 1) {
		high_bet = n_big_blind;                         /* set the highest bet to the big blind */
		pot = 0;

		//advance special functions
		if(++small_blind == players.end()) {
			small_blind = players.begin();
		}
		if(++big_blind == players.end()) {
			big_blind = players.begin();
		}
		if(++current_player == players.end()) {
			current_player = players.begin();
		}

		highest_better=big_blind;

		//set each players has_folded to 0, so that each player can play again
		for ( it=players.begin(); it!=players.end(); it++ ) {
			it -> reset_fold();
			it -> set_bet(0);

			if ( it->get_chips() <= 0 ) {
				cout	<< "Player is game-over, removing him" << endl;
				players.erase(it);
			}
		}

//		cout	<< "Starting a new round of poker" << endl;
		round();
		break;

		if(++dealer == players.end()) {
			dealer = players.begin();
		}
	}
}

void Poker_game::deal_player_cards() {
	std::vector<Poker_player>::iterator it;

	cout << "Dealing player cards" << endl;
	cout << "--------------------" << endl;
	unsigned int j;
	for ( it=players.begin(); it!=players.end(); it++) {     /* iterate over all players */
		for(j=0; j<2; j++) {                                 /* draw 2 cards */
			it -> set_card(j, deck.draw_card());
		}
	}
}

void Poker_game::flop() {
	cout << "Dealing flop" << endl;
	cout << "------------" << endl;
	unsigned int j;
	//deal 3 common cards
	for(j=0; j<3; j++) {                    /* draw 3 cards */
		common_cards[j] = deck.draw_card();
	}
	n_common_cards = 3;
}

void Poker_game::turn() {
	cout << "Dealing turn" << endl;
	cout << "------------" << endl;
	//deal 1 card
	common_cards[3] = deck.draw_card();
	n_common_cards = 4;
}

void Poker_game::river() {
	//deal 1 card
	cout << "Dealing river" << endl;
	cout << "-------------" << endl;
	common_cards[4] = deck.draw_card();
	n_common_cards = 5;
}

void Poker_game::betting_round () {
	Poker_action *action;

// _________________________________________
///  might need to go some other place here \
//| it does not work correctly when players |
//\ fold in a previous round                /
// -----------------------------------------
//        \   ^__^
//         \  (oo)\_______
//            (__)\       )\/\
//                ||----w |
//                ||     ||
	int n_players = players.size();             /* might need to be some other place */

	while ( n_players > 1 && current_player != highest_better ) {         /* while there are still players */
		print_info();
		if(!current_player -> folded()) {       /* only when player has not folded yet */
			action = current_player -> poker_action(high_bet); /* current player needs to play */

			if(action->action == "fold") {
				n_players--;                
				current_player -> fold();       /* put cards away */
			} else if ( action->action == "check" ) { 
			} else if ( action->action == "call" ) { 
				pot += action->new_player_chips;
			} else if ( action->action == "raise" ) {
				high_bet = action->new_high_bet;
				highest_better = current_player;
				pot += action->new_player_chips;
			}

			else {
				continue;
			}
		}
		if(++current_player == players.end()) {
			current_player = players.begin();
		}
	}

	return;
}

void Poker_game::print_info (  ) {
	unsigned int i;
	std::vector<Poker_player>::iterator it;
//	cout	<< "Info about the game" << endl;
//	cout	<< "Still " << players.size() << " players in the game" << endl;
	cout	<< "+++++++++++++++++" << endl;
	cout	<< "Pot: " << pot << endl;
	cout	<< "Common cards: ";
	for(i=0; i<n_common_cards; i++) {
//		cout	<< common_cards[i] << " ";
		cout	<< card2str(common_cards[i]) << ",";
	}
	cout	<< endl;
	for ( it=players.begin(); it!=players.end(); it++) {     /* iterate over all players */
		it -> print_info();
	}

	return ;
}		/* -----  end of method Poker_game::print_info  ----- */

void Poker_game::setup(){
        fstream fin("gameconfig");

        string playerstring,valuestring;

        getline(fin,playerstring);
        getline(fin,valuestring);
        

        string buf; // Have a buffer string
        stringstream s1(playerstring); // Insert the string into a stream
        stringstream s2(valuestring);

        vector<string> playernames; // Create vector to hold our words
        vector<int> values;

        while (s1 >> buf){
                playernames.push_back(buf);
        }
        
        while (s2 >> buf){
                values.push_back(atoi(buf.c_str()));
        }
        
        Poker_player player("",0);

        for (std::vector<string>::iterator it = playernames.begin() ; it != playernames.end(); ++it){
                player.set_name(*it);
                player.set_chips(values.at(2));
                add_player(player);
                //cout<<"Player "<<*it<<" added to the game"<<endl;
        }      

        n_small_blind=values.at(0);
        n_big_blind=values.at(1);
//        cout<<"Credits: "<<player.get_chips()<<"  Small blind: "<<n_small_blind<<"  Big blind: "<<n_big_blind<<endl;

        fin.close();
}
