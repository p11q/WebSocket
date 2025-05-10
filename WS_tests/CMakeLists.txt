find_package(Catch2 3 REQUIRED PATHS "/home/user/Projects/C++/WebSocket/dep/libs" "/home/user/Projects/C++/WebSocket/includes") # Указали версию Catch и пути к файлам

add_executable(WS_tests_run WS_test.cpp)

target_include_directories(WS_tests_run PUBLIC "/home/user/Projects/C++/WebSocket/dep/catch/include" "/home/user/Projects/C++/WebSocket/includes") # Указали пути к includes

target_link_libraries(WS_tests_run PUBLIC Catch2::Catch2WithMain)

