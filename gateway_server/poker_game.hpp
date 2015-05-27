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
		void getProbability(int nPlayers, std::array<int,2*NMAXPLAYERS> handcards,int nCommonCards, int commoncards[5],double *arr);
		void betting_round();

		void print_info();                      /* print info about the game */
		void update_probs();


	protected:

	private:
		Card_deck deck;                                     /* card deck for the game */
		vector<Poker_player> players;                       /* all players that are still competing */

//		int dealer, small_blind, big_blind, current_player; /* indexes for special players */
//		int highest_better;

		int common_cards[5];
		unsigned int n_small_blind, n_big_blind;            /* worth of small and big blind */

		std::vector<Poker_player>::iterator dealer, small_blind, big_blind, current_player; /* indexes for special players */
		std::vector<Poker_player>::iterator highest_better;

		unsigned int n_common_cards; /* holds the number of cards currently on the table */
		unsigned int high_bet;       /* set the bet to the big blind */
		unsigned int pot;            /* amount of chips in the pot */

		double winprobs[NMAXPLAYERS];


		/*-----------------------------------------------------------------------------
		 *  socket variables
		 *-----------------------------------------------------------------------------*/
		int serv_sock;
		struct sockaddr_in serv_addr, cli_addr;
		socklen_t clilen;
		char buffer[2048];

		Socket sock;

		
		/*-----------------------------------------------------------------------------
		 *  Ncurses variables
		 *-----------------------------------------------------------------------------*/
		WINDOW *wGameInfo;
};

#endif
