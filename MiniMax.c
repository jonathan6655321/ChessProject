//
// Created by Jonathan on 9/10/2017.
//


#include "MiniMax.h"



/*
 * returns the location index (0-63) of the position to move the piece at
 * with alpha beta pruning
 */
MiniMaxMove minimax(GameBoard *gameState, int depth, int alpha, int beta, Player currentPlayer, int (*scoreFunction)(GameBoard *))
{
    if(depth == 0)
    {
        MiniMaxMove bestMove = {-1,-1, (*scoreFunction)(gameState)};
        return bestMove;
    }
    else
    {
        if(currentPlayer == Player1) // maximizing player
        {
//            int maxValue = INT_MIN;
            MiniMaxMove bestMove = {-1,-1, INT_MIN};
            // iterate over all possible next game states:
            // for every piece
            for(int pieceIndex = getFirstPieceIndexForPlayer(currentPlayer);
                    pieceIndex <= getLastPieceIndexForPlayer(currentPlayer);
                    pieceIndex++)
            {
                int pieceLocationIndex = getLocationIndexForPieceIndex(gameState, pieceIndex);
                LegalMoves pieceCanMoveTo;
                char row = getRowFromLocationIndex(pieceLocationIndex);
                char col = getColFromLocationIndex(pieceLocationIndex);
                getLegalMovesForPieceAt(row, col, gameState, &pieceCanMoveTo);

                GameBoard child;
                // for every possible move
                for(int moveLocationIndex=0; moveLocationIndex<BOARD_SIZE; moveLocationIndex++)
                {
                    if(pieceCanMoveTo.legalMovesArray[moveLocationIndex] != LEGAL_MOVE)
                        continue;
                    else
                    {
                        // create the child board:
                        child = (*gameState);
                        char rowTo = getRowFromLocationIndex(moveLocationIndex);
                        char colTo = getColFromLocationIndex(moveLocationIndex);
                        movePiece(row, col, rowTo, colTo, &child);

                        // continue with algo:
                        MiniMaxMove possibleMove = minimax(&child, depth-1, alpha, beta,
                                                           getOtherPlayer(currentPlayer), scoreFunction);
                        if(possibleMove.boardValueAfterMove > bestMove.boardValueAfterMove)
                        {
                            bestMove.boardValueAfterMove = possibleMove.boardValueAfterMove;
                            bestMove.pieceIndex = pieceIndex;
                            bestMove.toLocationIndex = moveLocationIndex;
                        }
                        alpha = max(alpha, bestMove.boardValueAfterMove);
                        if(beta <= alpha)
                            return bestMove;
                    }
                }
            }
        }
        else // minimizing player
        {
            MiniMaxMove bestMove = {-1,-1, INT_MAX};

            // iterate over all possible next game states:
            // for every piece
            for(int pieceIndex = getFirstPieceIndexForPlayer(currentPlayer);
                pieceIndex <= getLastPieceIndexForPlayer(currentPlayer);
                pieceIndex++)
            {
                int pieceLocationIndex = getLocationIndexForPieceIndex(gameState, pieceIndex);
                LegalMoves pieceCanMoveTo;
                char row = getRowFromLocationIndex(pieceLocationIndex);
                char col = getColFromLocationIndex(pieceLocationIndex);
                getLegalMovesForPieceAt(row, col, gameState, &pieceCanMoveTo);

                GameBoard child;
                // for every possible move
                for(int moveLocationIndex=0; moveLocationIndex<BOARD_SIZE; moveLocationIndex++)
                {
                    if(pieceCanMoveTo.legalMovesArray[moveLocationIndex] != LEGAL_MOVE)
                        continue;
                    else
                    {
                        // create the child board:
                        child = (*gameState);
                        char rowTo = getRowFromLocationIndex(moveLocationIndex);
                        char colTo = getColFromLocationIndex(moveLocationIndex);
                        movePiece(row, col, rowTo, colTo, &child);

                        MiniMaxMove possibleMove = minimax(&child, depth-1, alpha, beta,
                                                       getOtherPlayer(currentPlayer), scoreFunction);

                        // continue with algo:
                        if(possibleMove.boardValueAfterMove < bestMove.boardValueAfterMove)
                        {
                            bestMove.boardValueAfterMove = possibleMove.boardValueAfterMove;
                            bestMove.pieceIndex = pieceIndex;
                            bestMove.toLocationIndex = moveLocationIndex;
                        }

                        beta = min(beta, bestMove.boardValueAfterMove);
                        if(beta <= alpha)
                            return bestMove;
                    }
                }
            }
        }
    }
}


/*
 * simple max function
 */
int max(int a, int b)
{
    return (a>=b)?a:b;
}

/*
 * simple min function
 */
int min(int a, int b)
{
    return (a<=b)?a:b;
}


/*
 * receives board and returns its score, relative to player 1
 */
int scoreFunction(GameBoard *gameBoard)
{
    int score = 0;
    score+= PAWN_VAL*numPawns(gameBoard, Player1);
    score-= PAWN_VAL*numPawns(gameBoard, Player2);

    score+= KNIGHT_VAL*numKnights(gameBoard, Player1);
    score-= KNIGHT_VAL*numKnights(gameBoard, Player2);

    score+= BISHOP_VAL*numBishops(gameBoard, Player1);
    score-= BISHOP_VAL*numBishops(gameBoard, Player2);

    score+= ROOK_VAL*numRooks(gameBoard, Player1);
    score-= ROOK_VAL*numRooks(gameBoard, Player2);

    score+= QUEEN_VAL*numQueens(gameBoard, Player1);
    score-= QUEEN_VAL*numQueens(gameBoard, Player2);

    score+= KING_VAL*numKings(gameBoard, Player1);
    score-= KING_VAL*numKings(gameBoard, Player2);

    return score;
}