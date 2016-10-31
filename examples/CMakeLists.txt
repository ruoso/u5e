
foreach(EXAMPLE
    simple_iteration
    smallest_code
    truncate_on_codepoint
    truncate_on_grapheme
    grapheme_iteration
    normalization_form_d
    )
  add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
  target_compile_options(${EXAMPLE} PUBLIC -std=c++1y)
  target_link_libraries(${EXAMPLE} u5e)
endforeach(EXAMPLE)
