/*
 * =====================================================================================
 *
 *       Filename:  server.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015-04-30 00:01:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Christophe Schmol (cs), christophe_schmol@yahoo.de
 *        Company:  RWTH Aachen University
 *
 * =====================================================================================
 */

#include	<iostream>
#include	"card_deck.hpp"
#include	"poker_player.hpp"


int main ( int argc, char *argv[] )
{
	poker_card pc;


	Card_deck cards;
	pc = cards.draw_card();
	cout << "Card: " << pc.suit << pc.number <<endl;
	return 0;
}				/* ----------  end of function main  ---------- */
