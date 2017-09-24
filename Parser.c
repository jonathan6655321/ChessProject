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
    } else if (strcmp(stringCommand, SET_MOVE_COMMAND_STRING) == 0) {
        return setMove;
    } else if (strcmp(stringCommand, CASTLE_COMMAND_STRING) == 0) {
        return castleMove;
    } else if (strcmp(stringCommand, GET_MOVES_COMMAND_STRING) == 0) {
        return getMoves;
    } else if (strcmp(stringCommand, SAVE_GAME_COMMAND_STRING) == 0) {
        return saveGame;
    } else if (strcmp(stringCommand, UNDO_MOVE_COMMAND_STRING) == 0) {
        return undoMove;
    } else if (strcmp(stringCommand, PAWN_PROMOTE_TO_PAWN_STRING) == 0) {
        return pawnPromoteToPawn;
    } else if (strcmp(stringCommand, PAWN_PROMOTE_TO_ROOK_STRING) == 0) {
        return pawnPromoteToRook;
    } else if (strcmp(stringCommand, PAWN_PROMOTE_TO_KNIGHT_STRING) == 0) {
        return pawnPromoteToKnight;
    } else if (strcmp(stringCommand, PAWN_PROMOTE_TO_BISHOP_STRING) == 0) {
        return pawnPromoteToBishop;
    } else if (strcmp(stringCommand, PAWN_PROMOTE_TO_QUEEN_STRING) == 0) {
        return pawnPromoteToQueen;
    } else if (strcmp(stringCommand, RESET_GAME_COMMAND_STRING) == 0) {
        return resetGame;
    } else if (strcmp(stringCommand, QUIT_GAME_COMMAND_STRING) == 0) {
        return quitGame;
    } else {
        return invalidCommand;
    }
}

void parseCommandsArguments(Command *command) {
    int x,x1;
	switch (command->commandType) {
        case setGameMode:
        case setDifficulty:
        case setUserColor:
            command->numberOfArgs = sscanf(command->stringArgument,
                                           SETTING_ARGUMENT_FORMAT_STRING, &command->argument[0]);
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
            }else{
            	command->argument[0] = '0' + x;
            	command->argument[2] = '0' + x1;
            }
            break;
        case castleMove:
        case getMoves:
            command->numberOfArgs = sscanf(command->stringArgument,
                                           GET_MOVES_ARGUMENT_FORMAT_STRING, &x,
                                           &command->argument[1]);
            if (command->numberOfArgs != 2) {
                command->commandType = invalidCommand;
            }else{
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
        case castleMove:
        case getMoves:
        case undoMove:
        case saveGame:
        case resetGame:
        case quitGame:
            break;
        default:
            command.commandType = invalidCommand;
    }
    if(command.commandType == castleMove && !CAN_HANDLE_CASTLE_MOVE){
        command.commandType = invalidCommand;
    }
    return command;
}

Command getNextPawnPromotionCommand() {
    StringCommand stringCommand = getNextStringCommand();
    Command command = parseStringCommand(stringCommand);
    switch (command.commandType) {
        case pawnPromoteToPawn:
        case pawnPromoteToBishop:
        case pawnPromoteToKnight:
        case pawnPromoteToRook:
        case pawnPromoteToQueen:
        case resetGame:
        case quitGame:
            break;
        default:
            command.commandType = invalidCommand;
    }
    return command;
}
