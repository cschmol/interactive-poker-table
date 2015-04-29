#!/usr/bin/env perl 
#===============================================================================
#
#         FILE: test_card_deck.pl
#
#        USAGE: ./test_card_deck.pl  
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
#      CREATED: 2015-04-26 10:39:41
#     REVISION: ---
#===============================================================================

use strict;
use warnings;
use utf8;

use lib '.';
use card_deck;

my $holdem_deck = new card_deck;
$holdem_deck->reset_deck;

print $holdem_deck->draw_card . "\n";

$holdem_deck->print_cards;

