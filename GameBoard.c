//
// Created by Jonathan on 7/18/2017.
//


#include "GameBoard.h"
#include "Pieces.h"

// assumes row: 1-8, and col: A-H
int rowColAsIndex(int row, char col)
{
    return 8*(row-1) + (col - 'A') - 1;
}

Piece * getPieceAt(int row, char col, GameBoard * gameBoard)
{
    return gameBoard->gameState[rowColAsIndex(row,col)];
}

void setPieceAt(int row, char col, GameBoard * gameBoard, Piece * piece)
{
    gameBoard->gameState[rowColAsIndex(row,col)] = piece;
}

void removePieceAt(int row, char col, GameBoard * gameBoard)
{
    gameBoard->gameState[rowColAsIndex(row,col)] = NULL;
}
