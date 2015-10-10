cmake_minimum_required(VERSION 2.8)

project(u5e)
add_library(u5e
  src/u5e/version.cpp
  )

target_include_directories(u5e PUBLIC include/)

add_subdirectory(googletest/googletest)
enable_testing()

include_directories(${u5e_SOURCE_DIR}/include ${gtest_SOURCE_DIR}/include)

add_executable(001_version.t t/001_version.t.cpp)
target_link_libraries(001_version.t u5e gtest gtest_main)
add_test(001_version 001_version.t)