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
CMAKE_SOURCE_DIR = /home/vchavauty/Documents/Code/Yolk/Rewrite

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vchavauty/Documents/Code/Yolk/Rewrite/build

# Include any dependencies generated for this target.
include CMakeFiles/Example.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Example.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Example.dir/flags.make

CMakeFiles/Example.dir/main.cpp.o: CMakeFiles/Example.dir/flags.make
CMakeFiles/Example.dir/main.cpp.o: ../main.cpp
CMakeFiles/Example.dir/main.cpp.o: CMakeFiles/Example.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vchavauty/Documents/Code/Yolk/Rewrite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Example.dir/main.cpp.o"
	/usr/bin/clang++-13 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Example.dir/main.cpp.o -MF CMakeFiles/Example.dir/main.cpp.o.d -o CMakeFiles/Example.dir/main.cpp.o -c /home/vchavauty/Documents/Code/Yolk/Rewrite/main.cpp

CMakeFiles/Example.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Example.dir/main.cpp.i"
	/usr/bin/clang++-13 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vchavauty/Documents/Code/Yolk/Rewrite/main.cpp > CMakeFiles/Example.dir/main.cpp.i

CMakeFiles/Example.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Example.dir/main.cpp.s"
	/usr/bin/clang++-13 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vchavauty/Documents/Code/Yolk/Rewrite/main.cpp -o CMakeFiles/Example.dir/main.cpp.s

# Object files for target Example
Example_OBJECTS = \
"CMakeFiles/Example.dir/main.cpp.o"

# External object files for target Example
Example_EXTERNAL_OBJECTS =

Example: CMakeFiles/Example.dir/main.cpp.o
Example: CMakeFiles/Example.dir/build.make
Example: src/libYolk.so.1.0
Example: CMakeFiles/Example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vchavauty/Documents/Code/Yolk/Rewrite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Example.dir/build: Example
.PHONY : CMakeFiles/Example.dir/build

CMakeFiles/Example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Example.dir/clean

CMakeFiles/Example.dir/depend:
	cd /home/vchavauty/Documents/Code/Yolk/Rewrite/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vchavauty/Documents/Code/Yolk/Rewrite /home/vchavauty/Documents/Code/Yolk/Rewrite /home/vchavauty/Documents/Code/Yolk/Rewrite/build /home/vchavauty/Documents/Code/Yolk/Rewrite/build /home/vchavauty/Documents/Code/Yolk/Rewrite/build/CMakeFiles/Example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Example.dir/depend

