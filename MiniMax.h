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

#define PAWN_VAL 10
#define KNIGHT_VAL 30
#define BISHOP_VAL 30
#define ROOK_VAL 50
#define QUEEN_VAL 90
#define KING_VAL 1000

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
int minimax(GameBoard *gameState, int depth, int alpha, int beta, Player currentPlayer,
            int (*scoreFunction)(GameBoard *), MiniMaxMove *bestMove);

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
int amazingScoreFunction(GameBoard *gameBoard);
int centerControlScore(GameBoard *gameBoard);



#endif //CHESSPROJECT_MINIMAX_H
