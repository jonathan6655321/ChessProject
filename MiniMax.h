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

// taken from chessprogramming.com
#define BETTER_PAWN_VAL 100
#define BETTER_KNIGHT_VAL 350
#define BETTER_BISHOP_VAL 350
#define BETTER_ROOK_VAL 525
#define BETTER_QUEEN_VAL 1000
#define BETTER_KING_VAL 10000

#define CENTER_VAL 3
#define INNER_CENTER_VAL 6

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
 * used for expert mode
 */
int amazingScoreFunction(GameBoard *gameBoard);

/*
 * taken from chessprogramming.com
 */
int advancedMaterialScoreFunction(GameBoard *gameBoard);

/*
 * receive points for controlling center squares
 * these are considered important in chess
 */
int centerControlScore(GameBoard *gameBoard);

/*
 * we ended up not using this actually but it is said this is important
 * expensive computationally
 */
int mobilityScore(GameBoard *gameBoard);

/*
 * used in the function 'mobilityScore'
 */
int getMobilityScoreByPlayer(GameBoard *gameBoard, Player player);

/*
 * counts legal moves for piece after this struct is initialized.
 */
int countMoves(LegalMoves *pieceCanMoveTo);

/*
 * checks if this move leaves the opponent with no moves and king threatened
 * ended up not using this
 */
int checkmateMoveScore(GameBoard *gameBoard);



/*
 * sums the opponents average distances from king
 * the further away the opponent is the better for you
 */
int getKingDistanceScoreByPlayer(GameBoard *gameBoard, Player player);

/*
 * for certain piece. used in above function
 */
int enemyPieceAverageDistancesToKing(LegalMoves *pieceCanMoveTo, char enemyKingRow, char enemyKingCol, char row,
                                     char col);
/*
 * with distance from king taken into account
 */
int getDistanceFromKingScore(GameBoard *gameBoard);

/*
 * used for deciding when to starting trying to get close to the king
 */
int countPiecesOnBoard(GameBoard *gameBoard);
#endif //CHESSPROJECT_MINIMAX_H
