#ifndef SOCKET_HPP
#define SOCKET_HPP


#include	"poker_player.hpp"
#include	"card_deck.hpp"
#include	<algorithm>
#include	<vector>
#include	<string>

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

using namespace std;

class Socket;

Socket &operator<<(Socket& x, string str);
Socket &operator>>(Socket &x, string &str);

class Socket
{
	public:
		Socket();
		Socket(int s);

		int get_sock();

		bool send(string s);
		string recv();


	private:
		int sock;                               /* socket variable */
		struct sockaddr_in serv_addr;
		socklen_t serv_len;

		char buffer[512];

};

#endif
