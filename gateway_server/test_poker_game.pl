#!/usr/bin/env perl 

use strict;
use warnings;
use utf8;
#use diagnostics;

use lib '.';
use poker_game;
use poker_player;


my @players = ();

#determine number of players
print "How many players?";
my $players = <STDIN>;
chomp $players;

#fill player objects with names
foreach (1..$players) {
	print "Please enter a name: ";
	my $name = <STDIN>;
	chomp $name;

	my $pl = new poker_player(name => $name);
	push @players, $pl;

}

print "Players for this round: \n";
foreach my $i (@players) {
	#$i->print_info();
}

my $test = \@players;
foreach my $i (@$test) {
	#$i->print_info;
}

my $poker_game = new poker_game(players => \@players);

$poker_game->player_cards();
$poker_game->list_players();



