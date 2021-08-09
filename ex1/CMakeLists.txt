cmake_minimum_required(VERSION 2.8.12.2)
project(AP1)

set(CMAKE_CXX_STANDARD 11)

add_executable(AP1 main.cpp Iris.h Iris.cpp main.h utils.cpp utils.h
        KnnClassifier.h)
