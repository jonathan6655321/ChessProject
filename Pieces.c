/*
 * Pieces.c
 *
 *  Created on: Jul 18, 2017
 *      Author: Jonathan
 */
#include <stdlib.h>
#include "Pieces.h"

char getPieceChar(Piece * piece)
{
	PieceType type = piece->type;
	Color color = piece->color;
	char c;
	switch (type)
	{
		case Pawn: c = 'm';
			break;
		case Bishop: c = 'b';
			break;
		case Rook: c = 'r';
			break;
		case Knight: c = 'n';
			break;
		case Queen: c = 'q';
			break;
		case King: c = 'k';
			break;
		default:
			return 'X'; // so we can recognize the erro TODO X?
	}
	if(color == Black)
	{
		c = toupper(c);
	}

	return c;
}

Piece *makePiece(PieceType type, Color color)
{
    Piece *piece = malloc(sizeof(Piece));
    piece->type = type;
    piece->color = color;
    return piece;
}

Color getOppositeColor(Color color)
{
    if(color == White)
    {
        return Black;
    }
    else
    {
        return White;
    }
}