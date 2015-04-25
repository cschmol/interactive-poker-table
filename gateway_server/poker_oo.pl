#!/usr/bin/env perl 

use strict;
use warnings;
use utf8;


my @suits = ("S", "H", "D", "C");
my @numbers = (1..13);
my $players;	#number of players


my $object = card_deck->new;
foreach (1..20) {
	$object->draw_card;
}

my @arr = $object->get_cards;

foreach my $i (@arr) {
	print $i . "\n";
}

exit();

package card_deck;

sub init_deck;
sub draw_card;
sub print_cards;

sub new {
	my $class = shift;
	my $self = {@_};

	
	my $bl = bless $self, $class;
	reset_deck $self;

	return $bl;
}

sub reset_deck() {
	my $self = shift;
	#initialize the card deck
	foreach my $suit (@suits) {
		foreach my $number (@numbers) {
			$self->{cards}{$suit}{$number} = 1;
		}
	}
}

sub draw_card() {
	my $self = shift;
	my ($suit, $number);

	do {
		$suit = $suits[int(rand(4))];
		$number = $numbers[int(rand(13))];
	} while($self->{cards}{$suit}{$number} == 0);

	#remove card from deck
	$self->{cards}{$suit}{$number} = 0;

	return $suit . $number;
}

sub print_cards() {
	my $self = shift;

	foreach my $suit (@suits) {
		foreach my $number (@numbers) {
			print "$suit:$number -> $self->{cards}{$suit}{$number}\n";
		}
	}
}

sub get_cards() {
	my $self = shift;
	my @c;
	foreach my $suit (@suits) {
		foreach my $number (@numbers) {
			if($self->{cards}{$suit}{$number} == 0) {
				push @c, $suit . $number;
			}
		}
	}
	return @c;
}
