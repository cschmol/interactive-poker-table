#include	"poker_player.hpp"

Poker_player::Poker_player(string n, unsigned int c) {
	name 	= n;                                /* set name */
	chips 	= c;                                /* set number of chips */
	bet		= 0;
	hand_cards[0] = hand_cards[1] = -1;         /* needs to be initalizized to -1 */
	has_folded = false;
	winprob= 0;

}

Poker_player::Poker_player(string n, unsigned int c, int s) {
	name 	= n;                                /* set name */
	chips 	= c;                                /* set number of chips */
	bet		= 0;
	hand_cards[0] = hand_cards[1] = -1;         /* needs to be initalizized to -1 */
	has_folded = false;
	cli_socket = s;

	sock = new Socket(s);
	*sock << "Interactive Poker Table\n";

}

Poker_player::~Poker_player() {
}

string Poker_player::get_name (  )
{
	return name;
}

void Poker_player::set_name (string value)
{
	name	= value;
	return ;
}


unsigned int Poker_player::get_chips (  )
{
	return chips;
}

void Poker_player::set_chips ( unsigned int c )
{
	chips = c;
	return ;
}

unsigned int Poker_player::get_bet() {
	return bet;
}

void Poker_player::set_bet ( unsigned int b ) {
	bet = b;
	return;
}

void Poker_player::set_card (int index, int card) {
	hand_cards[index] = card;
}


void Poker_player::set_prob(double prob) {
	winprob=prob;
}

double Poker_player::get_prob() {
	return winprob;
}

//10, 2, cards
void Poker_player::print_info(int line, int n_cards, int *comm_cards) {
	mvprintw(line, 0, "Name: %s, Chips: %d, Bet: %d, Cards: %s | %s",
			  name.c_str(), chips, bet, card2str(hand_cards[0]).c_str(),
			  card2str(hand_cards[1]).c_str());
	printw("\todds: %f", winning_odds(100, n_cards, comm_cards));


	refresh();

}

bool Poker_player::folded() {
	return has_folded;
}


Poker_action *Poker_player::poker_action(unsigned int new_bet) {
	Poker_action *pa = new Poker_action;
	string action;
	string amount;
	char buffer[512];

	bool unvalid_action = true;

//	wbkgd(wnd, COLOR_PAIR(1));
//	wrefresh(wnd);

	do {
		sprintf(buffer, "ch:%d,nb:%d,b:%d,p:%f(%s)$ ", chips, new_bet, bet,winprob,name.c_str());
		sock->send(buffer);
//		mvwprintw(wnd, 0, 0, "ch:%d,nb:%d,b:%d(%s)$", chips, new_bet, bet, name.c_str());
//		wrefresh(wnd);
		action = sock->recv();
		action.erase(action.length() - 1);
		//sock->send(action);

		if(action == "fold") {
			has_folded = true;
			unvalid_action = false;

		} else if(action== "check") {
			if ( new_bet > bet ) {
				sock->send("You cannot check now");
				continue;
			}
			unvalid_action = false;

		} else if(action == "call") {
			pa->new_player_chips = new_bet - bet;
			if(make_bet(pa->new_player_chips)) {
			} else {
				sock->send("You don't have enough chips to call");
				has_folded = true;
			}
			unvalid_action = false;

		} else if(action == "raise") {
			do {
				sock->send("What should be the new high bet?");
				amount = sock->recv();
				amount.erase(amount.length() - 1);
				istringstream ( amount ) >> pa->new_high_bet; /* convert string to integer */
			} while (pa->new_high_bet <= new_bet || !make_bet(pa->new_high_bet - bet)); /* works because of short-circuit || */

			unvalid_action = false;
		}

		pa->action = action;

	} while (unvalid_action);


//	wbkgd(wnd, COLOR_PAIR(2));
//	wrefresh(wnd);
	return pa;
}


/* deduct the amount of chips specified */
/* if player has less chips, return the amount of chips */
unsigned int Poker_player::deduct_chips(unsigned int c)  {
	if(chips > c) {
		chips -= c;
		return c;
	} else {
		chips = 0;
		return c;
	}
}
void Poker_player::reset_fold() {
	has_folded=false;
}


int Poker_player::get_card ( int index )
{
	return hand_cards[index];
}


bool Poker_player::make_bet(unsigned int c) {
	if(c>chips) {
		return false;
	} else {
		chips -= c;                             /* decrease chips by bet */
		bet += c;                               /* increase bet by bet */
		return true;
	}
}

void Poker_player::fold() {
	has_folded = true;
}


WINDOW *Poker_player::get_wnd() {
	return wnd;
}

void Poker_player::set_wnd(WINDOW *w) {
	wnd = w;
	return;
}

void Poker_player::print_hello() {
//	wprintw(wnd, "Hello World");
//	wrefresh(wnd);
	return;
}

double Poker_player::winning_odds(int rounds, int n_common_cards, int *common_cards) { /* only when player cards are already dealt */
	int i;
	int own_cards[7], opponent_cards[7];
	own_cards[0] = hand_cards[0];
	own_cards[1] = hand_cards[1];
	int own_rank, opponent_rank;

	double wins = 0, losses = 0;

	rounds = 100;

	while(rounds--) {                     /* as many rounds as needed */
		Card_deck cd;                           /* generate a new card deck for every round */
		cd.shuffle();
		if(own_cards[0] == -1 || own_cards[1] == -1) {
			own_cards[0] == cd.draw_card();
			own_cards[1] == cd.draw_card();
		} else {
			own_cards[0] = hand_cards[0];
			own_cards[1] = hand_cards[1];
		}

		opponent_cards[0] = cd.draw_card();
		opponent_cards[1] = cd.draw_card();

		for(i=2; i<2+n_common_cards; i++) {
			own_cards[i] = common_cards[i-2];
			opponent_cards[i] = own_cards[i];
		}

		for(i=2+n_common_cards; i<7; i++) { /* simulate common cards */
			own_cards[i] = cd.draw_card();
			opponent_cards[i] = own_cards[i];
		}

		own_rank = evaluator.GetRank(own_cards[0], own_cards[1], own_cards[2], own_cards[3], own_cards[4], own_cards[5], own_cards[6]); 
		opponent_rank = evaluator.GetRank(opponent_cards[0], opponent_cards[1], opponent_cards[2], opponent_cards[3], opponent_cards[4], opponent_cards[5], opponent_cards[6]);

		if(own_rank < opponent_rank) {
			losses++;
		} else {
			wins++;
		}
		if(rounds % 10 == 0) {
			mvprintw(15, 0, "roundstogo: %d, wins: %f, losses: %f, ratio: %f", rounds,  (double) wins, (double) losses, (double) wins / ((double) wins + (double) losses));
			clrtoeol();
			refresh();
			getch();
		}
	}

	double odds = wins / (wins+losses);
	mvprintw(LINES - 5, 0, "Calculated odds: %f", odds);
	refresh();
	return odds;
//	mvprintw(LINES - 5, 0, "from alg: %f", odds);
//	return (wins / (wins + losses));
//	return (double) (double) wins / ( (double) wins + (double) losses );
}













