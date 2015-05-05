
#include	"poker_player.hpp"

void Poker_player::print_info() {
	cout << "Name: " << name << endl;
	cout << "Chips: " << chips << endl;
}

void Poker_player::poker_action() {
	string action;
	cout << "Player " << name
		 << " needs to chose an action" << endl
		 << "fold/check/call/raise" << endl;
	cin >> action;

	//see what action the player wants
	if(action == "fold") {

	} else if(action== "check") {

	} else if(action == "call") {

	} else if(action == "raise") {

	}

}

