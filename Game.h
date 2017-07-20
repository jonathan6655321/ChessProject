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
#define DEFAULT_USER_COLOR White
#define DEFAULT_CURRENT_PLAYER Player1
#define CAN_HANDLE_EXPERT_DIFFICULTY '1'

//STRUCTS&ENUMS:
typedef enum {
	PlayerVsComputer = '1', PlayerVsPlayer = '2'
} GameMode;


typedef struct Game {
	GameBoard board;
	Piece historyPiecesBefore[MAX_HISTORY_SIZE];
	Piece historyPiecesAfter[MAX_HISTORY_SIZE];
	char historyPositions[MAX_HISTORY_SIZE][4];
	char historyIsSet[MAX_HISTORY_SIZE];
	int historyIndex;
	char difficulty;
	Color player1Color;
	GameMode gameMode;
	Player currentPlayer;
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
	char argument[8];
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
void initHistoryArray(Game* game) ;

#endif /* GAME_H_ */
