#ifndef POKER_PLAYER_HPP
#define POKER_PLAYER_HPP
/*
 * =====================================================================================
 *
 *       Filename:  poker_player.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015-04-30 17:15:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */

#include	"poker_game.hpp"


/*
 * =====================================================================================
 *        Class:  Poker_player
 *  Description:  
 * =====================================================================================
 */
class Poker_player
{
	public:
		/* ====================  LIFECYCLE     ======================================= */
		Poker_player ();                             /* constructor */

		/* ====================  ACCESSORS     ======================================= */
		/*
		 *--------------------------------------------------------------------------------------
		 *       Class:  Poker_player
		 *      Method:  get_chips
		 *--------------------------------------------------------------------------------------
		 */
		inline unsigned int
			get_chips (  )
			{
				return chips;
			}		/* -----  end of method Poker_player::get_chips  ----- */

		/*
		 *--------------------------------------------------------------------------------------
		 *       Class:  Poker_player
		 *      Method:  get_name
		 *--------------------------------------------------------------------------------------
		 */
		inline String
			Poker_player::get_name (  )
			{
				return name;
			}		/* -----  end of method Poker_player::get_name  ----- */

		/*
		 *--------------------------------------------------------------------------------------
		 *       Class:  Poker_player
		 *      Method:  set_name
		 *--------------------------------------------------------------------------------------
		 */
		inline void
			Poker_player::set_name ( int value )
			{
				name	= value;
				return ;
			}		/* -----  end of method Poker_player::set_name  ----- */

		void
			Poker_player::set_chips ( unsigned int c )
			{
				chips = c;
				return ;
			}		/* -----  end of method Poker_player::set_chips  ----- */


		/*
		 *--------------------------------------------------------------------------------------
		 *       Class:  Poker_player
		 *      Method:  set_chips
		 *--------------------------------------------------------------------------------------
		 */
		inline void
			Poker_player::set_chips ( int value )
			{
				chips	= value;
				return ;
			}		/* -----  end of method Poker_player::set_chips  ----- */


		/* ====================  MUTATORS      ======================================= */

		/* ====================  OPERATORS     ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */
	protected:

	private:
		String name;
		unsigned int chips;
		array<poker_card, 2> hand_cards;

}; /* -----  end of class Poker_player  ----- */

#endif
