/*
 * Game.h
 *
 *  Created on: 19 ???? 2017
 *      Author: kessi
 */
#ifndef GAME_H_
#define GAME_H_

#include <string.h>
#include "consoleRendering.h"
#include "Moves.h"
#include "GameBoard.h"
#include "constants.h"

//CONSTANTS:

//STRUCTS&ENUMS:
typedef enum {
    PlayerVsComputer = '1', PlayerVsPlayer = '2'
} GameMode;


typedef struct Game {
    GameBoard board;
    Piece historyPiecesBefore[MAX_HISTORY_SIZE];
    Piece historyPiecesAfter[MAX_HISTORY_SIZE];
    char historyPositions[MAX_HISTORY_SIZE][4];
    char historyNumberOfPieceToSet[MAX_HISTORY_SIZE];
    int historyIndex;
    char difficulty;
    Color player1Color;
    GameMode gameMode;
    Player currentPlayer;
    int needToReprintBoard;
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
    quitMessage,
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
/*!
 * Handle actions on game.
 * @param command - command from user/computer..
 * @param game the game the action is made on.
 * @return handle message depending on the command type.
 */
HandleCommandMessage handleCommand(Command command, Game *game);

/*!
 * Handle changing of game mode.
 * @param command - command from user/computer.
 * @param game - the game the action is made on.
 * @return
 *      setGameModeMessage, if success.
        errorSetGameModeMessage, if game mode illegal.
 */
HandleCommandMessage handleSetGameMode(Command command, Game *game);

/*!
 * Handle action of "set defult" - setting the game variables to their default values.
 * @param game - the game the action is made on.
 * @return successMessage. (can't fail).
 */
HandleCommandMessage handleSetDefault(Game *game);

/*!
 * Handle changing of difficulty.
 * @param command - command from user/computer.
 * @param game - the game the action is made on.
 * @return
 *      successMessage, if changed successfully.
        errorSetDifficultyMessage, if illegal level.
        errorExpertSetDifficultyMessage, if expert level(5) is unsupported.
 */
HandleCommandMessage handleSetDifficulty(Command command, Game *game);

/*!
 * Handle changing the user color in PlayerVSComputer mode.
 * @param command - command from user/computer.
 * @param game - the game the action is made on.
 * @return
 *      successMessage, if successfully change color.
 *      illegalMessage, if color is illegal or if game mode is PlayerVsPlayer.
 */
HandleCommandMessage handleSetUserColor(Command command, Game *game);
//TODO: check if we need to start game immediately after loading. if not then the start game action should be changed accordingly.
/*!
 * Handle load game setting from file.
 * @param command - command from user/computer.
 * @param game - the game the action is made on.
 * @return
 *      successMessage, if successfully loaded the game setting from the file.
 *      errorLoadMessage, if couldn't load the file.
 */
HandleCommandMessage handleLoadSettings(Command command, Game *game);

/*!
 * Handle print game setting command.
 * @param game - the game the action is made on.
 * @return
 *      printSettingMessage, containing the necessary information for the printing:
 *          argument 0: game mode
 *          argument 1: difficulty
 *          argument 2: player color
 */
HandleCommandMessage handlePrintSettings(Game *game);

//TODO: make the first more if player color 1 is black
/*!
 * start the game!
 * also init the board and the history arrays.
 * @param game - the game the action is made on.
 * @return
 *      successMessage, can only success.
 */
HandleCommandMessage handleStartGame(Game *game);

/*!
 * Handle move action, change the board accordingly, save the move to the history array, and change current player.
 * @param command - command from user/computer.
 * @param game - the game the action is made on.
 * @return
 *      errorSetMovePositionsMessage, if position given as command argument is illegal.
 *      errorSetMoveNotYourPieceMessage, if position given as command argument does not contain current player piece.
 *      errorIllegalMoveMessage, if the position the player try to move to is illegal for this piece.
 *      setMoveMessage, if successfully executed move. if so the message contains the following argument:
 *          argument 0: the piece type that was at this position before the move.
 *          argument 1: the piece type that was at this position after the move.
 */
HandleCommandMessage handleSetMove(Command command, Game *game);

/*!
 *
 * @param command - command from user/computer.
 * @param game - the game the action is made on.
 * @return
 */
//TODO: add documentaion after implementing Somer getMoves.
HandleCommandMessage handleGetMoves(Command command, Game *game);

/*!
 * Save the current game to a file.
 * @param command - command from user/computer.
 * @param game - the game the action is made on.
 * @return
 *      errorSaveMessage, if couldn't write to the file location given.
 *      successMessage, if the game saved.
 */
HandleCommandMessage handleSaveGame(Command command, Game *game);

/*!
 *
 * @param game - the game the action is made on.
 * @return
 */

/*!
 * generate a computer move depending on the difficulty.
 * @param game - the game the action is made on.
 * @return
 *      the command needed for invoking this move inside the game.
 */
Command getComputerMove(Game *game);

/*!
 *
 * @param game - the game the action is made on.
 * @return
 */
//TODO: documentaion of this method when done.
CheckmateType getCheckmate(Game *game);

/*!
 * initialize the game history arrays to 0.
 * @param game - the game the action is made on.
 */
void initHistoryArray(Game *game);

/*!
 * @param game - the game the action is made on.
 * @return return the Color of the current Player
 */
Color getCurrentPlayerColor(Game *game);

/*!
 * print the game board to the console.
 * @param game - the game the action is made on.
 */
void printGame(Game *game);

/*!
 * switch current player (Player 1 -> Player 2) Or (Player 2 -> Player 1).
 * @param game - the game the action is made on.
 */
void switchPlayer(Game *game);

#endif /* GAME_H_ */
