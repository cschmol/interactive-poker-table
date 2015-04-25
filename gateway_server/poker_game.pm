#!/usr/bin/env perl 
#===============================================================================
#
#         FILE: poker_game.pl
#
#        USAGE: ./poker_game.pl  
#
#  DESCRIPTION: 
#
#      OPTIONS: ---
# REQUIREMENTS: ---
#         BUGS: ---
#        NOTES: ---
#       AUTHOR: YOUR NAME (), 
# ORGANIZATION: 
#      VERSION: 1.0
#      CREATED: 2015-04-25 22:33:13
#     REVISION: ---
#===============================================================================

use strict;
use warnings;
use utf8;

my @suits = ("S", "H", "D", "C");
my @numbers = (1..13);


package poker_game;

sub new {
	my $class = shift;
	my $self = {@_};

	$self->{round} = 0;
	#one array for the players
	$self->{holdem_cards} = new card_deck;

	my $bl = bless $self, $class;

	return $bl;
}

#give players their cards
sub player_cards {
	my $self = shift;
	#each player gets 2 cards
	foreach my $player ($self->{players}) {
		foreach (1..2) {
			my $card = ($self->{holdem_cards})->draw_card();
			push $player->{cards}, $card;
		}
	}
}

#deal 3 cards for common use
sub flop {
	my $self = shift;
}

#deal 1 card for common use
sub turn {
	my $self = shift;
}

#deal 1 card for common use
sub river {
	my $self = shift;
}
