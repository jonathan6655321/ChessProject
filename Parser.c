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

CommandType parseStringCommandType(char *stringCommand) {
    if (strcmp(stringCommand, LOAD_DEFAULT_SETTINGS_COMMAND_STRING) == 0) return loadDefaultSettings;
    if (strcmp(stringCommand, SET_DIFFICULTY_COMMAND_STRING) == 0)        return setDifficulty;
    if (strcmp(stringCommand, SET_GAME_MODE_COMMAND_STRING) == 0)         return setGameMode;
    if (strcmp(stringCommand, LOAD_SETTINGS_COMMAND_STRING) == 0)         return loadSettings;
    if (strcmp(stringCommand, SET_USER_COLOR_COMMAND_STRING) == 0)        return setUserColor;
    if (strcmp(stringCommand, PRINT_SETTINGS_COMMAND_STRING) == 0)        return printSettings;
    if (strcmp(stringCommand, QUIT_GAME_COMMAND_STRING) == 0)             return quitGame;
    if (strcmp(stringCommand, START_GAME_COMMAND_STRING) == 0)            return startGame;
    if (strcmp(stringCommand, SET_MOVE_COMMAND_STRING) == 0)              return setMove;
    if (strcmp(stringCommand, GET_MOVES_COMMAND_STRING) == 0)             return getMoves;
    if (strcmp(stringCommand, SAVE_GAME_COMMAND_STRING) == 0)             return saveGame;
    if (strcmp(stringCommand, UNDO_MOVE_COMMAND_STRING) == 0)             return undoMove;
    if (strcmp(stringCommand, RESET_GAME_COMMAND_STRING) == 0)            return resetGame;
    if (strcmp(stringCommand, QUIT_GAME_COMMAND_STRING) == 0)             return quitGame;
    return invalidCommand;

}

void parseCommandsArguments(Command *command) {
    int x, x1;
    switch (command->commandType) {
        case setGameMode:
        case setDifficulty:
        case setUserColor:
            command->numberOfArgs = sscanf(command->stringArgument, SETTING_ARGUMENT_FORMAT_STRING,
                                           &command->argument[0]);
            if (command->numberOfArgs != 1) {
                command->commandType = invalidCommand;
            }
            break;
        case setMove:
            command->numberOfArgs = sscanf(command->stringArgument,
                                           SET_MOVE_ARGUMENT_FORMAT_STRING, &x,
                                           &command->argument[1], &x1,
                                           &command->argument[3]);
            if (command->numberOfArgs != 4) {
                command->commandType = invalidCommand;
            } else {
                command->argument[0] = '0' + x;
                command->argument[2] = '0' + x1;
            }
            break;
        case getMoves:
            command->numberOfArgs = sscanf(command->stringArgument,
                                           GET_MOVES_ARGUMENT_FORMAT_STRING, &x,
                                           &command->argument[1]);
            if (command->numberOfArgs != 2) {
                command->commandType = invalidCommand;
            } else {
                command->argument[0] = '0' + x;
            }
            break;
        default:
            return;
    }
}

Command parseStringCommand(StringCommand stringCommand) {
    Command command;
    strcpy(command.stringArgument, stringCommand.stringArgument);
    //get command's type:
    command.commandType = parseStringCommandType(
            stringCommand.stringCommand);
    //get command's arguments:
    parseCommandsArguments(&command);
    return command;
}

Command getNextSettingCommand() {
    StringCommand stringCommand = getNextStringCommand();
    Command command = parseStringCommand(stringCommand);
    switch (command.commandType) {
        case loadDefaultSettings:
        case setDifficulty:
        case setGameMode:
        case printSettings:
        case loadSettings:
        case setUserColor:
        case quitGame:
        case startGame:
            break;
        default:
            command.commandType = invalidCommand;
            break;
    }
    return command;
}

Command getNextGameCommand() {
    StringCommand stringCommand = getNextStringCommand();
    Command command = parseStringCommand(stringCommand);
    switch (command.commandType) {
        case setMove:
        case getMoves:
        case undoMove:
        case saveGame:
        case resetGame:
        case quitGame:
            break;
        default:
            command.commandType = invalidCommand;
    }
    return command;
}