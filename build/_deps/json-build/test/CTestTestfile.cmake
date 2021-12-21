# CMake generated Testfile for 
# Source directory: /home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test
# Build directory: /home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(download_test_data "/usr/local/bin/cmake" "--build" "/home/vchavauty/Documents/Code/Yolk/build" "--target" "download_test_data")
set_tests_properties(download_test_data PROPERTIES  FIXTURES_SETUP "TEST_DATA" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;10;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-algorithms "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-algorithms" "--no-skip")
set_tests_properties(test-algorithms PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-allocator "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-allocator" "--no-skip")
set_tests_properties(test-allocator PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-alt-string "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-alt-string" "--no-skip")
set_tests_properties(test-alt-string PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-bson "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-bson" "--no-skip")
set_tests_properties(test-bson PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-capacity "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-capacity" "--no-skip")
set_tests_properties(test-capacity PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-cbor "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-cbor" "--no-skip")
set_tests_properties(test-cbor PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-class_const_iterator "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-class_const_iterator" "--no-skip")
set_tests_properties(test-class_const_iterator PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-class_iterator "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-class_iterator" "--no-skip")
set_tests_properties(test-class_iterator PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-class_lexer "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-class_lexer" "--no-skip")
set_tests_properties(test-class_lexer PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-class_parser "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-class_parser" "--no-skip")
set_tests_properties(test-class_parser PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-comparison "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-comparison" "--no-skip")
set_tests_properties(test-comparison PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-concepts "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-concepts" "--no-skip")
set_tests_properties(test-concepts PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-constructor1 "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-constructor1" "--no-skip")
set_tests_properties(test-constructor1 PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-constructor2 "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-constructor2" "--no-skip")
set_tests_properties(test-constructor2 PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-convenience "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-convenience" "--no-skip")
set_tests_properties(test-convenience PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-conversions "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-conversions" "--no-skip")
set_tests_properties(test-conversions PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-deserialization "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-deserialization" "--no-skip")
set_tests_properties(test-deserialization PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-element_access1 "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-element_access1" "--no-skip")
set_tests_properties(test-element_access1 PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-element_access2 "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-element_access2" "--no-skip")
set_tests_properties(test-element_access2 PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-inspection "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-inspection" "--no-skip")
set_tests_properties(test-inspection PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-items "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-items" "--no-skip")
set_tests_properties(test-items PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-iterators1 "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-iterators1" "--no-skip")
set_tests_properties(test-iterators1 PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-iterators2 "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-iterators2" "--no-skip")
set_tests_properties(test-iterators2 PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-json_patch "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-json_patch" "--no-skip")
set_tests_properties(test-json_patch PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-json_pointer "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-json_pointer" "--no-skip")
set_tests_properties(test-json_pointer PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-large_json "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-large_json" "--no-skip")
set_tests_properties(test-large_json PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-merge_patch "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-merge_patch" "--no-skip")
set_tests_properties(test-merge_patch PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-meta "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-meta" "--no-skip")
set_tests_properties(test-meta PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-modifiers "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-modifiers" "--no-skip")
set_tests_properties(test-modifiers PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-msgpack "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-msgpack" "--no-skip")
set_tests_properties(test-msgpack PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-noexcept "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-noexcept" "--no-skip")
set_tests_properties(test-noexcept PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-pointer_access "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-pointer_access" "--no-skip")
set_tests_properties(test-pointer_access PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-readme "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-readme" "--no-skip")
set_tests_properties(test-readme PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-reference_access "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-reference_access" "--no-skip")
set_tests_properties(test-reference_access PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-regression "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-regression" "--no-skip")
set_tests_properties(test-regression PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-serialization "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-serialization" "--no-skip")
set_tests_properties(test-serialization PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-testsuites "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-testsuites" "--no-skip")
set_tests_properties(test-testsuites PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-to_chars "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-to_chars" "--no-skip")
set_tests_properties(test-to_chars PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-ubjson "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-ubjson" "--no-skip")
set_tests_properties(test-ubjson PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-udt "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-udt" "--no-skip")
set_tests_properties(test-udt PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-unicode "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-unicode" "--no-skip")
set_tests_properties(test-unicode PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-user_defined_input "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-user_defined_input" "--no-skip")
set_tests_properties(test-user_defined_input PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
add_test(test-wstring "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/test-wstring" "--no-skip")
set_tests_properties(test-wstring PROPERTIES  FIXTURES_REQUIRED "TEST_DATA" LABELS "all" WORKING_DIRECTORY "/home/vchavauty/Documents/Code/Yolk" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;158;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/CMakeLists.txt;0;")
subdirs("cmake_import")
subdirs("cmake_import_minver")
subdirs("cmake_add_subdirectory")
subdirs("cmake_fetch_content")
