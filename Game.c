/*
 * Game.c
 *
 *  Created on: 19 ???? 2017
 *      Author: kessi
 */
#include "Game.h"

HandleCommandMessage handleCommand(Command command, Game* game) {
	HandleCommandMessage message;
	switch (command.commandType) {
	case loadDefaultSettings:
		return handleSetDefult(game);
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
	case saveGame:
		return handleSaveGame(command, game);
	case undoMove:
		return handleUndoMove(game);
	default:
		message.messageType = invalidCommandMessage;
	}
	return message;
}

HandleCommandMessage handleSetGameMode(Command command, Game* game) {
	HandleCommandMessage message;
	char gameModeChar = command.stringArgument[0];
	message.argument[0] = gameModeChar;
	if (command.numberOfArgs == 1 && '1' <= gameModeChar
			&& gameModeChar <= '2') {
		message.messageType = setGameModeMessage;
		game->gameMode = gameModeChar;
	} else {
		message.messageType = errorSetGameModeMessage;
	}
	return message;
}
HandleCommandMessage handleSetDefult(Game* game) {
	game->gameMode = DEFAULT_GAME_MODE;
	game->difficulty = DEFAULT_DIFFICULTY;
	game->player1Color = DEFAULT_USER_COLOR;
    initGame(&(game->board), game->player1Color);

	HandleCommandMessage message;
	message.messageType = successMessage;
	return message;
}
HandleCommandMessage handleSetDifficulty(Command command, Game* game) {
	HandleCommandMessage message;
	char difficulty = command.stringArgument[0];
	message.argument[0] = command.stringArgument[0];
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
HandleCommandMessage handleSetUserColor(Command command, Game* game) {
	HandleCommandMessage message;
	char color = command.stringArgument[0];
	if (command.numberOfArgs == 1 && game->gameMode != PlayerVsPlayer
			&& '0' <= color && color <= '1') {
		game->player1Color = color;
		message.messageType = successMessage;
	} else {
		message.messageType = invalidCommandMessage;
	}
	return message;
}
HandleCommandMessage handleLoadSettings(Command command, Game* game) {
	HandleCommandMessage message;
	message.messageType = errorLoadMessage;
//TODO: implement load from file.
	return message;
}
HandleCommandMessage handlePrintSettings(Game* game) {
	HandleCommandMessage message;
	message.messageType = printSettingMessage;
	message.argument[0] = game->gameMode == PlayerVsComputer;
	message.argument[1] = game->difficulty;
	message.argument[2] = game->player1Color;
	return message;
}
HandleCommandMessage handleStartGame(Game* game) {
	game->currentPlayer = White;
	HandleCommandMessage message;
	message.messageType = successMessage;
	return message;
}
HandleCommandMessage handleSetMove(Command command, Game* game) {
	HandleCommandMessage message;
	message.messageType = errorLoadMessage;
	return message;
//TODO: return in arg[0] piece type
}
HandleCommandMessage handleGetMoves(Command command, Game* game) {
	HandleCommandMessage message;
	message.messageType = errorLoadMessage;
	return message;
//TODO: return in new struct from Somer the get moves
}
HandleCommandMessage handleSaveGame(Command command, Game* game) {
	HandleCommandMessage message;
	message.messageType = errorLoadMessage;
//TODO: implement save to file.
	return message;
}
HandleCommandMessage handleUndoMove(Game* game) {
	HandleCommandMessage message;
	message.messageType = errorLoadMessage;
//TODO: undo move.
	return message;
}
Command getComputerMove(Game* game) {
	Command command;
//TODO: implement createComputerMove.
	return command;
}
CheckmateType getCheckmate(Game* game) {
	return 0;
//TODO: return checkmate from game board somer version.
}

