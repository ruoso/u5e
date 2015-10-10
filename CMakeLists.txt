cmake_minimum_required(VERSION 2.8)



project(u5e)
add_library(u5e
  src/u5e/version.cpp
  )

target_include_directories(u5e PUBLIC include/)

