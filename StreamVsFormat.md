# Streams versus String Formatting

The C++ standard library provides support for localization on a level that doesn't quite have a analogous comparison in other languages. The way in which the stream itself is made aware of locales and how the shift operator on streams has its behaviors dependant on locales is an unique design decision on how input and output operates on an application.

Localization happens in many different levels, and coupling the reading and writing to streams with that is, imho, an unecessarily heavy-handed decision. Specifically, most applications read and write from streams much more frequently than when interacting with the localized user interface. It is much more frequent that an application will be dealing with serialization formats and network protocols that are not locale-dependant, than an application will be dealing with interactive input and output that is meant to be localized.

When working in an internationalized application, it is crucial that the moments in which the locale reflects in the behavior of the application should be explicitly demarcated from the places in which the application is dealing with "data" input and output. The C++ standard library makes that harder.

For that reason, the u5e library will explicitly mark the string formatting support as a trait of the text type, such that you won't mistakingly mix and match internationlized text with non-internationalized operations and vice-versa.

The string formatting is then composed into the stream via a trait that brings in the different shift operator overloads.

This requires the building of an entirely separate class hierarchy for describing text streams.

