//
// Created by Jonathan on 7/18/2017.
//


#include <stdlib.h>
#include "GameBoard.h"
#include "Pieces.h"
#define PLAYER_1_QUEEN_INDEX 3
#define PLAYER_1_KING_INDEX 4
//#define PLAYER_1_BISHOP_1 2
//#define PLAYER_1_BISHOP_2 5
//#define PLAYER_1_ROOK_1 2
//#define PLAYER_1_ROOK_2 2
//#define PLAYER_1_KNIGHT_1 2
//#define PLAYER_1_BISHOP_1 2

#define PLAYER_2_QUEEN_INDEX 27
#define PLAYER_2_KING_INDEX 28


/*
 * receives an index from 0-31 and inits piece to hold the player and type of this index
 * indexes 0-15 hold Player 1 pieces
 * indexes 16-31 hold Player 2 pieces
 * in both, the order is isomorphic to the initial game ordering, when player 1 is white.
 * 0-7 hold Player 1: Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook.
 * 8-15 hold Player 1: Pawns
 * 16-23 hold Player 2: Pawns
 * 24-31 hold Player 2: Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook.
 */
int getPieceFromIndex(Piece *piece, int i)
{
    if (i > 31 || i < 0)
    {
        // TODO delete this print
//        printf("invalid index, i needs to be in range 0-31");
        return FAIL;
    }
    piece->player = getPlayerFromIndex(i);
    piece->type = getTypeFromIndex(i);

    return SUCCESS;
}

Player getPlayerFromIndex(int i)
{
    if (i <= 15)
    {
        return Player1;
    }
    else
    {
        return Player2;
    }
}
PieceType getTypeFromIndex(int i)
{
    if(i >= 8 && i <= 23)
    {
        return Pawn;
    }
    else if (i == PLAYER_1_QUEEN_INDEX || i == PLAYER_2_QUEEN_INDEX)
    {
        return Queen;
    }
    else if (i == PLAYER_1_KING_INDEX || i==PLAYER_2_KING_INDEX)
    {
        return King;
    }
    else
    {
        i = i % 8;
        if (i==0 || i==7)
        {
            return Rook;
        }
        else if (i==1 || i == 6)
        {
            return Knight;
        }
        else // (i==2 || i == 5)
        {
            return Bishop;
        }
    }
}

/*
 * used for undo, assumes piece is not on the board now.
 * fails player has max amount of this kind of piece.
 */
int getPieceIndexFromPiece(GameBoard *gameBoard, Piece *piece)
{
    PieceType type = piece->type;
    Player piecePlayer = piece->player;
    switch (type)
    {
        case Pawn:
            if (piecePlayer == Player1)
            {
                for (int i=8; i<=15; i++)
                {
                    if(getLocationIndexForPieceIndex(gameBoard, i) == NOT_IN_GAME)
                    {
                        return i;
                    }
                }
            }
            else
            {
                for (int i=16; i<=23; i++)
                {
                    if(getLocationIndexForPieceIndex(gameBoard, i) == NOT_IN_GAME)
                    {
                        return i;
                    }
                }
            }
            break;
        case Bishop: // 2,5
            if (piecePlayer == Player1)
            {
                if (getLocationIndexForPieceIndex(gameBoard, 2) == NOT_IN_GAME)
                {
                    return 2;
                }
                if (getLocationIndexForPieceIndex(gameBoard, 5) == NOT_IN_GAME)
                {
                    return 5;
                }
            }
            else
            {
                if (getLocationIndexForPieceIndex(gameBoard, 26) == NOT_IN_GAME)
                {
                    return 26;
                }
                if (getLocationIndexForPieceIndex(gameBoard, 29) == NOT_IN_GAME)
                {
                    return 29;
                }
            }
            break;
        case Rook:
            if (piecePlayer == Player1)
            {
                if (getLocationIndexForPieceIndex(gameBoard, 0) == NOT_IN_GAME)
                {
                    return 0;
                }
                if (getLocationIndexForPieceIndex(gameBoard, 7) == NOT_IN_GAME)
                {
                    return 7;
                }
            }
            else
            {
                if (getLocationIndexForPieceIndex(gameBoard, 24) == NOT_IN_GAME)
                {
                    return 24;
                }
                if (getLocationIndexForPieceIndex(gameBoard, 31) == NOT_IN_GAME)
                {
                    return 31;
                }
            }
            break;
        case Knight:
            if (piecePlayer == Player1)
            {
                if (getLocationIndexForPieceIndex(gameBoard, 1) == NOT_IN_GAME)
                {
                    return 1;
                }
                if (getLocationIndexForPieceIndex(gameBoard, 6) == NOT_IN_GAME)
                {
                    return 6;
                }
            }
            else
            {
                if (getLocationIndexForPieceIndex(gameBoard, 25) == NOT_IN_GAME)
                {
                    return 25;
                }
                if (getLocationIndexForPieceIndex(gameBoard, 30) == NOT_IN_GAME)
                {
                    return 30;
                }
            }
            break;
        case Queen:
            if (piecePlayer == Player1)
            {
                if (getLocationIndexForPieceIndex(gameBoard, 3) == NOT_IN_GAME)
                {
                    return 3;
                }
                if (getLocationIndexForPieceIndex(gameBoard, 4) == NOT_IN_GAME)
                {
                    return 4;
                }
            }
            else
            {
                if (getLocationIndexForPieceIndex(gameBoard, 27) == NOT_IN_GAME)
                {
                    return 27;
                }
                if (getLocationIndexForPieceIndex(gameBoard, 28) == NOT_IN_GAME)
                {
                    return 28;
                }
            }
            break;
        default:
            return -1; // this should never happen...
    }
}

/*
 * places all pieces on the board
 */
void initGame(GameBoard *gameBoard, Color player1Color)
{   int pieceIndex = 0;
    for (char row='1'; row <='8'; row++)
    {
        for(char col='A'; col <= 'H'; col ++)
        {
            if (row == '1' || row == '2' || row == '7' || row == '8')
            {
                gameBoard->mapPieceIndexToLocationOnBoard[pieceIndex] = rowColToLocationIndex(row,col);
                gameBoard->mapLocationOnBoardToPieceIndex[rowColToLocationIndex(row,col)] = pieceIndex++;
            }
            else
            {
                gameBoard->mapLocationOnBoardToPieceIndex[rowColToLocationIndex(row,col)] = NO_PIECE;
            }
        }
    }
    // swap queen and king in case player 1 is black
    if (player1Color == Black)
    {
        swapQueenKing(gameBoard);
    }
}

/*
 * used in initGame in case Player1 is Black
 */
void swapQueenKing(GameBoard *gameBoard)
{
    gameBoard->mapPieceIndexToLocationOnBoard[PLAYER_1_QUEEN_INDEX]++;
    gameBoard->mapPieceIndexToLocationOnBoard[PLAYER_1_KING_INDEX]--;
    gameBoard->mapPieceIndexToLocationOnBoard[PLAYER_2_QUEEN_INDEX]++;
    gameBoard->mapPieceIndexToLocationOnBoard[PLAYER_2_KING_INDEX]--;

    gameBoard->mapLocationOnBoardToPieceIndex[rowColToLocationIndex('1','E')] = PLAYER_1_QUEEN_INDEX;
    gameBoard->mapLocationOnBoardToPieceIndex[rowColToLocationIndex('1','D')] = PLAYER_1_KING_INDEX;
    gameBoard->mapLocationOnBoardToPieceIndex[rowColToLocationIndex('8','E')] = PLAYER_2_QUEEN_INDEX;
    gameBoard->mapLocationOnBoardToPieceIndex[rowColToLocationIndex('8','D')] = PLAYER_2_KING_INDEX;
}

/*
 * assumes row: 1-8, and col: A-H
 * inits piece to hold the params of the piece in location row col
 * if there is no piece there function returns -1
 */
int getPieceAt(char row, char col, GameBoard *gameBoard, Piece *piece)
{
    int pieceIndex = getIndexOfPieceAt(row,col,gameBoard);
    if(pieceIndex == NO_PIECE)
    {
        return FAIL;
    }
    else
    {
        return getPieceFromIndex(piece,pieceIndex);
    }
    return SUCCESS;
}

int getPieceFromLocationIndex(GameBoard *gameBoard, int locationIndex, Piece *piece)
{
    int pieceIndex = gameBoard->mapLocationOnBoardToPieceIndex[locationIndex];
    return getPieceFromIndex(piece ,pieceIndex);
}


/*
 * converts row, col (as user inputs it) into location index used in gameboard
 */
int rowColToLocationIndex(char row, char col)
{
    if(isValidRowCol(row,col) == FAIL)
    {
        return FAIL;
    }
    else
        return (row - '1')*8 + (col-'A');
}

int isValidRowCol(char row, char col)
{
    if (row < '1' || row > '8' || col < 'A' || col > 'H')
    {
//        printf("Invalid row, col\n");
        return FAIL;
    }
    else
        return SUCCESS;
}

/*
 * moves piece and returns the index of the piece in the location arrived at
 * fails if row, col invalid.
 * fails if trying to move a NO_PIECE
 */
int movePiece(char rowFrom, char colFrom, char rowTo, char colTo, GameBoard *gameBoard)
{
    if(isValidRowCol(rowFrom,colFrom) == FAIL || isValidRowCol(rowFrom,colFrom) == FAIL)
        return FAIL;

    int pieceAtDestinationIndex = getIndexOfPieceAt(rowTo,colTo, gameBoard);
    int movingPieceIndex = getIndexOfPieceAt(rowFrom,colFrom, gameBoard);
    if(movingPieceIndex == NO_PIECE)
    {
        return FAIL;
    }
    removePieceAt(rowFrom, colFrom, gameBoard);
    setPieceAt(rowTo, colTo, gameBoard, movingPieceIndex);


    return pieceAtDestinationIndex;
}

/*
 * set piece of index pieceIndex at location row col
 */
void setPieceAt(char row, char col, GameBoard *gameBoard, int pieceIndex)
{
    if (isValidRowCol(row,col) == FAIL)
    {
        return;
    }
    gameBoard->mapLocationOnBoardToPieceIndex[rowColToLocationIndex(row,col)] = pieceIndex;
    gameBoard->mapPieceIndexToLocationOnBoard[pieceIndex] = rowColToLocationIndex(row,col);
}

/*
 * remove piece at row col
 */
void removePieceAt(char row, char col, GameBoard *gameBoard)
{
    if (isValidRowCol(row,col) == FAIL)
    {
        return;
    }
    gameBoard->mapPieceIndexToLocationOnBoard[gameBoard->mapLocationOnBoardToPieceIndex[rowColToLocationIndex(row,col)]] = NOT_IN_GAME;
    gameBoard->mapLocationOnBoardToPieceIndex[rowColToLocationIndex(row,col)] = NO_PIECE;
}

/*
 * returns index of piece at row col
 *
 * note: returns NO_PIECE if no piece there
 */
int getIndexOfPieceAt(char row, char col, GameBoard *gameBoard)
{
    if (isValidRowCol(row,col) == FAIL)
    {
        return FAIL;
    }
    return gameBoard->mapLocationOnBoardToPieceIndex[rowColToLocationIndex(row,col)];
}


/*
 * returns 1 if is
 * 0 if player 2
 */
int isPlayer1Index(int i)
{
    if (i >=0 && i <= 15)
    {
        return SUCCESS;
    }
    else // (i >=16 && i <= 31)
    {
        return FAIL;
    }
}

/*
 * gets two indexes and returns SUCCESS if belong to same player
 * if two different player pieces, or if at least one is a NO_PIECE: returns FAIL
 */
int isSamePlayerPiece(int piece1Index, int piece2Index)
{
    if(piece1Index<0 || piece2Index<0 )
    {
        return FAIL;
    }
    else if (piece1Index / 16 == piece2Index / 16)
    {
        return SUCCESS;
    }
    else
        return FAIL;
}

/*
 * returns current location of pieceIndex
 * returns NOT_IN_GAME if was eaten at any point
 */
int getLocationIndexForPieceIndex(GameBoard *gameBoard, int pieceIndex)
{
    return gameBoard->mapPieceIndexToLocationOnBoard[pieceIndex];
}

char getRowFromLocationIndex(int i)
{
    return '1' + (i/NUM_ROWS);
}

char getColFromLocationIndex(int i)
{
    return 'A' + (i % NUM_COLS);
}