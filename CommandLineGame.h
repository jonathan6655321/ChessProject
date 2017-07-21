/*
 * CommandLineGame.h
 *
 *  Created on: 19 ???? 2017
 *      Author: kessi
 */

#ifndef COMMANDLINEGAME_H_
#define COMMANDLINEGAME_H_

#include "Game.h"
#include "Parser.h"
#include "Messages.h"

typedef enum {
    settingCommandState, gameCommandState, gameEndedCommandState
} commandLineState;

/*!
 * start a console game chess.
 */
void commandLineGameLoop();

/*!
 *
 * @param game - the game the action is made on.
 * @return  true if it's a move that need a user input.
 *          otherwise false.
 */
int isUserMove(Game *game);

/*!
 * Handle printing of messages to the console.
 * @param game - the game the action is made on.
 * @param command - the command that was given to the game to execute beforehand.
 * @param message - the message the game return after executing the command.
 */
void printCommandLineMessages(Game *game, Command command,
                              HandleCommandMessage message);

/*!
 * Handle switching states.
 *      resetGame command - switch to setting state.
 *      startGame command - switch to game state.
 * @param command - the command that was given to the game to execute beforehand.
 * @param state - pointer to the current game state.
 */
void switchStateIfNeeded(Command command, commandLineState *state);

/*!
 * send a "set value to default" command to the game.
 * @param game - the game the action is made on.
 */
void setGameDefaultValue(Game *game);

/*!
 * Handle printing the move message after executing.
 * @param game - the game the action is made on.
 * @param command - the command that was given to the game to execute beforehand.
 *          argument[0-3] = <x,y> to <w,z>
 * @param message - move message with
 *          arguement[0] = piece type that was moved.
 */
void handlePrintMove(Game *game, Command command, HandleCommandMessage message);

/*!
 * Handle printing the settings after "print setting" command.
 * @param message - print settings message containing:
 *          argument[0] = game mode
 *          argument[1] = difficulty
 *          argument[2] = user color
 */
void handlePrintSettingMessage(HandleCommandMessage message);

/*!
 * Handle printing of check, checkmate and tie situations.
 * @param checkmateType - the checkmate type that the game returned.
 * @param moveWasComputerMove - true if the last move was made by a computer.
 */
void handlePrintCheckmate(CheckmateType checkmateType,
                          int moveWasComputerMove);

/*!
 * Handle checkmates -> end the game if needed (state - game ended state).
 * @param game - the game the action is made on.
 * @param state - pointer to the current game state.
 */
void handleCheckmates(Game *game, commandLineState *state);

/*!
 * Handle printing the moves that were canceled after an undo command.
 * @param game - the game the action is made on.
 * @param message - an undo message from game containing the data on the moves that were canceled.
 *      argument 0-3 first move that was canceled <x,y> to <w,z>
 *      argument 3-7 second move that was canceled <x,y> to <w,z>
 */
void handlePrintUndoMessage(Game *game, HandleCommandMessage message);

#endif /* COMMANDLINEGAME_H_ */
