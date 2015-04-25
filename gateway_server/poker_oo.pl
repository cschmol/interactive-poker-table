#!/usr/bin/env perl 

use strict;
use warnings;
use utf8;


my @suits = ("S", "H", "D", "C");
my @numbers = (1..13);
my $players;	#number of players


use card_deck;
use poker_player;
use poker_game;


my @players = 	(	new poker_player(name => "Christophe"),
					new poker_player(name => "Nina"), 
					new poker_player(name => "Ekin"),
					new poker_player(name => "Malina"),
				);

my $poker_game = new poker_game(players => \@players);

$poker_game->player_cards();



