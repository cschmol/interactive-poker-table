#include	"poker_game.hpp"
#include	<iterator>

#define MAX_PLAYERS 8






Poker_game::Poker_game () {                            /* constructor */
	n_common_cards=0;
	for(int i=0; i<5; i++) {
		common_cards[i] = -1;           /* initalize the cards with -1 */
	}
	n_common_cards = 0;                         /* no common cards have been dealt */

	for(int i=0; i<NMAXPLAYERS; i++) {
		winprops[i] = 0;           /* initalize the cards with -1 */
	}

}

Poker_game::~Poker_game (  )
{
	//close(serv_sock);                          /* close the socket */
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

	mvprintw(16, 0, "Pre-flop");
	clrtoeol();
	refresh();
	deal_player_cards();                             /* deal player cards */
	betting_round();
	print_info();
	current_player = big_blind;
	highest_better = big_blind;
	if(++current_player == players.end()) {
		current_player = players.begin();
	}

	mvprintw(16, 0, "Flop");
	clrtoeol();
	
	flop();                                     /* deal the flop */
	mvprintw(17, 0, "Common cards: %s %s %s",card2str(common_cards[0]).c_str(),card2str(common_cards[1]).c_str(),card2str(common_cards[2]).c_str());
	refresh();
	betting_round();
	print_info();
	current_player = big_blind;
	highest_better = big_blind;
	if(++current_player == players.end()) {
		current_player = players.begin();
	}

	mvprintw(16, 0, "Turn");
	clrtoeol();
	refresh();
	turn();                                     /* deal the turn */
	betting_round();
	print_info();
	current_player = big_blind;
	highest_better = big_blind;
	if(++current_player == players.end()) {
		current_player = players.begin();
	}

	mvprintw(16, 0, "River");
	clrtoeol();
	refresh();
	river();                                    /* deal the river */
	betting_round();
	print_info();
	current_player = big_blind;
	highest_better = big_blind;
	if(++current_player == players.end()) {
		current_player = players.begin();
	}


	//determine a winner
	unsigned int winner;                                 /* do that by hand now */
	print_info();
	do {
		mvprintw(0, 0, "Please determine a winner by hand: ");
		winner = getch();
	} while (winner > players.size());

	mvprintw(1, 0, "Player %d has won", winner);
	mvprintw(2, 0, "He wins a pot of %d", pot);
	(players.at(winner)) .set_chips( (players.at(winner)) . get_chips() + pot );
	pot = 0;

	//blinds logic
}

void Poker_game::start() {
	std::vector<Poker_player>::iterator it;
//	cout	<< "Starting the poker game now" << endl;

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

//	cout 	<< "Dealer: ";
//	dealer->print_info();
//	cout 	<< "small_blind";
//	small_blind->print_info();
//	cout 	<< "big_blind";
//	big_blind->print_info();
//	cout 	<< "current_player";
//	current_player->print_info();

	while(players.size() > 1) {
		high_bet = n_big_blind;                         /* set the highest bet to the big blind */
		pot = 0;


		highest_better=big_blind;

		//set each players has_folded to 0, so that each player can play again
		for ( it=players.begin(); it!=players.end(); it++ ) {
			it -> reset_fold();
			it -> set_bet(0);

			if ( it->get_chips() <= 0 ) {
//				cout	<< "Player " << it->get_name() << " is game-over, removing him" << endl;
				players.erase(it);
			}
		}

//		cout	<< "Starting a new round of poker" << endl;
		round();
//		break;

		if(++dealer == players.end()) {
			dealer = players.begin();
		}
		
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
	}
}

void Poker_game::deal_player_cards() {
	std::vector<Poker_player>::iterator it;

//	cout << "Dealing player cards" << endl;
//	cout << "--------------------" << endl;
	unsigned int j;
	for ( it=players.begin(); it!=players.end(); it++) {     /* iterate over all players */
		for(j=0; j<2; j++) {                                 /* draw 2 cards */
			it -> set_card(j, deck.draw_card());
		}
	}
}

void Poker_game::flop() {
//	cout << "Dealing flop" << endl;
//	cout << "------------" << endl;
	unsigned int j;
	//deal 3 common cards
	for(j=0; j<3; j++) {                    /* draw 3 cards */
		common_cards[j] = deck.draw_card();
	}
	n_common_cards = 3;
}

void Poker_game::turn() {
//	cout << "Dealing turn" << endl;
//	cout << "------------" << endl;
	//deal 1 card
	common_cards[3] = deck.draw_card();
	n_common_cards = 4;
}

void Poker_game::river() {
	//deal 1 card
//	cout << "Dealing river" << endl;
//	cout << "-------------" << endl;
	common_cards[4] = deck.draw_card();
	n_common_cards = 5;
}

void Poker_game::betting_round () {
	Poker_action *action;
	bool big_blind_played = false;
//	cout	<< "Beginning betting round" << endl;

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
				continue;
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

//void print_info(int line, int n_cards, int *comm_cards) {
void Poker_game::print_info (  ) {
	unsigned int i;
	std::vector<Poker_player>::iterator it;
//	cout	<< "Info about the game" << endl;
//	cout	<< "Still " << players.size() << " players in the game" << endl;
//	cout	<< "+++++++++++++++++" << endl;
//	cout	<< "Pot: " << pot << endl;
//	cout	<< "Common cards: ";
	for(i=0; i<n_common_cards; i++) {
//		cout	<< common_cards[i] << " ";
//		cout	<< card2str(common_cards[i]) << ",";
	}
//	cout	<< endl;
	int line = 10;
	for ( it=players.begin(); it!=players.end(); it++) {     /* iterate over all players */
		it -> print_info(line++, n_common_cards, common_cards);
		clrtoeol();
		if(it == big_blind) {
			printw("\tBB");
		}
		if(it == small_blind) {
			printw("\tSB");
		}
		if(it == dealer) {
			printw("\tD");
		}
		if(it == highest_better) {
			printw("\tHIGH");
		}
		if(it == current_player) {
			printw("\t\t<----");
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


			player->set_name(*it);
			player->set_chips(values.at(2));
			player->set_wnd(stdscr);
			add_player(player);
			mvprintw(LINES-1, 0, "Player %s added to the game", it->c_str());
			clrtoeol();
			refresh();
        }      

        n_small_blind=values.at(0);
        n_big_blind=values.at(1);


        fin.close();
}


void Poker_game::getProbability(int nPlayers, std::array<int,10> handcards,int nCommonCards, std::array<int,5> commoncards,double *arr)
{

    SevenEval const* eval = new SevenEval();

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));

    auto engine = std::default_random_engine{};
    engine.seed(now_c);

    std::array<std::array<int,47>,NMAXPLAYERS> player_decks;
    std::array<std::array<int,4400>,NMAXPLAYERS> spare_cards_player;
    //std::array<std::array<int,47>,NMAXPLAYERS> spare_cards_samples;


    for (int i= 0; i<NMAXPLAYERS; i++)
    {
        spare_cards_player[i].fill(0);
        //spare_cards_samples[i].fill(0);
        player_decks[i].fill(0);
    }




    int cardindexplayers[NMAXPLAYERS]={0,0,0,0,0,0,0,0,0,0};

    for (int i= 0; i<52; i++)
    {
        for (int k=0;k<nCommonCards;k++)
        {
              for(int j=0;j<nPlayers;j++)
                {
                    if (i!=handcards[2*j] && i!=handcards[2*j+1])
                    {
                        player_decks[j][cardindexplayers[j]]=i;
                        spare_cards_player[j][cardindexplayers[j]]=i;
                        cardindexplayers[j]++;
                    }
                }
            }
    }

    /*if (nCommonCards==5)
    {

    }
    else
    {

    }*/
    for(int j=0;j<nPlayers;j++)
    {
            for(int i=0;i<NSHUFFLEDDECKS;i++)
            {
                std::shuffle(std::begin(player_decks[j]), std::end(player_decks[j]), engine);

                for(int k=0;k<44;k++)
                {
                    spare_cards_player[j][i*44+k]=player_decks[j][k];
                }

            }
    }



    for(int j=0;j<nPlayers;j++)
    {
                std::shuffle(std::begin(spare_cards_player[j]), std::end(spare_cards_player[j]), engine);
                //std::shuffle(std::begin(spare_cards_samples[j]), std::end(spare_cards_samples[j]), engine);
    }


    std::array<int,NMAXPLAYERS> nPlayerWins;

    nPlayerWins.fill(0);
    int playerrank,samplerank;

    switch (nCommonCards)
    {
    case 3:
        for (int j=0;j<nPlayers;j++)
        {
                for (int k=0;k<NSAMPLEHANDS  ;k++)
                {
                    playerrank=eval->GetRank(handcards[j*2], handcards[j*2+1], commoncards[0], commoncards[1], commoncards[2], spare_cards_player[j][2*k], spare_cards_player[j][2*k+1]);
                    samplerank=eval->GetRank(commoncards[0], commoncards[1], commoncards[2], spare_cards_player[j][4*k], spare_cards_player[j][4*k+1],spare_cards_player[j][4*k+2],spare_cards_player[j][4*k+3]);
                    if (playerrank>samplerank)
                        nPlayerWins[j]++;
                }


        }
        break;
    case 4:
        for (int j=0;j<nPlayers;j++)
        {
                for (int k=0;k<NSAMPLEHANDS  ;k++)
                {
                    playerrank=eval->GetRank(handcards[j*2], handcards[j*2+1], commoncards[0], commoncards[1], commoncards[2], commoncards[3], spare_cards_player[j][k]);
                    samplerank=eval->GetRank(commoncards[0], commoncards[1], commoncards[2], commoncards[3], spare_cards_player[j][4*k],spare_cards_player[j][4*k+1],spare_cards_player[j][4*k+2]);
                    if (playerrank>samplerank)
                        nPlayerWins[j]++;


                }


        }
        break;
    case 5:
        for (int j=0;j<nPlayers;j++)
        {
                for (int k=0;k<NSAMPLEHANDS  ;k++)
                {
                    playerrank=eval->GetRank(handcards[j*2], handcards[j*2+1], commoncards[0], commoncards[1], commoncards[2], commoncards[3], commoncards[4]);
                    samplerank=eval->GetRank(commoncards[0], commoncards[1], commoncards[2], commoncards[3], commoncards[4],spare_cards_player[j][2*k],spare_cards_player[j][2*k+1]);
                    if (playerrank>samplerank)
                        nPlayerWins[j]++;
                }


        }
        break;
    }



    for (int j=0;j<nPlayers;j++)
    {

        *arr=static_cast<double>(nPlayerWins[j])/static_cast<double>(NSAMPLEHANDS);
        //std::cout<<*arr<<std::endl;
        arr++;
    }



}

