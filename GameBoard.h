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
#define FIRST_ROW_CHAR '1'
#define LAST_ROW_CHAR '8'
#define FIRST_COL_CHAR 'A'
#define LAST_COL_CHAR 'H'

#define NUM_STARTING_PIECES 32
#define FIRST_PLAYER_1_PIECE_INDEX 0
#define LAST_PLAYER_1_PIECE_INDEX 15
#define FIRST_PLAYER_2_PIECE_INDEX 16
#define LAST_PLAYER_2_PIECE_INDEX 31
#define NO_PIECE -2
#define NOT_IN_GAME -1

#define PLAYER_1_QUEEN_INDEX 3
#define PLAYER_1_KING_INDEX 4
#define PLAYER_1_ROOK_1 0
#define PLAYER_1_ROOK_2 7
#define PLAYER_1_KNIGHT_1 1
#define PLAYER_1_KNIGHT_2 6
#define PLAYER_1_BISHOP_1 2
#define PLAYER_1_BISHOP_2 5
#define PLAYER_1_FIRST_PAWN 8
#define PLAYER_1_LAST_PAWN 15

#define PLAYER_2_QUEEN_INDEX 27
#define PLAYER_2_KING_INDEX 28
#define PLAYER_2_ROOK_1 24
#define PLAYER_2_ROOK_2 31
#define PLAYER_2_KNIGHT_1 25
#define PLAYER_2_KNIGHT_2 30
#define PLAYER_2_BISHOP_1 26
#define PLAYER_2_BISHOP_2 29
#define PLAYER_2_FIRST_PAWN 16
#define PLAYER_2_LAST_PAWN 23

typedef struct GameBoard {
    /*
     * each location holds the index of the piece in it.
     */
    int mapLocationOnBoardToPieceIndex[BOARD_SIZE];
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
    Black = '0',
    White = '1'
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
int getPieceFromLocationIndex(GameBoard *gameBoard, int locationIndex, Piece *piece);

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

/*
 *
 */
int isSamePlayerPiece(int piece1Index, int piece2Index);

/*
 * returns current location of pieceIndex
 * returns NOT_IN_GAME if was eaten at any point
 */
int getLocationIndexForPieceIndex(GameBoard *gameBoard, int pieceIndex);

/*
 * used for undo, assumes piece is not on the board now.
 * fails player has max amount of this kind of piece.
 */
int getPieceIndexFromPiece(GameBoard *gameBoard, Piece *piece);

/*!
 *
 * @param i
 * @return '1' to '8'
 */
char getRowFromLocationIndex(int i);

/*!
 *
 * @param i
 * @return 'A' to 'H'
 */
char getColFromLocationIndex(int i);

/*
 * gets player and returns the relevant index.
 */
int getFirstPieceIndexForPlayer(Player player);
int getLastPieceIndexForPlayer(Player player);

/*
 * these help with scoring function
 * return  the number of pieces by type for certain player
 */
int numPawns(GameBoard *gameBoard, Player player);
int numKnights(GameBoard *gameBoard, Player player);
int numBishops(GameBoard *gameBoard, Player player);
int numRooks(GameBoard *gameBoard, Player player);
int numQueens(GameBoard *gameBoard, Player player);
int numKings(GameBoard *gameBoard, Player player);

int isValidLocationIndex(int i);

/*
 * assumes gameboard is valid, aka NOT_IN_GAME and NOT_A_PIECE in appropriate places
 * gets lowercase (white) or upper case (black) char
 * returns an index of the piece which fits this char
 * priority goes to NOT_IN_GAME pieceIndex
 */
int getPieceIndexFromPieceChar(GameBoard *gameBoard, char pieceChar, Color player1Color);

/*
 * simply this:
 */
PieceType getTypeFromChar(char pieceChar);

void initEmptyGame(GameBoard *gameBoard);

#endif //CHESSPROJECT_GAMEBOARD_H
