//
// Created by Jonathan on 7/19/2017.
//

#include <stdlib.h>
#include "consoleRendering.h"


/*
 * according to specifications in PDF
 */
void printBoard(GameBoard *gameBoard, Color player1Color) {
	char row, col;
	Piece *tempPiece = malloc(sizeof(Piece));
	if (tempPiece == NULL) {
		printf(MALLOC_ERROR);
		return;
	}
	for (row = '8'; row >= '1'; --row) {
		printf("%c| ", row);
		for (col = 'A'; col <= 'H'; ++col) {
			if (getPieceAt(row, col, gameBoard, tempPiece) == FAIL) {
				printf("_ ");
			} else {
				printf("%c ", getPieceChar(tempPiece, player1Color));
			}
		}
		printf("|\n");
	}
	printf("  -----------------\n");
	printf("   A B C D E F G H\n");

	free(tempPiece);
}

/*
 * black -> white
 * white -> black
 */
Color getOppositeColor(Color color) {
	if (color == White) {
		return Black;
	} else {
		return White;
	}
}

/*
 * get chars according to conventions: black is upper case
 */
char getPieceChar(Piece * piece, Color player1Color) {
	PieceType type = piece->type;
	char c;
	switch (type) {
	case Pawn:
		c = 'm';
		break;
	case Bishop:
		c = 'b';
		break;
	case Rook:
		c = 'r';
		break;
	case Knight:
		c = 'n';
		break;
	case Queen:
		c = 'q';
		break;
	case King:
		c = 'k';
		break;
	default:
		return '_'; // this should never happen...
	}
	Player piecePlayer = piece->player;
	if ((piecePlayer == Player1 && player1Color == Black) || (piecePlayer
			== Player2 && player1Color == White)) {
		c = toupper(c);
	}

	return c;
}
