#!/usr/bin/env perl 

use strict;
use warnings;
use utf8;

#declare subroutinges here
sub get_player_action();
sub distribute_cards();
sub rank();
sub card_rank($);

my @cards_of_all_players;

#global variables:
my @suits = ("S", "H", "D", "C");
my @numbers = (1..10, "B", "D", "K");
my $players;	#number of players

my @holdem_cards = (
"H1", "H2", "H3", "H4", "H5", "H6", "H7", "H8", "H9", "H10", "HB", "HD", "HK",
"D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "D10", "DB", "DD", "DK",
"S1", "S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "S10", "SB", "SD", "SS",
"S1", "S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "S10", "SB", "SD", "SK"
);

my @common_cards = ("", "", "", "", "");
my @player_chips = ("", "", "", "", "");

my @player_cards;	#holds the cards of all players
my $i;	#iteration variable

#check command-line
if ($#ARGV < 0) {
	die "Usage: ./poker.pl <players>\n";
}

$players = $ARGV[0];
print "Beginning poker game with $players players\n";
distribute_cards();
print "Cards got distributed to players:\n";

#print out players cards
for($i=0; $i<$players; $i++) {
	print "Player $i: $player_cards[$i]{card1}, $player_cards[$i]{card2}\n";
}

my ($dealer, $small_blind, $big_blind);
$i = 0;

$dealer=0, $small_blind=($dealer+1)%$players, $big_blind=($dealer+2)%$players;
my $active_player = ($big_blind+1)%$players;
my $pot = 0;

my @players_left = (0..($players-1));

#main loop for the poker game
#iterate over the rounds
while(scalar(@players_left) > 1) {
	print "Dealer: $dealer\nSmall Blind: $small_blind\nBig Blind: $big_blind\n\n";
	$pot = 0;
	my $round = 0;
	my $player_bet=$big_blind;

	#give players cards
	distribute_cards();

	#players that have not fold'ed
	my $players_to_go = $players;

	#all cards played
	while($round < 3) {
		#get cards from dealer
		deal($round);
		
		my $p = $players_to_go;
		
		#while all players have betted the same
		while($p--) {
			print "action required from player $active_player:\n";
			print get_player_action();
			$active_player = ($active_player++)%$players;
		}
		print "Betting round done\n";
	}

	$dealer = ($dealer+1)%$players;
	$small_blind=($dealer+1)%$players, $big_blind=($dealer+2)%$players, $active_player=($dealer+3)%$players;
	$active_player = ($big_blind+1)%$players;

}

sub get_player_action() {
	my $player_action;
	print "Do you want to fold(f), check(ch), call(ca), raise(r)? ";
	$player_action = <STDIN>;
	chomp $player_action;
	return $player_action;
}

sub deal {

}

sub distribute_cards() {
	my $cards_left = 52;
	my ($card);
	my $rand;
	my $player;
	my $i;

	#have to reset the holdem cards also


	#do this for all players
	for($player=0; $player<$players; $player++) {
		#select cards for that player
		for($i=0; $i<2; $i++) {
			$rand = int(rand($cards_left--));
			$card = $holdem_cards[$rand];
			splice @holdem_cards, $rand, 1;
			if($i==0) {
				$player_cards[$player]{card1} = $card;
			} else {
				$player_cards[$player]{card2} = $card;
			}
		}
	}

	#create the 2d-matrix of all holdem cards
	#first initialize everything with zero's
	foreach my $player (0..($players)) {
		foreach my $suit (@suits) {
			for my $number (1..10,"B","D","K") {
				#print $_ . $i . "\n";
				$cards_of_all_players[$player]{$suit}{$number} = 0;
			}
		}
	}

	#still need to fill the array $cards_of_all_players correctly
	
}

#arguments: player1, player2, common
sub winner {
	my $winning_player=0, my $max_rank=0, my $current_rank;
	for(my $i=0; $i<$players; $i++) {
		$current_rank = card_rank($i);
		if($current_rank > $max_rank) {
			$winning_player = $i;
			$max_rank = $current_rank;
		}
	}
	return $winning_player;
}


#arguments: player, player_cards, common_cards
sub card_rank ($) {
	my ($suit, $number, $player);
	print "card_rank called \n";
	#check for flush
	foreach $suit (@suits) {
		my $count = 0;
		foreach $number (@numbers) {
			if($cards_of_all_players[$player]{$suit}{$number} == 1) {
				$count++;
			}
		}
		if($count > 4) {
			print "Player has a flush\n";
		}
	}
	
	#check for street
	#B,D,K müssen als Zahlen dargestellt werden um leichter sortiert zu werden
	foreach $suit (@suits) {
		my $count = 0;
		foreach $number (sort @numbers) {
			if($cards_of_all_players[$player]{$suit}{$number} == 1) {
				$count++;
			} else {
				$count=1;
			}
		}
		if($count > 4) {
			print "Player has a street\n";
		}
	}

	#check for four cards
	foreach $number (sort @numbers) {
		my $count = 0;
		foreach $suit (@suits) {
			if($cards_of_all_players[$player]{$suit}{$number} == 1) {
				$count++;
			} else {
				$count=0;
			}
		}
		if($count > 4) {
			print "Player has 4 cards of the same number\n";
		}
	}

	#	print "Player $i: $player_cards[$i]{card1}, $player_cards[$i]{card2}\n";
	
}






my %card_deck;
my $suit, my $number;

sub init_deck() {
	#initialize the card deck
	foreach $suit (@suits) {
		foreach $number (@numbers) {
			$card_deck{$suit}{$number} = 1;
		}
	}
}

sub draw_card() {
	my ($suit, $number);
	
	do {
		$suit = $suits[int(rand(4))];
		$number = $numbers[int(rand(13))];
	} while($card_deck{$suit}{$number} == 1);

	#remove card from deck
	$card_deck{$suit}{$number} = 0;

	return $suit . $number;
}



















