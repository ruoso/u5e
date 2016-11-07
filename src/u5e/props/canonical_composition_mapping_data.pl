#!/usr/bin/perl
use strict;
use warnings;

#
# extract from UnicodeData.txt the Decomposition_Mapping attribute.
# But extract it from the perspective of someone trying to compose a
# character instead of decompose it.
#
open my $ucd, '<', 'UnicodeData.txt'
  or die "Failed to open UnicodeData.txt: $!\n";
my %d;
my %ccc;
while (defined (my $line = <$ucd>)) {
  chomp $line;
  # we will not decode the hex data and store the codepoints as string.
  my ($codepoint, $ccc, $decomposition) = (split /;/, $line)[0,3,5];

  # collect the ccc for every character
  $ccc{$codepoint} = $ccc || 0;

  # only canonical composition
  next unless $decomposition;
  next if $decomposition =~ /^\</;

  # ignore codepoints that are already decomposed.
  # singletons are excluded from re-composition
  next unless $decomposition =~ /^[a-fA-F0-9]+ [a-fA-F0-9]+/;

  # ignore if the composed characte is not a starter
  next unless $ccc == 0;

  warn "$decomposition duplicated between $codepoint and $d{$decomposition}"
    if exists $d{$decomposition};
  $d{$decomposition} = $codepoint;
}
close $ucd;

my %excl;
open my $excl, '<', 'CompositionExclusions.txt'
  or die "Failed to open CompositionExclusions.txt: $!";
while (defined (my $line = <$excl>)) {
  chomp $line;
  $line =~ s/#.*//;
  $line =~ s/\s.+//;
  next unless $line;
  $excl{$line} = 1;
}
close $excl;

my @all_decompositions = keys %d;
foreach my $decomposition (@all_decompositions) {
  my ($first) = split(/ /, $decomposition);
  if ($ccc{$first} != 0) {
    # ignore decompositions that start with a character that is not a
    # starter.
    delete $d{$decomposition};
  } else {
    my $composition = $d{$decomposition};
    if (exists $excl{$composition}) {
      # characters explicitly excluded from re-composition
      delete $d{$decomposition};
    }
  }
}


#
# Output the data
#
my @sorted_keys = sort
  {
    ( hex(($a =~ /^([a-fA-F0-9]+)/)[0])
      <=>
      hex(($b =~ /^([a-fA-F0-9]+)/)[0])
    ) ||
    ( hex(($a =~ /\s([a-fA-F0-9]+)/)[0])
      <=>
      hex(($b =~ /\s([a-fA-F0-9]+)/)[0])
    )
  }
  keys %d;

open my $o, '>', 'canonical_composition_mapping_data.hpp'
  or die $!;
print $o
  join(",\n",
       map {
         my $k = $_;
         my ($dc1, $dc2, $dc3) = split / /, $k;
         warn "$k has more than two decomposed characters"
           if $dc3;
         "{ ".join(", ", map { hex($_) } $dc1, $dc2, $d{$k})." }";
       } @sorted_keys
      );
close $o;
