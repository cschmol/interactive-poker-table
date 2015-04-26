use strict;
use warnings;



my @suits = ("S", "H", "D", "C");
my @numbers = (1..13);
 
package poker_player;

sub action;
sub get_chips;
sub set_chips;

sub new {
	my $class = shift;

	my $self = {@_};

	$self->{chips} = 1000 if !exists $self->{chips};
	$self->{name} = "dummy" if !exists $self->{name};
	$self->{cards} = ();

	my $bl = bless $self, $class;

	return $bl;
}

sub action {
	my $self = shift;
	my %action;

	printf "Please enter action for the current player:";
	my $action = <STDIN>;
	chomp $action;
	if($action eq "fold") {
		printf "You folded\n";
	}
	if($action eq "check") {
		printf "You checked\n";
	}
	if($action eq "call") {
		#check if player has enough chips available
		printf "You called\n";
	}
	if($action eq "raise") {
		printf "By how much do you want to raise?";
		my $raise = <STDIN>;
		chomp $raise;
		#check if player has enough chips available
		printf "You raised by $raise\n";
	}
	$action{action} = $action;
}

sub print_info {
	my $self = shift;
	print "Name: $self->{name}, Chips: $self->{chips}\n";
}

sub get_chips {
	my $self = shift;
	return $self->{chips};
}

sub set_chips {
	my $self = shift;
	$self->{chips} = shift;
}

