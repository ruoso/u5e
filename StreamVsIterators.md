# Streams vs Iterators

> TL;DR: streams only make sense when dealing with raw data, and they should always operate in the 'native character size' of the underlying channel. Operating in text requires bidirectional, concurrent access, such as what iterators provide.

There is a tension in purpose between streams and iterators in the C++ standard library. On one hand, it seems as if the basic form of interaction with text should be through streams and the shift operator overloads. On the other hand, not everything can be represented as a stream.

The moment where this becomes the most obvious is when you are dealing with multi-octet encodings as well as when dealing with multi-codepoint graphemes. When getting the next "character" from a stream, there's an implicit expectation that the underlying channel supports a "character" of exatly that size.

This is important because when we're talking about underlying streams backed up  by file descriptors (e.g.: sockets or files on disk), the operating system has a "native character size" by which that operation happens. On POSIX systems, that "native character size" is an octet. When we're talking about network operations, they are defined by the TCP and UDP protocols to be have the "native character size" of an octet.

The important side-effect of this fact is that when dealing with a stream of a given "native character size", any "character type" bigger than that will unavoidably be subject to being truncated or split across separate read operations.

When you are writing network-aware code, regardless of the encoding of the data being transmitted, the size of the TCP packet will be measured in bytes, regardless of you having decided to use a wchar on your code. In that lies a great challenge:

> If you try to do a non-blocking write of a wchar to a socket, and you only get half of it written, what do you do?

#### Option 1: keep a local buffer of half-sent wchars

This looks good at first, but when you look at how this actually reflects on the several layers of API surrounding that decision, you will quickly notice that this will fall apart. What does your abstraction return to the calling code? Your off_t type is not a floating point, so you can't say that you wrote half a character.

#### Option 2: Block until you can actually send the whole wchar

This would look good if the original write operation was a blocking write, but non-blocking writes are definitely a fundamental part of any network protocol, so blindly disabling that feature sounds unacceptable.

## What is the alternative?

The alternative is actually not new, and it's actually fairly well understood by the designers of more recent languages. The requirement is that you can't talk about "text" when dealing with any sort of serialization. Languages like python3 have addressed this as a first-level problem by having two distinct types for 'raw data' and 'text string'.

The process of converting between that 'raw data' and a 'text string' is the explicit layering of encoding and decoding. The result is that there's a chosen internal representation of the encoding used by the language for 'text' and the user is not exposed to that. The user is still required to explictly encode and decode text, even if that encoding turns out to be a no-op in the case where the input/output encoding matches the internal encoding.

The C++ standard library does not make that distinction, and in that sense, std::string is just 'raw data', and there is not a separate type to clearly demarcate what parts of your code are dealing with raw data (as network protocols must) and which parts of your code are dealing with text (as human interfaces and business logic must).

## What am I proposing?

I'm proposing a data/text firewall in the type system.

### Streams can only deal with raw data

Streams, due to the very nature of the underlying mechanisms, can only operate on raw data, specifically because they must be able to operate with incomplete data.

If a particular operating system API allows operating in 16-bit sized operations, then the stream can be made as such. This will, of course, require the operating system to deal with the possibility of incomplete 'characters' from the TCP packet -- I am not at all familiar with Windows APIs, but I have seen some documentation that seems to indicate Windows offers such API -- In those cases, the 'native character size' of the stream should clearly be 16 bits.

On any Unix-like Operating System, however, that 'native character size' is unequivocally an octet, therefore all streams must only operate on that size.

### Text requires bidirectional, concurrent access

As much as we like to thing about text as a sequence, I came to the conclusion that it is not viable to work with text without supporting bidirectional access, follow a few reasons:

#### How to get the current 'codepoint'

When dealing with text, you don't want to even know that a particular codepoint is represented as more than one byte. You want to be able to count the number of codepoints and you want to be able to traverse one codepoint at a time.

Getting the current 'codepoint' in utf8 may require you to read several characters in advance (mathematically up to 6, but the standard currently limits to 4). In the case of streams, this requires you to read ahead.

The 'peek' function on basic_istream, therefore, will require to read ahead and put back in order to get the current codepoint without modifying the current position indicator.

On the case of iterators, you can perform the read-ahead in a copy of the iterator, thus allowing you to implement the correct semantics without manipulation of the underlying buffer.

#### You can't tell if a grapheme is complete

When you move from working with 'codepoints' to working with graphemes, this problem gets the semantics to a whole new level. There's no way to tell, as you read from a stream, if you have finished reading the grapheme or not until you read the beggining of the next grapheme or you reach the end of the buffer.

That basically makes the semantics of a stream that operated on graphemes terribly complicated, because now getc would need to either block until the beginning of the next grapheme or return some magic value describing that it received some data, but it can't be sure that it's a complete grapheme.

Again, if we can just iterate over the data instead, it's trivial to read-ahead to determine wether or not we have a full grapheme.

## The specific network protocol or file format has better hints

When operating in the IRC protocol, for instance, the network protocol specifies how many octets are expected to be read and specifies when truncation or splitting of messages may occur.

The same happens when reading from an XML file. The XML parser can easily chunk out the sequence of octets in more meaningful sections in which partial characters are not allowed.

The important point is that both an IRC network library and an XML parser already have to support incomplete reads for the semantics implied by the specific technology. Therefore it's not at all unreasonable to expect the XML SAX event to be delayed until the complete XML token is received, at which point we can hold that entire token as addressable memory.

To illustrate this in another way. When handling a large utf-8 encoded file as a single unit, the `mmap` function is a better tool than the `read` function.

## Room for optimization when dealing with known-to-be-good data

The other interesting side-effect of this approach is that you create some room for optimization when you know the data to be well-formed. If you're dealing with non-validated utf8, you must always bound-check due to the risk of an incomplete character at the end of the buffer.

However, if you have already validated that text to be well-formed, that bounds-check can be optimized away.