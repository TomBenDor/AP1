cmake_minimum_required(VERSION 2.8.12.2)

project(Server)

add_executable(Server main.cpp KnnClassifier.h Classifiable.h Iris.h
        Iris.cpp ../utils.h ../utils.cpp TCPServer.cpp TCPServer.h metrics/Distance.h
        metrics/EuclideanDistance.h metrics/ChebyshevDistance.h metrics/ManhattanDistance.h commands/Command.h
        DefaultIO.h commands/Command.cpp commands/UploadUnclassified.cpp commands/UploadUnclassified.h StandardIO.cpp
        StandardIO.h commands/ChangeAlgoSettings.h)