//
// Created by Jonathan on 7/20/2017.
//

#ifndef CHESSPROJECT_MOVES_H
#define CHESSPROJECT_MOVES_H

#include "GameBoard.h"

#define VALID_MOVE 1
#define INVALID_MOVE 0

typedef struct LegalMoves
{
    /*
     * 0,1 array which holds all legal moves for a piece
     * 1 is legal
     * 0 is illegal
     *
     * legal means: you can move the piece there.
     * takes into account pieces on the way, and piece type
     */
    int legalMovesArray[BOARD_SIZE];
}LegalMoves;


/*
 * sets legalMoves to hold legal moves for piece at row col
 * fails if no piece at row col
 * fails if row col invalid
 */
int getLegalMovesForPieceAt(char row,char col,GameBoard *gameBoard,LegalMoves *legalMoves);

/*
 * used in getLegalMovesForPieceAt
 */
int getLegalMovesForPawnAt(char row,char col,GameBoard *gameBoard, Piece *piece, LegalMoves *legalMoves);
int getLegalMovesForBishopAt(char row, char col, GameBoard *gameBoard, LegalMoves *legalMoves);
int getLegalMovesForRookAt(char row, char col, GameBoard *gameBoard, LegalMoves *legalMoves);
int getLegalMovesForKnighAt(char row, char col, GameBoard *gameBoard, LegalMoves *legalMoves);
int getLegalMovesForQueenAt(char row, char col, GameBoard *gameBoard, LegalMoves *legalMoves);
int getLegalMovesForKingAt(char row, char col, GameBoard *gameBoard, LegalMoves *legalMoves);

void setMoveValid(char row, char col,LegalMoves *legalMoves);

/*
 * prints the board with the valid moves of the piece
 */
void printLegalMoves(LegalMoves *legalMoves);

#endif //CHESSPROJECT_MOVES_H
