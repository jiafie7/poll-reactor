cmake_minimum_required(VERSION 3.19)

project(poll-reactor)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-g -O2 -Wall -Werror -Wno-unused)

include_directories(./)

file(GLOB_RECURSE SOURCES "utility/*.cpp" "socket/*.cpp" "thread/*.cpp" "task/*.cpp" "frame/*.cpp")

add_executable(server ${SOURCES} server.cpp)
add_executable(client ${SOURCES} client.cpp)
