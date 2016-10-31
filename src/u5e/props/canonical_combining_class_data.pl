#!/usr/bin/perl
use strict;
use warnings;

#
# extract from UnicodeData.txt the Canonical_Combining_Class attribute.
#
open my $ucd, '<', 'UnicodeData.txt'
  or die "Failed to open UnicodeData.txt: $!\n";
my %d;
while (defined (my $line = <$ucd>)) {
  chomp $line;
  # we will not decode the hex data and store the codepoints as string.
  my ($codepoint, $class) = (split /;/, $line)[0,3];
  # default is 0
  next unless $class;
  $d{$codepoint} = $class;
}
close $ucd;

#
# Output the data
#
my @sorted_keys = sort { hex($a) <=> hex($b) } keys %d;

open my $o, '>', 'canonical_combining_class_data.hpp'
  or die $!;
print $o
  join(",\n",
       map {
         "{ ".hex($_).", ".$d{$_}." }";
       } @sorted_keys
      );
close $o;
