/*
 * mainGameLoop.c
 *
 *  Created on: 19 July 2017
 *      Author: kessi
 */

#include "CommandLineGame.h"

//create a empty game board
static const Game EmptyGame;

void commandLineGameLoop() {
	commandLineState state = settingCommandState;
	Game game = EmptyGame;
	Command command;
	HandleCommandMessage commandMessage;

	setGameDefultValue(&game);
	command.commandType = resetGame;

	while (command.commandType != quitGame && state != gameEndedCommandState) {
		if (state == settingCommandState) {
			if (command.commandType == resetGame) {
				game = EmptyGame;
				setGameDefultValue(&game);
				printf("%s", SETTING_STATE_FIRST_MESSAGE);
			}
			command = getNextSettingCommand();
		} else if (state == gameCommandState) {
			if (isUserMove(&game)) {
				//TODO: print game board
				printf(ASK_FOR_PLAYER_MOVE_FORMAT_STRING,
						((game.currentPlayer == Player1)
								^ (game.player1Color == Black)) ?
								WHITE_COLOR_SMALL_STRING :
								BLACK_COLOR_SMALL_STRING);
				command = getNextGameCommand();
			} else { //Computer Move
				command = getComputerMove(&game);
			}
		}

		commandMessage = handleCommand(command, &game);
		printCommandLineMessages(&game, command, commandMessage);
		switchStateIfNeeded(command, &state);
		handleCheckmates(&game, &state);
	}
}

int isUserMove(Game* game) {
	if (game->gameMode == PlayerVsPlayer) {
		return 1;
	} else if (game->currentPlayer == game->player1Color) {
		return 1;
	}
	return 0;
}

void handlePrintSettingMessage(HandleCommandMessage message) {
	if (message.argument[0] == PlayerVsComputer) {
		printf(PRINT_SETTING_FORMAT_IN_GAME_MODE_1_STRING, message.argument[1],
				message.argument[2] == White ?
						WHITE_COLOR_STRING : BLACK_COLOR_STRING);
	} else {
		printf("%s", PRINT_SETTING_FORMAT_IN_GAME_MODE_2_STRING);
	}
}

void handlePrintUndoMessage(Game * game, HandleCommandMessage message) {
	Color currentPlayerColor =
			((game.currentPlayer == Player1) ^ (game.player1Color == Black)) ?
					BLACK_COLOR_SMALL_STRING : WHITE_COLOR_SMALL_STRING;
}

void handlePrintMove(Game* game, Command command, HandleCommandMessage message) {
	//if game is against AI and the current player is after the AI:
	int moveWasComputerMove = (game->gameMode == PlayerVsComputer
			&& game->currentPlayer == game->player1Color);
	if (moveWasComputerMove) {
		printf(COMPUTER_MOVE_FORMAT_STRING, pieceName(message.argument[0]),
				command.argument[0], command.argument[1], command.argument[2],
				command.argument[3]);
	}

	CheckmateType checkmateType = getCheckmate(game);
	handlePrintCheckmate(checkmateType, moveWasComputerMove);
}

void handlePrintCheckmate(CheckmateType checkmateType,
		int moveWasComputerMove) {
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

void handleCheckmates(Game* game, commandLineState* state) {
	if (*state == gameCommandState) {
		CheckmateType checkmateType = getCheckmate(game);
		if (checkmateType == whiteCheckmated || checkmateType == blackCheckmated
				|| checkmateType == tie) {
			*state = gameEndedCommandState;
		}
	}
}

void switchStateIfNeeded(Command command, commandLineState* state) {
	if (command.commandType == resetGame) {
		*state = settingCommandState;
	} else if (command.commandType == resetGame) {
		*state = gameCommandState;
	}
}

void setGameDefultValue(Game* game) {
	Command command;
	command.commandType = loadDefaultSettings;
	handleCommand(command, game);
}

void printCommandLineMessages(Game* game, Command command,
		HandleCommandMessage message) {
	switch (message.messageType) {
	case successMessage:
		break;
	case setGameModeMessage:
		printf(SET_GAME_MODE_FORMAT_STRING, message.argument[0]);
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
	default:
		printf("%s", "something wrong happened here");
		break;
	}
}
