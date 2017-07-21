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
 * @param stringCommand - a string command containing command string.
 * @return
 *      the command type if success, and invalid command if not.
 */
CommandType parseStringCommandType(char *stringCommand);

/*!
 * parse the arguments of a specific command.
 * @param command the command it's argument are needed to parse.
 */
void parseSettingCommandsArguments(Command *command);

/*!
 * parse a string command into command type (parse both command type and arguments).
 * @param stringCommand - the string command containing both the argument and the command in string form.
 * @return a parsed setting command.
 */
Command parseSettingCommand(StringCommand stringCommand);

/*!
 * get user input, parse it, and return the command the user entered. (return only setting commands)
 * @return Command - containing the argument and the type the user enteted.
 */
Command getNextSettingCommand();

/*!
 * get user input, parse it, and return the command the user entered. (return only game commands)
 * @return Command - containing the argument and the type the user entered.
 */
Command getNextGameCommand();

/*!
 * get user input, parse it, and return the command the user entered. (return only pawn promotion commands)
 * @return Command - containing the type the user entered.
 */
Command getNextPawnPromotionCommand();

#endif /* PARSER_H_ */
