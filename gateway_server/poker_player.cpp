
#include	"poker_player.hpp"

Poker_player::Poker_player(string n, unsigned int c) {
	name 	= n;
	chips 	= c;
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

void Poker_player::print_info() {
	cout << "Name: " << name << endl;
	cout << "Chips: " << chips << endl;
}

Poker_action *Poker_player::poker_action() {
	Poker_action *pa = new Poker_action;
	string action;
	cout << "You still have " << get_chips() << " chips" << endl;
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

	pa->action = "test";
	pa->amount = 1234;


	return pa;
}

