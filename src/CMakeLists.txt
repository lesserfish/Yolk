cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

project(Yolk VERSION 1.0 DESCRIPTION "Yolk library")

include(external/nlohmann_json.cmake SYSTEM)

add_library(${PROJECT_NAME} INTERFACE)

set_target_properties(${PROJECT_NAME} PROPERTIES 
                VERSION ${PROJECT_VERSION}
                LINKER_LANGUAGE CXX)

if(MSVC)
  target_compile_options(${PROJECT_NAME} INTERFACE /W4 /WX)
else()
  target_compile_options(${PROJECT_NAME} INTERFACE -Wall -Wextra -Wpedantic)
endif()


target_link_libraries(${PROJECT_NAME} INTERFACE nlohmann_json::nlohmann_json)