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
            return getLegalMovesForPawnAt(row,col,gameBoard,legalMoves);
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


int getLegalMovesForPawnAt(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves)
{
    int pieceAtDestinationIndex;
    if(isPlayer1Index(getIndexOfPieceAt(row,col,gameBoard)) == SUCCESS)
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
        pieceAtDestinationIndex = getIndexOfPieceAt(row+1,col+1,gameBoard);
        if (pieceAtDestinationIndex >= 0 && isPlayer1Index(pieceAtDestinationIndex) == FAIL)
        {
            setMoveValid(row+1,col+1,legalMoves);
        }
        pieceAtDestinationIndex = getIndexOfPieceAt(row+1,col-1,gameBoard);
        if (pieceAtDestinationIndex >= 0 && isPlayer1Index(pieceAtDestinationIndex) == FAIL)
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
        pieceAtDestinationIndex = getIndexOfPieceAt(row-1,col+1,gameBoard);
        if (pieceAtDestinationIndex >= 0 && isPlayer1Index(pieceAtDestinationIndex) == SUCCESS)
        {
            setMoveValid(row-1,col+1,legalMoves);
        }
        pieceAtDestinationIndex = getIndexOfPieceAt(row-1,col-1,gameBoard);
        if (pieceAtDestinationIndex >= 0 && isPlayer1Index(pieceAtDestinationIndex) == SUCCESS)
        {
            setMoveValid(row-1,col-1,legalMoves);
        }
    }
    return SUCCESS;
}

void setLegalMovesDiagonals(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves)
{
    setRightUpDiagonal(row,col,gameBoard, legalMoves);
    setLeftUpDiagonal(row,col,gameBoard, legalMoves);
    setRightDownDiagonal(row,col,gameBoard, legalMoves);
    setLeftDownDiagonal(row,col,gameBoard, legalMoves);
}

void setRightUpDiagonal(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves)
{
    int k = 1;
    int pieceIndex = getIndexOfPieceAt(row,col,gameBoard);
    int tempPieceIndex;
    while(isValidRowCol(row+k,col+k) == SUCCESS)
    {
        tempPieceIndex = getIndexOfPieceAt(row+k,col+k,gameBoard);
        if (tempPieceIndex == NO_PIECE)
        {
            setMoveValid(row+k, col+k,legalMoves);
        }
        else
        {
            if (isSamePlayerPiece(pieceIndex,tempPieceIndex) == FAIL)
            {
                setMoveValid(row+k, col+k,legalMoves);
            }
            break;
        }
        ++k;
    }
}
void setLeftUpDiagonal(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves)
{
    int k = 1;
    int pieceIndex = getIndexOfPieceAt(row,col,gameBoard);
    int tempPieceIndex;
    while(isValidRowCol(row+k,col-k) == SUCCESS)
    {
        tempPieceIndex = getIndexOfPieceAt(row+k,col-k,gameBoard);
        if (tempPieceIndex == NO_PIECE)
        {
            setMoveValid(row+k, col-k,legalMoves);
        }
        else
        {
            if (isSamePlayerPiece(pieceIndex,tempPieceIndex) == FAIL)
            {
                setMoveValid(row+k, col-k,legalMoves);
            }
            break;
        }
        ++k;
    }
}
void setRightDownDiagonal(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves)
{
    int k = 1;
    int pieceIndex = getIndexOfPieceAt(row,col,gameBoard);
    int tempPieceIndex;
    while(isValidRowCol(row-k,col+k) == SUCCESS)
    {
        tempPieceIndex = getIndexOfPieceAt(row-k,col+k,gameBoard);
        if (tempPieceIndex == NO_PIECE)
        {
            setMoveValid(row-k, col+k,legalMoves);
        }
        else
        {
            if (isSamePlayerPiece(pieceIndex,tempPieceIndex) == FAIL)
            {
                setMoveValid(row-k, col+k,legalMoves);
            }
            break;
        }
        ++k;
    }
}
void setLeftDownDiagonal(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves)
{
    int k = 1;
    int pieceIndex = getIndexOfPieceAt(row,col,gameBoard);
    int tempPieceIndex;
    while(isValidRowCol(row-k,col-k) == SUCCESS)
    {
        tempPieceIndex = getIndexOfPieceAt(row-k,col-k,gameBoard);
        if (tempPieceIndex == NO_PIECE)
        {
            setMoveValid(row-k, col-k,legalMoves);
        }
        else
        {
            if (isSamePlayerPiece(pieceIndex,tempPieceIndex) == FAIL)
            {
                setMoveValid(row-k, col-k,legalMoves);
            }
            break;
        }
        ++k;
    }
}

/*
 * used in Queen and rook
 */
void setLegalStraightMoves(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves)
{
    setLegalStraightMovesRight(row, col, gameBoard,legalMoves);
    setLegalStraightMovesLeft(row, col, gameBoard,legalMoves);
    setLegalStraightMovesUp(row, col, gameBoard,legalMoves);
    setLegalStraightMovesDown(row, col, gameBoard,legalMoves);
}
void setLegalStraightMovesRight(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves)
{
    int k = 1;
    int pieceIndex = getIndexOfPieceAt(row,col,gameBoard);
    int tempPieceIndex;
    while(isValidRowCol(row,col+k) == SUCCESS)
    {
        tempPieceIndex = getIndexOfPieceAt(row,col+k,gameBoard);
        if (tempPieceIndex == NO_PIECE)
        {
            setMoveValid(row, col+k,legalMoves);
        }
        else
        {
            if (isSamePlayerPiece(pieceIndex,tempPieceIndex) == FAIL)
            {
                setMoveValid(row, col+k,legalMoves);
            }
            break;
        }
        ++k;
    }
}
void setLegalStraightMovesLeft(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves)
{
    int k = 1;
    int pieceIndex = getIndexOfPieceAt(row,col,gameBoard);
    int tempPieceIndex;
    while(isValidRowCol(row,col-k) == SUCCESS)
    {
        tempPieceIndex = getIndexOfPieceAt(row,col-k,gameBoard);
        if (tempPieceIndex == NO_PIECE)
        {
            setMoveValid(row, col-k,legalMoves);
        }
        else
        {
            if (isSamePlayerPiece(pieceIndex,tempPieceIndex) == FAIL)
            {
                setMoveValid(row, col-k,legalMoves);
            }
            break;
        }
        ++k;
    }
}

void setLegalStraightMovesUp(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves)
{
    int k = 1;
    int pieceIndex = getIndexOfPieceAt(row,col,gameBoard);
    int tempPieceIndex;
    while(isValidRowCol(row+k,col) == SUCCESS)
    {
        tempPieceIndex = getIndexOfPieceAt(row+k,col,gameBoard);
        if (tempPieceIndex == NO_PIECE)
        {
            setMoveValid(row+k,col,legalMoves);
        }
        else
        {
            if (isSamePlayerPiece(pieceIndex,tempPieceIndex) == FAIL)
            {
                setMoveValid(row+k,col,legalMoves);
            }
            break;
        }
        ++k;
    }
}
void setLegalStraightMovesDown(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves)
{
    int k = 1;
    int pieceIndex = getIndexOfPieceAt(row,col,gameBoard);
    int tempPieceIndex;
    while(isValidRowCol(row-k,col) == SUCCESS)
    {
        tempPieceIndex = getIndexOfPieceAt(row-k,col,gameBoard);
        if (tempPieceIndex == NO_PIECE )
        {
            setMoveValid(row-k,col,legalMoves);
        }
        else
        {
            if (isSamePlayerPiece(pieceIndex,tempPieceIndex) == FAIL)
            {
                setMoveValid(row-k,col,legalMoves);
            }
            break;
        }
        ++k;
    }
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