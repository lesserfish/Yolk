if(EXISTS "/home/lesserfish/Documents/Code/Yolk/Rewrite/build/tests/TEST[1]_tests.cmake")
  include("/home/lesserfish/Documents/Code/Yolk/Rewrite/build/tests/TEST[1]_tests.cmake")
else()
  add_test(TEST_NOT_BUILT TEST_NOT_BUILT)
endif()