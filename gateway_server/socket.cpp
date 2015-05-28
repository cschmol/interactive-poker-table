#include	"socket.hpp"

Socket::Socket() {
	sock = socket(AF_INET, SOCK_STREAM, 0);     /* we're using TCP sockets with IPv4 */
	if(sock<0) {
		perror("socket()");
		exit(1);


	}
//	cout	<< "Socket created with success: " << sock << endl;

	int optval = 1;

	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))<0) {
		perror("setsockopt:");
		exit(1);
	}

	bzero(&serv_addr, sizeof(serv_addr));       /* zero that structure */

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8888);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	int status = bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	if(status<0) {
		perror("error: ");
		exit(1);
	}

	if(listen(sock, 10) < 0) {                  /* listen on socket */
		perror("listen()");
		exit(1);
	}	
//	cout	<< "Listening on socket" << endl;
}

Socket::Socket(int s) {
	//struct sockaddr cli_addr;
	//socklen_t clilen = sizeof(cli_addr);

//	cout << "supplied socket: " << s << endl;

	sock = accept(s, NULL, NULL);
	if(sock<0) {
		perror("accept");
		exit(1);
	} else {
//		cout	<< "Accepted a client successfully" << endl;
	}

}

int Socket::get_sock() {
	return sock;
}

bool Socket::send(string s) {
	memset(buffer, 0, sizeof(buffer));
	strcpy(buffer, s.c_str());
	if(::send(sock, buffer, s.length()+1, 0)<0) {
		return false;
	} else {
		return true;
	}
}

string Socket::recv() {
	memset(buffer, 0, sizeof(buffer));
	if(::recv(sock, buffer, sizeof(buffer), 0)<0) {
		return "";
	} else {
		return buffer;
	}
}



Socket &operator<<(Socket& x, string str) {
	x.send(str);
	return x;
}

Socket &operator>>(Socket &x, string &str) {
	str = x.recv();
	return x;
}




