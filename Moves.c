//
// Created by Jonathan on 7/20/2017.
//


#include "Moves.h"
#include "ArrayUtils.h"

/*
 * gets <x,y> and <i,j> and moves from first to second
 * if x,y or i,j not on board returns: invalidPosition
 * if at position x,y no users piece: returns notYourPiece
 * if is your piece but illegal move request returns: illegalMove
 *
 */
ResponseType executeUserMoveCommand(char rowFrom, char colFrom, char rowTo,
		char colTo, GameBoard *gameBoard, Player currentPlayer) {
	Piece pieceAtDestinationAfter, pieceDestinationBefore;
	if (isValidRowCol(rowFrom, colFrom) == FAIL || isValidRowCol(rowTo, colTo)
			== FAIL) {
		return InvalidPosition;
	} else {
		// trying to move no piece, or enemy piece
		if (getPieceAt(rowFrom, colFrom, gameBoard, &pieceAtDestinationAfter)
				== FAIL || pieceAtDestinationAfter.player != currentPlayer) {
			return NotYourPiece;
		} else {
			LegalMoves legalMoves = { 0 };
			getLegalMovesForPieceAt(rowFrom, colFrom, gameBoard, &legalMoves);
			if (legalMoves.legalMovesArray[rowColToLocationIndex(rowTo, colTo)]
					== ILLEGAL_MOVE) {
				return IllegalMove;
			} else {
				if (getPieceAt(rowTo, colTo, gameBoard, &pieceDestinationBefore)
						== FAIL) {
					movePiece(rowFrom, colFrom, rowTo, colTo, gameBoard);
					return MadeMove;
				} else {
					movePiece(rowFrom, colFrom, rowTo, colTo, gameBoard);
					return AteOpponentsPiece;
				}
			}
		}
	}
}

/*
 * gets row, col and piece from user. and sets the piece in this location.
 * Assumes the piece is not in the game!
 */
int executeSetPieceAt(char row, char col, Piece * piece, GameBoard *gameBoard) {
	int pieceIndex = getPieceIndexFromPiece(gameBoard, piece);
	if (pieceIndex >= 0) {
		setPieceAt(row, col, gameBoard, pieceIndex);
		return SUCCESS;
	} else
		return FAIL;
}

/*
 * sets legalMoves to hold possible moves for piece at row col
 * checks if move corresponds with chess rules.
 *
 * DOES NOT CHECK if KING IS THREATENED
 *
 *
 * fails if no piece at row col
 * fails if row col invalid
 *
 * MAKE SURE LEGALMOVES is 0 initialized!
 */
int getPossibleMovesForPieceAt(char row, char col, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	if (isValidRowCol(row, col) == FAIL) {
		return FAIL;
	}

	Piece piece;
	if (getPieceAt(row, col, gameBoard, &piece) == FAIL) {
		return FAIL;
	}

	switch (piece.type) {
	case Pawn:
		getLegalMovesForPawnAt(row, col, gameBoard, legalMoves);
		break;
	case Bishop:
		getLegalMovesForBishopAt(row, col, gameBoard, legalMoves);
		break;
	case Rook:
		getLegalMovesForRookAt(row, col, gameBoard, legalMoves);
		break;
	case Knight:
		getLegalMovesForKnightAt(row, col, gameBoard, legalMoves);
		break;
	case Queen:
		getLegalMovesForQueenAt(row, col, gameBoard, legalMoves);
		break;
	case King:
		getLegalMovesForKingAt(row, col, gameBoard, legalMoves);
		break;
	default:
		return FAIL; // this should never happen...
	}
	return SUCCESS;
}

/*
 * gets legal moves: according to piece type, makes sure no king threatened after move
 */
int getLegalMovesForPieceAt(char row, char col, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	if (getPossibleMovesForPieceAt(row, col, gameBoard, legalMoves) == FAIL)
		return FAIL;
	removeMovesThatDangerKing(row, col, gameBoard, legalMoves);
	return SUCCESS;
}

void getLegalMovesForPawnAt(char row, char col, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	int pieceAtDestinationIndex;
	if (isPlayer1Index(getIndexOfPieceAt(row, col, gameBoard)) == SUCCESS) {
		// moves forward:
		if (getIndexOfPieceAt(row + 1, col, gameBoard) == NO_PIECE) {
			setMoveLegal(row + 1, col, legalMoves);
			// didn't move, can move twice
			if (row == '2' && getIndexOfPieceAt(row + 2, col, gameBoard)
					== NO_PIECE) {
				setMoveLegal(row + 2, col, legalMoves);
			}
		}

		// diagonals:
		pieceAtDestinationIndex
				= getIndexOfPieceAt(row + 1, col + 1, gameBoard);
		if (pieceAtDestinationIndex >= 0 && (isPlayer1Index(
				pieceAtDestinationIndex) == FAIL)) {
			setMoveLegal(row + 1, col + 1, legalMoves);
		}
		pieceAtDestinationIndex
				= getIndexOfPieceAt(row + 1, col - 1, gameBoard);
		if (pieceAtDestinationIndex >= 0 && (isPlayer1Index(
				pieceAtDestinationIndex) == FAIL)) {
			setMoveLegal(row + 1, col - 1, legalMoves);
		}
	} else {
		// moves forward:
		if (getIndexOfPieceAt(row - 1, col, gameBoard) == NO_PIECE) {
			setMoveLegal(row - 1, col, legalMoves);
			// didn't move, can move twice
			if (row == '7' && getIndexOfPieceAt(row - 2, col, gameBoard)
					== NO_PIECE) {
				setMoveLegal(row - 2, col, legalMoves);
			}
		}

		// diagonals:
		pieceAtDestinationIndex
				= getIndexOfPieceAt(row - 1, col + 1, gameBoard);
		if (pieceAtDestinationIndex >= 0 && (isPlayer1Index(
				pieceAtDestinationIndex) == SUCCESS)) {
			setMoveLegal(row - 1, col + 1, legalMoves);
		}
		pieceAtDestinationIndex
				= getIndexOfPieceAt(row - 1, col - 1, gameBoard);
		if (pieceAtDestinationIndex >= 0 && (isPlayer1Index(
				pieceAtDestinationIndex) == SUCCESS)) {
			setMoveLegal(row - 1, col - 1, legalMoves);
		}
	}
}
void getLegalMovesForBishopAt(char row, char col, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	setLegalMovesDiagonals(row, col, gameBoard, legalMoves);
}
void getLegalMovesForRookAt(char row, char col, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	setLegalStraightMoves(row, col, gameBoard, legalMoves);
}
void getLegalMovesForQueenAt(char row, char col, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	setLegalStraightMoves(row, col, gameBoard, legalMoves);
	setLegalMovesDiagonals(row, col, gameBoard, legalMoves);
}
void getLegalMovesForKnightAt(char row, char col, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	int knightsIndex = getIndexOfPieceAt(row, col, gameBoard);
	if (isValidRowCol(row + 2, col + 1) == SUCCESS && isSamePlayerPiece(
			knightsIndex, getIndexOfPieceAt(row + 2, col + 1, gameBoard))
			== FAIL) {
		setMoveLegal(row + 2, col + 1, legalMoves);
	}
	if (isValidRowCol(row + 2, col - 1) == SUCCESS && isSamePlayerPiece(
			knightsIndex, getIndexOfPieceAt(row + 2, col - 1, gameBoard))
			== FAIL) {
		setMoveLegal(row + 2, col - 1, legalMoves);
	}
	if (isValidRowCol(row - 2, col + 1) == SUCCESS && isSamePlayerPiece(
			knightsIndex, getIndexOfPieceAt(row - 2, col + 1, gameBoard))
			== FAIL) {
		setMoveLegal(row - 2, col + 1, legalMoves);
	}
	if (isValidRowCol(row - 2, col - 1) == SUCCESS && isSamePlayerPiece(
			knightsIndex, getIndexOfPieceAt(row - 2, col - 1, gameBoard))
			== FAIL) {
		setMoveLegal(row - 2, col - 1, legalMoves);
	}
	if (isValidRowCol(row + 1, col + 2) == SUCCESS && isSamePlayerPiece(
			knightsIndex, getIndexOfPieceAt(row + 1, col + 2, gameBoard))
			== FAIL) {
		setMoveLegal(row + 1, col + 2, legalMoves);
	}
	if (isValidRowCol(row + 1, col - 2) == SUCCESS && isSamePlayerPiece(
			knightsIndex, getIndexOfPieceAt(row + 1, col - 2, gameBoard))
			== FAIL) {
		setMoveLegal(row + 1, col - 2, legalMoves);
	}
	if (isValidRowCol(row - 1, col - 2) == SUCCESS && isSamePlayerPiece(
			knightsIndex, getIndexOfPieceAt(row - 1, col - 2, gameBoard))
			== FAIL) {
		setMoveLegal(row - 1, col - 2, legalMoves);
	}
	if (isValidRowCol(row - 1, col + 2) == SUCCESS && isSamePlayerPiece(
			knightsIndex, getIndexOfPieceAt(row - 1, col + 2, gameBoard))
			== FAIL) {
		setMoveLegal(row - 1, col + 2, legalMoves);
	}
}
void getLegalMovesForKingAt(char row, char col, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	int knightsIndex = getIndexOfPieceAt(row, col, gameBoard);
	if (isValidRowCol(row + 1, col) == SUCCESS && isSamePlayerPiece(
			knightsIndex, getIndexOfPieceAt(row + 1, col, gameBoard)) == FAIL) {
		setMoveLegal(row + 1, col, legalMoves);
	}
	if (isValidRowCol(row - 1, col) == SUCCESS && isSamePlayerPiece(
			knightsIndex, getIndexOfPieceAt(row - 1, col, gameBoard)) == FAIL) {
		setMoveLegal(row - 1, col, legalMoves);
	}
	if (isValidRowCol(row, col + 1) == SUCCESS && isSamePlayerPiece(
			knightsIndex, getIndexOfPieceAt(row, col + 1, gameBoard)) == FAIL) {
		setMoveLegal(row, col + 1, legalMoves);
	}
	if (isValidRowCol(row, col - 1) == SUCCESS && isSamePlayerPiece(
			knightsIndex, getIndexOfPieceAt(row, col - 1, gameBoard)) == FAIL) {
		setMoveLegal(row, col - 1, legalMoves);
	}
	if (isValidRowCol(row + 1, col + 1) == SUCCESS && isSamePlayerPiece(
			knightsIndex, getIndexOfPieceAt(row + 1, col + 1, gameBoard))
			== FAIL) {
		setMoveLegal(row + 1, col + 1, legalMoves);
	}
	if (isValidRowCol(row + 1, col - 1) == SUCCESS && isSamePlayerPiece(
			knightsIndex, getIndexOfPieceAt(row + 1, col - 1, gameBoard))
			== FAIL) {
		setMoveLegal(row + 1, col - 1, legalMoves);
	}
	if (isValidRowCol(row - 1, col - 1) == SUCCESS && isSamePlayerPiece(
			knightsIndex, getIndexOfPieceAt(row - 1, col - 1, gameBoard))
			== FAIL) {
		setMoveLegal(row - 1, col - 1, legalMoves);
	}
	if (isValidRowCol(row - 1, col + 1) == SUCCESS && isSamePlayerPiece(
			knightsIndex, getIndexOfPieceAt(row - 1, col + 1, gameBoard))
			== FAIL) {
		setMoveLegal(row - 1, col + 1, legalMoves);
	}
}

void setLegalMovesDiagonals(char row, char col, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	setRightUpDiagonal(row, col, gameBoard, legalMoves);
	setLeftUpDiagonal(row, col, gameBoard, legalMoves);
	setRightDownDiagonal(row, col, gameBoard, legalMoves);
	setLeftDownDiagonal(row, col, gameBoard, legalMoves);
}

void setRightUpDiagonal(char row, char col, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	int k = 1;
	int pieceIndex = getIndexOfPieceAt(row, col, gameBoard);
	int tempPieceIndex;
	while (isValidRowCol(row + k, col + k) == SUCCESS) {
		tempPieceIndex = getIndexOfPieceAt(row + k, col + k, gameBoard);
		if (tempPieceIndex == NO_PIECE) {
			setMoveLegal(row + k, col + k, legalMoves);
		} else {
			if (isSamePlayerPiece(pieceIndex, tempPieceIndex) == FAIL) {
				setMoveLegal(row + k, col + k, legalMoves);
			}
			break;
		}
		++k;
	}
}
void setLeftUpDiagonal(char row, char col, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	int k = 1;
	int pieceIndex = getIndexOfPieceAt(row, col, gameBoard);
	int tempPieceIndex;
	while (isValidRowCol(row + k, col - k) == SUCCESS) {
		tempPieceIndex = getIndexOfPieceAt(row + k, col - k, gameBoard);
		if (tempPieceIndex == NO_PIECE) {
			setMoveLegal(row + k, col - k, legalMoves);
		} else {
			if (isSamePlayerPiece(pieceIndex, tempPieceIndex) == FAIL) {
				setMoveLegal(row + k, col - k, legalMoves);
			}
			break;
		}
		++k;
	}
}
void setRightDownDiagonal(char row, char col, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	int k = 1;
	int pieceIndex = getIndexOfPieceAt(row, col, gameBoard);
	int tempPieceIndex;
	while (isValidRowCol(row - k, col + k) == SUCCESS) {
		tempPieceIndex = getIndexOfPieceAt(row - k, col + k, gameBoard);
		if (tempPieceIndex == NO_PIECE) {
			setMoveLegal(row - k, col + k, legalMoves);
		} else {
			if (isSamePlayerPiece(pieceIndex, tempPieceIndex) == FAIL) {
				setMoveLegal(row - k, col + k, legalMoves);
			}
			break;
		}
		++k;
	}
}
void setLeftDownDiagonal(char row, char col, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	int k = 1;
	int pieceIndex = getIndexOfPieceAt(row, col, gameBoard);
	int tempPieceIndex;
	while (isValidRowCol(row - k, col - k) == SUCCESS) {
		tempPieceIndex = getIndexOfPieceAt(row - k, col - k, gameBoard);
		if (tempPieceIndex == NO_PIECE) {
			setMoveLegal(row - k, col - k, legalMoves);
		} else {
			if (isSamePlayerPiece(pieceIndex, tempPieceIndex) == FAIL) {
				setMoveLegal(row - k, col - k, legalMoves);
			}
			break;
		}
		++k;
	}
}

/*
 * used in Queen and rook
 */
void setLegalStraightMoves(char row, char col, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	setLegalStraightMovesRight(row, col, gameBoard, legalMoves);
	setLegalStraightMovesLeft(row, col, gameBoard, legalMoves);
	setLegalStraightMovesUp(row, col, gameBoard, legalMoves);
	setLegalStraightMovesDown(row, col, gameBoard, legalMoves);
}
void setLegalStraightMovesRight(char row, char col, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	int k = 1;
	int pieceIndex = getIndexOfPieceAt(row, col, gameBoard);
	int tempPieceIndex;
	while (isValidRowCol(row, col + k) == SUCCESS) {
		tempPieceIndex = getIndexOfPieceAt(row, col + k, gameBoard);
		if (tempPieceIndex == NO_PIECE) {
			setMoveLegal(row, col + k, legalMoves);
		} else {
			if (isSamePlayerPiece(pieceIndex, tempPieceIndex) == FAIL) {
				setMoveLegal(row, col + k, legalMoves);
			}
			break;
		}
		++k;
	}
}
void setLegalStraightMovesLeft(char row, char col, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	int k = 1;
	int pieceIndex = getIndexOfPieceAt(row, col, gameBoard);
	int tempPieceIndex;
	while (isValidRowCol(row, col - k) == SUCCESS) {
		tempPieceIndex = getIndexOfPieceAt(row, col - k, gameBoard);
		if (tempPieceIndex == NO_PIECE) {
			setMoveLegal(row, col - k, legalMoves);
		} else {
			if (isSamePlayerPiece(pieceIndex, tempPieceIndex) == FAIL) {
				setMoveLegal(row, col - k, legalMoves);
			}
			break;
		}
		++k;
	}
}

void setLegalStraightMovesUp(char row, char col, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	int k = 1;
	int pieceIndex = getIndexOfPieceAt(row, col, gameBoard);
	int tempPieceIndex;
	while (isValidRowCol(row + k, col) == SUCCESS) {
		tempPieceIndex = getIndexOfPieceAt(row + k, col, gameBoard);
		if (tempPieceIndex == NO_PIECE) {
			setMoveLegal(row + k, col, legalMoves);
		} else {
			if (isSamePlayerPiece(pieceIndex, tempPieceIndex) == FAIL) {
				setMoveLegal(row + k, col, legalMoves);
			}
			break;
		}
		++k;
	}
}
void setLegalStraightMovesDown(char row, char col, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	int k = 1;
	int pieceIndex = getIndexOfPieceAt(row, col, gameBoard);
	int tempPieceIndex;
	while (isValidRowCol(row - k, col) == SUCCESS) {
		tempPieceIndex = getIndexOfPieceAt(row - k, col, gameBoard);
		if (tempPieceIndex == NO_PIECE) {
			setMoveLegal(row - k, col, legalMoves);
		} else {
			if (isSamePlayerPiece(pieceIndex, tempPieceIndex) == FAIL) {
				setMoveLegal(row - k, col, legalMoves);
			}
			break;
		}
		++k;
	}
}

void setMoveLegal(char row, char col, LegalMoves *legalMoves) {
	legalMoves->legalMovesArray[rowColToLocationIndex(row, col)] = LEGAL_MOVE;
}

void printLegalMoves(LegalMoves *legalMoves) {
	char row, col;
	for (row = '8'; row >= '1'; --row) {
		printf("%c| ", row);
		for (col = 'A'; col <= 'H'; ++col) {
			if (legalMoves->legalMovesArray[rowColToLocationIndex(row, col)]
					== ILLEGAL_MOVE) {
				printf("_ ");
			} else {
				printf("X ");
			}
		}
		printf("|\n");
	}
	printf("  -----------------\n");
	printf("   A B C D E F G H\n");
}

/*
 * for testing..
 */
void printLegalMovesForAllPieces(GameBoard *gameBoard) {
	char row, col;
	for (row = '8'; row >= '1'; --row) {
		for (col = 'A'; col <= 'H'; ++col) {
			printf("The moves for piece at %c%c are: \n", row, col);
			LegalMoves legalMoves = { 0 };
			getLegalMovesForPieceAt(row, col, gameBoard, &legalMoves);
			printLegalMoves(&legalMoves);
			printBoard(gameBoard, White);
			printf("\n---------------\n");
		}
	}
}

/*
 * gets x,y and currentPlayer
 * if invalid x,y returns: invalidPosition
 * if at position x,y no users piece: returns notYourPiece
 *
 * returns the ExecuteGetMovesResponse initialized
 */
ExecuteGetMovesResponse executeUserGetMovesCommand(char pieceRow,
		char pieceCol, GameBoard *gameBoard, Player currentPlayer) {
	ExecuteGetMovesResponse response = { 0 };

	response.type = getResponseTypeForGetMoves(pieceRow, pieceCol, gameBoard,
			currentPlayer);
	if (!(response.type == InvalidPosition || response.type == NotYourPiece)) {
		getLegalMovesForPieceAt(pieceRow, pieceCol, gameBoard,
				&response.allMoves);

		getPositionsThreatenedByOpponent(pieceRow, pieceCol, gameBoard,
				currentPlayer, &response.allMoves,
				&response.threatenedByOpponentMoves);
		getMovesThatEatOpponent(gameBoard, &response.allMoves, currentPlayer,
				&response.opponentAtLocationMoves);

		response.castleType = NoCastlingMovePossible;
	}
	return response;
}

void getMovesThatEatOpponent(GameBoard *gameBoard, LegalMoves *allMoves,
		Player currentPlayer, LegalMoves *opponentAtLocationMoves) {
	//    (*opponentAtLocationMoves).legalMovesArray = {0};
	int i;
	for (i = 0; i < BOARD_SIZE; i++) {
		if (allMoves->legalMovesArray[i] == LEGAL_MOVE) {
			Piece piece;
			int res = getPieceFromLocationIndex(gameBoard, i, &piece);
			if (res == SUCCESS && piece.player != currentPlayer) {
				opponentAtLocationMoves->legalMovesArray[i] = LEGAL_MOVE;
			}
		}
	}
}

void getPositionsThreatenedByOpponent(char pieceRow, char pieceCol,
		GameBoard *gameBoard, Player currentPlayer, LegalMoves *allMoves,
		LegalMoves *threatenedByOpponentMoves) {
	//    (*threatenedByOpponentMoves) = {0};
	int moveIndex, i, j;
	int firstPieceIndex =
			(currentPlayer == Player1) ? FIRST_PLAYER_2_PIECE_INDEX
					: FIRST_PLAYER_1_PIECE_INDEX;
	int lastPieceIndex = (currentPlayer == Player1) ? LAST_PLAYER_2_PIECE_INDEX
			: LAST_PLAYER_1_PIECE_INDEX;

	for (moveIndex = 0; moveIndex < BOARD_SIZE; moveIndex++) {
		if (allMoves->legalMovesArray[moveIndex] != LEGAL_MOVE)
			continue;

		// create a new board with the piece at the destination corresponding to moveIndex
		GameBoard gameAfterMove;
		memcpy(&gameAfterMove, gameBoard, sizeof(GameBoard));
		movePiece(pieceRow, pieceCol, getRowFromLocationIndex(moveIndex),
				getColFromLocationIndex(moveIndex), &gameAfterMove);

		// board needs to be correct at this point..

		for (i = firstPieceIndex; i <= lastPieceIndex; i++) {
			LegalMoves currentOpponentPieceMoves = { 0 };
			int opponentPieceLocationIndex = getLocationIndexForPieceIndex(
					&gameAfterMove, i);
			if (opponentPieceLocationIndex == NOT_IN_GAME)
				continue;

			char opponentPieceRow = getRowFromLocationIndex(
					opponentPieceLocationIndex);
			char opponentPieceCol = getColFromLocationIndex(
					opponentPieceLocationIndex);

			getLegalMovesForPieceAt(opponentPieceRow, opponentPieceCol,
					&gameAfterMove, &currentOpponentPieceMoves);
			for (j = 0; j < BOARD_SIZE; j++) {
				Piece p;
				if (getPieceFromLocationIndex(&gameAfterMove, j, &p) == FAIL)
					continue;
				if (currentOpponentPieceMoves.legalMovesArray[j] == LEGAL_MOVE
						&& p.player == currentPlayer)
					threatenedByOpponentMoves->legalMovesArray[j] = LEGAL_MOVE;
			}
		}
	}

}

/*
 * returns: InvalidPositon, NotYourPiece or OK
 * according to relevant logic..
 */
ResponseType getResponseTypeForGetMoves(char pieceRow, char pieceCol,
		GameBoard *gameBoard, Player currentPlayer) {
	if (isValidRowCol(pieceRow, pieceCol) == FAIL) {
		return InvalidPosition;
	} else {
		Piece pieceAtLocation = { 0 };
		// trying to move no piece, or enemy piece
		if (getPieceAt(pieceRow, pieceCol, gameBoard, &pieceAtLocation) == FAIL
				|| pieceAtLocation.player != currentPlayer) {
			return NotYourPiece;
		} else {
			return OK;
		}
	}
}

/*
 * wrapper for getPossibleMovesForPieceAt
 *
 *
 */
int getPossibleMovesForPieceByIndex(int pieceIndex, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	if (pieceIndex < FIRST_PLAYER_1_PIECE_INDEX || pieceIndex
			> LAST_PLAYER_2_PIECE_INDEX) {
		return FAIL;
	} else {
		int locationIndex =
				getLocationIndexForPieceIndex(gameBoard, pieceIndex);
		char row = getRowFromLocationIndex(locationIndex);
		char col = getColFromLocationIndex(locationIndex);

		return getPossibleMovesForPieceAt(row, col, gameBoard, legalMoves);
	}
}

/*
 * wrapper for getLegalMovesForPieceAt
 */
int getLegalMovesForPieceByIndex(int pieceIndex, GameBoard *gameBoard,
		LegalMoves *legalMoves) {
	if (pieceIndex < FIRST_PLAYER_1_PIECE_INDEX || pieceIndex
			> LAST_PLAYER_2_PIECE_INDEX) {
		return FAIL;
	} else {
		int locationIndex =
				getLocationIndexForPieceIndex(gameBoard, pieceIndex);
		char row = getRowFromLocationIndex(locationIndex);
		char col = getColFromLocationIndex(locationIndex);

		return getLegalMovesForPieceAt(row, col, gameBoard, legalMoves);
	}
}

/*
 * gets player whose king we are checking
 *
 */
int isKingThreatened(Player kingOwner, GameBoard *gameBoard) {
	int pieceIndex;
	Player kingThreatener = getOtherPlayer(kingOwner);
	LegalMoves allThreatenerPossibleMoves = { 0 };

	// iterate over other players pieces
	int firstPiece = getFirstPieceIndexForPlayer(kingThreatener);
	int lastPiece = getLastPieceIndexForPlayer(kingThreatener);
	for (pieceIndex = firstPiece; pieceIndex <= lastPiece; pieceIndex++) {
		LegalMoves currentPieceMoves = { 0 };
		if (getPossibleMovesForPieceByIndex(pieceIndex, gameBoard,
				&currentPieceMoves) == FAIL)
			continue;
		arrayOr(allThreatenerPossibleMoves.legalMovesArray,
				currentPieceMoves.legalMovesArray, BOARD_SIZE);
	}

	int kingLocationIndex = getLocationIndexForPieceIndex(gameBoard,
			getKingIndexByPlayer(kingOwner));
	if (allThreatenerPossibleMoves.legalMovesArray[kingLocationIndex] != 0)
		return SUCCESS;
	else
		return FAIL;
}

int getKingIndexByPlayer(Player kingOwner) {
	if (kingOwner == Player1)
		return PLAYER_1_KING_INDEX;
	else
		return PLAYER_2_KING_INDEX;
}

/*
 * checks which moves endanger the same players king (thus illegal)
 * gets location of piece to move
 * get all possible moves it can make
 *
 * assumes row col holds piece and pieceCanMoveTo holds that pieces possible moves
 * alters legalMoves in place
 */
void removeMovesThatDangerKing(char row, char col, GameBoard *gameBoard,
		LegalMoves *pieceCanMoveTo) {
	int moveLocationIndex;
	GameBoard gameAfterMove = { 0 };
	Player kingOwner = getPlayerFromIndex(
			getIndexOfPieceAt(row, col, gameBoard)); // same as piece owner
	// for every possible move
	for (moveLocationIndex = 0; moveLocationIndex < BOARD_SIZE; moveLocationIndex++) {
		if ((*pieceCanMoveTo).legalMovesArray[moveLocationIndex]
				== ILLEGAL_MOVE) {
			continue;
		} else {
			// create the gameAfterMove board:
			gameAfterMove = (*gameBoard);
			char rowTo = getRowFromLocationIndex(moveLocationIndex);
			char colTo = getColFromLocationIndex(moveLocationIndex);
			movePiece(row, col, rowTo, colTo, &gameAfterMove);

			if (isKingThreatened(kingOwner, &gameAfterMove) == SUCCESS)
				pieceCanMoveTo->legalMovesArray[moveLocationIndex]
						= ILLEGAL_MOVE;
		}
	}
}

/*
 * returns SUCCESS if has
 * FAIL otherwise
 */
int hasLegalMoves(Player player, GameBoard *gameBoard) {
	int pieceIndex;
	LegalMoves allPossibleMoves = { 0 };

	// iterate over other players pieces
	int firstPiece = getFirstPieceIndexForPlayer(player);
	int lastPiece = getLastPieceIndexForPlayer(player);
	for (pieceIndex = firstPiece; pieceIndex <= lastPiece; pieceIndex++) {
		LegalMoves currentPieceMoves = { 0 };
		getLegalMovesForPieceByIndex(pieceIndex, gameBoard, &currentPieceMoves);
		arrayOr(allPossibleMoves.legalMovesArray,
				currentPieceMoves.legalMovesArray, BOARD_SIZE);
	}

	if (isZeroArray(allPossibleMoves.legalMovesArray, BOARD_SIZE) == SUCCESS)
		return FAIL;
	else
		return SUCCESS;
}
