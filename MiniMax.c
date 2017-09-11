//
// Created by Jonathan on 9/10/2017.
//


#include "MiniMax.h"



/*
 * returns the location index (0-63) of the position to move the piece at
 * with alpha beta pruning
 */
int minimax(GameBoard *gameState, int depth, int alpha, int beta, Player currentPlayer,
                    int (*scoreFunction)(GameBoard *), MiniMaxMove *bestMove)
{
    if(depth == 0)
    {
        bestMove->toLocationIndex = -1;
        bestMove->pieceIndex = -1;
        return (*scoreFunction)(gameState);
    }
    else
    {
        if(currentPlayer == Player1) // maximizing player
        {
            int maxValue = INT_MIN;
            int hadAChild = 0;
            // iterate over all possible next game states:
            // for every piece
            int firstPiece = getFirstPieceIndexForPlayer(currentPlayer);
            int lastPiece = getLastPieceIndexForPlayer(currentPlayer);
            for(int pieceIndex = firstPiece;
                    pieceIndex <= lastPiece;
                    pieceIndex++)
            {
                int pieceLocationIndex = getLocationIndexForPieceIndex(gameState, pieceIndex);
                if(!isValidLocationIndex(pieceLocationIndex))
                    continue;
                LegalMoves pieceCanMoveTo = {0};
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
                        hadAChild = 1;
                        // create the child board:
                        child = (*gameState);
                        char rowTo = getRowFromLocationIndex(moveLocationIndex);
                        char colTo = getColFromLocationIndex(moveLocationIndex);
                        movePiece(row, col, rowTo, colTo, &child);

                        // continue with algo:
                        MiniMaxMove uselessMove = {0};
                        int currentVal = minimax(&child, depth-1, alpha, beta,
                                                           getOtherPlayer(currentPlayer), scoreFunction, &uselessMove);

                        if(currentVal > maxValue)
                        {
                            maxValue = currentVal;
                            bestMove->pieceIndex = pieceIndex;
                            bestMove->toLocationIndex = moveLocationIndex;
                        }
                        alpha = max(alpha, maxValue);
                        if(beta <= alpha)
                        {
                            return maxValue;
                        }
                    }
                }
            }
            // no piece could move:
            if(!hadAChild)
            {
                bestMove->toLocationIndex = -1;
                bestMove->pieceIndex = -1;
                return (*scoreFunction)(gameState);
            }
            return maxValue;
        }
        else // minimizing player
        {
            int minValue = INT_MAX;
            int hadAChild = 0;
            // iterate over all possible next game states:
            // for every piece
            int firstPiece = getFirstPieceIndexForPlayer(currentPlayer);
            int lastPiece = getLastPieceIndexForPlayer(currentPlayer);
            for(int pieceIndex = firstPiece;
                pieceIndex <= lastPiece;
                pieceIndex++)
            {
                int pieceLocationIndex = getLocationIndexForPieceIndex(gameState, pieceIndex);
                if(!isValidLocationIndex(pieceLocationIndex))
                    continue;
                LegalMoves pieceCanMoveTo = {0};
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
                        hadAChild=1;
                        // create the child board:
                        child = (*gameState);
                        char rowTo = getRowFromLocationIndex(moveLocationIndex);
                        char colTo = getColFromLocationIndex(moveLocationIndex);
                        movePiece(row, col, rowTo, colTo, &child);


                        MiniMaxMove uselessMove = {0};
                        int currentValue = minimax(&child, depth-1, alpha, beta,
                                                       getOtherPlayer(currentPlayer), scoreFunction, &uselessMove);
                        // continue with algo:
                        if(currentValue < minValue)
                        {
                            minValue = currentValue;
                            bestMove->pieceIndex = pieceIndex;
                            bestMove->toLocationIndex = moveLocationIndex;
                        }

                        beta = min(beta, minValue);
                        if(beta <= alpha)
                        {
                            return minValue;
                        }
                    }
                }
            }
            // no piece could move:
            if(!hadAChild)
            {
                bestMove->toLocationIndex = -1;
                bestMove->pieceIndex = -1;
                return (*scoreFunction)(gameState);
            }
            return minValue;
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