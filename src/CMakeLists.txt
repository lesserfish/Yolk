cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

project(Yolk VERSION 1.0 DESCRIPTION "Yolk library")

add_library(${PROJECT_NAME} SHARED ./Yolk/YolkVM/Instruction.cpp Yolk/YolkVM/VirtualMachine.cpp Yolk/YolkVM/OVO.cpp Yolk/Assembler/Assembler.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES 
                VERSION ${PROJECT_VERSION}
                LINKER_LANGUAGE CXX)

if(MSVC)
  target_compile_options(${PROJECT_NAME} PUBLIC /W4 /WX)
else()
  target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wpedantic)
endif()
