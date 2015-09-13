# the Encoding concept

The Encoding concept allows several encoding class traits to be implemented and be used interchangeably. Although the encoding is not responsible for the direct memory acess (the buffer type is), all other parts of this library will use this as the interface to the in-memory representation of the string. Everything outside the encoding trait can only interate or access the string via codepoints.

# Type definition

```TYPE enc_buffer_type```: The type of buffer, see [u5e::buffer](U5EBuffer.md) for details.

# Attributes

```enc_buffer_type buffer```: the buffer attribute will hold the buffer for the data in this encoding. But, again, only the encoding type is expected to manipulate this buffer. Every other part of this library will only access the in-memory representation through the encoding layer.
