
#include	"poker_player.hpp"

Poker_player::Poker_player(string n, unsigned int c) {
	name 	= n;                                /* set name */
	chips 	= c;                                /* set number of chips */
	bet		= 0;
	hand_cards[0] = hand_cards[1] = -1;         /* needs to be initalizized to -1 */
	has_folded = false;
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
	cout << "Player " << name << " has bet set to " << b << endl;
	bet = b;
	return;
}

void Poker_player::set_card (int index, int card) {
	hand_cards[index] = card;
}

void Poker_player::print_info() {
	cout << "Name: " << name << "\t";
	cout << "Chips: " << chips << "\t";
	cout << "Bet: " << bet << "\t";
	cout << "Cards: " << card2str(hand_cards[0]) << " " << card2str(hand_cards[1]) << endl;
}

bool Poker_player::folded() {
	return has_folded;
}


Poker_action *Poker_player::poker_action(unsigned int new_bet) {
	Poker_action *pa = new Poker_action;
	string action;

	bool unvalid_action = true;

	do {
		//get the action from stdin
		cout << "Player " << name
			 << " needs to chose an action (" 
			 << "fold/check/call/raise) : " << endl;
		cout << "Chips: "   << chips   << endl;
		cout << "new_bet: " << new_bet << endl;
		cout << "bet: "     << bet     << endl;
		cin >> action;                          /* read action */

		if(action == "fold") {
			has_folded = true;
			unvalid_action = false;

		} else if(action== "check") {
			if ( new_bet > bet ) {
				cout << "You cannot check now" << endl;
				continue;
			}
			unvalid_action = false;

		} else if(action == "call") {
			if ( chips < new_bet ) {
				cout << "You cannot call now" << endl;
				has_folded = true;              /* player folds then */
			} else if ( new_bet == bet) {
				cout << "No need to call, check'ing instead" << endl;
			} else {
				pa->new_player_chips = new_bet - bet;
				chips = chips - new_bet + bet;
				bet = new_bet;
			}
			unvalid_action = false;

		} else if(action == "raise") {
			do {
				cout << "What should be the new high bet?";
				cin >> pa->new_high_bet;
			} while(pa->new_high_bet<=new_bet || pa->new_high_bet-bet > chips);
			int remaining = pa->new_high_bet - bet; /* what needs to be put in the middle */
			pa->new_player_chips = remaining;
			chips -= remaining;                 /* deduct that amount */
			bet = pa->new_high_bet;
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
