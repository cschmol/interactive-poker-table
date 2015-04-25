#
#===============================================================================
#
#         FILE: poker_player.pm
#
#  DESCRIPTION: 
#
#        FILES: ---
#         BUGS: ---
#        NOTES: ---
#       AUTHOR: YOUR NAME (), 
# ORGANIZATION: 
#      VERSION: 1.0
#      CREATED: 2015-04-25 22:31:31
#     REVISION: ---
#===============================================================================

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

	$self->{chips} = 1000 	if undef $self->{chips};
	$self->{name} = "dummy" if undef $self->{name};
	$self->{cards} = ();

	my $bl = bless $self, $class;

	return $bl;
}

sub action {
	my $self = shift;

	printf "Please enter action for the current player:";
}

sub get_chips {
	my $self = shift;
	return $self->{chips};
}

sub set_chips {
	my $self = shift;
	$self->{chips} = shift;
}

