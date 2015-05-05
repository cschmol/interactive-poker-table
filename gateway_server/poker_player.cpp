
#include	"poker_player.hpp"

void Poker_player::print_info() {
	cout << "Name of the player: " << name << endl;
}


Poker_action *Poker_player::get_action() {
	string player_action;
	unsigned int raise_amount;

	Poker_action *ret = new Poker_action;

	cout << "It is " << name << "'s turn" << endl;
	cout << "Do you want to fold/check/call/raise? ";
	cin >> player_action;

	if(player_action == "raise") {


		cin >> raise_amount;
		if(raise_amount < chips) {
			cout << "You do not have enough chips available";
		}
		ret -> amount = raise_amount;
	}

	ret -> action = player_action;
	return ret;
}
