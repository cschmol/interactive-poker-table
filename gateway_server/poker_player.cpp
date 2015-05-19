
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
	bet = b;
	return;
}

void Poker_player::set_card (int index, int card) {
	hand_cards[index] = card;
}

void Poker_player::print_info() {
	cout << "Name: " << name << "\t";
	cout << "Chips: " << chips << endl;
}

bool Poker_player::folded() {
	return has_folded;
}


Poker_action *Poker_player::poker_action(unsigned int new_bet) {
	Poker_action *pa = new Poker_action;
	string action;


	bool unvalid_action = true;

	do {
//		cout << "Chips: "   << chips   << endl;
//		cout << "new_bet: " << new_bet << endl;
//		cout << "bet: "     << bet     << endl;

		cout << "Player " << name
			 << " needs to chose an action (" 
			 << "fold/check/call/raise) : " << endl;
		cin >> action;

		//see what action the player wants
		if(action == "fold") {
			has_folded = true;                      /* player out of the round */
			unvalid_action = false;

		} else if(action== "check") {
			if ( new_bet > bet ) {
				cout << "You cannot check now" << endl;
				continue;
			}
			unvalid_action = false;

		} else if(action == "call") {
			if ( chips < new_bet ) {
				cout << "You cannot bet now" << endl;
				cout << "Therefore folding now" << endl;
				has_folded = true;                  /* do it like this for now */
			} else if ( new_bet == bet) {
				cout << "no need to call now, only fold/raise/check" << endl;
			} else {
				chips -= new_bet - bet;             /* chips are what is left when player has betted the same */
				bet = new_bet;                      /* set the new player bet accordingly */
			}
			unvalid_action = false;

		} else if(action == "raise") {
			do {
				cout << "By how much do you want to re-raise?";
				cin >> pa->amount;
			} while(pa->amount<=0 || pa->amount > chips);
			chips = chips + bet -pa->amount;
//			chips -= pa->amount - bet;
			bet = new_bet + pa->amount;
			unvalid_action = false;
		}

		pa->action = action;

		cout << endl;
	} while (unvalid_action);


	return pa;
}
