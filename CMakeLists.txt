cmake_minimum_required(VERSION 2.8)


project(u5e)
add_library(u5e
  src/u5e/version.cpp
  )
target_include_directories(u5e PUBLIC include/)
target_compile_options(u5e PUBLIC -std=c++1y)
add_subdirectory(googletest/googletest)
enable_testing()

include_directories(${u5e_SOURCE_DIR}/include ${gtest_SOURCE_DIR}/include)

foreach(TEST
    001_version
    002_utf32_encoded_iterator
    003_utf8_encoded_iterator
    )
  add_executable(${TEST}.t t/${TEST}.t.cpp)
  target_compile_options(${TEST}.t PUBLIC -std=c++1y)
  target_link_libraries(${TEST}.t u5e gtest gtest_main)
  add_test(${TEST} ${TEST}.t)
endforeach(TEST)

foreach(EXAMPLE
    simple_iteration
    )
  add_executable(${EXAMPLE} examples/${EXAMPLE}.cpp)
  target_compile_options(${EXAMPLE} PUBLIC -std=c++1y)
  target_link_libraries(${EXAMPLE} u5e)
endforeach(EXAMPLE)