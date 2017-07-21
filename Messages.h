/*
 * Messages.h
 *
 *  Created on: 19 ???? 2017
 *      Author: kessi
 */

#ifndef MESSAGES_H_
#define MESSAGES_H_

#define SETTING_STATE_FIRST_MESSAGE "Specify game setting or type 'start' to begin a game with the current setting:\n"
#define SET_GAME_MODE_FORMAT_STRING "Game mode is set to %c players\n"
#define SET_GAME_MODE_ERROR_STRING "Wrong game mode\n"
#define SET_DIFFICULTY_EXPERT_ERROR_STRING "Expert level not supported, please choose a value between 1 to 4:\n"
#define SET_DIFFICULTY_ERROR_STRING "Wrong difficulty level. The value should be between 1 to 5\n"
#define LOAD_SETTING_ERROR_STRING "Error: File doesn't exist or cannot be opened\n"
#define PRINT_SETTING_FORMAT_IN_GAME_MODE_1_STRING "SETTINGS:\nGAME_MODE: 1\nDIFFICULTY_LVL: %c\nUSER_CLR: %s\n"
#define PRINT_SETTING_FORMAT_IN_GAME_MODE_2_STRING "SETTINGS:\nGAME_MODE: 2\n"
#define BLACK_COLOR_STRING "BLACK"
#define WHITE_COLOR_STRING "WHITE"
#define BLACK_COLOR_SMALL_STRING "black"
#define WHITE_COLOR_SMALL_STRING "white"
#define QUITING_STRING "Exiting...\n"
#define SET_MOVE_POSITION_ERROR_STRING "Invalid position on the board\n"
#define SET_MOVE_WRONG_PIECE_COLOR_ERROR_STRING "The specified position does not contain your piece\n"
#define SET_MOVE_ILLEGAL_MOVE_ERROR_STRING "Illegal move\n"
#define COMPUTER_MOVE_FORMAT_STRING "Computer: move %s at <%c,%c> to <%c,%c>\n"
#define WHITE_CHECK_STRING "Check: white King is threatened!\n"
#define BLACK_CHECK_STRING "Check: black King is threatened!\n"
#define COMPUTER_CHECK_STRING "Check!\n"
#define WHITE_CHECKMATED_STRING "Checkmate! black player wins the game\n"
#define BLACK_CHECKMATED_STRING "Checkmate! white player wins the game\n"
#define TIE_STRING "The game is tied\n"
#define TIE_STRING2 "The game ends in a tie\n"
//^TODO: one for the PVP and one for PVC, they will probably say that we should only use one of them, but we should check that before we submit
#define ASK_FOR_PLAYER_MOVE_FORMAT_STRING "%s player - enter your move:\n"
#define SAVE_SETTING_ERROR_STRING "File cannot be created or modified\n"
#define UNDO_FOR_2_PLAYERS_ERROR_STRING "Undo command not available in 2 players mode\n"
#define UNDO_EMPTY_HISTORY_ERROR_STRING "Empty history, move cannot be undone\n"
#define UNDO_FORMAT_STRING "Undo move for player %s : <%c,%c> -> <%c,%c>\n"
#define RESTARTING_STRING "Restarting...\n"
#define CASTLING_MOVE_ILLEGAL_ERROR_STRING "Illegal castling move\n"
#define CASTLING_MOVE_NO_ROOK_ERROR_STRING "Wrong position for a rook\n"
#define CASTLING_MOVE_COMPUTER_FORMAT_STRING "Computer: castle King at <%c,%c> and Rook at <%c,%c>\n"
#define PAWN_PROMOTION_REQUEST_STRING "Pawn promotion- please replace the pawn by queen, rook, knight, bishop or pawn:\n"
#define PAWN_PROMOTION_COMPUTER_FORMAT_STRING "Computer: move pawn <%c,%c> to <%c,%c> and promote to %s\n"
#define PAWN_PROMOTION_INVALID_STRING "Invalid Type\n"
#define GET_MOVES_INVALID_POSITION_ERROR_STRING "Invalid position on the board\n"
#define GET_MOVES_NOT_YOUR_PIECE_ERROR_FORMAT_STRING "The specified position does not contain %s player piece\n"


#define PAWN_NAME_STRING "pawn"
#define BISHOP_NAME_STRING "bishop"
#define KNIGHT_NAME_STRING "knight"
#define ROOK_NAME_STRING "rook"
#define QUEEN_NAME_STRING "queen"
#define KING_NAME_STRING "king"

#define pieceNameM(x) (x)==Pawn ? PAWN_NAME_STRING : "error"
#define pieceNameB(x) (x)==Bishop ? BISHOP_NAME_STRING : (pieceNameM(x))
#define pieceNameN(x) (x)==Rook ? KNIGHT_NAME_STRING : (pieceNameB(x))
#define pieceNameR(x) (x)==Knight ? ROOK_NAME_STRING : (pieceNameN(x))
#define pieceNameQ(x) (x)==Queen ? QUEEN_NAME_STRING : (pieceNameR(x))
#define getPieceTypeName(x)  ((x)==King ? KING_NAME_STRING : (pieceNameQ(x)))

#define getColorName(x) ((x)==White ? WHITE_COLOR_SMALL_STRING : BLACK_COLOR_SMALL_STRING)
#define getCAPITALColorName(x) ((x)==White ? WHITE_COLOR_STRING : BLACK_COLOR_STRING)

#endif /* MESSAGES_H_ */
