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

#define PAWN_VAL 1
#define KNIGHT_VAL 3
#define BISHOP_VAL 3
#define ROOK_VAL 5
#define QUEEN_VAL 9
#define KING_VAL 100

typedef struct{
    int pieceIndex;
    int toLocationIndex;
    int boardValueAfterMove;
} MiniMaxMove;

/*
 *
 * returns the location index (0-63) of the position to move the piece at
 * with alpha beta pruning
 */
MiniMaxMove minimax(GameBoard *gameState, int depth, int alpha, int beta, Player currentPlayer, int (*scoreFunction)(GameBoard *));

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



#endif //CHESSPROJECT_MINIMAX_H
