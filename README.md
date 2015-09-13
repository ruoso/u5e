# u5e
Unicode Text C++ library

# What is this library?

This library provides support for Unicode Text, as specified by the Unicode Standard.

# Why?

Proper supporting international text is one of these problems that you either think is very easy because you never had to deal with internationalized text, or you give up on it because you think no one can support Unicode correctly. This library is an attempt to provide a simple reusable set of interfaces to deal with international text.

# Why not just use the icu library?

The first reason for me to consider this was that the icu library is much more complex than what's required for supporting text. ICU also supports the full localization definitions of the Unicode CLDR, which makes its support surface much larger than would be required for simply handling text.

Secondly, the icu library forces the internal representation of the text to always be in a particular encoding. I believe that this is an unecessary constraint, and one of the points of this library is to make the encoding pluggable without requiring different APIs or explicit conversions.

# What are the guiding principles?

The basic guiding principles for the design of this library are:

1. Basic data types are always Plain-Old-Data structs with no constructors or descructors. This is important to allow the types to be fully usable regardless of memory allocation or life-time requirements. It is very easy to wrap a POD type into a smart-pointer type that manages its life-cycle, but it's much harder to reuse a fundamental type in other scenarios when it makes this type of assumptions (I'm looking at you, std::string).
2. Basic data types are always immutable. This library will never mutate values in-place, even though it some times may be the case that doing in-place mutation can represent an improvement, there are ways to optimize this by building a sequence of immutable buffers. However, when you do have mutable data, it's orders of magnitude harder to optimize the code for parallelism.
3. Different aspects of how a class works will be composed using traits and concepts. Even though concepts is not yet a supported language feature, we will document the expected API of the traits and it's part of the contract that anyone implementing a trait to obey the expected concept.
4. There is no default unit. Most of the confusion around unicode is derived from the misconceptions on how to iterate over text and how to count and measure it. This libray defines and uses the following units:
   1. encoded size: This measure the size of the text in its in-memory representation. It is not necessarily a number of bytes, but it's rather a variable size depending on the encoding and on the architecture where the code is running: for instance, UTF8 always uses octets as the encoding unit, however UTF32 may either use a 32 bit int, if the endianess is the same, o it may still be forced to use octets if it's the wrong endianess. The size in bytes is an implementation detail that is architecture-specific and can be measured using operators like sizeof().
   2. codepoint: The unicode standard calls this "character", but the oveloading of this term is definitely one of the main sources of confusion around the unicode standard, therefore, in this library we just do not ever use the term "character", and prefer the more precise term "codepoint", which represents an encoded unicode entity, which is usually represented as U+DEADBEEF.
   3. grapheme: The grapheme is the unit of rendering, also referenced in the standard as "grapheme cluster". It represents a sequence of one or more codepoints that represent a single graphical symbol, previous versions of the unicode standard had a simple rule of "base character" and "combining characters", but more recent versions of the standard support more complex definitions for grapheme cluster boundaries.
   4. word: A word is a set of graphemes that form a unit, it can be as simple as "two words" for english, but it requires the use of the unicode database for full internationalization support.
   5. sentence: A collection of words. There is a property of codepoints in the unicode database that specifies if a given character is a sentence separator or not.

# The different aspects of Text

In order to allow maximum reusability of the code, each aspect of the text is going to be expressed in this library as a concept. Different traits will implement that concept in different ways in order to at the same time allow room for optimizations. For instance, UTF32 with native endianess will be able to use the native integer type, while UTF32 with the foreign endianess will need to use four octets and will need to do the byte-swapping at runtime for most operations.

The usage of traits for this also gives us transparent type-safety. Such that we can statically evaluate if you are incorrectly mixing texts of different encodings, which is the most common form of mistake when handling internationalized text.

## Encoding

The encoding concept will provide that basic interface from the in-memory representation to iteration and access of codepoints.

## Normalization Form

Normalization is what allows equivalent sequences of characters to be treated as being the same. By making the normalization a trait of the text, we allow the implicit re-normalization when dealing with denormalized text, at te same time that it gives room for important optimizations when two different texts have the same normalization form.

## Locale tailoring

The unicode standard has several features that are coupled with the tailoring to specific locales, this will also be applicable to different features. Making this into a trait allows to selectively disable the tailoring for application where the speed gain from not supporting this is more important than the use cases where such support is a requirement. Making this into a trait even allows optimizing away the storage required for storing the language of the text, or if an application needs optimization for the tailoring for a single language, it could be implemented directly as code and avoid any runtime language queries.

