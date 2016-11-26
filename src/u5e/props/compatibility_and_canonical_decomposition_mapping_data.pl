#!/usr/bin/perl
use strict;
use warnings;

#
# extract from UnicodeData.txt the Decomposition_Mapping attribute.
# Note that this will already fully recurse into the fully decomposed
# character. It is better to pay this extra space cost in read-only
# data than to pay the extra runtime cost of recursively expanding it.
#
open my $ucd, '<', 'UnicodeData.txt'
  or die "Failed to open UnicodeData.txt: $!\n";
my %d;
while (defined (my $line = <$ucd>)) {
  chomp $line;
  # we will not decode the hex data and store the codepoints as string.
  my ($codepoint, $decomposition) = (split /;/, $line)[0,5];
  # ignore codepoints that are already decomposed.
  next unless $decomposition;
  # we include the compat decompoistions as well
  $decomposition =~ s/^<compat> //;
  # but no other
  next if $decomposition =~ /^\</;
  $d{$codepoint} = [ split /\s+/, $decomposition ];
}
close $ucd;

#
# we have the primary decomposition mapping, now we need to recurse in
# order to get them fully decomposed.
#
my $continue = 1;
while ($continue) {
  $continue = 0;
  foreach my $k (keys %d) {
    $d{$k} =
      [
       map {
         if (exists $d{$_}) {
           $continue = 1;
           @{$d{$_}}
         } else {
           $_;
         }
       }
       @{$d{$k}}
      ];
  }
}

#
# Output the data
#
my @sorted_keys = sort { hex($a) <=> hex($b) } keys %d;

open my $o, '>', 'compatibility_and_canonical_decomposition_mapping_data.hpp'
  or die $!;
print $o
  join(",\n",
       map {
         my $k = $_;
         "{ ".hex($k).", ".join(", ", map { hex($_) } @{$d{$k}}). ", 0 }";
       } @sorted_keys
      );
close $o;
