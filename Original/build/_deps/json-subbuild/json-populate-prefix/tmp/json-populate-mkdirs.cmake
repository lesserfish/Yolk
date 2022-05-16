# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/lesserfish/Documents/Code/Yolk/Original/build/_deps/json-src"
  "/home/lesserfish/Documents/Code/Yolk/Original/build/_deps/json-build"
  "/home/lesserfish/Documents/Code/Yolk/Original/build/_deps/json-subbuild/json-populate-prefix"
  "/home/lesserfish/Documents/Code/Yolk/Original/build/_deps/json-subbuild/json-populate-prefix/tmp"
  "/home/lesserfish/Documents/Code/Yolk/Original/build/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp"
  "/home/lesserfish/Documents/Code/Yolk/Original/build/_deps/json-subbuild/json-populate-prefix/src"
  "/home/lesserfish/Documents/Code/Yolk/Original/build/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/lesserfish/Documents/Code/Yolk/Original/build/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp/${subDir}")
endforeach()
