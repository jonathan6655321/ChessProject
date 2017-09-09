//
// Created by Jonathan on 7/20/2017.
//


#include "Moves.h"


/*
 * gets <x,y> and <i,j> and moves from first to second
 * if x,y or i,j not on board returns: invalidPosition
 * if at position x,y no users piece: returns notYourPiece
 * if is your piece but illegal move request returns: illegalMove
 *
 */
ResponseType executeUserMoveCommand(char rowFrom, char colFrom, char rowTo, char colTo, GameBoard *gameBoard, Player currentPlayer,
                           Piece *pieceDestinationBefore, Piece* pieceAtDestinationAfter)
{
    if (isValidRowCol(rowFrom,colFrom) == FAIL || isValidRowCol(rowTo,colTo) == FAIL)
    {
        return InvalidPosition;
    }
    else
    {
        // trying to move no piece, or enemy piece
        if (getPieceAt(rowFrom,colFrom,gameBoard,pieceAtDestinationAfter) == FAIL ||
                pieceAtDestinationAfter->player != currentPlayer)
        {
            return NotYourPiece;
        }
        else
        {
            LegalMoves legalMoves = {0};
            getLegalMovesForPieceAt(rowFrom,colFrom,gameBoard,&legalMoves);
            if (legalMoves.legalMovesArray[rowColToLocationIndex(rowTo, colTo)] == ILLEGAL_MOVE)
            {
                return IllegalMove;
            }
            else
            {
                if (getPieceAt(rowTo,colTo,gameBoard,pieceDestinationBefore) == FAIL)
                {
                    movePiece(rowFrom,colFrom,rowTo,colTo,gameBoard);
                    return MadeMove;
                }
                else
                {
                    movePiece(rowFrom,colFrom,rowTo,colTo,gameBoard);
                    return AteOpponentsPiece;
                }
            }
        }
    }
}

/*
 * gets row, col and piece from user. and sets the piece in this location.
 * Assumes the piece is not in the game!
 */
int executeSetPieceAt(char row, char col, Piece * piece, GameBoard *gameBoard)
{
    int pieceIndex = getPieceIndexFromPiece(gameBoard,piece);
    if (pieceIndex >= 0)
    {
        setPieceAt(row,col,gameBoard,pieceIndex);
        return SUCCESS;
    }
    else
        return FAIL;
}



/*
 * sets legalMoves to hold legal moves for piece at row col
 * fails if no piece at row col
 * fails if row col invalid
 *
 * MAKE SURE LEGALMOVES is 0 initialized!
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
        case Pawn: getLegalMovesForPawnAt(row,col,gameBoard,legalMoves);
            break;
        case Bishop: getLegalMovesForBishopAt(row,col,gameBoard,legalMoves);
            break;
        case Rook: getLegalMovesForRookAt(row,col,gameBoard,legalMoves);
            break;
        case Knight: getLegalMovesForKnightAt(row, col, gameBoard, legalMoves);
            break;
        case Queen: getLegalMovesForQueenAt(row,col,gameBoard,legalMoves);
            break;
        case King: getLegalMovesForKingAt(row,col,gameBoard,legalMoves);
            break;
        default:
            return FAIL; // this should never happen...
    }
    return SUCCESS;
}


void getLegalMovesForPawnAt(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves)
{
    int pieceAtDestinationIndex;
    if(isPlayer1Index(getIndexOfPieceAt(row,col,gameBoard)) == SUCCESS)
    {
        // moves forward:
        if(getIndexOfPieceAt(row+1,col,gameBoard) == NO_PIECE)
        {
            setMoveLegal(row + 1, col, legalMoves);
            // didn't move, can move twice
            if (row == '2' && getIndexOfPieceAt(row+2,col,gameBoard) == NO_PIECE)
            {
                setMoveLegal(row + 2, col, legalMoves);
            }
        }

        // diagonals:
        pieceAtDestinationIndex = getIndexOfPieceAt(row+1,col+1,gameBoard);
        if (pieceAtDestinationIndex >= 0 && isPlayer1Index(pieceAtDestinationIndex) == FAIL)
        {
            setMoveLegal(row + 1, col + 1, legalMoves);
        }
        pieceAtDestinationIndex = getIndexOfPieceAt(row+1,col-1,gameBoard);
        if (pieceAtDestinationIndex >= 0 && isPlayer1Index(pieceAtDestinationIndex) == FAIL)
        {
            setMoveLegal(row + 1, col - 1, legalMoves);
        }
    }
    else
    {
        // moves forward:
        if(getIndexOfPieceAt(row-1,col,gameBoard) == NO_PIECE)
        {
            setMoveLegal(row - 1, col, legalMoves);
            // didn't move, can move twice
            if (row == '7' && getIndexOfPieceAt(row-2,col,gameBoard) == NO_PIECE)
            {
                setMoveLegal(row - 2, col, legalMoves);
            }
        }

        // diagonals:
        pieceAtDestinationIndex = getIndexOfPieceAt(row-1,col+1,gameBoard);
        if (pieceAtDestinationIndex >= 0 && isPlayer1Index(pieceAtDestinationIndex) == SUCCESS)
        {
            setMoveLegal(row - 1, col + 1, legalMoves);
        }
        pieceAtDestinationIndex = getIndexOfPieceAt(row-1,col-1,gameBoard);
        if (pieceAtDestinationIndex >= 0 && isPlayer1Index(pieceAtDestinationIndex) == SUCCESS)
        {
            setMoveLegal(row - 1, col - 1, legalMoves);
        }
    }
}
void getLegalMovesForBishopAt(char row, char col, GameBoard *gameBoard, LegalMoves *legalMoves)
{
    setLegalMovesDiagonals(row,col,gameBoard,legalMoves);
}
void getLegalMovesForRookAt(char row, char col, GameBoard *gameBoard, LegalMoves *legalMoves)
{
    setLegalStraightMoves(row,col,gameBoard,legalMoves);
}
void getLegalMovesForQueenAt(char row, char col, GameBoard *gameBoard, LegalMoves *legalMoves)
{
    setLegalStraightMoves(row,col,gameBoard,legalMoves);
    setLegalMovesDiagonals(row,col,gameBoard,legalMoves);
}
void getLegalMovesForKnightAt(char row, char col, GameBoard *gameBoard, LegalMoves *legalMoves)
{
    int knightsIndex = getIndexOfPieceAt(row,col,gameBoard);
    if(isValidRowCol(row+2,col+1) == SUCCESS && isSamePlayerPiece(knightsIndex,getIndexOfPieceAt(row+2,col+1,gameBoard))==FAIL)
    {
        setMoveLegal(row + 2, col + 1, legalMoves);
    }
    if(isValidRowCol(row+2,col-1) == SUCCESS && isSamePlayerPiece(knightsIndex,getIndexOfPieceAt(row+2,col-1,gameBoard))==FAIL)
    {
        setMoveLegal(row + 2, col - 1, legalMoves);
    }
    if(isValidRowCol(row-2,col+1) == SUCCESS && isSamePlayerPiece(knightsIndex,getIndexOfPieceAt(row-2,col+1,gameBoard))==FAIL)
    {
        setMoveLegal(row - 2, col + 1, legalMoves);
    }
    if(isValidRowCol(row-2,col-1) == SUCCESS && isSamePlayerPiece(knightsIndex,getIndexOfPieceAt(row-2,col-1,gameBoard))==FAIL)
    {
        setMoveLegal(row - 2, col - 1, legalMoves);
    }
    if(isValidRowCol(row+1,col+2) == SUCCESS && isSamePlayerPiece(knightsIndex,getIndexOfPieceAt(row+1,col+2,gameBoard))==FAIL)
    {
        setMoveLegal(row + 1, col + 2, legalMoves);
    }
    if(isValidRowCol(row+1,col-2) == SUCCESS && isSamePlayerPiece(knightsIndex,getIndexOfPieceAt(row+1,col-2,gameBoard))==FAIL)
    {
        setMoveLegal(row + 1, col - 2, legalMoves);
    }
    if(isValidRowCol(row-1,col-2) == SUCCESS && isSamePlayerPiece(knightsIndex,getIndexOfPieceAt(row-1,col-2,gameBoard))==FAIL)
    {
        setMoveLegal(row - 1, col - 2, legalMoves);
    }
    if(isValidRowCol(row-1,col+2) == SUCCESS && isSamePlayerPiece(knightsIndex,getIndexOfPieceAt(row-1,col+2,gameBoard))==FAIL)
    {
        setMoveLegal(row - 1, col + 2, legalMoves);
    }
}
void getLegalMovesForKingAt(char row, char col, GameBoard *gameBoard, LegalMoves *legalMoves)
{
    int knightsIndex = getIndexOfPieceAt(row,col,gameBoard);
    if(isValidRowCol(row+1,col) == SUCCESS && isSamePlayerPiece(knightsIndex,getIndexOfPieceAt(row+1,col,gameBoard))==FAIL)
    {
        setMoveLegal(row + 1, col, legalMoves);
    }
    if(isValidRowCol(row-1,col) == SUCCESS && isSamePlayerPiece(knightsIndex,getIndexOfPieceAt(row-1,col,gameBoard))==FAIL)
    {
        setMoveLegal(row - 1, col, legalMoves);
    }
    if(isValidRowCol(row,col+1) == SUCCESS && isSamePlayerPiece(knightsIndex,getIndexOfPieceAt(row,col+1,gameBoard))==FAIL)
    {
        setMoveLegal(row, col + 1, legalMoves);
    }
    if(isValidRowCol(row,col-1) == SUCCESS && isSamePlayerPiece(knightsIndex,getIndexOfPieceAt(row,col-1,gameBoard))==FAIL)
    {
        setMoveLegal(row, col - 1, legalMoves);
    }
    if(isValidRowCol(row+1,col+1) == SUCCESS && isSamePlayerPiece(knightsIndex,getIndexOfPieceAt(row+1,col+1,gameBoard))==FAIL)
    {
        setMoveLegal(row + 1, col + 1, legalMoves);
    }
    if(isValidRowCol(row+1,col-1) == SUCCESS && isSamePlayerPiece(knightsIndex,getIndexOfPieceAt(row+1,col-1,gameBoard))==FAIL)
    {
        setMoveLegal(row + 1, col - 1, legalMoves);
    }
    if(isValidRowCol(row-1,col-1) == SUCCESS && isSamePlayerPiece(knightsIndex,getIndexOfPieceAt(row-1,col-1,gameBoard))==FAIL)
    {
        setMoveLegal(row - 1, col - 1, legalMoves);
    }
    if(isValidRowCol(row-1,col+1) == SUCCESS && isSamePlayerPiece(knightsIndex,getIndexOfPieceAt(row-1,col+1,gameBoard))==FAIL)
    {
        setMoveLegal(row - 1, col + 1, legalMoves);
    }
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
            setMoveLegal(row + k, col + k, legalMoves);
        }
        else
        {
            if (isSamePlayerPiece(pieceIndex,tempPieceIndex) == FAIL)
            {
                setMoveLegal(row + k, col + k, legalMoves);
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
            setMoveLegal(row + k, col - k, legalMoves);
        }
        else
        {
            if (isSamePlayerPiece(pieceIndex,tempPieceIndex) == FAIL)
            {
                setMoveLegal(row + k, col - k, legalMoves);
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
            setMoveLegal(row - k, col + k, legalMoves);
        }
        else
        {
            if (isSamePlayerPiece(pieceIndex,tempPieceIndex) == FAIL)
            {
                setMoveLegal(row - k, col + k, legalMoves);
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
            setMoveLegal(row - k, col - k, legalMoves);
        }
        else
        {
            if (isSamePlayerPiece(pieceIndex,tempPieceIndex) == FAIL)
            {
                setMoveLegal(row - k, col - k, legalMoves);
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
            setMoveLegal(row, col + k, legalMoves);
        }
        else
        {
            if (isSamePlayerPiece(pieceIndex,tempPieceIndex) == FAIL)
            {
                setMoveLegal(row, col + k, legalMoves);
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
            setMoveLegal(row, col - k, legalMoves);
        }
        else
        {
            if (isSamePlayerPiece(pieceIndex,tempPieceIndex) == FAIL)
            {
                setMoveLegal(row, col - k, legalMoves);
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
            setMoveLegal(row + k, col, legalMoves);
        }
        else
        {
            if (isSamePlayerPiece(pieceIndex,tempPieceIndex) == FAIL)
            {
                setMoveLegal(row + k, col, legalMoves);
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
            setMoveLegal(row - k, col, legalMoves);
        }
        else
        {
            if (isSamePlayerPiece(pieceIndex,tempPieceIndex) == FAIL)
            {
                setMoveLegal(row - k, col, legalMoves);
            }
            break;
        }
        ++k;
    }
}



void setMoveLegal(char row, char col, LegalMoves *legalMoves)
{
    legalMoves->legalMovesArray[rowColToLocationIndex(row,col)] = LEGAL_MOVE;
}


void printLegalMoves(LegalMoves *legalMoves)
{
    for (char row = '8'; row >='1' ; --row)
    {
        printf("%c| ", row);
        for (char col = 'A'; col <= 'H'; ++col)
        {
            if(legalMoves->legalMovesArray[rowColToLocationIndex(row,col)] == ILLEGAL_MOVE)
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

/*
 * for testing..
 */
void printLegalMovesForAllPieces(GameBoard *gameBoard)
{
    for (char row = '8'; row >='1' ; --row)
    {
        for (char col = 'A'; col <= 'H'; ++col)
        {
            printf("The moves for piece at %c%c are: \n", row, col);
            LegalMoves legalMoves = {0};
            getLegalMovesForPieceAt(row,col,gameBoard,&legalMoves);
            printLegalMoves(&legalMoves);
            printBoard(gameBoard,White);
            printf("\n---------------\n");
        }
    }
}


ExecuteGetMovesResponse executeUserGetMovesCommand(char pieceRow, char pieceCol, GameBoard *gameBoard, Player currentPlayer);