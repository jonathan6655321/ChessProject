/*
 * Game.h
 *
 *  Created on: 19 ???? 2017
 *      Author: kessi
 */
#ifndef GAME_H_
#define GAME_H_
#include "GameBoard.h"
#include "constants.h"

//CONSTANTS:
#define MAX_HISTORY_SIZE 6
#define MAX_COMMAND_LENGTH 1024
#define DEFAULT_GAME_MODE PlayerVsComputer
#define DEFAULT_DIFFICULTY '2'
#define DEFAULT_USER_COLOR WhiteColor
#define CAN_HANDLE_EXPERT_DIFFICULTY '1'

//STRUCTS&ENUMS:
typedef enum {
	PlayerVsComputer = '1', PlayerVsPlayer = '2'
} GameMode;

typedef enum ColorType{
	BlackColor = '0',
	WhiteColor = '1'
}ColorType;


typedef struct Game {
	GameBoard board;
	char history[MAX_HISTORY_SIZE][10]; //TODO: implements.
	char difficulty;
	ColorType player1Color;
	GameMode gameMode;
	ColorType currentPlayer;
} Game;

typedef enum {
	//settings commands
	setGameMode,
	setDifficulty,
	setUserColor,
	loadSettings,
	loadDefaultSettings,
	printSettings,
	startGame,
	//game commands
	setMove,
	getMoves,
	saveGame,
	undoMove,
	resetGame,
	//general commands
	quitGame,
	invalidCommand
} CommandType;

typedef struct Command {
	CommandType commandType;
	char stringArgument[MAX_COMMAND_LENGTH];
	char argument[4];
	int numberOfArgs;
} Command;

typedef enum {
	successMessage,
	setGameModeMessage,
	errorSetGameModeMessage,
	errorSetDifficultyMessage,
	errorExpertSetDifficultyMessage,
	errorLoadMessage,
	printSettingMessage,
	errorSetMovePositionsMessage,
	errorSetMoveNotYourPieceMessage,
	errorIllegalMoveMessage,
	setMoveMessage,
	errorSaveMessage,
	errorUndo2PlayerModeMessage,
	errorUndoEmptyHistoryMessage,
	undoMessage,
	resetMessage,
	invalidCommandMessage
} HandleCommandMessageType;

typedef enum {
	whiteChecked, whiteCheckmated, blackChecked, blackCheckmated, tie, noCheck
} CheckmateType;

typedef struct HandleCommandMessage {
	HandleCommandMessageType messageType;
	char argument[4];
//TODO: add what Somer will output from game
} HandleCommandMessage;

//METHODS
HandleCommandMessage handleCommand(Command command, Game* game);

HandleCommandMessage handleSetGameMode(Command command, Game* game);
HandleCommandMessage handleSetDefult(Game* game);
HandleCommandMessage handleSetDifficulty(Command command, Game* game);
HandleCommandMessage handleSetUserColor(Command command, Game* game);
HandleCommandMessage handleLoadSettings(Command command, Game* game);
HandleCommandMessage handlePrintSettings(Game* game);
//TODO: make the first more if player color 1 is black
HandleCommandMessage handleStartGame(Game* game);
HandleCommandMessage handleSetMove(Command command, Game* game);
HandleCommandMessage handleGetMoves(Command command, Game* game);
HandleCommandMessage handleSaveGame(Command command, Game* game);
HandleCommandMessage handleUndoMove(Game* game);

Command getComputerMove(Game* game);
CheckmateType getCheckmate(Game* game);

#endif /* GAME_H_ */
