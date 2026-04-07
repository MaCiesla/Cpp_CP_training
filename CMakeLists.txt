cmake_minimum_required(VERSION 3.14)
project(JsonConfigParser VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL" CACHE STRING "" FORCE)
endif()

include(FetchContent)

# Fetch nlohmann/json
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Fetch GoogleTest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(gmock_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.12.1.tar.gz
)
FetchContent_MakeAvailable(googletest)

# Add library
add_library(config_parser src/ConfigParser.cpp)
target_include_directories(config_parser PUBLIC include)
target_link_libraries(config_parser PUBLIC nlohmann_json::nlohmann_json)
set_target_properties(config_parser PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# Add application executable
add_executable(json_config_app src/main.cpp)
target_link_libraries(json_config_app PRIVATE config_parser)
set_target_properties(json_config_app PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# Add tests
enable_testing()
add_executable(config_parser_tests tests/ConfigParserTest.cpp)
target_link_libraries(config_parser_tests PRIVATE config_parser gtest_main)
set_target_properties(config_parser_tests PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
add_test(NAME ConfigParserTests COMMAND config_parser_tests)