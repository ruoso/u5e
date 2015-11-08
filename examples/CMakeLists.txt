
foreach(EXAMPLE
    simple_iteration
    smallest_code
    )
  add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
  target_compile_options(${EXAMPLE} PUBLIC -std=c++1y)
  target_link_libraries(${EXAMPLE} u5e)
endforeach(EXAMPLE)