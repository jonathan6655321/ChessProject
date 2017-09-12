//
// Created by Jonathan on 9/11/2017.
//

#ifndef CHESSPROJECT_XMLUTILS_H
#define CHESSPROJECT_XMLUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pieces.h"
#include "GameBoard.h"

#define FILE_1_PATH "saved_game_1.xml"
#define XML_HEADER "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
#define SAVE_ERROR "Error: couldn't save file"
#define MAX_WORD_LENGTH 50
#define MAX_LINE_LENGTH 200

#define CURRENT_TURN_TAG_NAME "current_turn"
#define GAME_MODE_TAG_NAME "game_mode"
#define DIFFICULTY_TAG_NAME "difficulty"
#define USER_COLOR_TAG_NAME "user_color"
#define GAME "game"
#define BOARD "board"
#define BOARD_ROW "row_"
#define ROW_TAG_LENGTH 5

#define INVALID -1



/*
 * game mode: 1: 1-player, 2: 2-player
 * difficulty: 1-5
 * color: 0-black, 1-white,
 * path to file to save this data to
 *
 * returns SUCCESS or FAIL
 */
int saveGameToFile(GameBoard *gameboard, Player currentPlayerTurn, int gameMode,
                    int difficulty, Color color, char *path);

/*
 * write general tag, used by specific functions
 */
int writeWholeTag(char *tagContent, char *tagName, FILE *fp);
int writeOneTag(char *tagName, FILE *fp, int isClosingTag);
int writeString(char *str, FILE *fp);

/*
 * write specific tags:
 */
int writeHeader(FILE *fp);
int writeTurn(Player currentPlayerTurn, FILE *fp);
int writeMode(int gameMode, FILE *fp);
int writeColor(Color color, FILE *fp);
int writeDifficulty(int difficulty, FILE *fp);
int writeGameBoard(GameBoard *gameBoard, FILE *fp, Color color);


/*
 * game mode: 1: 1-player, 2: 2-player
 * difficulty: 1-5
 * color: 0-black, 1-white,
 * path to file to save this data to
 *
 * returns SUCCESS or FAIL
 */
int loadGameFromFile(GameBoard *gameboard, Player *currentPlayerTurn, int *gameMode,
                     int *difficulty, Color *color, char *path);

/*
 * makes pointers invalid, for checking parsing results.
 */
void initPointers(GameBoard *gameboard, Player *currentPlayerTurn, int *gameMode,
                    int *difficulty, Color *color);

/*
 * gets parsed result of tagName and tagContent
 * sets the relevant pointer to the value of tagContent
 */
void setPointer(char *tagName, char *tagContent, GameBoard *gameBoard,
                Player *currentPlayerTurn, int *gameMode, int *difficulty, Color *color);

#endif //CHESSPROJECT_XMLUTILS_H
