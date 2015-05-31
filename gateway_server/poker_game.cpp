#include	"poker_game.hpp"
#include	<iterator>



Poker_game::Poker_game () {
	n_common_cards=0;
	for(int i=0; i<5; i++) {
		common_cards[i] = -1;           /* initalize the cards with -1 */
	}
	n_common_cards = 0;
}

Poker_game::Poker_game (SevenEval *se) {                         /* constructor */
	n_common_cards=0;
	for(int i=0; i<5; i++) {
		common_cards[i] = -1;           /* initalize the cards with -1 */
	}
	n_common_cards = 0;
	evaluator = se;
}

Poker_game::~Poker_game (  ) {
}

bool Poker_game::add_player(Poker_player *player) {
	if(players.size()<MAX_PLAYERS) {
		players.push_back(*player);
		return true;
	} else {
		cerr << "Maximum number of players reached" << endl;
		return false;
	}
}

void Poker_game::deal_common_cards(int count) {
	for(int i=0; i<count; i++) {                /* deal as many cards as specified */
		common_cards[n_common_cards++] = deck.draw_card();
	}
}

void Poker_game::reset_iterators() {
	current_player = highest_better = big_blind;
}

void Poker_game::round() {                          /* corresponds to 1 round of poker */

	pot = 0;
	
	//set the big&small blind's bets accordingly
	small_blind -> deduct_chips ( n_small_blind );
	big_blind -> deduct_chips ( n_big_blind );
	small_blind -> set_bet ( n_small_blind );
	big_blind -> set_bet ( n_big_blind );

	//add the blinds to the pot
	pot += n_small_blind;
	pot += n_big_blind;

	int common_cards_pr[] = {0, 3, 1, 1};
	int player_cards_pr[] = {2, 0, 0, 0};

	//the different rounds of poker
	for(int i=0; i<4; i++) {
		deal_player_cards(player_cards_pr[i]);
		deal_common_cards(common_cards_pr[i]);
		betting_round();
		print_info();
		reset_iterators();
		if(++current_player == players.end()) { /* circular "iterator" */
			current_player = players.begin();
		}

	}

	//determine a winner
	print_info();
	
	mvprintw(LINES-1, 0, "Press ENTER to show the winner");
	getch();
	move(LINES-1,0);
	clrtoeol();
	refresh();

	//determine a winner
	std::vector<Poker_player>::iterator winner=players.begin(), it;
	unsigned int max_rank = 0, rank;

	for(it=players.begin(); it!=players.end(); it++) { /* iterate over all players */
		//calculate the rank here for each player
//		rank = evaluator.GetRank(it->get_card(0), it->get_card(1), common_cards[0], common_cards[1], common_cards[2], common_cards[3], common_cards[4]);
		rank = it->rank(5, common_cards);
		if(rank > max_rank) {                   /* when beaten */
			winner = it;                        /* set the winner to iterator */
			max_rank = rank;                    /* raise the maximum rank */
		}
	}

	mvprintw(LINES - 4, 0, "... the winner is %s", (winner->get_name()).c_str());
	it->set_chips(it->get_chips() + pot);
	getch();
	

	//check if splitpot is needed

	pot = 0;                                    /* reset the pot to 0 */
}

void Poker_game::start() {
	std::vector<Poker_player>::iterator it;

	mvprintw(3, 0, "Starting the poker game now");

	dealer=players.begin();

	small_blind = dealer;
	if(++small_blind == players.end()) {
		small_blind = players.begin();
	}
	big_blind = small_blind;
	if(++big_blind == players.end()) {
		big_blind = players.begin();
	}
	current_player = big_blind;
	if(++current_player == players.end()) {
		current_player = players.begin();
	}

	while(players.size() > 1) {
		high_bet = n_big_blind;                         /* set the highest bet to the big blind */
		pot = 0;


		highest_better=big_blind;

		//set each players has_folded to 0, so that each player can play again
		for ( it=players.begin(); it!=players.end(); it++ ) {
			it -> reset_fold();
			it -> set_bet(0);

			if ( it->get_chips() <= 0 ) {
				players.erase(it);
			}
		}

		round();

		if(++dealer == players.end()) {
			dealer = players.begin();
		}
		if(++small_blind == players.end()) {
			small_blind = players.begin();
		}
		if(++big_blind == players.end()) {
			big_blind = players.begin();
		}
		if(++current_player == players.end()) {
			current_player = players.begin();
		}
	}
}

void Poker_game::deal_player_cards(int n) {
	std::vector<Poker_player>::iterator it;
	for ( it=players.begin(); it!=players.end(); it++) {     /* iterate over all players */
		for(int j=0; j<n; j++) {                                 /* draw 2 cards */
			it -> set_card(j, deck.draw_card());
		}
	}
}

void Poker_game::deal_common_cards(unsigned int n) {
	//deal n common cards
	for ( unsigned int i=0; i<n; i++) {
		common_cards[n_common_cards++] = deck.draw_card();
	}
}

void Poker_game::betting_round () {
	Poker_action *action;
	//bool big_blind_played = false;

// _________________________________________
//  might need to go some other place here 
//  it does not work correctly when players 
//  fold in a previous round                
// -----------------------------------------
	int n_players = players.size();             /* might need to be some other place */

	while ( (n_players > 1 && current_player != highest_better) || (current_player==highest_better && current_player==big_blind) ) {         /* while there are still players */
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
				continue;                       /* give the player another chance to chose an action */
			}
		}
		if(current_player==big_blind && current_player==highest_better) {       /* Assure that big blind can also play */
			break;
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

	if (n_common_cards!=0)
	{
		string text = "Common Cards: ";

		move(19, 0);          // move to begining of line
		clrtoeol();          // clear line
		
		for(i=0; i<n_common_cards; i++) {
			text = text +" "+ card2str(common_cards[i]);
		}
		mvprintw(19, 0, "%s",text.c_str());
	}

	move(16, 0);          // move to begining of line
	clrtoeol();          // clear line
	mvprintw(16, 0, "Current pot: %d",pot);

	int line = 9;
	for ( it=players.begin(); it!=players.end(); it++) {     /* iterate over all players */
		it -> print_info(++line, n_common_cards, common_cards);
		clrtoeol();
		if(it == big_blind) {
			printw("\tBB");
		} else if(it == small_blind) {
			printw("\tSB");
		} else if(it == dealer) {
			printw("\tD");
		}
		if(it == highest_better) {
			printw("\tHIGH");
		}
		if(it == current_player) {
			printw("\t<-");
		}
		refresh();
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

		mvprintw(0, COLS/3, "Interactive Poker Table");
		refresh();

        for (std::vector<string>::iterator it = playernames.begin() ; it != playernames.end(); ++it){
			mvprintw(LINES-2, 0, "Waiting for player %s to connect", it->c_str());
			clrtoeol();
			refresh();

			Poker_player *player = new Poker_player("", 0, sock.get_sock());
			player->set_evaluator(evaluator);


			player->set_name(*it);
			player->set_chips(values.at(2));
			add_player(player);
			mvprintw(LINES-1, 0, "Player %s added to the game", it->c_str());
			clrtoeol();
			refresh();
        }      
	
		move(LINES-2, 0); // move to begining of line
		clrtoeol();       // clear line
		move(LINES-1, 0); // move to begining of line
		clrtoeol();       // clear line
		refresh();

        n_small_blind=values.at(0);
        n_big_blind=values.at(1);


        fin.close();
}





