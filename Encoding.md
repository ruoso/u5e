# the Encoding concept

The Encoding concept allows several encoding class traits to be implemented and be used interchangeably. Although the encoding is not responsible for the direct memory acess (the buffer type is), all other parts of this library will use this as the interface to the in-memory representation of the string. Everything outside the encoding trait can only interate or access the string via codepoints.

# Type definition

```TYPE enc_buffer_type```: The type of buffer, see [u5e::buffer](U5EBuffer.md) for details.

```TYPE enc_iterator_type```: Since some encodings may give the oportunity for some guarantees that other encodings won't, the iterator type is delegated to the encoding.

```TYPE enc_reverse_iterator_type```: Since some encodings may give the oportunity for some guarantees that other encodings won't, the iterator type is delegated to the encoding.

# Attributes

```const static enc_buffer_type.size_type min_codepoint_size```: minimum size required by a single codepoint

```const static enc_buffer_type.size_type max_codepoint_size```: maximum size required by a single codepoint

```const static enc_buffer_type.size_type max_bmp_codepoint_size```: maximum size required by a single codepoint in the basic multilingual plane. Useful for picking a better estimate for a buffer size.

```const static enc_buffer_type.size_type max_ascii_codepoint_size```: maximum size required by a single codepoint in the 7bit ascii table. Useful for picking a better estimate for a buffer size when dealing with what is known to be text containing only non-control-characters from the 7bit ascii table.

# Methods

The methods here are the primitives required to implement the access to the encoded buffer. This will also include additional primitives for the mutating operations.
