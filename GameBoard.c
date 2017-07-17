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

    // set Rooks:
    setPieceAt(1,'A',gameBoard,makePiece(Rook,playerColor));
    setPieceAt(1,'H',gameBoard,makePiece(Rook,playerColor));
    setPieceAt(8,'A',gameBoard,makePiece(Rook,opponentColor));
    setPieceAt(8,'H',gameBoard,makePiece(Rook,opponentColor));

    // set Knights:
    setPieceAt(1,'B',gameBoard,makePiece(Knight,playerColor));
    setPieceAt(1,'G',gameBoard,makePiece(Knight,playerColor));
    setPieceAt(8,'B',gameBoard,makePiece(Knight,opponentColor));
    setPieceAt(8,'G',gameBoard,makePiece(Knight,opponentColor));

    // set Bishops:
    setPieceAt(1,'C',gameBoard,makePiece(Bishop,playerColor));
    setPieceAt(1,'F',gameBoard,makePiece(Bishop,playerColor));
    setPieceAt(8,'C',gameBoard,makePiece(Bishop,opponentColor));
    setPieceAt(8,'F',gameBoard,makePiece(Bishop,opponentColor));


    // set King and Queen according to Queen on same color convention
    if(playerColor == White) // Player's Queen is on White!
    {
        setPieceAt(1,'D',gameBoard,makePiece(Queen,playerColor));
        setPieceAt(1,'E',gameBoard,makePiece(King,playerColor));
        setPieceAt(8,'D',gameBoard,makePiece(Queen,opponentColor));
        setPieceAt(8,'E',gameBoard,makePiece(King,opponentColor));
    }
    else // Player's Queen is on Black!
    {
        setPieceAt(1,'E',gameBoard,makePiece(Queen,playerColor));
        setPieceAt(1,'D',gameBoard,makePiece(King,playerColor));
        setPieceAt(8,'E',gameBoard,makePiece(Queen,opponentColor));
        setPieceAt(8,'D',gameBoard,makePiece(King,opponentColor));
    }
}
