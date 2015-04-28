#!/usr/bin/env perl 

use strict;
use warnings;
use utf8;

my @suits = ("S", "H", "D", "C");
my @numbers = (1..13);

use lib '.';
use card_deck;
use poker_player;

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
	foreach my $player (0..3) {
		foreach my $c (1..2) {
			my $card = ($self->{holdem_cards})->draw_card();
			#push $player->{cards}, $card;
			$self->{players}[$player]->{cards}[$c] = $card;
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

sub list_players {
	my $self = shift;

	my $ref = $self->{players};
	#@$ref[1]->print_info;
	print @$ref;
	#there seem to be more elements in that array
	foreach my $player (@$ref) {
		print $player . "\n";
		#$player->print_info();
		#print ".";
	}
}





