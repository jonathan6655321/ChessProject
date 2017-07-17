//
// Created by Jonathan on 7/18/2017.
//


#include <stdlib.h>
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
    free(gameBoard->gameState[rowColAsIndex(row,col)]);
    gameBoard->gameState[rowColAsIndex(row,col)] = NULL;
}

GameBoard *makeGameBoard(Color playerColor)
{
    GameBoard *gameBoard = malloc(sizeof(GameBoard)); // sets all pointers to NULL
    Color opponentColor = getOppositeColor(playerColor);

    // set pawns
    for (char col='A'; col <= 'H' ; col++)
    {
        setPieceAt(2,col,gameBoard, makePiece(Pawn,playerColor));
        setPieceAt(7,col,gameBoard, makePiece(Pawn,opponentColor));
    }

    
}
