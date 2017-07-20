#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <string.h>
#include "Game.h"


//COMMANDS STRINGS:
	//general commands string
		#define QUIT_GAME_COMMAND_STRING "quit"

	//setting commands string
		#define SET_GAME_MODE_COMMAND_STRING "game_mode"
		#define SET_DIFFICULTY_COMMAND_STRING "difficulty"
		#define SET_USER_COLOR_COMMAND_STRING "user_color"
		#define LOAD_SETTINGS_COMMAND_STRING "load"
		#define LOAD_DEFAULT_SETTINGS_COMMAND_STRING "default"
		#define PRINT_SETTINGS_COMMAND_STRING "print_setting"
		#define START_GAME_COMMAND_STRING "start"

	//game commands string
		#define SET_MOVE_COMMAND_STRING "move"
		#define GET_MOVES_COMMAND_STRING "get_moves"
		#define SAVE_GAME_COMMAND_STRING "save"
		#define UNDO_MOVE_COMMAND_STRING "undo"
		#define RESET_GAME_COMMAND_STRING "reset"
		#define QUIT_GAME_COMMAND_STRING "quit"

//FORMAT STRINGS:
	//setting format string
		#define SETTING_ARGUMENT_FORMAT_STRING "%c"

	//game format string
		#define SET_MOVE_ARGUMENT_FORMAT_STRING "<%c,%c> to <%c,%c>"
		#define GET_MOVES_ARGUMENT_FORMAT_STRING "<%c,%c>"


//STRUCTS&ENUMS:
	typedef struct StringCommand{
		char stringCommand[MAX_COMMAND_LENGTH];
		char stringArgument[MAX_COMMAND_LENGTH];
	} StringCommand;


	//METHODS:
	//GENERAL METHODS:
		void getNextCommandLine(char* line);
		StringCommand getNextStringCommand();

	//SETTING COMMANDS:
		CommandType parseStringSettingCommandType(char* stringCommand);
		void parseSettingCommandsArguments(Command* settingCommand);
		Command parseStringSettingCommand(StringCommand stringCommand);
		Command getNextSettingCommand();

	//GAME COMMANDS:
		CommandType parseStringGameCommandType(char* stringCommand);
		void parseGameCommandsArguments(Command* gameCommand);
		Command parseStringGameCommand(StringCommand stringCommand);
		Command getNextGameCommand();
#endif /* PARSER_H_ */
