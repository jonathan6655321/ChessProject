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
void handleCommandLineMessages(Game* game, Command command,
		HandleCommandMessage message);
void switchStateIfNeeded(Command command, commandLineState* state);
void setGameDefultValue(Game* game);
void printMove(Game* game, Command command, HandleCommandMessage message);
void handlePrintSettingMessage(HandleCommandMessage message);
void handleCheckmatePrinting(CheckmateType checkmateType,
		int moveWasComputerMove);
void handleCheckmates(Game* game, commandLineState* state);
#endif /* COMMANDLINEGAME_H_ */
