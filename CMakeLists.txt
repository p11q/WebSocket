cmake_minimum_required(VERSION 3.27)

project(WebSocket)

set(CMAKE_CXX_STANDARD 17)

add_executable(WebSocket main.cpp)

add_subdirectory(WS_tests)

find_package(Boost 1.85.0 PATHS  "/home/user/Projects/C++/WebSocket/dep")

target_include_directories(WebSocket PUBLIC "/home/user/Projects/C++/WebSocket/dep/boost/include")
