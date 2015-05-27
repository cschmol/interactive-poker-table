#include	"poker_player.hpp"

Poker_player::Poker_player(string n, unsigned int c) {
	name 	= n;                                /* set name */
	chips 	= c;                                /* set number of chips */
	bet		= 0;
	hand_cards[0] = hand_cards[1] = -1;         /* needs to be initalizized to -1 */
	has_folded = false;

}

Poker_player::Poker_player(string n, unsigned int c, int s) {
	name 	= n;                                /* set name */
	chips 	= c;                                /* set number of chips */
	bet		= 0;
	hand_cards[0] = hand_cards[1] = -1;         /* needs to be initalizized to -1 */
	has_folded = false;
	cli_socket = s;

	sock = new Socket(s);
	sock->send("Welcome to the game");

}

Poker_player::~Poker_player() {
//	cout	<< "Poker_player " << name << " destroyed now" << endl;
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

//10, 2, cards
void Poker_player::print_info(int line, int n_cards, int *comm_cards) {
	mvprintw(line, 0, "Name: %s, Chips: %d, Bet: %d, Cards: %s | %s",
			  name.c_str(), chips, bet, card2str(hand_cards[0]).c_str(),
			  card2str(hand_cards[1]).c_str());
	int i;
//	for(i=0; i<n_cards; i++) {
//		cout << i << ": " << comm_cards[i] << " ";
//	}
//	cout <<	"Winning_odds:" << winning_odds(5, n_cards, comm_cards) << endl;

	//mvprintw(LINES - 4, 0, "%f", odds);
	//mvprintw(line, COLS - 30, "\tOdds: %f", odds);
	refresh();
	//getch();
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
		sprintf(buffer, "\nch:%d,nb:%d,b:%d(%s)$", chips, new_bet, bet, name.c_str());
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

void *Poker_player::set_wnd(WINDOW *w) {
	wnd = w;
}

void Poker_player::print_hello() {
//	wprintw(wnd, "Hello World");
//	wrefresh(wnd);
}













