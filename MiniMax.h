//
// Created by Jonathan on 9/10/2017.
//

#ifndef CHESSPROJECT_MINIMAX_H
#define CHESSPROJECT_MINIMAX_H

#include <limits.h>
#include "GameBoard.h"
#include "Moves.h"
#include "Pieces.h"
#include<stdio.h>
#include <stdlib.h>

// the scores were multiplied by 10 so that we could supply a value for center control
// in integers without passing the value of a pawn
#define PAWN_VAL 10
#define KNIGHT_VAL 30
#define BISHOP_VAL 30
#define ROOK_VAL 50
#define QUEEN_VAL 90
#define KING_VAL 1000

#define BETTER_PAWN_VAL 100
#define BETTER_KNIGHT_VAL 350
#define BETTER_BISHOP_VAL 350
#define BETTER_ROOK_VAL 525
#define BETTER_QUEEN_VAL 1000
#define BETTER_KING_VAL 10000

#define CENTER_VAL 5
#define INNER_CENTER_VAL 4

typedef struct{
    int pieceIndex;
    int toLocationIndex;
} MiniMaxMove;

/*
 *
 * returns the location index (0-63) of the position to move the piece at
 * with alpha beta pruning
 */
int minimax(GameBoard *gameState, int height, int alpha, int beta, Player currentPlayer,
            int (*scoreFunction)(GameBoard *), MiniMaxMove *bestMove, int isRoot);

/*
 * simple max function
 */
int max(int a, int b);

/*
 * simple min function
 */
int min(int a, int b);

/*
 * receives board and returns its score, relative to player 1
 */
int scoreFunction(GameBoard *gameBoard);
/*
 * taken from chessprogramming.com
 */
int advancedMaterialScoreFunction(GameBoard *gameBoard);

int amazingScoreFunction(GameBoard *gameBoard);
int centerControlScore(GameBoard *gameBoard);
int mobilityScore(GameBoard *gameBoard);
int getMobilityScoreByPlayer(GameBoard *gameBoard, Player player);
int countMoves(LegalMoves *pieceCanMoveTo);
/*
 * checks if this move leaves the opponent with no moves and king threatened
 */
int checkmateMoveScore(GameBoard *gameBoard);
/*
 * takes into account distance from king
 */
int getAdvancedMobilityScoreByPlayer(GameBoard *gameBoard, Player player);
int countCloserToEnemyKingMoves(LegalMoves *pieceCanMoveTo,  char enemyKingRow, char enemyKingCol, char row, char col);
/*
 * with distance from king taken into account
 */
int getCloseToKing(GameBoard *gameBoard);
int countPiecesOnBoard(GameBoard *gameBoard);
#endif //CHESSPROJECT_MINIMAX_H
