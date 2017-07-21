//
// Created by kessi on 21/07/2017.
//

#ifndef CHESSPROJECT_COMMANDLINECOMMANDS_H
#define CHESSPROJECT_COMMANDLINECOMMANDS_H

#include "Parser.h"

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
                #define CASTLE_COMMAND_STRING "castle"
                #define GET_MOVES_COMMAND_STRING "get_moves"
                #define SAVE_GAME_COMMAND_STRING "save"
                #define UNDO_MOVE_COMMAND_STRING "undo"
                #define RESET_GAME_COMMAND_STRING "reset"
                #define QUIT_GAME_COMMAND_STRING "quit"

        //pawn promote commands string
                #define PAWN_PROMOTE_TO_PAWN_STRING "pawn"
                #define PAWN_PROMOTE_TO_ROOK_STRING "rook"
                #define PAWN_PROMOTE_TO_KNIGHT_STRING "knight"
                #define PAWN_PROMOTE_TO_BISHOP_STRING "bishop"
                #define PAWN_PROMOTE_TO_QUEEN_STRING "queen"


#endif //CHESSPROJECT_COMMANDLINECOMMANDS_H
