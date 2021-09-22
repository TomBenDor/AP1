cmake_minimum_required(VERSION 2.8.12.2)

project(Client)

add_executable(Client main.cpp ../utils.h ../utils.cpp TCPClient.cpp TCPClient.h)