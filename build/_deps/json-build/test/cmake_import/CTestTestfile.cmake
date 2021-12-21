# CMake generated Testfile for 
# Source directory: /home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/cmake_import
# Build directory: /home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/cmake_import
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cmake_import_configure "/usr/local/bin/cmake" "-G" "Unix Makefiles" "-A" "" "-DCMAKE_CXX_COMPILER=/usr/bin/c++" "-Dnlohmann_json_DIR=/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build" "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/cmake_import/project")
set_tests_properties(cmake_import_configure PROPERTIES  FIXTURES_SETUP "cmake_import" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/cmake_import/CMakeLists.txt;1;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/cmake_import/CMakeLists.txt;0;")
add_test(cmake_import_build "/usr/local/bin/cmake" "--build" ".")
set_tests_properties(cmake_import_build PROPERTIES  FIXTURES_REQUIRED "cmake_import" _BACKTRACE_TRIPLES "/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/cmake_import/CMakeLists.txt;9;add_test;/home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/cmake_import/CMakeLists.txt;0;")
