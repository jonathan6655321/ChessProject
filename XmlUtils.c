//
// Created by Jonathan on 9/11/2017.
//

#include "XmlUtils.h"

int saveGameToFile(GameBoard *gameBoard, Player currentPlayerTurn,
		int gameMode, int difficulty, Color color, char *path) {
	FILE *fp;
	fp = fopen(path, "w");// overwrites the previous file completely!
	if (fp == NULL) {
		//printf("open file failed\n\n %s", strerror(errno));
		return FAIL;
	}

	if (writeHeader(fp) == FAIL)
		return FAIL;

	writeOneTag(GAME, fp, 0);
	if (writeString("\n", fp) == FAIL)
		return FAIL;
	if (writeTurn(currentPlayerTurn, fp) == FAIL)
		return FAIL;
	if (writeMode(gameMode, fp) == FAIL)
		return FAIL;
	if (writeColor(color, fp) == FAIL)
		return FAIL;
	if (writeDifficulty(difficulty, fp) == FAIL)
		return FAIL;
	if (writeGameBoard(gameBoard, fp, color) == FAIL)
		return FAIL;

	writeOneTag(GAME, fp, 1);

	fclose(fp);
	return SUCCESS;
}

/*
 * writes the first line of the xml
 */
int writeHeader(FILE *fp) {
	size_t written = fwrite(XML_HEADER, 1, (unsigned) strlen(XML_HEADER), fp);
	if (written != (unsigned) strlen(XML_HEADER)) {
		//printf("%s %s", SAVE_ERROR, strerror(errno));
		return FAIL;
	}
	return SUCCESS;
}

int writeWholeTag(char *tagContent, char *tagName, FILE *fp) {
	if (writeOneTag(tagName, fp, 0) == FAIL || writeString(tagContent, fp)
			== FAIL || writeOneTag(tagName, fp, 1) == FAIL)
		return FAIL;
	else
		return SUCCESS;
}

int writeOneTag(char *tagName, FILE *fp, int isClosingTag) {
	int numBytes;
	char str[BUFSIZ];
	if (isClosingTag) {
		//        printf("%s %d\n\n", tagName,(unsigned)strlen(tagName));
		numBytes = (unsigned) strlen(tagName) + 4;
		sprintf(str, "</%s>\n", tagName);
	} else {
		numBytes = (unsigned) strlen(tagName) + 2;
		sprintf(str, "<%s>", tagName);
	}

	//    printf("\nprinting: %s", str);
	//    printf("num chars in str: %d\n\n", sizeof(str));

	size_t written = fwrite(str, 1, numBytes, fp);
	if (written <= 0) {
		//printf("%s %s", SAVE_ERROR, strerror(errno));
		return FAIL;
	}
	return SUCCESS;
}

/*
 * make sure string is terminated by zero!
 */
int writeString(char *str, FILE *fp) {
	//    printf("printing: %s", str);
	size_t written = fwrite(str, 1, (unsigned) strlen(str), fp);
	if (written <= 0) {
		//printf("%s %s", SAVE_ERROR, strerror(errno));
		return FAIL;
	}
	return SUCCESS;
}

int writeTurn(Player currentPlayerTurn, FILE *fp) {
	char turn[2] = { '\0' };
	sprintf(turn, "%d", ((currentPlayerTurn == Player1) ? 1 : 2));
	return writeWholeTag(turn, CURRENT_TURN_TAG_NAME, fp);
}

int writeMode(int gameMode, FILE *fp) {
	char mode[2] = { '\0' };
	sprintf(mode, "%d", gameMode);
	return writeWholeTag(mode, GAME_MODE_TAG_NAME, fp);
}

int writeColor(Color color, FILE *fp) {
	char col[2] = { '\0' };
	sprintf(col, "%c", color);
	return writeWholeTag(col, USER_COLOR_TAG_NAME, fp);
}

int writeDifficulty(int difficulty, FILE *fp) {
	char diff[2] = { '\0' };
	sprintf(diff, "%d", difficulty);
	return writeWholeTag(diff, DIFFICULTY_TAG_NAME, fp);
}

int writeGameBoard(GameBoard *gameBoard, FILE *fp, Color color) {
	if (writeOneTag(BOARD, fp, 0) == FAIL)
		return FAIL;
	if (writeString("\n", fp) == FAIL)
		return FAIL;
	int r, c;
	for (r = LAST_ROW_CHAR; r >= FIRST_ROW_CHAR; r--) {
		char row[NUM_COLS + 1] = { '\0' };
		for (c = FIRST_COL_CHAR; c <= LAST_COL_CHAR; c++) {
			Piece p;
			p.type = None;
			getPieceAt(r, c, gameBoard, &p);
			row[c - FIRST_COL_CHAR] = getPieceChar(&p, color);
		}
		row[NUM_COLS + 1] = '\0';
		char rowTag[ROW_TAG_LENGTH] = { '\0' };
		sprintf(rowTag, "%s%d", BOARD_ROW, r - FIRST_ROW_CHAR + 1);
		if (writeWholeTag(row, rowTag, fp) == FAIL)
			return FAIL;
	}

	if (writeOneTag(BOARD, fp, 1) == FAIL)
		return FAIL;
	return SUCCESS;
}

/*
 *
 * game mode: 1: 1-player, 2: 2-player
 * difficulty: 1-5
 * color: 0-black, 1-white,
 * path to file to save this data to
 *
 * returns SUCCESS or FAIL
 */
int loadGameFromFile(GameBoard *gameboard, Player *currentPlayerTurn,
		int *gameMode, int *difficulty, Color *color, char *path) {
	FILE *fp;
	fp = fopen(path, "r");
	if (fp == NULL) {
		return FAIL;
	}
	initPointers(gameboard, currentPlayerTurn, gameMode, difficulty, color);

	do {

		char line[MAX_LINE_LENGTH] = { '\0' };
		char tagName[MAX_WORD_LENGTH] = { '\0' };
		char tagContent[MAX_WORD_LENGTH] = { '\0' };
		fgets(line, MAX_LINE_LENGTH - 1, fp);
		int i;
		int inFirstTag = 1;
		int locInFirstTag = 0;
		int locInContent = 0;
		for (i = 0; line[i] != '\0'; i++) {
			char c = line[i];
			if (inFirstTag) {
				if (c == '<') {
					locInFirstTag = 0;
					continue;
				}
				if (c == '>') {
					inFirstTag = 0;
					continue;
				} else {
					tagName[locInFirstTag] = c;
					locInFirstTag++;
					tagName[locInFirstTag] = '\0';
				}
			} else // in tagContent
			{
				if (c == '<')
					break;
				else {
					tagContent[locInContent] = c;
					locInContent++;
					tagContent[locInContent] = '\0';
				}
			}
		}

		setPointer(tagName, tagContent, gameboard, currentPlayerTurn, gameMode,
				difficulty, color);

	} while (!feof(fp));
	fclose(fp);
	return SUCCESS;
}

void initPointers(GameBoard *gameBoard, Player *currentPlayerTurn,
		int *gameMode, int *difficulty, Color *color) {
	GameBoard new;
	initEmptyGame(&new);
	(*gameBoard) = new;
	(*currentPlayerTurn) = INVALID;
	(*gameMode) = INVALID;
	(*difficulty) = INVALID;
	(*color) = INVALID;
}

void setPointer(char *tagName, char *tagContent, GameBoard *gameBoard,
		Player *currentPlayerTurn, int *gameMode, int *difficulty, Color *color) {
	if (strcmp(tagName, CURRENT_TURN_TAG_NAME) == 0) {
		int t = atoi(tagContent);
		(*currentPlayerTurn) = (t == 1) ? Player1 : Player2;
		return;
	}
	if (strcmp(tagName, GAME_MODE_TAG_NAME) == 0) {
		int gm = atoi(tagContent);
		(*gameMode) = gm;
		return;
	}
	if (strcmp(tagName, DIFFICULTY_TAG_NAME) == 0) {
		int d = atoi(tagContent);
		(*difficulty) = d;
		return;
	}
	if (strcmp(tagName, USER_COLOR_TAG_NAME) == 0) {
		(*color) = *tagContent;
		return;
	}
	if (strncmp(tagName, BOARD_ROW, ROW_TAG_LENGTH - 1) == 0) {
		char col, row = tagName[ROW_TAG_LENGTH - 1];
		for (col = FIRST_COL_CHAR; col <= LAST_COL_CHAR; col++) {
			char pieceChar = tagContent[col - FIRST_COL_CHAR];
			if (pieceChar != '_') {
				int pieceIndex = getPieceIndexFromPieceChar(gameBoard,
						pieceChar, *color);
				setPieceAt(row, col, gameBoard, pieceIndex);
			}
		}
	}

}
