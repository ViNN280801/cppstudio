cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(BinaryTree
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wextra")

add_executable(main main.cpp BinaryTree.cpp)
