find_package(Catch2 3 REQUIRED PATHS "/home/User/Projects/C++/WebSocket/libs" "/home/User/Projects/C++/WebSocket") # Указали версию Catch и пути к файлам

add_executable(WS_tests_run WS_test.cpp)

target_include_directories(WS_tests_run PUBLIC "/home/User/Projects/C++/WebSocket/libs/include" "/home/User/Projects/C++/WebSocket") # Указали пути к includes

target_link_libraries(WS_tests_run PUBLIC Catch2::Catch2WithMain)

