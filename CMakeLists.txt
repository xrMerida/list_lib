cmake_minimum_required(VERSION 3.21)
project(List)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES src/*.cpp)
add_library(list_lib src/list.cpp)
target_include_directories(list_lib PUBLIC include/list)

add_executable(list src/main.cpp)
target_link_libraries(list PRIVATE list_lib)
