# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/lesserfish/Documents/Software/cmake/bin/cmake

# The command to remove a file.
RM = /home/lesserfish/Documents/Software/cmake/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lesserfish/Documents/Code/Yolk/Rewrite

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lesserfish/Documents/Code/Yolk/Rewrite/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/TEST.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/TEST.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/TEST.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/TEST.dir/flags.make

tests/CMakeFiles/TEST.dir/Yolk/Wrapper/test_tvariable.cpp.o: tests/CMakeFiles/TEST.dir/flags.make
tests/CMakeFiles/TEST.dir/Yolk/Wrapper/test_tvariable.cpp.o: ../tests/Yolk/Wrapper/test_tvariable.cpp
tests/CMakeFiles/TEST.dir/Yolk/Wrapper/test_tvariable.cpp.o: tests/CMakeFiles/TEST.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lesserfish/Documents/Code/Yolk/Rewrite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/TEST.dir/Yolk/Wrapper/test_tvariable.cpp.o"
	cd /home/lesserfish/Documents/Code/Yolk/Rewrite/build/tests && /usr/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/TEST.dir/Yolk/Wrapper/test_tvariable.cpp.o -MF CMakeFiles/TEST.dir/Yolk/Wrapper/test_tvariable.cpp.o.d -o CMakeFiles/TEST.dir/Yolk/Wrapper/test_tvariable.cpp.o -c /home/lesserfish/Documents/Code/Yolk/Rewrite/tests/Yolk/Wrapper/test_tvariable.cpp

tests/CMakeFiles/TEST.dir/Yolk/Wrapper/test_tvariable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TEST.dir/Yolk/Wrapper/test_tvariable.cpp.i"
	cd /home/lesserfish/Documents/Code/Yolk/Rewrite/build/tests && /usr/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lesserfish/Documents/Code/Yolk/Rewrite/tests/Yolk/Wrapper/test_tvariable.cpp > CMakeFiles/TEST.dir/Yolk/Wrapper/test_tvariable.cpp.i

tests/CMakeFiles/TEST.dir/Yolk/Wrapper/test_tvariable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TEST.dir/Yolk/Wrapper/test_tvariable.cpp.s"
	cd /home/lesserfish/Documents/Code/Yolk/Rewrite/build/tests && /usr/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lesserfish/Documents/Code/Yolk/Rewrite/tests/Yolk/Wrapper/test_tvariable.cpp -o CMakeFiles/TEST.dir/Yolk/Wrapper/test_tvariable.cpp.s

# Object files for target TEST
TEST_OBJECTS = \
"CMakeFiles/TEST.dir/Yolk/Wrapper/test_tvariable.cpp.o"

# External object files for target TEST
TEST_EXTERNAL_OBJECTS =

tests/TEST: tests/CMakeFiles/TEST.dir/Yolk/Wrapper/test_tvariable.cpp.o
tests/TEST: tests/CMakeFiles/TEST.dir/build.make
tests/TEST: lib/libgtest_main.a
tests/TEST: src/libYolk.so.1.0
tests/TEST: lib/libgtest.a
tests/TEST: tests/CMakeFiles/TEST.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lesserfish/Documents/Code/Yolk/Rewrite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TEST"
	cd /home/lesserfish/Documents/Code/Yolk/Rewrite/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TEST.dir/link.txt --verbose=$(VERBOSE)
	cd /home/lesserfish/Documents/Code/Yolk/Rewrite/build/tests && /home/lesserfish/Documents/Software/cmake/bin/cmake -D TEST_TARGET=TEST -D TEST_EXECUTABLE=/home/lesserfish/Documents/Code/Yolk/Rewrite/build/tests/TEST -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/lesserfish/Documents/Code/Yolk/Rewrite/tests -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=TEST_TESTS -D CTEST_FILE=/home/lesserfish/Documents/Code/Yolk/Rewrite/build/tests/TEST[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /home/lesserfish/Documents/Software/cmake/share/cmake-3.23/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
tests/CMakeFiles/TEST.dir/build: tests/TEST
.PHONY : tests/CMakeFiles/TEST.dir/build

tests/CMakeFiles/TEST.dir/clean:
	cd /home/lesserfish/Documents/Code/Yolk/Rewrite/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/TEST.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/TEST.dir/clean

tests/CMakeFiles/TEST.dir/depend:
	cd /home/lesserfish/Documents/Code/Yolk/Rewrite/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lesserfish/Documents/Code/Yolk/Rewrite /home/lesserfish/Documents/Code/Yolk/Rewrite/tests /home/lesserfish/Documents/Code/Yolk/Rewrite/build /home/lesserfish/Documents/Code/Yolk/Rewrite/build/tests /home/lesserfish/Documents/Code/Yolk/Rewrite/build/tests/CMakeFiles/TEST.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/TEST.dir/depend

