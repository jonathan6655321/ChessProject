/*
 * mainGameLoop.c
 *
 *  Created on: 19 July 2017
 *      Author: kessi
 */

#include "CommandLineGame.h"
#include "Moves.h"
#include "Game.h"

void commandLineGameLoop() {
	commandLineState state = settingCommandState;
	Game game;
	GameHistory gameHistory;
	Command command;
	HandleCommandMessage commandMessage;

	command.commandType = resetGame;
	while (command.commandType != quitGame) {
		if (state == settingCommandState) {
			if (command.commandType == resetGame) {
				// reset structs
				game = EmptyGame;
				gameHistory = EmptyGameHistory;
				game.gameHistory = &gameHistory;

				// set gave default value
				setGameDefaultValue(&game);
				printf("%s", SETTING_STATE_FIRST_MESSAGE);
			}
			command = getNextSettingCommand();
		} else if (state == gameCommandState) {
			if (isUserMove(&game)) {
				if (game.needToReprintBoard) {
					game.needToReprintBoard = 0;
					printGame(&game);
				}
				printf(ASK_FOR_PLAYER_MOVE_FORMAT_STRING,
						getColorName(getCurrentPlayerColor(&game)));
				command = getNextGameCommand();
			} else { //Computer Move
				command = getComputerMove(&game);
			}
		} else if (state == gameEndedCommandState) {
			// should exit!
			return;
		}
		commandMessage = handleCommand(command, &game);
		handlePawnPromotionLoop(&command, &commandMessage, &game);
		printCommandLineMessages(&game, command, commandMessage);
		switchStateIfNeeded(command, &state);
		handleCheckmates(&game, &state);
	}
}

int isUserMove(Game *game) {
	return (game->gameMode == PlayerVsPlayer || game->currentPlayer == Player1);
}

void handlePrintSettingMessage(HandleCommandMessage message) {
	if (message.argument[0] == PlayerVsComputer) {
		printf(PRINT_SETTING_FORMAT_IN_GAME_MODE_1_STRING, message.argument[1],
				getCAPITALColorName(message.argument[2]));
	} else {
		printf("%s", PRINT_SETTING_FORMAT_IN_GAME_MODE_2_STRING);
	}
}

void handlePrintUndoMessage(Game *game, HandleCommandMessage message) {
	Color currentPlayerColor = getCurrentPlayerColor(game);
	Color lastPlayerColor = getOppositeColor(currentPlayerColor);

	printf(UNDO_FORMAT_STRING, getColorName(lastPlayerColor),
			message.argument[2], message.argument[3], message.argument[0],
			message.argument[1]);
	printf(UNDO_FORMAT_STRING, getColorName(currentPlayerColor),
			message.argument[6], message.argument[7], message.argument[4],
			message.argument[5]);
}

void handlePrintMove(Game *game, Command command, HandleCommandMessage message) {
	//if game is against AI and the current player is after the AI:
	int moveWasComputerMove = (game->gameMode == PlayerVsComputer
			&& game->currentPlayer == Player1);
	if (moveWasComputerMove) {
		printf(COMPUTER_MOVE_FORMAT_STRING,
				getPieceTypeName(message.argument[0]), command.argument[0],
				command.argument[1], command.argument[2], command.argument[3]);
	}

	handlePrintCheckmate(getCheckmate(game), moveWasComputerMove);
}

void handlePrintPawnPromotion(Game *game, Command command) {
	//if game is against AI and the current player is after the AI:
	int moveWasComputerMove = (game->gameMode == PlayerVsComputer
			&& game->currentPlayer == Player1);
	if (moveWasComputerMove) {
		printf(PAWN_PROMOTION_COMPUTER_FORMAT_STRING, command.argument[0],
				command.argument[1], command.argument[2], command.argument[3],
				getPieceTypeName(command.argument[4]));
	}

	handlePrintCheckmate(getCheckmate(game), moveWasComputerMove);
}

void handlePrintCastleMove(Game *game, HandleCommandMessage message) {
	//if game is against AI and the current player is after the AI:
	int moveWasComputerMove = (game->gameMode == PlayerVsComputer
			&& game->currentPlayer == Player1);
	if (moveWasComputerMove) {
		printf(CASTLING_MOVE_COMPUTER_FORMAT_STRING, message.argument[0],
				message.argument[1], message.argument[2], message.argument[3]);
	}
	handlePrintCheckmate(getCheckmate(game), moveWasComputerMove);
}

void handlePrintGetMoves(Game *game, Command command,
		HandleCommandMessage message) {
	int currentIndex;
	char row, col;
	int isPossible, isThreatened, isCapturing, isCastle;
	isCastle = 0;
	// Regular move:
	for (row = '1'; row <= '8'; ++row) {
		for (col = 'A'; col <= 'H'; ++col) {
			currentIndex = rowColToLocationIndex(row, col);
			isPossible
					= message.getMovesResponse.allMoves.legalMovesArray[currentIndex];
			isThreatened
					= message.getMovesResponse.threatenedByOpponentMoves.legalMovesArray[currentIndex];
			isCapturing
					= message.getMovesResponse.opponentAtLocationMoves.legalMovesArray[currentIndex];
			PRINT_SINGLE_GET_MOVE(row, col, isPossible, isThreatened, isCapturing, isCastle);
		}
	}

	// Castle move:
	isCastle = 1;
	// castle move can't be threatened (it's the king!)
	// castle move can't capture anything (need to be unoccupied!).
	isThreatened = 0;
	isCapturing = 0;
	row = command.argument[0];
	char shortCastleCol, longCastleCol;
	if (command.argument[1] == 'E') {
		longCastleCol = 'C';
		shortCastleCol = 'G';
	} else if (command.argument[1] == 'D') {
		longCastleCol = 'F';
		shortCastleCol = 'B';
	} else {
		// We are moving the rook!
		if (command.argument[1] == 'A') {
			longCastleCol = 'D';
			shortCastleCol = 'C';
		} else {
			longCastleCol = 'E';
			shortCastleCol = 'F';
		}
		if (message.getMovesResponse.castleType == LongCastle) {
			currentIndex = rowColToLocationIndex(row, longCastleCol);
		} else {
			currentIndex = rowColToLocationIndex(row, shortCastleCol);
		}
		// if we are moving the rook, we need to check if it's being threatened.
		isThreatened
				= message.getMovesResponse.threatenedByOpponentMoves.legalMovesArray[currentIndex];
	}
	// long castle
	isPossible = (message.getMovesResponse.castleType == BothCastle
			|| message.getMovesResponse.castleType == LongCastle);
	PRINT_SINGLE_GET_MOVE(row, longCastleCol, isPossible, isThreatened, isCapturing, isCastle);
	// short castle
	isPossible = (message.getMovesResponse.castleType == BothCastle
			|| message.getMovesResponse.castleType == ShortCastle);
	PRINT_SINGLE_GET_MOVE(row, shortCastleCol, isPossible, isThreatened, isCapturing, isCastle);
}

void handlePrintCheckmate(CheckmateType checkmateType, int moveWasComputerMove) {
	switch (checkmateType) {
	case blackChecked:
		if (moveWasComputerMove) {
			printf("%s", COMPUTER_CHECK_STRING);
		} else {
			printf("%s", BLACK_CHECK_STRING);
		}
		break;
	case whiteChecked:
		if (moveWasComputerMove) {
			printf("%s", COMPUTER_CHECK_STRING);
		} else {
			printf("%s", WHITE_CHECK_STRING);
		}
		break;
	case blackCheckmated:
		printf("%s", BLACK_CHECKMATED_STRING);
		break;
	case whiteCheckmated:
		printf("%s", WHITE_CHECKMATED_STRING);
		break;
	case tie:
		printf("%s", TIE_STRING);
		break;
	default:
		return;
	}
}

void handleCheckmates(Game *game, commandLineState *state) {
	if (*state == gameCommandState) {
		CheckmateType checkmateType = getCheckmate(game);
		if (checkmateType == whiteCheckmated || checkmateType
				== blackCheckmated || checkmateType == tie) {
			*state = gameEndedCommandState;
		}
	}
}

void switchStateIfNeeded(Command command, commandLineState *state) {
	if (command.commandType == resetGame) {
		*state = settingCommandState;
	} else if (command.commandType == startGame) {
		*state = gameCommandState;
	}
}

void handlePawnPromotionLoop(Command *command, HandleCommandMessage *message,
		Game *game) {
	if (message->messageType == pawnPromoteNeededMessage) { // TODO pawn promotion
		if (CAN_HANDLE_PAWN_PROMOTION) {
			Command pawnCommand;
			pawnCommand.commandType = invalidCommand;
			while (pawnCommand.commandType == invalidCommand) {
				printf("%s", PAWN_PROMOTION_REQUEST_STRING);
				pawnCommand = getNextPawnPromotionCommand();
				if ((pawnCommand.commandType == invalidCommand)) {
					printf("%s", PAWN_PROMOTION_INVALID_STRING);
				}
			}
			switch (pawnCommand.commandType) {
			case pawnPromoteToPawn:
				command->argument[4] = Pawn;
				break;
			case pawnPromoteToRook:
				command->argument[4] = Rook;
				break;
			case pawnPromoteToKnight:
				command->argument[4] = Knight;
				break;
			case pawnPromoteToBishop:
				command->argument[4] = Bishop;
				break;
			case pawnPromoteToQueen:
				command->argument[4] = Queen;
				break;
			case quitGame:
			case resetGame:
				command->commandType = pawnCommand.commandType;
			default:
				break;
			}
			*message = handleCommand(*command, game);
		} else {
			command->argument[4] = Pawn;
		}
	}
}

void setGameDefaultValue(Game *game) {
	Command command;
	command.commandType = loadDefaultSettings;
	handleCommand(command, game);
}

void printCommandLineMessages(Game *game, Command command,
		HandleCommandMessage message) {
	switch (message.messageType) {
	case successMessage:
		break;
	case setGameModeMessage:
		if (message.argument[0] == '1') {
			printf(SET_GAME_MODE_1_STRING);
		} else {
			printf(SET_GAME_MODE_2_STRING);
		}
		break;
	case errorSetGameModeMessage:
		printf("%s", SET_GAME_MODE_ERROR_STRING);
		break;
	case errorExpertSetDifficultyMessage:
		printf("%s", SET_DIFFICULTY_EXPERT_ERROR_STRING);
		break;
	case errorSetDifficultyMessage:
		printf("%s", SET_DIFFICULTY_ERROR_STRING);
		break;
	case errorLoadMessage:
		printf("%s", LOAD_SETTING_ERROR_STRING);
		break;
	case printSettingMessage:
		handlePrintSettingMessage(message);
		break;
	case errorSetMovePositionsMessage:
		printf("%s", SET_MOVE_POSITION_ERROR_STRING);
		break;
	case errorSetMoveNotYourPieceMessage:
		printf("%s", SET_MOVE_WRONG_PIECE_COLOR_ERROR_STRING);
		break;
	case errorIllegalMoveMessage:
		printf("%s", SET_MOVE_ILLEGAL_MOVE_ERROR_STRING);
		break;
	case setMoveMessage:
		handlePrintMove(game, command, message);
		break;
	case pawnPromoteNeededMessage:
		printf("%s", "ERROR: this shouldn't happen...");
		break;
	case pawnPromoteMessage:
		handlePrintPawnPromotion(game, command);
		break;
	case errorCastleMoveNoRookMessage:
		printf("%s", CASTLING_MOVE_NO_ROOK_ERROR_STRING);
		break;
	case errorCastleMoveIllegalMoveMessage:
		printf("%s", CASTLING_MOVE_ILLEGAL_ERROR_STRING);
		break;
	case castleMoveMessage:
		handlePrintCastleMove(game, message);
		break;
	case getMovesMessage:
		handlePrintGetMoves(game, command, message);
		break;
	case errorGetMovesInvalidPositionMessage:
		printf("%s", GET_MOVES_INVALID_POSITION_ERROR_STRING);
		break;
	case errorGetMovesNotYourPieceMessage:
		printf(GET_MOVES_NOT_YOUR_PIECE_ERROR_FORMAT_STRING,
				getColorName(getCurrentPlayerColor(game)));
		break;
	case errorSaveMessage:
		printf("%s", SAVE_SETTING_ERROR_STRING);
		break;
	case errorUndo2PlayerModeMessage:
		printf("%s", UNDO_FOR_2_PLAYERS_ERROR_STRING);
		break;
	case errorUndoEmptyHistoryMessage:
		printf("%s", UNDO_EMPTY_HISTORY_ERROR_STRING);
		break;
	case undoMessage:
		handlePrintUndoMessage(game, message);
		break;
	case resetMessage:
		printf("%s", RESTARTING_STRING);
		break;
	case quitMessage:
		printf("%s", QUITING_STRING);
		break;
	case invalidCommandMessage:
		printf("%s", "Invalid command\n"); //TODO: this wasn't in the PDF so we need to check if we actually need this.
		break;
	}
}
