# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vchavauty/Documents/Code/Yolk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vchavauty/Documents/Code/Yolk/build

# Include any dependencies generated for this target.
include _deps/json-build/test/CMakeFiles/test-meta.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include _deps/json-build/test/CMakeFiles/test-meta.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/json-build/test/CMakeFiles/test-meta.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/json-build/test/CMakeFiles/test-meta.dir/flags.make

_deps/json-build/test/CMakeFiles/test-meta.dir/src/unit-meta.cpp.o: _deps/json-build/test/CMakeFiles/test-meta.dir/flags.make
_deps/json-build/test/CMakeFiles/test-meta.dir/src/unit-meta.cpp.o: _deps/json-src/test/src/unit-meta.cpp
_deps/json-build/test/CMakeFiles/test-meta.dir/src/unit-meta.cpp.o: _deps/json-build/test/CMakeFiles/test-meta.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vchavauty/Documents/Code/Yolk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/json-build/test/CMakeFiles/test-meta.dir/src/unit-meta.cpp.o"
	cd /home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT _deps/json-build/test/CMakeFiles/test-meta.dir/src/unit-meta.cpp.o -MF CMakeFiles/test-meta.dir/src/unit-meta.cpp.o.d -o CMakeFiles/test-meta.dir/src/unit-meta.cpp.o -c /home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/src/unit-meta.cpp

_deps/json-build/test/CMakeFiles/test-meta.dir/src/unit-meta.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-meta.dir/src/unit-meta.cpp.i"
	cd /home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/src/unit-meta.cpp > CMakeFiles/test-meta.dir/src/unit-meta.cpp.i

_deps/json-build/test/CMakeFiles/test-meta.dir/src/unit-meta.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-meta.dir/src/unit-meta.cpp.s"
	cd /home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test/src/unit-meta.cpp -o CMakeFiles/test-meta.dir/src/unit-meta.cpp.s

# Object files for target test-meta
test__meta_OBJECTS = \
"CMakeFiles/test-meta.dir/src/unit-meta.cpp.o"

# External object files for target test-meta
test__meta_EXTERNAL_OBJECTS = \
"/home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/CMakeFiles/doctest_main.dir/src/unit.cpp.o"

_deps/json-build/test/test-meta: _deps/json-build/test/CMakeFiles/test-meta.dir/src/unit-meta.cpp.o
_deps/json-build/test/test-meta: _deps/json-build/test/CMakeFiles/doctest_main.dir/src/unit.cpp.o
_deps/json-build/test/test-meta: _deps/json-build/test/CMakeFiles/test-meta.dir/build.make
_deps/json-build/test/test-meta: _deps/json-build/test/CMakeFiles/test-meta.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vchavauty/Documents/Code/Yolk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-meta"
	cd /home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-meta.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/json-build/test/CMakeFiles/test-meta.dir/build: _deps/json-build/test/test-meta
.PHONY : _deps/json-build/test/CMakeFiles/test-meta.dir/build

_deps/json-build/test/CMakeFiles/test-meta.dir/clean:
	cd /home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test && $(CMAKE_COMMAND) -P CMakeFiles/test-meta.dir/cmake_clean.cmake
.PHONY : _deps/json-build/test/CMakeFiles/test-meta.dir/clean

_deps/json-build/test/CMakeFiles/test-meta.dir/depend:
	cd /home/vchavauty/Documents/Code/Yolk/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vchavauty/Documents/Code/Yolk /home/vchavauty/Documents/Code/Yolk/build/_deps/json-src/test /home/vchavauty/Documents/Code/Yolk/build /home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test /home/vchavauty/Documents/Code/Yolk/build/_deps/json-build/test/CMakeFiles/test-meta.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/json-build/test/CMakeFiles/test-meta.dir/depend

