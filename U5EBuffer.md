# u5e::buffer

This class exists because string_view is not a part of the C++ standard. Maybe at some point in the future it will become a simple typedef for string_view, we may even allow you to set it as a typedef to std::experimental::string_view if your C++ compiler and STL supports it.

We will try to stick as closely as possible to what the experimental string_view definition is, in the hope that this class will disappear (although there is a chance that the spec changes in a way that we may be required to keep this forever).
