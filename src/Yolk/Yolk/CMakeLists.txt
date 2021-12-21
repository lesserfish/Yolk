#Yolk/Yolk/CMakeLists.txt

cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

project(yolk VERSION 1.0 DESCRIPTION "Yolk library")

add_library(${PROJECT_NAME} INTERFACE)

set_target_properties(${PROJECT_NAME} PROPERTIES 
                VERSION ${PROJECT_VERSION}
                LINKER_LANGUAGE CXX)
