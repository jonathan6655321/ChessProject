//
// Created by Jonathan on 7/18/2017.
//


#include <stdlib.h>
#include "GameBoard.h"
#include "Pieces.h"






































// -----------------------------------------------------------------------------------------------------------------------
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

int initGameBoard(Color playerColor)
{
    GameBoard *gameBoard = (GameBoard*)calloc(1,sizeof(GameBoard)); // sets all pointers to NULL
    if(gameBoard == NULL)
    {
        printf(MALLOC_ERROR);
        return -1;
    }
    Color opponentColor = getOppositeColor(playerColor);
    Piece * currentPiecePointer = gameBoard->allPieces;


    // set pawns
    for (char col='A'; col <= 'H' ; col++)
    {
        setPieceAt(2,col,gameBoard, initPiece(currentPiecePointer++, Pawn, playerColor, 2,col, Player1));
        setPieceAt(7,col,gameBoard, initPiece(currentPiecePointer++, Pawn, opponentColor,7,col,));
    }

    // set Rooks:
    setPieceAt(1,'A',gameBoard, initPiece(currentPiecePointer++, Rook, playerColor, 1,'A',));
    setPieceAt(1,'H',gameBoard, initPiece(currentPiecePointer++, Rook, playerColor,1,'H',));
    setPieceAt(8,'A',gameBoard, initPiece(currentPiecePointer++, Rook, opponentColor,8,'A',));
    setPieceAt(8,'H',gameBoard, initPiece(currentPiecePointer++, Rook, opponentColor,8,'H',));

    // set Knights:
    setPieceAt(1,'B',gameBoard, initPiece(currentPiecePointer++, Knight, playerColor,1,'B',);
    setPieceAt(1,'G',gameBoard, initPiece(currentPiecePointer++, Knight, playerColor,1,'G',));
    setPieceAt(8,'B',gameBoard, initPiece(currentPiecePointer++, Knight, opponentColor,8,'B',));
    setPieceAt(8,'G',gameBoard, initPiece(currentPiecePointer++, Knight, opponentColor,8,'G',));

    // set Bishops:
    setPieceAt(1,'C',gameBoard, initPiece(currentPiecePointer++, Bishop, playerColor,1,'C',));
    setPieceAt(1,'F',gameBoard, initPiece(currentPiecePointer++, Bishop, playerColor,1,'F',));
    setPieceAt(8,'C',gameBoard, initPiece(currentPiecePointer++, Bishop, opponentColor,8,'C',));
    setPieceAt(8,'F',gameBoard, initPiece(currentPiecePointer++, Bishop, opponentColor,8,'F',));


    // set King and Queen according to Queen on same color convention
    if(playerColor == White) // Player's Queen is on White!
    {
        setPieceAt(1,'D',gameBoard, initPiece(currentPiecePointer++, Queen, playerColor,1,'D',));
        setPieceAt(1,'E',gameBoard, initPiece(currentPiecePointer++, King, playerColor,1,'E',));
        setPieceAt(8,'D',gameBoard, initPiece(currentPiecePointer++, Queen, opponentColor,8,'D',));
        setPieceAt(8,'E',gameBoard, initPiece(currentPiecePointer++, King, opponentColor,8,'E',));
    }
    else // Player's Queen is on Black!
    {
        setPieceAt(1,'E',gameBoard, initPiece(currentPiecePointer++, Queen, playerColor,1,'E',));
        setPieceAt(1,'D',gameBoard, initPiece(currentPiecePointer++, King, playerColor,1,'D',));
        setPieceAt(8,'E',gameBoard, initPiece(currentPiecePointer++, Queen, opponentColor,8,'E',));
        setPieceAt(8,'D',gameBoard, initPiece(currentPiecePointer++, King, opponentColor,8,'D',));
    }
}


void printBoard(GameBoard *gameBoard)
{
    Piece *tempPiece;
    for (int row = 8; row >=1 ; --row)
    {
        printf("%d| ", row);
        for (char col = 'A'; col <= 'H'; ++col)
        {
            tempPiece = getPieceAt(row,col,gameBoard);
            if(tempPiece == NULL)
            {
                printf("_ ");
            }
            else
            {
                printf("%c ", getPieceChar(tempPiece));
            }
        }
        printf("|\n");
    }
    printf("  -----------------\n");
    printf("   A B C D E F G H\n");
}