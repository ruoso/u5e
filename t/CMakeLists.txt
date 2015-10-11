foreach(TEST
    001_version
    002_utf32_encoded_iterator
    003_utf8_encoded_iterator
    )
  add_executable(${TEST}.t ${TEST}.t.cpp)
  target_compile_options(${TEST}.t PUBLIC -std=c++1y)
  target_link_libraries(${TEST}.t u5e gtest gtest_main)
  add_test(${TEST} ${TEST}.t)
endforeach(TEST)
