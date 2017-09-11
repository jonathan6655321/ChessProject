/*
 * Pieces.c
 *
 *  Created on: Jul 18, 2017
 *      Author: Jonathan
 */
#include <stdlib.h>
#include "Pieces.h"

void initPiece(Piece *piece, PieceType type, Player player)
{
    piece->player = player;
    piece->type = type;
}

/*
 * returns the other player
 */
Player getOtherPlayer(Player player)
{
    return (player == Player1)?Player2:Player1;
}


































/*
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
			return 'X'; // this should never happen...
	}
	if(color == Black)
	{
		c = toupper(c);
	}

	return c;
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

int setPossibleMoves(Piece *piece)
{
    PieceType type = piece->type;
    switch (type)
    {
        case Pawn: return setPossibleMovesPawn(piece);
        case Bishop: return setPossibleMovesBishop(piece);
        case Rook: return setPossibleMovesRook(piece);
        case Knight: return setPossibleMovesKnight(piece);
        case Queen: return setPossibleMovesQueen(piece);
        case King: return setPossibleMovesKing(piece);
        default:
            return -1; // this should never happen...
    }
}

 */