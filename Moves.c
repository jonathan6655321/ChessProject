//
// Created by Jonathan on 7/20/2017.
//


#include "Moves.h"


/*
 * make sure legal moves is 0 initialized!!!
 */
int getLegalMovesForPieceAt(char row, char col, GameBoard *gameBoard,LegalMoves *legalMoves)
{
    if(isValidRowCol(row,col) == FAIL)
    {
        return FAIL;
    }

    Piece piece;
    if (getPieceAt(row,col,gameBoard,&piece) == FAIL)
    {
        return FAIL;
    }

    switch (piece.type)
    {
        case Pawn:
            return getLegalMovesForPawnAt(row,col,gameBoard,&piece,legalMoves);
//        case Bishop:
//            return getLegalMovesForBishopAt(row,col,gameBoard,legalMoves);
//        case Rook:
//            return getLegalMovesForRookAt(row,col,gameBoard,legalMoves);
//        case Knight:
//            return getLegalMovesForKnighAt(row,col,gameBoard,legalMoves);
//        case Queen:
//            return getLegalMovesForQueenAt(row,col,gameBoard,legalMoves);
//        case King:
//            return getLegalMovesForKingAt(row,col,gameBoard,legalMoves);
        default:
            return FAIL; // this should never happen...
    }
}


int getLegalMovesForPawnAt(char row,char col,GameBoard *gameBoard, Piece *piece, LegalMoves *legalMoves)
{
    int i;
    if(piece->player == Player1)
    {
        // moves forward:
        if(getIndexOfPieceAt(row+1,col,gameBoard) == NO_PIECE)
        {
            setMoveValid(row+1,col,legalMoves);
            // didn't move, can move twice
            if (row == '2' && getIndexOfPieceAt(row+2,col,gameBoard) == NO_PIECE)
            {
                setMoveValid(row+2,col,legalMoves);
            }
        }

        // diagonals:
        i = getIndexOfPieceAt(row+1,col+1,gameBoard);
        if (i >= 0 && isPlayer1Index(i) == FAIL)
        {
            setMoveValid(row+1,col+1,legalMoves);
        }
        i = getIndexOfPieceAt(row+1,col-1,gameBoard);
        if (i >= 0 && isPlayer1Index(i) == FAIL)
        {
            setMoveValid(row+1,col-1,legalMoves);
        }
    }
    else
    {
        // moves forward:
        if(getIndexOfPieceAt(row-1,col,gameBoard) == NO_PIECE)
        {
            setMoveValid(row-1,col,legalMoves);
            // didn't move, can move twice
            if (row == '7' && getIndexOfPieceAt(row-2,col,gameBoard) == NO_PIECE)
            {
                setMoveValid(row-2,col,legalMoves);
            }
        }

        // diagonals:
        i = getIndexOfPieceAt(row-1,col+1,gameBoard);
        if (i >= 0 && isPlayer1Index(i) == SUCCESS)
        {
            setMoveValid(row-1,col+1,legalMoves);
        }
        i = getIndexOfPieceAt(row-1,col-1,gameBoard);
        if (i >= 0 && isPlayer1Index(i) == SUCCESS)
        {
            setMoveValid(row-1,col-1,legalMoves);
        }
    }
    return SUCCESS;
}


void setMoveValid(char row, char col,LegalMoves *legalMoves)
{
    legalMoves->legalMovesArray[rowColToLocationIndex(row,col)] = VALID_MOVE;
}


void printLegalMoves(LegalMoves *legalMoves)
{
    for (char row = '8'; row >='1' ; --row)
    {
        printf("%c| ", row);
        for (char col = 'A'; col <= 'H'; ++col)
        {
            if(legalMoves->legalMovesArray[rowColToLocationIndex(row,col)] == INVALID_MOVE)
            {
                printf("_ ");
            }
            else
            {
                printf("X ");
            }
        }
        printf("|\n");
    }
    printf("  -----------------\n");
    printf("   A B C D E F G H\n");
}