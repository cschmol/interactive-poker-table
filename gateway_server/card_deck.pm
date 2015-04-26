use strict;
use warnings;
 
my @suits = ("S", "H", "D", "C");
my @numbers = (1..13);

package card_deck;

sub init_deck;
sub draw_card;

#constructor for the class
sub new {
	my $class = shift;
	my $self = {@_};

	
	my $bl = bless $self, $class;

	#set all cards as available
	reset_deck $self;

	return $bl;
}

#set all cards as available in the deck
sub reset_deck() {
	my $self = shift;
	#initialize the card deck
	foreach my $suit (@suits) {
		foreach my $number (@numbers) {
			$self->{cards}{$suit}{$number} = 1;
		}
	}
}

#draw one card from the card deck and set that card as no longer available in the deck
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

#return an array of still available cards
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
