#!/usr/bin/env perl

use warnings;
use strict;
use 5.010;
use utf8;
use constant {
	MIN => 5,
	MAX => 15
};

my %mat;
my $name = "dict";

$name = $ARGV[0] if (defined $ARGV[0] && -e $ARGV[0]);
open(my $fd, "<", $name) or die "no word list file!";

while(<$fd>){															# update matrix,
	chomp;																#  basing on given word-list
	my @string = split(//);
	push @string, '0';													# append 'word-end' mark
	$mat{1}{lc $string[0]}{lc $string[1]} += 1;							# '1' is 'word-start' mark
	for( my $i = 0; $i < @string - 2; $i++ ){
		$mat{lc $string[$i]}{lc $string[$i+1]}{lc $string[$i+2]} += 1;	# update matrix of occurences
	}
}
close($fd);

my @result;

do {
	@result = ();

	my @list;

	my $last = '1';	# start generating from 'word-start' mark 
	my $curr;
	my $next;
	
	push @list, $_ for keys %{$mat{$last}};	# random-pick first letter from any letters
	$curr = $list[rand($#list)];				#  that occured as first letter

	do {
		@list = ();
		push @result, $last;
		for my $key ( keys %{$mat{$last}{$curr}} ){					# add every letter that occured
			for( my $i = $mat{$last}{$curr}{$key}; $i > 0; $i-- ){	# after $last and $curr to @list
				push @list, $key;									# (as many times as it occured)
			}
		}
		$next = $list[rand($#list)];	# random-pick one letter from @list

		$next = 0 if( not @list );		# if for any reason @list was empty,
										#  stop generating word
		$last = $curr;
		$curr = $next;
	} until ( $curr eq 0 || $last eq 0 ); # if any letter is 'word-end' mark, stop generating

} until ( @result > MIN && @result < MAX ); # generate words until result has right length

shift @result;				# delete 'word-start' mark
$result[0] = uc $result[0];	# uppercase first letter, pure aesthetics :D

print for( @result );		# print result
say "";						#
