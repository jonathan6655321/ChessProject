//
// Created by Jonathan on 7/20/2017.
//

#ifndef CHESSPROJECT_MOVES_H
#define CHESSPROJECT_MOVES_H

#include "GameBoard.h"
#include "consoleRendering.h"
#include <stdio.h>
#include <string.h>

#define LEGAL_MOVE 1
#define ILLEGAL_MOVE 0
typedef struct LegalMoves
{
    /*
     * 0,1 array which holds all legal moves for a piece
     * 1 is legal
     * 0 is illegal
     *
     * legal means: you can move the piece there.
     * takes into account pieces on the way, and piece type
     */
    int legalMovesArray[BOARD_SIZE];
}LegalMoves;


typedef enum {
    InvalidPosition,
    NotYourPiece,
    IllegalMove,
    AteOpponentsPiece,
    MadeMove,
    PawnPromotionNeeded,
    AteOpponentsPiece_PawnPromote,
    MadeMove_Pawn_Promote,
    OK
} ResponseType;



/*
 * gets <x,y> and <i,j> and moves from first to second
 * if x,y or i,j not on board returns: invalidPosition
 * if at position x,y no users piece: returns notYourPiece
 * if is your piece but illegal move request returns: illegalMove
 *
 */
ResponseType executeUserMoveCommand(char rowFrom, char colFrom, char rowTo, char colTo, GameBoard *gameBoard, Player currentPlayer,
                                Piece *pieceDestinationBefore, Piece* pieceAtDestinationAfter);

/*
 * gets row, col and piece from user. and sets the piece in this location
 */
int executeSetPieceAt(char row, char col, Piece * piece, GameBoard *gameBoard);


typedef enum {
    LongCastle,
    ShortCastle,
    BothCastle,
    NoCastlingMovePossible
} CastleType;

typedef struct{

    ResponseType type;
    LegalMoves allMoves;
    LegalMoves threatenedByOpponentMoves;
    LegalMoves opponentAtLocationMoves;
    CastleType castleType;
} ExecuteGetMovesResponse;


/*
 * gets x,y and currentPlayer
 * if invalid x,y returns: invalidPosition
 * if at position x,y no users piece: returns notYourPiece
 *
 * returns the ExecuteGetMovesResponse initialized
 */
ExecuteGetMovesResponse executeUserGetMovesCommand(char pieceRow, char pieceCol, GameBoard *gameBoard, Player currentPlayer);


/*!
 *
 * @param gameBoard
 * @param allMoves
 * @param currentPlayer
 * @param threatenedByOpponentMoves
 *
 * inits threatendByOpponentMoves according to allMoves.
 */
void getPositionsThreatenedByOpponent(char pieceRow, char pieceCol, GameBoard *gameBoard, Player currentPlayer,
                                      LegalMoves *allMoves, LegalMoves *threatenedByOpponentMoves); // TODO castling threatened??

/*!
 *
 * @param gameBoard
 * @param allMoves
 * @param currentPlayer
 * @param opponentAtLocationMoves
 *
 * inits opponentAtLocationMoves
 */
void getMovesThatEatOpponent(GameBoard *gameBoard, LegalMoves *allMoves,
                             Player currentPlayer, LegalMoves *opponentAtLocationMoves);


/*
 *
 * returns: InvalidPositon, NotYourPiece or OK
 * according to relevant logic..
 */
ResponseType getResponseTypeForGetMoves(char pieceRow, char pieceCol, GameBoard *gameBoard, Player currentPlayer);



/*
 * sets legalMoves to hold legal moves for piece at row col
 * fails if no piece at row col
 * fails if row col invalid
 *
 * MAKE SURE LEGALMOVES is 0 initialized!
 */
int getLegalMovesForPieceAt(char row,char col,GameBoard *gameBoard,LegalMoves *legalMoves);

/*
 * used in getLegalMovesForPieceAt
 */
void getLegalMovesForPawnAt(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves);
void getLegalMovesForBishopAt(char row, char col, GameBoard *gameBoard, LegalMoves *legalMoves);
void getLegalMovesForRookAt(char row, char col, GameBoard *gameBoard, LegalMoves *legalMoves);
void getLegalMovesForKnightAt(char row, char col, GameBoard *gameBoard, LegalMoves *legalMoves);
void getLegalMovesForQueenAt(char row, char col, GameBoard *gameBoard, LegalMoves *legalMoves);
void getLegalMovesForKingAt(char row, char col, GameBoard *gameBoard, LegalMoves *legalMoves);

/*
 * used in Queen and bishop
 */
void setLegalMovesDiagonals(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves);
void setRightUpDiagonal(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves);
void setLeftUpDiagonal(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves);
void setRightDownDiagonal(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves);
void setLeftDownDiagonal(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves);

/*
 * used in Queen and rook
 */
void setLegalStraightMoves(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves);
void setLegalStraightMovesRight(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves);
void setLegalStraightMovesLeft(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves);
void setLegalStraightMovesUp(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves);
void setLegalStraightMovesDown(char row,char col,GameBoard *gameBoard, LegalMoves *legalMoves);

/*
 * set row col to valid in legalMoves
 */
void setMoveLegal(char row, char col, LegalMoves *legalMoves);

/*
 * prints the board with the valid moves of the piece
 */
void printLegalMoves(LegalMoves *legalMoves);

/*
 * for testing..
 */
void printLegalMovesForAllPieces(GameBoard *gameBoard);
#endif //CHESSPROJECT_MOVES_H

