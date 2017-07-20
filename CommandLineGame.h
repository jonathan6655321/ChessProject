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

void commandLineGameLoop();
int isUserMove(Game* game);
void printCommandLineMessages(Game* game, Command command,
		HandleCommandMessage message);
void switchStateIfNeeded(Command command, commandLineState* state);
void setGameDefaultValue(Game *game);
void handlePrintMove(Game* game, Command command, HandleCommandMessage message);
void handlePrintSettingMessage(HandleCommandMessage message);
void handlePrintCheckmate(CheckmateType checkmateType,
		int moveWasComputerMove);
void handleCheckmates(Game* game, commandLineState* state);
void handlePrintUndoMessage(Game * game, HandleCommandMessage message) ;

#endif /* COMMANDLINEGAME_H_ */
