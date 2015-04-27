#!/usr/bin/env perl 

use strict;
use warnings;
use utf8;


my @suits = ("S", "H", "D", "C");
my @numbers = (1..13);
my $players;	#number of players

use lib '.';

use card_deck;
use poker_player;
use poker_game;


#create a list of players to pass on poker_game
my @players;

#set player_chips, array of players
my $poker_game = new poker_game(players => \@players);

$poker_game->start();

#print stats of the game
$poker_game->game_stats;


#give players the 2 player_cards
$poker_game->player_cards();
#let players bet
$poker_game->betting_round();

#deal 3 community cards
$poker_game->flop();
#let players bet
$poker_game->betting_round();

#deal 1 community cards
$poker_game->turn();
#let players bet
$poker_game->betting_round();

#deal 1 community cards
$poker_game->river();
#let players bet
$poker_game->betting_round();



