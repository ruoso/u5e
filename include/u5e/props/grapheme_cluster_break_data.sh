#!/bin/sh
cat GraphemeBreakProperty.txt \
    | grep '^[A-F0-9]' \
    | perl -pe 's/^([0-9A-F]+)\s/$1..$1/' \
    | perl -pe 's/^([A-F0-9]+)..([A-F0-9]+)\s+;\s(\S+).+$/"{ ".join(", ",hex($1),hex($2),uc($3))." },"/e' \
    | sort -k2 -n > grapheme_cluster_break_data.hpp
