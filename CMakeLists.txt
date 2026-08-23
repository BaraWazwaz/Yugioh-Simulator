cmake_minimum_required(VERSION 3.15)
project(Yugioh-Simulator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

add_executable(program ${SOURCES} ${HEADERS})

target_include_directories(program PRIVATE include)
