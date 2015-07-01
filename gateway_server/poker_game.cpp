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
	nfc=0;
	eval = new SevenEval();

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


	addmessage("Starting a new round");
	pot = 0;

	n_players = players.size();
	
	//set the big&small blind's bets accordingly
	small_blind -> deduct_chips ( n_small_blind );
	big_blind -> deduct_chips ( n_big_blind );

	small_blind -> set_bet ( n_small_blind );
	big_blind -> set_bet ( n_big_blind );

	//add the blinds to the pot
	pot += n_small_blind;
	pot += n_big_blind;

	deck.reset();
	deal_player_cards();                             /* deal player cards */
	addmessage("Dealing player cards");
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
	draw();
	current_player = big_blind;
	highest_better = big_blind;
	if(++current_player == players.end()) {
		current_player = players.begin();
	}


	addmessage("Dealing the flop");	
	flop();                                     /* deal the flop */

	betting_round();
	draw();
	current_player = big_blind;
	highest_better = big_blind;
	if(++current_player == players.end()) {
		current_player = players.begin();
	}


	addmessage("Dealing the turn");
	turn();                                     /* deal the turn */
	betting_round();
	draw();
	current_player = big_blind;
	highest_better = big_blind;
	if(++current_player == players.end()) {
		current_player = players.begin();
	}

	addmessage("Dealing the river");
	river();                                    /* deal the river */
	betting_round();
	draw();
	current_player = big_blind;
	highest_better = big_blind;
	if(++current_player == players.end()) {
		current_player = players.begin();
	}


	//determine a winner
	unsigned int winner;                                 /* do that by hand now */


	addmessage("Press ENTER to show the winner");
	draw();
	getch();

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


		addmessage("Splitpot: "+text+" won this round");
		addmessage("They win a pot of "+std::to_string(pot)+"$");

	}
	else
	{
		winner = std::distance( player_ranks.begin(), it_rank ); //index of winner
	

		addmessage(players.at(winner).get_name()+" wins the round!");
		addmessage("He/She wins a pot of "+std::to_string(pot)+"$");
		(players.at(winner)) .set_chips( (players.at(winner)) . get_chips() + pot );

	}
	draw();
	pot = 0;
	
	//blinds logic
}

void Poker_game::start() {
	std::vector<Poker_player>::iterator it;
	addmessage("Starting the poker game now");



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
		n_common_cards=0;

		highest_better=big_blind;

		//set each players has_folded to 0, so that each player can play again


		round();

		for ( it=players.begin(); it!=players.end(); it++ ) {
			it -> reset_fold();
			it -> set_bet(0);

			if ( it->get_chips() <= 0 ) {
				addmessage(it->get_name()+" has no chips and lost the game");
				players.erase(it);
				update_player_windows(); 
				draw();
				it--;    //else a player would be skipped
			}
		}
		draw();


		//check if iterator is invalid because of erasing player
		if(dealer == players.end()) {
			dealer = players.begin();
		}
		

		if(small_blind == players.end()) {
			small_blind = players.begin();
		}
		if(big_blind == players.end()) {
			big_blind = players.begin();
		}
		if(current_player == players.end()) {
			current_player = players.begin();
		}
		


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
	getch();
	addmessage(players.at(0).get_name()+" has won the game");
	draw();
	getch();
	return;
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
	addmessage("New betting round");	


	while ((n_players > 1 && current_player != highest_better) || (current_player==highest_better && current_player==big_blind)) {         
		draw();
		if(!current_player -> folded()) {       /* only when player has not folded yet */


			if (n_players==1){
				action = new Poker_action;
				action->action="check";
			} 
			else
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



void Poker_game::setup(){


	std::srand(time(NULL));                                

	setlocale (LC_ALL, "");

    	wGameInfo= initscr();
    	clear();
    	noecho();
    	curs_set(0);
    	cbreak();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
    	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	bkgd(COLOR_PAIR(1));



	
	

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

			Poker_player *player = new Poker_player("", 0, sock.get_sock(),wGameInfo);


			player->set_name(*it);
			player->set_chips(values.at(2));
			add_player(player);
			mvprintw(LINES-1, 0, "Player %s added to the game", it->c_str());
			clrtoeol();
			refresh();
        }

	update_player_windows(); 

        n_small_blind=values.at(0);
        n_big_blind=values.at(1);
	nfc=values.at(3);


	wPot=derwin(wGameInfo,4,28,static_cast<int>(LINES/2-4/2),static_cast<int>(COLS/2)-28/2);
	wbkgd(wPot,COLOR_PAIR(2));

	wMessage=derwin(wGameInfo,5,COLS -static_cast<int>(COLS*0.65),LINES-5,static_cast<int>(COLS*0.65));
	wbkgd(wMessage,COLOR_PAIR(2));


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


void Poker_game::update_player_windows()
{
	int y;
	int x;
	double i=0;
	for (std::vector<Poker_player>::iterator it=players.begin(); it!=players.end(); it++) {
		double cosinus=cos(i/(players.size())*2*M_PI);
		double sinus=sin(i/(players.size())*2*M_PI);
		i=i+1;
		y=static_cast<int>(0.34*LINES*sinus+0.5*LINES-3);
		x=static_cast<int>(0.34*COLS*cosinus+0.5*COLS-11);
		mvprintw(i, 0, "%f,%d,%d,%f", i,y,x,cosinus);



		mvderwin(it->get_wnd(),y,x);
	}
}	


void Poker_game::draw()
{

	wclear(wGameInfo); 
	
	touchwin(wGameInfo);

	for (std::vector<Poker_player>::iterator it=players.begin(); it!=players.end(); it++) {
		 

		bool active=it==current_player;
		it->draw(active);
	}

	wclear(wPot);
	box(wPot, 0, 0);

	mvwprintw(wPot,1,1,+"        Pot: %d$",pot);
	
	if (n_common_cards!=0){
		wmove(wPot,2,1);

		for (unsigned int i=0;i<n_common_cards;i++)
			waddwstr(wPot,(card2unistr(common_cards[i])).c_str());
	}
	
	wrefresh(wPot);
	
	wclear(wMessage);



	for (unsigned int i=0;i<5;i++)
		mvwprintw(wMessage,4-i,0,message[i].c_str());

	wrefresh(wMessage);

	double i=0;
	for (std::vector<Poker_player>::iterator it=players.begin(); it!=players.end(); it++) {
		 
		double cosinus=cos(i/(players.size())*2*M_PI);
		double sinus=sin(i/(players.size())*2*M_PI);
		i=i+1;
		int y=static_cast<int>(0.17*LINES*sinus+0.5*LINES);
		int x=static_cast<int>(0.17*COLS*cosinus+0.5*COLS);
		
		mvwprintw(wGameInfo,y,x,"%d$",it->get_bet());
	}


	refresh();

}


void Poker_game::addmessage(std::string text){
	
	for (unsigned int i=4;i>0;i--)
		message[i]=message[i-1];

	message[0]=text;
}

