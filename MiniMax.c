//
// Created by Jonathan on 9/10/2017.
//


#include "MiniMax.h"



/*
 * returns the location index (0-63) of the position to move the piece at
 * with alpha beta pruning
 */
int minimax(GameBoard *gameState, int height, int alpha, int beta, Player currentPlayer,
                    int (*scoreFunction)(GameBoard *), MiniMaxMove *bestMove, int isRoot)
{
    if(height == 0)
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
                if(isRoot)
                    getLegalMovesForPieceAt(row, col, gameState, &pieceCanMoveTo);
                else
                    getPossibleMovesForPieceAt(row, col, gameState, &pieceCanMoveTo);


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
                        int currentVal = minimax(&child, height-1, alpha, beta,
                                                           getOtherPlayer(currentPlayer), scoreFunction, &uselessMove, 0);

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
                if(isRoot)
                    getLegalMovesForPieceAt(row, col, gameState, &pieceCanMoveTo);
                else
                    getPossibleMovesForPieceAt(row, col, gameState, &pieceCanMoveTo);


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
                        int currentValue = minimax(&child, height-1, alpha, beta,
                                                       getOtherPlayer(currentPlayer), scoreFunction, &uselessMove, 0);
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

int amazingScoreFunction(GameBoard *gameBoard)
{
    int score = scoreFunction(gameBoard);
    score += centerControlScore(gameBoard);
    score += mobilityScore(gameBoard);
    return score;
}

/*
 *
 */
int centerControlScore(GameBoard *gameBoard)
{
    int score = 0;
    int inInnerCenter = 0;
    for(char row = '3'; row <= '6'; row ++)
    {
        for(char col = 'C'; col<= 'F'; col++)
        {
            inInnerCenter = 0;
            if(row >= '4' && row <= '5' && col >= 'D' && col <= 'E')
            {
                inInnerCenter = 1;
            }
            int pieceIndex = getIndexOfPieceAt(row, col, gameBoard);

            if(pieceIndex!= NO_PIECE)
            {
                if(getPlayerFromIndex(pieceIndex) == Player1)
                {
                    score += inInnerCenter*INNER_CENTER_VAL + CENTER_VAL;
                }
                else
                {
                    score -= inInnerCenter*INNER_CENTER_VAL + CENTER_VAL;
                }
            }
        }
    }
    return score;
}

int mobilityScore(GameBoard *gameBoard)
{
    int score = 0;
    score += getMobilityScoreByPlayer(gameBoard, Player1);
    score -= getMobilityScoreByPlayer(gameBoard, Player2);

    // normalize:
    score /= 10;

    return score;
}

int getMobilityScoreByPlayer(GameBoard *gameBoard, Player player)
{
    int score = 0;
    int firstPiece = getFirstPieceIndexForPlayer(player);
    int lastPiece = getLastPieceIndexForPlayer(player);
    for(int pieceIndex = firstPiece;
        pieceIndex <= lastPiece;
        pieceIndex++)
    {
        if((pieceIndex >= PLAYER_1_FIRST_PAWN && pieceIndex <= PLAYER_1_LAST_PAWN)
                || (pieceIndex >= PLAYER_2_FIRST_PAWN && pieceIndex <= PLAYER_2_LAST_PAWN))
            continue;

        int pieceLocationIndex = getLocationIndexForPieceIndex(gameBoard, pieceIndex);
        if(!isValidLocationIndex(pieceLocationIndex))
            continue;
        LegalMoves pieceCanMoveTo = {0};
        char row = getRowFromLocationIndex(pieceLocationIndex);
        char col = getColFromLocationIndex(pieceLocationIndex);
        getPossibleMovesForPieceAt(row, col, gameBoard, &pieceCanMoveTo);

        score+= countMoves(&pieceCanMoveTo);
    }

    return score;
}

int countMoves(LegalMoves *pieceCanMoveTo)
{
    int cnt=0;
    for(int i=0; i<BOARD_SIZE; i++)
    {
        if(pieceCanMoveTo->legalMovesArray[i] > 0)
            cnt++;
    }
    return cnt;
}