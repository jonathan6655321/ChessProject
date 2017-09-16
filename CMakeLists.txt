cmake_minimum_required(VERSION 3.7.2)
project(ChessProject)

set(CMAKE_CXX_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
set(GCC_COVERAGE_LINK_FLAGS    "-lgcov")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

INCLUDE_DIRECTORIES("C:\\SDL2-2.0.5\\x86_64-mingw32\\include\\SDL2")

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
        Pieces.h
        CommandLineCommands.h MiniMaxAlgorithm.h MiniMax.h MiniMax.c)

add_executable(ChessProject ${SOURCE_FILES})