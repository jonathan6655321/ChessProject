//
// Created by Jonathan on 7/18/2017.
//

#ifndef CHESSPROJECT_GAMEBOARD_H
#define CHESSPROJECT_GAMEBOARD_H

#include <stdio.h>
#include "Pieces.h"
#define NUM_ROWS 8
#define NUM_COLS NUM_ROWS
#define BOARD_SIZE NUM_COLS*NUM_ROWS

#define NUM_STARTING_PIECES 32
#define NO_PIECE -2
#define NOT_IN_GAME -1

typedef struct GameBoard {
    /*
     * each location holds the index of the piece in it.
     */
    int mapLocationOnBoardToPieceIndex[NUM_ROWS*NUM_COLS];
    int mapPieceIndexToLocationOnBoard[NUM_STARTING_PIECES];
} GameBoard;


/*
 * receives an index from 0-31 and inits piece to hold the player and type of this index
 * indexes 0-15 hold Player 1 pieces
 * indexes 16-31 hold Player 2 pieces
 * in both, the order is isomorphic to the initial game ordering.
 * 0-7 hold Player 1: Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook.
 * 8-15 hold Player 1: Pawns
 * 16-23 hold Player 2: Pawns
 * 24-31 hold Player 2: Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook.
 */
int getPieceFromIndex(Piece *piece, int i);
Player getPlayerFromIndex(int i); // used in above^
PieceType getTypeFromIndex(int i); // used in above^^

typedef enum Color{
    Black,
    White
}Color;

/*
 * places all pieces on the board
 */
void initGame(GameBoard *gameBoard, Color player1Color);

/*
 * used in initGame in case Player1 is Black
 */
void swapQueenKing(GameBoard *gameBoard);

/*
 * assumes row: 1-8, and col: A-H
 * inits piece to hold the params of the piece in location row col
 * if there is no piece there function returns -1
 */
int getPieceAt(char row, char col, GameBoard *gameBoard, Piece *piece);

/*
 *
 */
int rowColToLocationIndex(char row, char col);
/*
 * checks if row col are legal: row 1-8, col A-H
 */
int isValidRowCol(char row, char col);

/*
 * moves piece and returns the index of the piece in the location arrived at
 * fails if row, col invalid.
 * fails if trying to move a NO_PIECE
 */
int movePiece(char rowFrom, char colFrom, char rowTo, char colTo, GameBoard *gameBoard);

/*
 * set piece of index pieceIndex at location row col
 */
void setPieceAt(char row, char col, GameBoard *gameBoard, int pieceIndex);

/*
 * remove piece at row col
 */
void removePieceAt(char row, char col, GameBoard *gameBoard);

/*
 * returns index of piece at row col
 */
int getIndexOfPieceAt(char row, char col, GameBoard *gameBoard);

/*
 * returns 1 if is
 * 0 if player 2
 *
 * assumes valid index!
 */
int isPlayer1Index(int i);

#endif //CHESSPROJECT_GAMEBOARD_H
