include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

 set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

FILE(GLOB SOURCE_FILES Serializer/*.cpp Yolk/Memory/*.cpp Yolk/Wrapper/*.cpp Yolk/Wrapper/*.cpp Yolk/Object/*.cpp)
add_executable(TEST ${SOURCE_FILES})


target_link_libraries(TEST gtest_main Yolk nlohmann_json::nlohmann_json)

include(../src/Yolk/external/nlohmann_json.cmake)
include(GoogleTest)
gtest_discover_tests(TEST WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests)
