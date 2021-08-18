cmake_minimum_required(VERSION 2.8.12.2)
project(Server)
project(Client)

set(CMAKE_CXX_STANDARD 11)

add_executable(Server server/main.cpp)
add_executable(Client client/main.cpp)
