/*
 * Pieces.h
 *
 *  Created on: Jul 18, 2017
 *      Author: Jonathan
 */

#ifndef PIECES_H_
#define PIECES_H_

#include <ctype.h>
#include "GameBoard.h"
#include "constants.h"

typedef enum PieceType  {
	Pawn, // simple soldier
	Bishop, // "rats"
	Rook, // "tsariah"
	Knight, // "sus"
	Queen,
	King
} PieceType;

typedef enum Color{
	Black,
	White
}Color;
Color getOppositeColor(Color color);

typedef struct Position{
    int row;
    char col;
}Position;


/*
 * Player 1 is always the user. Player 2 can be the cpu or another user.
 * this is used to determine ownership of piece and direction pawns can move.
 * Player 1 always starts with pieces at rows 1,2
 */
typedef enum Player {
    Player1,
    Player2
}Player;

typedef struct Piece {
	PieceType type;
    Player player;
    Color color;
    Position currentPosition;

    // all moves which comply with board boundaries and piece type.
    // NOTE: does not take into account pieces on the board blocking the movement.
    int numPossibleMoves;
    Position possibleMoves[BOARD_SIZE];
} Piece;

// get the char representing the piece, based on color and type
char getPieceChar(Piece *piece);

// set all paramaters, including possible moves
int initPiece(Piece *piece, PieceType type, Color color, int row, char col, Player player);

// assumes all fields in piece were initialized before call.
int setPossibleMoves(Piece *piece);

#endif /* PIECES_H_ */


