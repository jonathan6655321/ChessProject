/*
 * Parser.c
 *
 *  Created on: 19 ???? 2017
 *      Author: kessi
 */
#include "Parser.h"

void getNextCommandLine(char *line) {
    fgets(line, MAX_COMMAND_LENGTH, stdin);
}

StringCommand getNextStringCommand() {
    char line[MAX_COMMAND_LENGTH];
    getNextCommandLine(line);
    StringCommand stringCommand;
    int lineIndex = 0, stringIndex = 0;
    //get string until first white space - COMMAND
    while (lineIndex < MAX_COMMAND_LENGTH && line[lineIndex] != '\0' && line[lineIndex] != '\n'
           && line[lineIndex] != ' ') {
        stringCommand.stringCommand[stringIndex] = line[lineIndex];
        lineIndex++;
        stringIndex++;
    }
    lineIndex++;
    stringCommand.stringCommand[stringIndex] = '\0';

    //get string after first white space - arguments
    stringIndex = 0;
    while (lineIndex < MAX_COMMAND_LENGTH && line[lineIndex] != '\0'
           && line[lineIndex] != '\n') {
        stringCommand.stringArgument[stringIndex] = line[lineIndex];
        lineIndex++;
        stringIndex++;
    }
    stringCommand.stringArgument[stringIndex] = '\0';

    return stringCommand;
}

CommandType parseStringSettingCommandType(char *stringCommand) {
    if (strcmp(stringCommand, LOAD_DEFAULT_SETTINGS_COMMAND_STRING) == 0) {
        return loadDefaultSettings;
    } else if (strcmp(stringCommand, SET_DIFFICULTY_COMMAND_STRING) == 0) {
        return setDifficulty;
    } else if (strcmp(stringCommand, SET_GAME_MODE_COMMAND_STRING) == 0) {
        return setGameMode;
    } else if (strcmp(stringCommand, LOAD_SETTINGS_COMMAND_STRING) == 0) {
        return loadSettings;
    } else if (strcmp(stringCommand, SET_USER_COLOR_COMMAND_STRING) == 0) {
        return setUserColor;
    } else if (strcmp(stringCommand, PRINT_SETTINGS_COMMAND_STRING) == 0) {
        return printSettings;
    } else if (strcmp(stringCommand, QUIT_GAME_COMMAND_STRING) == 0) {
        return quitGame;
    } else if (strcmp(stringCommand, START_GAME_COMMAND_STRING) == 0) {
        return startGame;
    } else {
        return invalidCommand;
    }
}

void parseSettingCommandsArguments(Command *settingCommand) {
    switch (settingCommand->commandType) {
        case setGameMode:
        case setDifficulty:
        case setUserColor:
            settingCommand->numberOfArgs = sscanf(settingCommand->stringArgument,
                                                  SETTING_ARGUMENT_FORMAT_STRING, &settingCommand->argument[0]);
            if(settingCommand->numberOfArgs != 1){
                settingCommand->commandType = invalidCommand;
            }
            break;
        default:
            return;
    }
}

Command parseStringSettingCommand(StringCommand stringCommand) {
    Command settingCommand;
    strcpy(settingCommand.stringArgument, stringCommand.stringArgument);
    //get command's type:
    settingCommand.commandType = parseStringSettingCommandType(
            stringCommand.stringCommand);
    //get command's arguments:
    parseSettingCommandsArguments(&settingCommand);
    return settingCommand;
}

Command getNextSettingCommand() {
    StringCommand stringCommand = getNextStringCommand();
    return parseStringSettingCommand(stringCommand);
}

CommandType parseStringGameCommandType(char *stringCommand) {
    if (strcmp(stringCommand, SET_MOVE_COMMAND_STRING) == 0) {
        return setMove;
    } else if (strcmp(stringCommand, GET_MOVES_COMMAND_STRING) == 0) {
        return getMoves;
    } else if (strcmp(stringCommand, SAVE_GAME_COMMAND_STRING) == 0) {
        return saveGame;
    } else if (strcmp(stringCommand, UNDO_MOVE_COMMAND_STRING) == 0) {
        return undoMove;
    } else if (strcmp(stringCommand, RESET_GAME_COMMAND_STRING) == 0) {
        return resetGame;
    } else if (strcmp(stringCommand, QUIT_GAME_COMMAND_STRING) == 0) {
        return quitGame;
    } else {
        return invalidCommand;
    }
}

void parseGameCommandsArguments(Command *gameCommand) {
    switch (gameCommand->commandType) {
        case setMove:
            gameCommand->numberOfArgs = sscanf(gameCommand->stringArgument,
                                               SET_MOVE_ARGUMENT_FORMAT_STRING, &gameCommand->argument[0],
                                               &gameCommand->argument[1], &gameCommand->argument[2],
                                               &gameCommand->argument[3]);
            if(gameCommand->numberOfArgs != 4){
                gameCommand->commandType = invalidCommand;
            }
            break;
        case getMoves:
            gameCommand->numberOfArgs = sscanf(gameCommand->stringArgument,
                                               GET_MOVES_ARGUMENT_FORMAT_STRING, &gameCommand->argument[0],
                                               &gameCommand->argument[1]);
            if(gameCommand->numberOfArgs != 2){
                gameCommand->commandType = invalidCommand;
            }
            break;
        default:
            return;
    }
}

Command parseStringGameCommand(StringCommand stringCommand) {
    Command gameCommand;
    strcpy(gameCommand.stringArgument, stringCommand.stringArgument);
    //get command's type:
    gameCommand.commandType = parseStringGameCommandType(
            stringCommand.stringCommand);
    //get command's arguments:
    parseGameCommandsArguments(&gameCommand);
    return gameCommand;
}

Command getNextGameCommand() {
    StringCommand stringCommand = getNextStringCommand();
    return parseStringGameCommand(stringCommand);
}
