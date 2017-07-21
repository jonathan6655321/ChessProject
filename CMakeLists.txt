cmake_minimum_required(VERSION 3.8)
project(ChessProject)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        CommandLineGame.c
        CommandLineGame.h
        consoleRendering.c
        consoleRendering.h
        constants.h
        Game.c
        Game.h
        GameBoard.c
        GameBoard.h
        main.c
        Messages.h
        Moves.c
        Moves.h
        Parser.c
        Parser.h
        Pieces.c
        Pieces.h CommandLineCommands.h)

add_executable(ChessProject ${SOURCE_FILES})