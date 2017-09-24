/*
 * Game.c
 *
 *  Created on: 19 ???? 2017
 *      Author: kessi
 */
#include "Game.h"

HandleCommandMessage handleCommand(Command command, Game *game) {
	HandleCommandMessage message;
	switch (command.commandType) {
	case setGameMode:
		return handleSetGameMode(command, game);
	case loadDefaultSettings:
		return handleSetDefault(game);
	case setDifficulty:
		return handleSetDifficulty(command, game);
	case setUserColor:
		return handleSetUserColor(command, game);
	case loadSettings:
		return handleLoadSettings(command, game);
	case printSettings:
		return handlePrintSettings(game);
	case startGame:
		return handleStartGame(game);
	case setMove:
		return handleSetMove(command, game);
	case getMoves:
		return handleGetMoves(command, game);
	case castleMove:
		return handleCastleMove(command, game);
	case saveGame:
		return handleSaveGame(command, game);
	case undoMove:
		return handleUndoMove(game);
	case resetGame:
		message.messageType = resetMessage;
		return message;
	case quitGame:
		message.messageType = quitMessage;
		return message;
	default:
		message.messageType = invalidCommandMessage;
		return message;
	}

}

HandleCommandMessage handleSetGameMode(Command command, Game *game) {
	HandleCommandMessage message;
	char gameModeChar = command.argument[0];
	message.argument[0] = gameModeChar;
	if (command.numberOfArgs == 1 && '1' <= gameModeChar && gameModeChar <= '2') {
		message.messageType = setGameModeMessage;
		game->gameMode = gameModeChar;
	} else {
		message.messageType = errorSetGameModeMessage;
	}
	return message;
}

HandleCommandMessage handleSetDefault(Game *game) {
	game->gameMode = DEFAULT_GAME_MODE;
	game->difficulty = DEFAULT_DIFFICULTY;
	game->currentPlayer = DEFAULT_CURRENT_PLAYER;
	game->player1Color = DEFAULT_USER_COLOR;
	HandleCommandMessage message;
	message.messageType = successMessage;
	return message;
}

HandleCommandMessage handleSetDifficulty(Command command, Game *game) {
	HandleCommandMessage message;
	char difficulty = command.argument[0];
	message.argument[0] = command.argument[0];
	if (command.numberOfArgs == 1 && '1' <= difficulty && difficulty <= '5') {
		if (difficulty == '5' && !(CAN_HANDLE_EXPERT_DIFFICULTY)) {
			message.messageType = errorExpertSetDifficultyMessage;
		} else {
			message.messageType = successMessage;
			game->difficulty = difficulty;
		}
	} else {
		message.messageType = errorSetDifficultyMessage;
	}
	return message;
}

HandleCommandMessage handleSetUserColor(Command command, Game *game) {
	HandleCommandMessage message;
	char color = command.argument[0];
	if (command.numberOfArgs == 1 && game->gameMode != PlayerVsPlayer && '0'
			<= color && color <= '1') {
		game->player1Color = color;
		message.messageType = successMessage;
	} else {
		message.messageType = invalidCommandMessage;
	}
	return message;
}

HandleCommandMessage handleLoadSettings(Command command, Game *game) {
	HandleCommandMessage message;
	message.messageType = successMessage;
	int gameMode, difficulty;
	int res = loadGameFromFile(&(game->board), &(game->currentPlayer),
			&gameMode, &difficulty, &(game->player1Color),
			command.stringArgument);
	if (res != FAIL) {
		game->needToReprintBoard = 1;
		game->gameMode = '0' + gameMode;
		game->difficulty = '0' + difficulty;
		game->isLoaded = 1;
	} else {
		message.messageType = errorLoadMessage;
	}
	return message;
}

HandleCommandMessage handlePrintSettings(Game *game) {
	HandleCommandMessage message;
	message.messageType = printSettingMessage;
	message.argument[0] = game->gameMode;
	message.argument[1] = game->difficulty;
	message.argument[2] = game->player1Color;
	return message;
}

HandleCommandMessage handleStartGame(Game *game) {
	game->needToReprintBoard = 1;
	if (!game->isLoaded) {
		if (game->gameMode == PlayerVsPlayer) {
			game->currentPlayer = Player1;
			game->player1Color = White;
		}
		initGame(&(game->board), game->player1Color);
		game->currentPlayer = (game->player1Color == White) ? Player1 : Player2;
	}
	HandleCommandMessage message;
	message.messageType = successMessage;
	return message;
}

HandleCommandMessage handleSetMove(Command command, Game *game) {
	char rowFrom = command.argument[0];
	char colFrom = command.argument[1];
	char rowTo = command.argument[2];
	char colTo = command.argument[3];
	HandleCommandMessage message;
	Game gameBeforeMove = *game;
	ResponseType response = executeUserMoveCommand(rowFrom, colFrom, rowTo,
			colTo, &(game->board), game->currentPlayer);
	switch (response) {
	//case where no move should be done:
	case InvalidPosition:
		message.messageType = errorSetMovePositionsMessage;
		return message;
	case NotYourPiece:
		message.messageType = errorSetMoveNotYourPieceMessage;
		return message;
	case IllegalMove:
		message.messageType = errorIllegalMoveMessage;
		return message;
	case PawnPromotionNeeded:
		message.messageType = pawnPromoteNeededMessage;
		return message;

		//cases where a move should be done:
	case AteOpponentsPiece_PawnPromote:
		message.messageType = pawnPromoteMessage;
		break;
	case AteOpponentsPiece:
		message.messageType = setMoveMessage;
		break;
	case MadeMove_Pawn_Promote:
		message.messageType = pawnPromoteMessage;
		break;
	case MadeMove:
		message.messageType = setMoveMessage;
		break;
	default:
		break;
	}
	for (int j = 0; j < 4; ++j) {
		game->lastMove[j] = command.argument[j];
	}
	Piece piece;
	game->needToReprintBoard = 1;
	game->gameHistory->historyIndex++;
	if (game->gameHistory->historyIndex >= MAX_HISTORY_SIZE) {
		game->gameHistory->historyIndex -= MAX_HISTORY_SIZE;
	}
	game->gameHistory->gameHistoryArray[game->gameHistory->historyIndex]
			= gameBeforeMove;
	game->gameHistory->lenght++;
	if (game->gameHistory->lenght > MAX_HISTORY_SIZE) {
		game->gameHistory->lenght--;
	}
	getPieceAt(command.argument[2], command.argument[3], &(game->board), &piece);
	message.argument[0] = piece.type;
	switchPlayer(game);
	return message;
}

HandleCommandMessage handleCastleMove(Command command, Game *game) {
	HandleCommandMessage message;
	message.messageType = errorCastleMoveIllegalMoveMessage;
	return message;
}

HandleCommandMessage handleGetMoves(Command command, Game *game) {
	HandleCommandMessage message;
	char row = command.argument[0];
	char col = command.argument[1];
	message.getMovesResponse = executeUserGetMovesCommand(row, col,
			&(game->board), game->currentPlayer);
	switch (message.getMovesResponse.type) {
	case InvalidPosition:
		message.messageType = errorGetMovesInvalidPositionMessage;
		break;
	case NotYourPiece:
		message.messageType = errorGetMovesNotYourPieceMessage;
		break;
	default:
		message.messageType = getMovesMessage;
		break;
	}
	return message;
}

HandleCommandMessage handleSaveGame(Command command, Game *game) {
	HandleCommandMessage message;
	message.messageType = successMessage;
	int gameMode = game->gameMode - '0', difficulty = game->difficulty - '0';
	int res = saveGameToFile(&(game->board), game->currentPlayer, gameMode,
			difficulty, game->player1Color, command.stringArgument);
	if (res != FAIL) {
	} else {
		message.messageType = errorSaveMessage;
	}
	return message;
}

HandleCommandMessage handleUndoMove(Game *game) {
	HandleCommandMessage message;
	if (game->gameMode == PlayerVsPlayer && !(CAN_UNDO_IN_2_PLAYER_MODE)) {
		message.messageType = errorUndo2PlayerModeMessage;
	} else if (game->gameHistory->lenght < 2) {
		message.messageType = errorUndoEmptyHistoryMessage;
	} else {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				message.argument[i * 4 + j] = game->lastMove[j];
			}
			*game
					= game->gameHistory->gameHistoryArray[game->gameHistory->historyIndex];
			game->gameHistory->historyIndex--;
			if (game->gameHistory->historyIndex < 0)
				game->gameHistory->historyIndex += MAX_HISTORY_SIZE;
			game->gameHistory->lenght--;
		}
		//TODO need to print board?
		game->needToReprintBoard = 1;
		message.messageType = undoMessage;
	}
	return message;
}

Command getComputerMove(Game *game) {
	Command command;
	command.commandType = setMove;
	command.numberOfArgs = 4;
	char rowFrom, colFrom, rowTo, colTo;
	MiniMaxMove miniMaxMove;

	if (game->difficulty == '5') {
		minimax(&(game->board), 5, INT_MIN, INT_MAX, game->currentPlayer,
				amazingScoreFunction, &miniMaxMove, 1);
	} else {
		minimax(&(game->board), game->difficulty - '0', INT_MIN, INT_MAX,
				game->currentPlayer, amazingScoreFunction, &miniMaxMove, 1); //TODO do we need the fast scoring funciton\ trivial?

	}

	rowFrom = getRowFromLocationIndex(
			getLocationIndexForPieceIndex(&(game->board),
					miniMaxMove.pieceIndex));
	colFrom = getColFromLocationIndex(
			getLocationIndexForPieceIndex(&(game->board),
					miniMaxMove.pieceIndex));
	rowTo = getRowFromLocationIndex(miniMaxMove.toLocationIndex);
	colTo = getColFromLocationIndex(miniMaxMove.toLocationIndex);

	command.argument[0] = rowFrom;
	command.argument[1] = colFrom;
	command.argument[2] = rowTo;
	command.argument[3] = colTo;
	return command;
}

CheckmateType getCheckmate(Game *game) {
	int thretened = (isKingThreatened(game->currentPlayer, &(game->board))
			== SUCCESS);
	int hasMoves = (hasLegalMoves(game->currentPlayer, &(game->board))
			== SUCCESS);
	int check = 0;
	int checkMate = 0;
	if (thretened) {
		if (hasMoves) {
			check = 1;
		} else {
			checkMate = 1;
		}
	} else {
		if (hasMoves) {
			return noCheck;
		} else {
			return tie;
		}
	}
	if (getCurrentPlayerColor(game) == White) {
		if (check) {
			return whiteChecked;
		}
		if (checkMate) {
			return whiteCheckmated;
		}
	} else {
		if (check) {
			return blackChecked;
		}
		if (checkMate) {
			return blackCheckmated;
		}
	}
	return noCheck;
}

void printGame(Game *game) {
	printBoard(&(game->board), game->player1Color);
}

void switchPlayer(Game *game) {
	if (game->currentPlayer == Player1) {
		game->currentPlayer = Player2;
	} else {
		game->currentPlayer = Player1;
	}
}

Color getCurrentPlayerColor(Game *game) {
	if (game->currentPlayer == Player1) {
		if (game->player1Color == White) {
			return White;
		} else {
			return Black;
		}
	} else {
		if (game->player1Color == White) {
			return Black;
		} else {
			return White;
		}
	}
}
