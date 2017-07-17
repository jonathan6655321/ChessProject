cmake_minimum_required(VERSION 3.7)
project(ChessProject)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Pieces.c
        Pieces.h GameBoard.c GameBoard.h)

add_executable(ChessProject ${SOURCE_FILES})