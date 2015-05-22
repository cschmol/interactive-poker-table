#define MAX_PLAYERS 8

#include	"poker_game.hpp"
#include	<iterator>


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

	deal_player_cards();                             /* deal player cards */
	betting_round();
	print_info();

	flop();                                     /* deal the flop */
	betting_round();
	print_info();

	turn();                                     /* deal the turn */
	betting_round();
	print_info();

	river();                                    /* deal the river */
	betting_round();
	print_info();


	//determine a winner
	int winner;                                 /* do that by hand now */
	print_info();
	cout << "Please determine a winner by hand: ";
	cin >> winner;

	cout << "Player " << winner << " has won" << endl;

	//blinds logic
}

void Poker_game::start() {
	unsigned int i;
	high_bet = 100;
	while(players.size() > 1) {
		//set each players has_folded to 0, so that every player can play again
		for ( i = 0; i < players.size(); i += 1 ) {
			(players.at(i)) . reset_fold();
			(players.at(i)) . set_bet(0);

			if((players.at(i)) . get_chips() <= 0) {
				cout	<< "Player is game-over, removing him" << endl;
				players.erase(players.begin()+i); /* player is game over, remove him */
			}
		}

		cout	<< "Starting a new round of poker" << endl;
		round();

		break;
	}
}

void Poker_game::deal_player_cards() {
	cout << "Dealing player cards" << endl;
	cout << "--------------------" << endl;
	unsigned int i, j;
	for(i=0; i<players.size(); i++) {           /* for each player*/
		for(j=0; j<2; j++) {                    /* draw 2 cards */
			(players.at(i)) . set_card(j, deck.draw_card()); /* set player card */
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

	cout << endl << "---------------------------" << endl;
	//some logic needed here
	dealer=0;
	small_blind=1;
	big_blind=2;

	//set the players
	current_player= (big_blind+1)%players.size();
	int highest_better=big_blind;

	//set the big & small blind bets
	(players.at(small_blind)) . set_bet(50);
	(players.at(small_blind)) . set_chips((players.at(small_blind) . get_chips() - 50));
	(players.at(big_blind)) . set_bet(100);
	(players.at(big_blind)) . set_chips((players.at(big_blind) . get_chips() - 100));

	int n_players = players.size();

	while ( n_players > 1 && current_player != highest_better ) {         /* while there are still players */
		print_info();
		if(!(players.at(current_player)).folded()) {                      /* only when this player has not folded yet */
			action = (players.at(current_player)).poker_action(high_bet); /* current player needs to play */

			if(action->action == "fold") {
				n_players--;                
			} else if ( action->action == "check" ) { 
			} else if ( action->action == "call" ) { 
			} else if ( action->action == "raise" ) {
				high_bet = action->new_high_bet;
				highest_better = current_player;
			}

			else {
				continue;
			}
		}
		current_player = (current_player+1)%players.size();
	}

	cout << endl << "---------------------------" << endl;
	return;
}

void Poker_game::print_info (  ) {
	unsigned int i;
	cout	<< "Info about the game" << endl;
	cout	<< "Still " << players.size() << " players in the game" << endl;
	cout	<< "Common cards: ";
	for(i=0; i<n_common_cards; i++) {
		cout	<< common_cards[i] << " ";
	}
	cout	<< endl;
	for ( i = 0; i < players.size(); i += 1 ) {
		cout << i << ":";
		(players.at(i)) . print_info();
	}

	return ;
}		/* -----  end of method Poker_game::print_info  ----- */

void Poker_game::setup(){
        cout<<"Setting Poker game up"<<endl;
        fstream fin("pokerconfig.txt");

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
                cout<<"Player "<<*it<<" added to the game"<<endl;
        }      

        n_small_blind=values.at(0);
        n_big_blind=values.at(1);
        cout<<"Credits: "<<player.get_chips()<<"  Small blind: "<<n_small_blind<<"  Big blind: "<<n_big_blind<<endl;

        fin.close();
}
