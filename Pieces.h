/*
 * Pieces.h
 *
 *  Created on: Jul 18, 2017
 *      Author: Jonathan
 */

#ifndef PIECES_H_
#define PIECES_H_

#include <ctype.h>
#include "constants.h"

typedef enum PieceType {
	Pawn = 'm', // simple soldier
	Bishop = 'b', // "rats"
	Rook = 'r', // "tsariah"
	Knight = 'n', // "sus"
	Queen = 'q',
	King = 'k',
	None = '_'
} PieceType;

/*
 * Player 1 is always the user. Player 2 can be the cpu or another user.
 * this is used to determine ownership of piece and direction pawns can move.
 * Player 1 always starts with pieces at rows 1,2
 */
typedef enum Player {
	Player1, Player2
} Player;

typedef struct Piece {
	PieceType type;
	Player player;
} Piece;

// sets all paramaters
void initPiece(Piece *piece, PieceType type, Player player);

/*
 * returns the other player
 */
Player getOtherPlayer(Player player);

#endif /* PIECES_H_ */

