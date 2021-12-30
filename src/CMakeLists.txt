cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

project(Yolk VERSION 1.0 DESCRIPTION "Yolk library")

include(external/nlohmann_json.cmake SYSTEM)

set(SOURCE_FILES Yolk/YolkVM/Elementary.cpp Yolk/YolkVM/YVM.cpp)

#add_library(${PROJECT_NAME} INTERFACE)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES 
                VERSION ${PROJECT_VERSION}
                LINKER_LANGUAGE CXX)

if(MSVC)
  target_compile_options(${PROJECT_NAME} PUBLIC /W4 /WX)
else()
  target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)