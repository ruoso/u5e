# The u5e class hierarchy

## Encoding Support

### Basic template classes

#### u5e::basic_encodedstreambuf 

Represents a streambuf in a particular encoding. It allows consistently reading and writing codepoints with a coherent API while preserving type-safety over the access to an underlying streambuf.

The undelying streambuf operates in the "native size", while the basic_encodedstreambuf introduces the "size in codepoints", which is consistent independent of which encoding is used.

#### u5e::basic_encodedstring_view

Represents a string_view in a particular encoding, it offers iterator access that operates consistently by traversing and writing codepoints.

The underlying string-like object operates in the "native size".

#### u5e::basic_encodedstring

Represents a string in a particular encoding, just like basic_encodedstring_view, but has capabilities that require memory allocation capabilities in the underlying type.

The underlying string-like object operates in the "native size"

### Pre-provided instantiations

#### u5e::utf8_string, u5e::utf8_stringbuf, u5e::utf8_string_view

UTF8-specific instantiations of the basic template classes.

#### u5e::utf32_native_string, u5e::utf32_native_string_view

UTF32 (with native bitness) instantiations of the basic template classes.

### Support Classese

#### u5e::utf8, u5e::utf8_iterator

Mechanical support for the UTF8 encoding

#### u5e::utf32_native

Mechanical support for the UTF32 (with native bitness) encoding.

#### u5e::codepoint

Describes the codepoint as an independent type

#### u5e::encoding_assertion

Static assertions for consistency regarding underlying storage and the
encoding in question.
