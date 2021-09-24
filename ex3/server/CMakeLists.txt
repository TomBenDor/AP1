cmake_minimum_required(VERSION 2.8.12.2)

project(Server)

add_executable(Server main.cpp KnnClassifier.h Classifiable.h Iris.h
        Iris.cpp ../utils.h ../utils.cpp TCPServer.cpp TCPServer.h metrics/Distance.h
        metrics/EuclideanDistance.h metrics/ChebyshevDistance.h metrics/ManhattanDistance.h commands/Command.h
        IO/DefaultIO.h commands/UploadUnclassifiedCommand.h IO/StandardIO.cpp
        IO/StandardIO.h commands/ChangeAlgoSettingsCommand.h IO/SocketIO.cpp IO/SocketIO.h ConfusionMatrix.cpp ConfusionMatrix.h commands/ConfusionMatrixCommand.h
        ClientData.h commands/ClassifyDataCommand.h)
