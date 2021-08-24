cmake_minimum_required(VERSION 2.8.12.2)
project(Server)
project(Client)

set(CMAKE_CXX_STANDARD 11)

add_executable(Server server/main.cpp server/KnnClassifier.h server/Classifiable.h server/Classifier.h server/Iris.h
        server/Iris.cpp server/UDPServer.h server/UDPServer.cpp utils.h utils.cpp server/TCPServer.cpp server/TCPServer.h)
add_executable(Client client/main.cpp utils.h utils.cpp client/UDPClient.cpp client/UDPClient.h)
