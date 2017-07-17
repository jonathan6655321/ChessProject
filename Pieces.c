/*
 * Pieces.c
 *
 *  Created on: Jul 18, 2017
 *      Author: Jonathan
 */
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
			return 'X'; // so we can recognize the erro TODO is there something better than this?
	}
	if(color == Black)
	{
		c = toupper(c);
	}

	return c;
}

