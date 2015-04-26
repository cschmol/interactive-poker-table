#!/usr/bin/env perl 

use strict;
use warnings;
use utf8;


use lib '.';
use poker_player;

my $players;

my $arr = 	[	new poker_player(name => "Test1"),
				new poker_player(name => "Test2"),
				new poker_player(name => "Test3"),
				new poker_player(name => "Test4"),
				new poker_player(name => "Test5"),
			];


print "How many players?";
$players = <STDIN>;
chomp $players;

foreach (1..$players) {
	print "Please enter a name: ";
	my $name = <STDIN>;
	chomp $name;

	my $pl = new poker_player(name => $name);
	push @$arr, $pl;

}
my $player = new poker_player(name => "Christophe");

$player->print_info();
push @{$arr}, $player;

foreach my $i (@{$arr}) {
	$i->print_info();
}

$player->action;





