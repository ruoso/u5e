# u5e

Unicode Text C++ library

# What is this library?

This library provides support for Unicode Text, as specified by the
Unicode Standard.

# Why?

Properly supporting international text is one of these problems that
you either think is very easy because you never had to deal with
internationalized text, or you give up on it because you think no one
can support Unicode correctly. This library is an attempt to provide a
simple reusable set of interfaces to deal with international text.

# Why not just use the icu library?

The first reason for me to consider this was that the icu library is
much more complex than what's required for supporting text. ICU also
supports the full localization definitions of the Unicode CLDR, which
makes its support surface much larger than would be required for
simply handling text.

Secondly, the icu library forces the internal representation of the
text to always be in a particular encoding (UTF16). I believe that
this is an unecessary constraint, and one of the points of this
library is to make the encoding pluggable without requiring different
APIs or explicit conversions.

## A note on legacy encodings

This library will not support converting to and from legacy encodings
as well as operating on them. You are expected to perform the
convertions at the borders of your application.

## A note on dynamic encodings

While it is technically possible to operate on text with a dynamically
assigned encoding, I honestly believe the use case for that is more
academic than anything else.

Your application should have one internal encoding and all text should
be converted on the borders of the application to whatever makes the
most sense for your application.

For instance, if you're dealing with mostly 7-bit ASCII text with the
ocasional exception (such as most latin languages), UTF8 is definitely
the most efficient usage of memory, and will promote the best cache
locality.

If, on the other hand, the application is expected to deal with mostly
non-latin text, UTF16 is believed to result in the smallest memory
usage.

But if you don't quite care about memory usage and you have a stronger
requirement for being able to do more efficient random access on the
text, UTF32 with native endianess will make the most sense.

It is, of course, technically feasible to have encodings that make
decisions at run time, but the cost of that runtime decision will be
paid over and over in the life-cycle of that object.

For that reason, it is much more intelligent to convert the text to
one of UTF8, UTF16 with native endianess or UTF32 with native
endianess at the border of your application. I cannot see a rason to
support any other encoding as the basis for operating on the text, any
other encoding may be considered a serialization format to be
converted to and from in the borders of your application.

## A note on endianess

The unicode standard defines UTF16BE and UTF16LE, as well as UTF32BE
and UTF32LE. The bare "UTF16" and "UTF32" encodings are actually
runtime-defined according to Byte-Order-Marker (BOM), the default, in
the absense of a BOM is Big-Endian, accorting to the standard -- utf8
is always little endian, and BOM characters in utf8 are not relevant.

This library introduces the terms UTF16NE and UTF32NE. Those are not
encodings, but rather architecture-specific runtime types that will
either be the BE or the LE variants depending on the machine that runs
it. Whenever you are using the UTF16NE and UTF32NE types, you are
expected to appropriately convert the incoming texts to the correct
native encoding on the borders of your application.

# This library will cover

These are the problems that this library intends to solve:

 * Iterating and truncating on correct boundaries for:
   * codepoints
   * graphemes
   * words
   * sentences
 * Normalization
   * All standard normalization forms
   * "Normalization Form Grapheme" (as used by the Perl 6 Rakudo project)
 * Explicitly Localized and Explicitly Non-localized support for:
   * Comparison
   * Sorting
   * Case Folding
   * Search Folding (folded to 'base character')
   * Tokenizing

# This library will not cover

These are the problems that are explicitly outside of the scope of
this library. They can, and most likely should, be solved in libraries
built on top of u5e.

 * Rendering
 * Font sizes
 * Word wrapping
 * Text presentation order (LTR vs RTL)
 * Number and Date formatting and parsing
 * Regular Expressions
 * Streaming, specifically partial reads and writes

# What are the guiding principles?

## Reuse as much of the STL as possible

Whenever possible, this library will provide a simple wrapping layer
that defines the unicode support on top of existing STL
types. Specifically, this library will not implement anything related
to specific IO layers or to memory allocation.

## Use Concepts for defining behavior

Different aspects of how a class works will be composed using traits
and concepts. Even though concepts is not yet a supported language
feature, we will document the expected API of the concept. It's part
of the contract to obey the expected concept.

## No "natural" unit

There is no default unit. Most of the confusion around unicode is
derived from the misconceptions on how to iterate over text and how to
count and measure it. This libray defines and uses the following
units:

1. native size: This measure the size of the text in its in-memory
   representation. It is not necessarily a number of bytes, but it's
   rather a variable size depending on the encoding and on the
   architecture where the code is running: for instance, UTF8 always
   uses octets as the encoding unit, however UTF32 may either use a 32
   bit int, if the endianess is the same, or it may still be forced to
   use octets if it's the wrong endianess. The size in bytes is an
   implementation detail that is architecture-specific and can be
   measured using operators like sizeof().

2. codepoint: The unicode standard calls this "character", but the
   oveloading of this term is definitely one of the main sources of
   confusion around the unicode standard, therefore, in this library
   we just do not ever use the term "character", and prefer the more
   precise term "codepoint", which represents an encoded unicode
   entity, which is usually represented as U+DEADBEEF.

3. grapheme: The grapheme is the unit of rendering, also referenced in
   the standard as "grapheme cluster" or "user perceived
   character". It represents a sequence of one or more codepoints that
   represent a single graphical symbol, previous versions of the
   unicode standard had a simple rule of "base character" and
   "combining characters", but more recent versions of the standard
   support more complex definitions for grapheme cluster boundaries.

4. word: A word is a set of graphemes that form a unit, it can be as
   simple as "two words" for english, but it requires the use of the
   unicode database for full internationalization support.

5. sentence: A collection of words. There is a property of codepoints
   in the unicode database that specifies if a given character is a
   sentence separator or not.

## Handling of text requires intermediate buffers

There is no sane way to handle text directly on streams, see [Streams versus Iterators](StreamVsIterators.md) for a longer discussion.

## Number and Date format is outside of the scope

The coupling of number and date format to streams is a major source of ambiguity in the standard library, see [Streams versus Format](StreamVsFormat.md) for a longer discussion.

# The different aspects of Text

In order to allow maximum reusability of the code, each aspect of the
text is going to be expressed in this library as a concept. Different
traits will implement that concept in different ways in order to at
the same time allow room for optimizations. For instance, UTF32 with
native endianess will be able to use the native integer type, while
UTF32 with the foreign endianess will need to use four octets and will
need to do the byte-swapping at runtime for most operations.

The usage of traits for this also gives us transparent
type-safety. Such that we can statically evaluate if you are
incorrectly mixing texts of different encodings, which is the most
common form of mistake when handling internationalized text.

## Encoding

The encoding concept will provide that basic interface from the
in-memory representation to iteration and access of codepoints.

## Normalization Form

Normalization is what allows equivalent sequences of characters to be
treated as being the same. By making the normalization a trait of the
text, we allow the implicit re-normalization when dealing with
denormalized text, at te same time that it gives room for important
optimizations when two different texts have the same normalization
form.

## Locale tailoring

The unicode standard has several features that are coupled with the
tailoring to specific locales, this will also be applicable to
different features. Making this into a trait allows to selectively
disable the tailoring for application where the speed gain from not
supporting this is more important than the use cases where such
support is a requirement. Making this into a trait even allows
optimizing away the storage required for storing the language of the
text, or if an application needs optimization for the tailoring for a
single language, it could be implemented directly as code and avoid
any runtime language queries.

