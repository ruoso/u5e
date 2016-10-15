cmake_minimum_required(VERSION 2.8.12)

project(u5e)
add_library(u5e
  src/u5e/version.cpp
  src/u5e/props/grapheme_cluster_break.cpp
  )
target_include_directories(u5e PUBLIC include/)
target_compile_options(u5e PUBLIC -std=c++1y -Wall -Werror)
add_subdirectory(googletest/googletest)
enable_testing()

include_directories(${u5e_SOURCE_DIR}/include ${gtest_SOURCE_DIR}/include)

add_subdirectory(t)
add_subdirectory(examples)

