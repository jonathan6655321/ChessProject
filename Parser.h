#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <string.h>
#include "Game.h"
#include "CommandLineCommands.h"

//FORMAT STRINGS:
    //setting format string
        #define SETTING_ARGUMENT_FORMAT_STRING "%c"

    //game format string
        #define SET_MOVE_ARGUMENT_FORMAT_STRING "<%c,%c> to <%c,%c>"
        #define GET_MOVES_ARGUMENT_FORMAT_STRING "<%c,%c>"


//STRUCTS&ENUMS:
    typedef struct StringCommand {
        char stringCommand[MAX_COMMAND_LENGTH];
        char stringArgument[MAX_COMMAND_LENGTH];
    } StringCommand;


/*!
 * load into line the next line.
 * @param line - buffer of char sized MAX_COMMAND_LENGTH.
 */
void getNextCommandLine(char *line);

/*!
 * get next line and then split it to command type and command argument (first white space).
 * @return
 *      StringCommand containing string of the command type received and the argument string received.
 */
StringCommand getNextStringCommand();

/*!
 * parse a string command into command type.
 * @param stringCommand - a string command containing both command string and argument string.
 * @return
 *      the command type if success, and invalid command if not.
 */
CommandType parseStringSettingCommandType(char *stringCommand);

/*!
 * parse the arguments of a specific setting command.
 * @param settingCommand the setting command it's argument are needed to parse.
 */
void parseSettingCommandsArguments(Command *settingCommand);

/*!
 * parse a string command into command type (parse both command type and arguments).
 * @param stringCommand - the string command containing both the argument and the command in string form.
 * @return a parsed setting command.
 */
Command parseStringSettingCommand(StringCommand stringCommand);

/*!
 * get user input, parse it, and return the command the user entered.
 * @return Command - containing the argument and the type the user enteted.
 */
Command getNextSettingCommand();

/*!
 * parse a string into command type.
 * @param stringCommand - a string containing the command.
 * @return the command type, or invalidCommand.
 */
CommandType parseStringGameCommandType(char *stringCommand);

/*!
 * parse the arguments of a specific game command.
 * @param gameCommand the game command and it's argument are needed to parse.
 * @return a parsed game command.
 */
void parseGameCommandsArguments(Command *gameCommand);

/*!
 * parse a string command into command type (parse both command type and arguments).
 * @param stringCommand - the string command containing both the argument and the command in string form.
 * @return a parsed setting command.
 */
Command parseStringGameCommand(StringCommand stringCommand);

/*!
 * get user input, parse it, and return the command the user entered.
 * @return Command - containing the argument and the type the user entered.
 */
Command getNextGameCommand();

#endif /* PARSER_H_ */
