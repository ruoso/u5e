# u5e::encoded_buffer<ENCODINGTYPE encoding>

This represents the buffer in a particular encoding, and the access to it, codepoint by codepoint regardless of the specific in-memory representation. However, this still does not offer the higher-level constructs of unicode text.

# Attributes

```encoding.enc_buffer_type raw_buffer```: the raw buffer holding the in-memory representation.

# Methods

Offer methods symmetric to [u5e::buffer](U5EBuffer.md) but that operate only in terms of codepoints.
