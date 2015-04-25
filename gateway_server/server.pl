#!/usr/bin/env perl 
#===============================================================================
#
#         FILE: server.pl
#
#        USAGE: ./server.pl  
#
#  DESCRIPTION: main server for the interactive poker table
#
#      OPTIONS: ---
# REQUIREMENTS: ---
#         BUGS: ---
#        NOTES: ---
#       AUTHOR: Christophe Schmol, 
# ORGANIZATION: 
#      VERSION: 1.0
#      CREATED: 2015-04-23 11:38:50
#     REVISION: ---
#===============================================================================

use strict;
use warnings;
use utf8;
use Socket;
use IO::Socket;





my $port = 7890;
my $proto = getprotobyname('tcp');
my $server = "localhost";  # Host IP running the server

# create a socket, make it reusable
socket(SOCKET, PF_INET, SOCK_STREAM, $proto)
   or die "Can't open socket $!\n";
setsockopt(SOCKET, SOL_SOCKET, SO_REUSEADDR, 1)
  or die "Can't set socket option to SO_REUSEADDR $!\n";

# bind to a port, then listen
bind( SOCKET, pack_sockaddr_in($port, inet_aton($server)))
	 or die "Can't bind to port $port! \n";

listen(SOCKET, 5) or die "listen: $!";
print "SERVER started on port $port\n";

# accepting a connection
my $client_addr;
while ($client_addr = accept(NEW_SOCKET, SOCKET)) {
	# send them a message, close connection
	my $name = gethostbyaddr($client_addr, AF_INET );
	print NEW_SOCKET "Smile from the server";
	print "Connection recieved from $name\n";
	close NEW_SOCKET;
}

#Struktur der Hauptschleife:
#while(1) {
#	select("connections");
#	if(game_event) {
#		update($game);
#		distribute($game);
#		set_active_player();
#	}
#}
