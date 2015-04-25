#!/usr/bin/env perl 

use strict;
use warnings;
use utf8;


my @suits = ("S", "H", "D", "C");
my @numbers = (1..10, "B", "D", "K");
my $players;	#number of players


#use card_deck;

my $object = new card_deck;
#$object->print_cards();
#$object->get_players;

package card_deck;

sub init_deck;
sub draw_card;
sub get_players;
sub print_cards;

sub new {
	my $class = shift;
	my $self = {
		players => "5",
	};

	reset_deck();

	#print_cards();

	#print "Class $class created" . "\n";
}

sub get_players() {
	my ($self) = @_;
	print "$self->{players}\n";
}

sub reset_deck() {
	my ($self) = @_;
	#initialize the card deck
	foreach my $suit (@suits) {
		foreach my $number (@numbers) {
			$self->{cards}{$suit}{$number} = 1;
		}
	}
}

sub draw_card() {
	my ($self) = @_;
	my ($suit, $number);

	do {
		$suit = $suits[int(rand(4))];
		$number = $numbers[int(rand(13))];
	} while($self->{cards}{$suit}{$number} == 1);

	#remove card from deck
	$self->{cards}{$suit}{$number} = 0;

	return $suit . $number;
}

sub print_cards() {
	my ($self) = @_;

	foreach my $suit (@suits) {
		foreach my $number (@numbers) {
			print "$suit:$number -> $self->{cards}{$suit}{$number}\n";
		}
	}
}



