/*
 * Pieces.h
 *
 *  Created on: Jul 18, 2017
 *      Author: Jonathan
 */

#ifndef PIECES_H_
#define PIECES_H_

#include <ctype.h>

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

typedef struct Piece {
	PieceType type;
	Color color;
} Piece;

char getPieceChar(Piece *piece);


#endif /* PIECES_H_ */
