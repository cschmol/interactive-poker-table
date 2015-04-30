#ifndef POKER_GAME_HPP
#define POKER_GAME_HPP
/*
 * =====================================================================================
 *
 *       Filename:  poker_game.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015-04-30 17:29:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */

#include	"poker_player.hpp"
#include	"card_deck.hpp"

/*
 * =====================================================================================
 *        Class:  Poker_game
 *  Description:  
 * =====================================================================================
 */
class Poker_game
{
	public:
		/* ====================  LIFECYCLE     ======================================= */
		Poker_game ();                             /* constructor */

		/* ====================  ACCESSORS     ======================================= */

		/* ====================  MUTATORS      ======================================= */

		/* ====================  OPERATORS     ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */
	protected:

	private:
		Card_deck deck;                         /* card deck for the game */
		vector<Poker_player>;                   /* participating players */

}; /* -----  end of class Poker_game  ----- */

#endif
