//
// Created by Jonathan on 7/18/2017.
//

#ifndef CHESSPROJECT_GAMEBOARD_H
#define CHESSPROJECT_GAMEBOARD_H

#include <stdio.h>
#include "Pieces.h"
#define NUM_ROWS 8

typedef struct GameBoard {
    Piece *gameState [NUM_ROWS * NUM_ROWS]; // 64 lengthed array, indeces 0-7 correspond to 1A - 1H, 8-15 to 2A-2H and so on

} GameBoard;

// assumes row: 1-8, and col: A-H
Piece * getPieceAt(int row, char col, GameBoard *gameBoard);
void setPieceAt(int row, char col, GameBoard *gameBoard, Piece * piece);
void removePieceAt(int row, char col, GameBoard *gameBoard);
int rowColAsIndex(int row, char col);

GameBoard *makeGameBoard(Color playerColor);
void printBoard(GameBoard *gameBoard);

#endif //CHESSPROJECT_GAMEBOARD_H
