//
// Created by Jonathan on 9/10/2017.
//


#include "MiniMax.h"

/*
 * returns the location index (0-63) of the position to move the piece at
 * with alpha beta pruning
 */
int minimax(GameBoard *gameState, int height, int alpha, int beta,
		Player currentPlayer, int(*scoreFunction)(GameBoard *),
		MiniMaxMove *bestMove, int isRoot) {
	int pieceIndex, moveLocationIndex;
	if (height == 0) {
		bestMove->toLocationIndex = -1;
		bestMove->pieceIndex = -1;
		return (*scoreFunction)(gameState);
	} else {
		if (currentPlayer == Player1) // maximizing player
		{
			int maxValue = INT_MIN;
			int hadAChild = 0;
			// iterate over all possible next game states:
			// for every piece
			int firstPiece = getFirstPieceIndexForPlayer(currentPlayer);
			int lastPiece = getLastPieceIndexForPlayer(currentPlayer);
			for (pieceIndex = firstPiece; pieceIndex <= lastPiece; pieceIndex++) {
				int pieceLocationIndex = getLocationIndexForPieceIndex(
						gameState, pieceIndex);
				if (!isValidLocationIndex(pieceLocationIndex))
					continue;
				LegalMoves pieceCanMoveTo = { 0 };
				char row = getRowFromLocationIndex(pieceLocationIndex);
				char col = getColFromLocationIndex(pieceLocationIndex);
				if (isRoot)
					getLegalMovesForPieceAt(row, col, gameState,
							&pieceCanMoveTo);
				else
					getPossibleMovesForPieceAt(row, col, gameState,
							&pieceCanMoveTo);

				GameBoard child;
				// for every possible move
				for (moveLocationIndex = 0; moveLocationIndex < BOARD_SIZE; moveLocationIndex++) {
					if (pieceCanMoveTo.legalMovesArray[moveLocationIndex]
							!= LEGAL_MOVE)
						continue;
					else {
						hadAChild = 1;
						// create the child board:
						child = (*gameState);
						char rowTo = getRowFromLocationIndex(moveLocationIndex);
						char colTo = getColFromLocationIndex(moveLocationIndex);
						movePiece(row, col, rowTo, colTo, &child);

						// continue with algo:
						MiniMaxMove uselessMove = { 0 };
						int currentVal = minimax(&child, height - 1, alpha,
								beta, getOtherPlayer(currentPlayer),
								scoreFunction, &uselessMove, 0);

						if (currentVal > maxValue) {
							maxValue = currentVal;
							bestMove->pieceIndex = pieceIndex;
							bestMove->toLocationIndex = moveLocationIndex;
						}
						alpha = max(alpha, maxValue);
						if (beta <= alpha) {
							return maxValue;
						}
					}
				}
			}
			// no piece could move:
			if (!hadAChild) {
				bestMove->toLocationIndex = -1;
				bestMove->pieceIndex = -1;
				return (*scoreFunction)(gameState);
			}
			return maxValue;
		} else // minimizing player
		{
			int minValue = INT_MAX;
			int hadAChild = 0;
			// iterate over all possible next game states:
			// for every piece
			int firstPiece = getFirstPieceIndexForPlayer(currentPlayer);
			int lastPiece = getLastPieceIndexForPlayer(currentPlayer);
			for (pieceIndex = firstPiece; pieceIndex <= lastPiece; pieceIndex++) {
				int pieceLocationIndex = getLocationIndexForPieceIndex(
						gameState, pieceIndex);
				if (!isValidLocationIndex(pieceLocationIndex))
					continue;
				LegalMoves pieceCanMoveTo = { 0 };
				char row = getRowFromLocationIndex(pieceLocationIndex);
				char col = getColFromLocationIndex(pieceLocationIndex);
				if (isRoot)
					getLegalMovesForPieceAt(row, col, gameState,
							&pieceCanMoveTo);
				else
					getPossibleMovesForPieceAt(row, col, gameState,
							&pieceCanMoveTo);

				GameBoard child;
				// for every possible move
				for (moveLocationIndex = 0; moveLocationIndex < BOARD_SIZE; moveLocationIndex++) {
					if (pieceCanMoveTo.legalMovesArray[moveLocationIndex]
							!= LEGAL_MOVE)
						continue;
					else {
						hadAChild = 1;
						// create the child board:
						child = (*gameState);
						char rowTo = getRowFromLocationIndex(moveLocationIndex);
						char colTo = getColFromLocationIndex(moveLocationIndex);
						movePiece(row, col, rowTo, colTo, &child);

						MiniMaxMove uselessMove = { 0 };
						int currentValue = minimax(&child, height - 1, alpha,
								beta, getOtherPlayer(currentPlayer),
								scoreFunction, &uselessMove, 0);
						// continue with algo:
						if (currentValue < minValue) {
							minValue = currentValue;
							bestMove->pieceIndex = pieceIndex;
							bestMove->toLocationIndex = moveLocationIndex;
						}

						beta = min(beta, minValue);
						if (beta <= alpha) {
							return minValue;
						}
					}
				}
			}
			// no piece could move:
			if (!hadAChild) {
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
int max(int a, int b) {
	return (a >= b) ? a : b;
}

/*
 * simple min function
 */
int min(int a, int b) {
	return (a <= b) ? a : b;
}

/*
 * receives board and returns its score, relative to player 1
 */
int scoreFunction(GameBoard *gameBoard) {
	int score = 0;
	score += PAWN_VAL * numPawns(gameBoard, Player1);
	score -= PAWN_VAL * numPawns(gameBoard, Player2);

	score += KNIGHT_VAL * numKnights(gameBoard, Player1);
	score -= KNIGHT_VAL * numKnights(gameBoard, Player2);

	score += BISHOP_VAL * numBishops(gameBoard, Player1);
	score -= BISHOP_VAL * numBishops(gameBoard, Player2);

	score += ROOK_VAL * numRooks(gameBoard, Player1);
	score -= ROOK_VAL * numRooks(gameBoard, Player2);

	score += QUEEN_VAL * numQueens(gameBoard, Player1);
	score -= QUEEN_VAL * numQueens(gameBoard, Player2);

	score += KING_VAL * numKings(gameBoard, Player1);
	score -= KING_VAL * numKings(gameBoard, Player2);

	return score;
}


/*
 * taken from chessprogramming.com
 */
int advancedMaterialScoreFunction(GameBoard *gameBoard) {
    int score = 0;
    score += BETTER_PAWN_VAL * numPawns(gameBoard, Player1);
    score -= BETTER_PAWN_VAL * numPawns(gameBoard, Player2);

    score += BETTER_KNIGHT_VAL * numKnights(gameBoard, Player1);
    score -= BETTER_KNIGHT_VAL * numKnights(gameBoard, Player2);

    score += BETTER_BISHOP_VAL * numBishops(gameBoard, Player1);
    score -= BETTER_BISHOP_VAL * numBishops(gameBoard, Player2);

    score += BETTER_ROOK_VAL * numRooks(gameBoard, Player1);
    score -= BETTER_ROOK_VAL * numRooks(gameBoard, Player2);

    score += BETTER_QUEEN_VAL * numQueens(gameBoard, Player1);
    score -= BETTER_QUEEN_VAL * numQueens(gameBoard, Player2);

    score += BETTER_KING_VAL * numKings(gameBoard, Player1);
    score -= BETTER_KING_VAL * numKings(gameBoard, Player2);

    return score;
}


/*
 * use regular score function along with center control
 *
 * when there are not many pieces we can look a bit deeper and
 * try to move towards opponents king
 */
int amazingScoreFunction(GameBoard *gameBoard) {
	int score = scoreFunction(gameBoard);
//	int score = advancedMaterialScoreFunction(gameBoard);
//    score += 0.1*mobilityScore(gameBoard);
//    score += 3*checkmateMoveScore(gameBoard);
	score += 1*centerControlScore(gameBoard);

	return score;
}


/*
 * checks if this move leaves the opponent with no moves and king threatened
 */
int checkmateMoveScore(GameBoard *gameBoard)
{
    int score = 0;
    if(isKingThreatened(Player1, gameBoard) && getMobilityScoreByPlayer(gameBoard, Player1) == 0)
    {
        score -= 100000;
    }
    if(isKingThreatened(Player2, gameBoard) && getMobilityScoreByPlayer(gameBoard, Player2) == 0)
    {
        score += 100000;
    }
    return score;
}

/*
 *
 */
int centerControlScore(GameBoard *gameBoard) {
	int score = 0;
	char col, row;
	int inInnerCenter = 0;
	for (row = '3'; row <= '6'; row++) {
		for (col = 'C'; col <= 'F'; col++) {
			inInnerCenter = 0;
			if (row >= '4' && row <= '5' && col >= 'D' && col <= 'E') {
				inInnerCenter = 1;
			}
			int pieceIndex = getIndexOfPieceAt(row, col, gameBoard);

			if (pieceIndex != NO_PIECE) {
				if (getPlayerFromIndex(pieceIndex) == Player1) {
					score += inInnerCenter * INNER_CENTER_VAL + CENTER_VAL;
				} else {
					score -= inInnerCenter * INNER_CENTER_VAL + CENTER_VAL;
				}
			}
		}
	}
	return score;
}

int mobilityScore(GameBoard *gameBoard) {
	int score = 0;
	score += getMobilityScoreByPlayer(gameBoard, Player1);
	score -= getMobilityScoreByPlayer(gameBoard, Player2);

	// normalize:
	score /= 10;
    score = min(score, PAWN_VAL);
	return score;
}

int getMobilityScoreByPlayer(GameBoard *gameBoard, Player player) {
	int pieceIndex, score = 0;
	int firstPiece = getFirstPieceIndexForPlayer(player);
	int lastPiece = getLastPieceIndexForPlayer(player);
	for (pieceIndex = firstPiece; pieceIndex <= lastPiece; pieceIndex++) {
		if ((pieceIndex >= PLAYER_1_FIRST_PAWN && pieceIndex
				<= PLAYER_1_LAST_PAWN) || (pieceIndex >= PLAYER_2_FIRST_PAWN
				&& pieceIndex <= PLAYER_2_LAST_PAWN))
			continue;

		int pieceLocationIndex = getLocationIndexForPieceIndex(gameBoard,
				pieceIndex);
		if (!isValidLocationIndex(pieceLocationIndex))
			continue;
		LegalMoves pieceCanMoveTo = { 0 };
		char row = getRowFromLocationIndex(pieceLocationIndex);
		char col = getColFromLocationIndex(pieceLocationIndex);
		getPossibleMovesForPieceAt(row, col, gameBoard, &pieceCanMoveTo);

		score += countMoves(&pieceCanMoveTo);
	}

	return score;
}

int countMoves(LegalMoves *pieceCanMoveTo) {
	int i, cnt = 0;
	for (i = 0; i < BOARD_SIZE; i++) {
		if (pieceCanMoveTo->legalMovesArray[i] > 0)
			cnt++;
	}
	return cnt;
}

int countPiecesOnBoard(GameBoard *gameBoard)
{
    int i, cnt = 0;
    for(i=0; i < NUM_STARTING_PIECES; i++)
    {
        int pieceLoc = getLocationIndexForPieceIndex(gameBoard, i);
        if( pieceLoc >= 0 && pieceLoc < BOARD_SIZE)
            cnt++;
    }
    return cnt;
}


/*
 * with distance from king taken into account
 */
int getDistanceFromKingScore(GameBoard *gameBoard) {
    int score = 0;
    score += getKingDistanceScoreByPlayer(gameBoard, Player1);
    score -= getKingDistanceScoreByPlayer(gameBoard, Player2);

    // normalize:
    score /= 10;
    score = min(score, PAWN_VAL-1);
    return score;
}

/*
 * sums the opponents average distances from king
 * the further away the opponent is the better for you
 */
int getKingDistanceScoreByPlayer(GameBoard *gameBoard, Player player) {
    int pieceIndex, score = 0;
    int firstPiece = getFirstPieceIndexForPlayer(getOtherPlayer(player));
    int lastPiece = getLastPieceIndexForPlayer(getOtherPlayer(player));

    char enemyKingRow;
    char enemyKingCol;
    int kingLocationIndex;

    if(player == Player1)
        kingLocationIndex = getLocationIndexForPieceIndex(gameBoard, PLAYER_1_KING_INDEX);
    else
        kingLocationIndex = getLocationIndexForPieceIndex(gameBoard, PLAYER_2_KING_INDEX);

    enemyKingRow = getRowFromLocationIndex(kingLocationIndex);
    enemyKingCol = getColFromLocationIndex(kingLocationIndex);

    for (pieceIndex = firstPiece; pieceIndex <= lastPiece; pieceIndex++) {
        int pieceLocationIndex = getLocationIndexForPieceIndex(gameBoard,
                                                               pieceIndex);
        if (!isValidLocationIndex(pieceLocationIndex))
            continue;
        LegalMoves pieceCanMoveTo = { 0 };
        char row = getRowFromLocationIndex(pieceLocationIndex);
        char col = getColFromLocationIndex(pieceLocationIndex);
        getPossibleMovesForPieceAt(row, col, gameBoard, &pieceCanMoveTo);


        score += enemyPieceAverageDistancesToKing(&pieceCanMoveTo, enemyKingRow, enemyKingCol, row, col);
    }

    return score;
}


int enemyPieceAverageDistancesToKing(LegalMoves *pieceCanMoveTo, char enemyKingRow, char enemyKingCol, char row, char col)
{
    int i, distancesSum = 0;
    int numMoves = 0;
    for (i = 0; i < BOARD_SIZE; i++) {
        if (pieceCanMoveTo->legalMovesArray[i] > 0 )
        {
            numMoves++;
            int currentDistance = abs(enemyKingRow - getRowFromLocationIndex(i)) + abs(enemyKingCol - getColFromLocationIndex(i));
            distancesSum += currentDistance;
        }
    }
    if (numMoves == 0 )
        return 0;
    return distancesSum/numMoves;
}
