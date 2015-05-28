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
		winprobs[i] = 0;           /* initalize the cards with -1 */
	}

	eval = new SevenEval();

}

Poker_game::~Poker_game (  )
{
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

	mvprintw(18, 0, "Pre-flop");
	clrtoeol();
	refresh();
	deal_player_cards();                             /* deal player cards */

	//Preflop odds

	std::array<int,2*NMAXPLAYERS> handcards;

	for (unsigned int i=0; i<players.size(); i++)
	{
		handcards[2*i]=players.at(i).get_card(0);   
		handcards[2*i+1]=players.at(i).get_card(1); 
	}	

	getProbability(static_cast<int>(players.size()),handcards,n_common_cards,common_cards,&winprobs[0]);
	
	update_probs();

	betting_round();
	print_info();
	current_player = big_blind;
	highest_better = big_blind;
	if(++current_player == players.end()) {
		current_player = players.begin();
	}

	mvprintw(18, 0, "Flop");
	clrtoeol();
	
	flop();                                     /* deal the flop */
	refresh();
	betting_round();
	print_info();
	current_player = big_blind;
	highest_better = big_blind;
	if(++current_player == players.end()) {
		current_player = players.begin();
	}

	mvprintw(18, 0, "Turn");
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

	mvprintw(18, 0, "River");
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
	
	mvprintw(LINES-1, 0, "Press ENTER to show the winner");
	getch();
	move(LINES-1,0);
	clrtoeol();
	refresh();
	

	std::vector<int> player_ranks;

	for (std::vector<Poker_player>::iterator it=players.begin(); it!=players.end(); it++ ) //create list with ranks of all players
	{
		if (!it->folded())
			player_ranks.push_back(eval->GetRank(it->get_card(0),it->get_card(1),common_cards[0],common_cards[1],common_cards[2],common_cards[3],common_cards[4]));
		else
			player_ranks.push_back(-1);
						
	}

	std::vector<int>::iterator it_rank= std::max_element(player_ranks.begin(),player_ranks.end()); 

	bool splitpot=false;
	std::vector<int> splitpot_index;

	for (std::vector<int>::iterator it=player_ranks.begin(); it!=player_ranks.end(); it++ ) //checking for splitpot
	{
		if ( (*it)==(*it_rank) && it!=it_rank )
		{
			splitpot = true;
			splitpot_index.push_back(std::distance( player_ranks.begin(), it )); 	
		}					
	}


	if (splitpot)
	{
		string text="";
		splitpot_index.push_back(std::distance( player_ranks.begin(), it_rank ));
		

		for (std::vector<int>::iterator it=splitpot_index.begin(); it!=splitpot_index.end(); it++ )
		{
			(players.at(*it)) .set_chips( (players.at(*it)).get_chips() + pot/splitpot_index.size() );
			text= text +" "+ players.at(*it).get_name();	
		}

		mvprintw(2, 0, "Splitpot: %s won this round", text.c_str());
		clrtoeol();
		mvprintw(3, 0, "They wins a pot of %d", pot);
		clrtoeol();
		refresh();

	}
	else
	{
		winner = std::distance( player_ranks.begin(), it_rank ); //index of winner
	

		mvprintw(2, 0, "%s has won this round", players.at(winner).get_name().c_str());
		clrtoeol();
		mvprintw(3, 0, "He/she wins a pot of %d", pot);
		clrtoeol();
		refresh();
		(players.at(winner)) .set_chips( (players.at(winner)) . get_chips() + pot );

	}

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


	//deal 3 common cards
	for(int j=0; j<3; j++) {                    /* draw 3 cards */
		common_cards[j] = deck.draw_card();
	}
	n_common_cards = 3;

	std::array<int,2*NMAXPLAYERS> handcards;

	for (unsigned int i=0; i<players.size(); i++)
	{
		handcards[2*i]=players.at(i).get_card(0);   
		handcards[2*i+1]=players.at(i).get_card(1); 
	}	

	getProbability(static_cast<int>(players.size()),handcards,n_common_cards,common_cards,&winprobs[0]);
	
	update_probs();
}

void Poker_game::turn() {
//	cout << "Dealing turn" << endl;
//	cout << "------------" << endl;
	//deal 1 card
	common_cards[3] = deck.draw_card();
	n_common_cards = 4;


	std::array<int,2*NMAXPLAYERS> handcards;

	for (unsigned int i=0; i<players.size(); i++)
	{
		handcards[2*i]=players.at(i).get_card(0);   
		handcards[2*i+1]=players.at(i).get_card(1); 
	}

	getProbability(static_cast<int>(players.size()),handcards,n_common_cards,common_cards,&winprobs[0]);

	update_probs();
}

void Poker_game::river() {
	//deal 1 card
//	cout << "Dealing river" << endl;
//	cout << "-------------" << endl;
	common_cards[4] = deck.draw_card();
	n_common_cards = 5;

	std::array<int,2*NMAXPLAYERS> handcards;

	for (unsigned int i=0; i<players.size(); i++)
	{
		handcards[2*i]=players.at(i).get_card(0);   
		handcards[2*i+1]=players.at(i).get_card(1); 
	}

	getProbability(static_cast<int>(players.size()),handcards,n_common_cards,common_cards,&winprobs[0]);

	update_probs();
}

void Poker_game::betting_round () {
	Poker_action *action;
	//bool big_blind_played = false;
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

//	cout	<< endl;
	int line = 9;
	for ( it=players.begin(); it!=players.end(); it++) {     /* iterate over all players */
		it -> print_info(++line, n_common_cards, common_cards);
		clrtoeol();
		if(it == big_blind) {
			//printw("\tBB");
			mvprintw(line, 70, "BB");
		}
		if(it == small_blind) {
			//printw("\tSB");
			mvprintw(line, 70, "SB");
		}
		if(it == dealer) {
			//printw("\tD");
			mvprintw(line, 70, "D");
		}
		if(it == highest_better) {
			//printw("\tHIGH");
			mvprintw(line, 74, "HIGH");
		}
		if(it == current_player) {
			//printw("\t\t<----");
			mvprintw(line, 67, "<-");
		}
//		printw("\todds: %f", current_player->winning_odds(100, n_common_cards, common_cards));
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
	
	move(LINES-2, 0);          // move to begining of line
	clrtoeol();          // clear line
	move(LINES-1, 0);          // move to begining of line
	clrtoeol();          // clear line
	refresh();

        n_small_blind=values.at(0);
        n_big_blind=values.at(1);


        fin.close();
}


void Poker_game::getProbability(int nPlayers, std::array<int,2*NMAXPLAYERS> handcards,int nCommonCards, int commoncards[5],double *arr)
{



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



    bool exist= false;
    int cardindexplayers[NMAXPLAYERS]={0,0,0,0,0,0,0,0};

    for (int i= 0; i<52; i++)
    {
        exist= false;
        for (int k=0;k<nCommonCards;k++)
        {
        if (i==commoncards[k])
            exist= true;
        }

        if (exist==true)
            continue;


              for(int j=0;j<nPlayers;j++)
                {
                    if (i!=handcards[2*j] && i!=handcards[2*j+1])
                    {

                        player_decks[j][cardindexplayers[j]]=i;
                        cardindexplayers[j]++;

                    }

            }
    }




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
    }


    std::array<int,NMAXPLAYERS> nPlayerWins;

    nPlayerWins.fill(0);
    int playerrank,samplerank;

    switch (nCommonCards)
    {
	case 0:
        for (int j=0;j<nPlayers;j++)
        {
                for (int k=0;k<NSAMPLEHANDS  ;k++)
                {
                    playerrank=eval->GetRank(handcards[j*2], handcards[j*2+1], spare_cards_player[j][4*k], spare_cards_player[j][4*k+1], spare_cards_player[j][4*k+2], spare_cards_player[j][4*k+3], spare_cards_player[j][4*k+4]);
                    samplerank=eval->GetRank(spare_cards_player[j][4*k+5], spare_cards_player[j][4*k+6], spare_cards_player[j][4*k], spare_cards_player[j][4*k+1], spare_cards_player[j][4*k+2], spare_cards_player[j][4*k+3], spare_cards_player[j][4*k+4]);
                    if (playerrank>samplerank)
                        nPlayerWins[j]++;
                }


        }
        break;
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

void Poker_game::update_probs()
{

	for (unsigned int i=0; i<players.size(); i++)
	{
		players.at(i).set_prob(winprobs[i]); 
	}


}




