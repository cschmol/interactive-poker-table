#ifndef POKER_GAME_HPP
#define POKER_GAME_HPP

#include	"poker_player.hpp"
#include	"card_deck.hpp"
#include	<algorithm>
#include	<vector>
#include	"socket.hpp"

#include 	<array>        // std::array
#include 	<random>       // std::default_random_engine
#include 	<chrono>       // std::chrono::system_clock

/*-----------------------------------------------------------------------------
 *  headers for sockets
 *-----------------------------------------------------------------------------*/
#include	<unistd.h>
#include	<errno.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<netdb.h>

#include	<strings.h>
#include	<ncurses.h>

const int NSAMPLEHANDS=1000;
const int NSHUFFLEDDECKS=100;
const int NMAXPLAYERS= 10;

class Poker_game
{
	public:
		Poker_game ();                          /* constructor */
		~Poker_game ();

		bool add_player(Poker_player *player);

		void start();                           /* players added, start game */
		void round();                           /* corresponds to 1 round of poker */
		void setup();
		void deal_common_cards(int count);

		void deal_player_cards();
		void flop();
		void turn();
		void river();

		/*-----------------------------------------------------------------------------
		 *  to be seen
		 *-----------------------------------------------------------------------------*/
		void getProbability(int nPlayers, std::array<int,2*NMAXPLAYERS> handcards,int nCommonCards, int commoncards[5],double *arr);
		void betting_round();

		void print_info();                      /* print info about the game */

		/*-----------------------------------------------------------------------------
		 *  to be seen
		 *-----------------------------------------------------------------------------*/
		void update_probs();


	protected:

	private:
		Card_deck deck;                                                                                     /* card deck for the game */
		vector<Poker_player> players;                                                                       /* all players that are still competing */

		int common_cards[5];                                                                                /* Cards in the middle */
		unsigned int n_small_blind, n_big_blind;                                                            /* worth of small and big blind */

		std::vector<Poker_player>::iterator dealer, small_blind, big_blind, current_player, highest_better; /* indexes for special players */

		unsigned int 	n_common_cards,                                                                     /* holds the number of cards currently on the table */
						high_bet,                                                                           /* set the bet to the big blind */
						pot;                                                                                /* amount of chips in the pot */


		/*-----------------------------------------------------------------------------
		 *  probability calculation
		 *-----------------------------------------------------------------------------*/
		double winprobs[NMAXPLAYERS];
		SevenEval const* eval;


		/*-----------------------------------------------------------------------------
		 *  socket variables
		 *-----------------------------------------------------------------------------*/
		Socket sock;

};

#endif
