#include	"poker_player.hpp"

Poker_player::Poker_player(string n, unsigned int c) {
	name 	= n;                                /* set name */
	chips 	= c;                                /* set number of chips */
	bet		= 0;
	hand_cards[0] = hand_cards[1] = -1;         /* needs to be initalizized to -1 */
	has_folded = false;
	winprob= 0;

}

Poker_player::Poker_player(string n, unsigned int c, int s,WINDOW *parentwin) {
	name 	= n;                                /* set name */
	chips 	= c;                                /* set number of chips */
	bet		= 0;
	hand_cards[0] = hand_cards[1] = -1;         /* needs to be initalizized to -1 */
	has_folded = false;
	cli_socket = s;

	sock = new Socket(s);
	sock->send("Welcome to the game");

	setlocale(LC_ALL,"");
	wnd=derwin(parentwin,6,22,10,10);
	wbkgd(wnd,COLOR_PAIR(2));
	

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


	refresh();

}

bool Poker_player::folded() {
	return has_folded;
}


Poker_action *Poker_player::poker_action(unsigned int new_bet) {
	Poker_action *pa = new Poker_action;
	string action;
	string amount;
	string allin;
	char buffer[512];

	bool unvalid_action = true;

//	wbkgd(wnd, COLOR_PAIR(1));
//	wrefresh(wnd);

	do {
		sprintf(buffer, "send/%d/%d/%d/%f/1",bet, chips, new_bet, winprob);
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

			if (pa->new_player_chips>chips){	//Allin?

				pa->new_player_chips=chips;
			}

			if(make_bet(pa->new_player_chips)) {
			} else {
				sock->send("You don't have enough chips to call");
				has_folded = true;
			}
			unvalid_action = false;

		} else if(action.substr(0,5) == "raise") {
				amount = action.substr(6,action.length()-6);
				//amount.erase(amount.length() - 1);
				istringstream ( amount ) >> pa->new_high_bet; /* convert string to integer */
				pa->new_player_chips = pa->new_high_bet -bet;

				action=action.substr(0,5);
				if (pa->new_high_bet >= new_bet && make_bet(pa->new_high_bet - bet))
					unvalid_action = false;

			
		}

		pa->action = action;

	} while (unvalid_action);



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


void Poker_player::draw(bool active){

	if (active)
		wbkgd(wnd,COLOR_PAIR(3));
	else
		wbkgd(wnd,COLOR_PAIR(2));

	wclear(wnd);
	


	box(wnd, 0, 0);
	mvwprintw(wnd,1,1,+"%s: %d$",name.c_str(),chips);

	

	if (has_folded)
		mvwprintw(wnd,2,1,"FOLDED");
	else{
		mvwprintw(wnd,2,1,"Bet: %d",bet);
		mvwprintw(wnd,3,1,"Odds: %f",winprob);
		mvwprintw(wnd,4,1,"Cards:");
		
		waddwstr(wnd, card2unistr(hand_cards[0]).c_str());
		waddwstr(wnd, card2unistr(hand_cards[1]).c_str());
	}
	wrefresh(wnd);


	
}








