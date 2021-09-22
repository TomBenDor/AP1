cmake_minimum_required(VERSION 2.8.12.2)
project(Server)
project(Client)

set(CMAKE_CXX_STANDARD 11)

add_executable(Server server/main.cpp server/KnnClassifier.h server/Classifiable.h server/Iris.h
        server/Iris.cpp utils.h utils.cpp server/TCPServer.cpp server/TCPServer.h server/metrics/Distance.h
        server/metrics/EuclideanDistance.h server/metrics/ChebyshevDistance.h server/metrics/ManhattanDistance.h server/commands/Command.h
        server/DefaultIO.h server/commands/Command.cpp server/commands/UploadUnclassified.cpp server/commands/UploadUnclassified.h server/StandardIO.cpp
        server/StandardIO.h server/commands/ChangeAlgoSettings.h)
add_executable(Client client/main.cpp utils.h utils.cpp client/TCPClient.cpp
        client/TCPClient.h)
