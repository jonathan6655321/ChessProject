/*
 * mainGameLoop.c
 *
 *  Created on: 19 July 2017
 *      Author: kessi
 */

#include "CommandLineGame.h"

int commandLineGameLoop() {
    Game game;
    GameHistory gameHistory;
    Command command;
    HandleCommandMessage commandMessage;
    // starts at setting state:
    commandLineState state = settingCommandState;
    // start by initializing the game
    command.commandType = resetGame;

    while (command.commandType != quitGame) {
        if (state == settingCommandState) {
            if (command.commandType == resetGame) {
                // reset structs
                game = EmptyGame;
                gameHistory = EmptyGameHistory;
                game.gameHistory = &gameHistory;

                // set gave default value
                setGameDefaultValue(&game);
                printf("%s", SETTING_STATE_FIRST_MESSAGE);
            }
            command = getNextSettingCommand();
        } else if (state == gameCommandState) {
            if (isUserMove(&game)) {
                if (game.needToReprintBoard) {
                    printGame(&game);
                    game.needToReprintBoard = 0;
                }
                printf(ASK_FOR_PLAYER_MOVE_FORMAT_STRING,
                       getColorName(getCurrentPlayerColor(&game)));
                command = getNextGameCommand();
            } else { //Computer Move
                command = getComputerMove(&game);
            }
        } else if (state == gameEndedCommandState) {
            // should exit!
            return 0;
        }
        commandMessage = handleCommand(command, &game);
        printCommandLineMessages(&game, command, commandMessage);
        switchStateIfNeeded(command, &state);
        handleCheckmates(&game, &state);
    }
    return 0;
}

int isUserMove(Game *game) {
    return (game->gameMode == PlayerVsPlayer || game->currentPlayer == Player1);
}

void handlePrintSettingMessage(HandleCommandMessage message) {
    if (message.argument[0] == PlayerVsComputer) {
        printf(PRINT_SETTING_FORMAT_IN_GAME_MODE_1_STRING, message.argument[1],
               getCAPITALColorName(message.argument[2]));
    } else {
        printf("%s", PRINT_SETTING_FORMAT_IN_GAME_MODE_2_STRING);
    }
}

void handlePrintUndoMessage(Game *game, HandleCommandMessage message) {
    Color currentPlayerColor = getCurrentPlayerColor(game);
    Color lastPlayerColor = getOppositeColor(currentPlayerColor);

    printf(UNDO_FORMAT_STRING, getColorName(lastPlayerColor),
           message.argument[2], message.argument[3], message.argument[0],
           message.argument[1]);
    printf(UNDO_FORMAT_STRING, getColorName(currentPlayerColor),
           message.argument[6], message.argument[7], message.argument[4],
           message.argument[5]);
}

void handlePrintMove(Game *game, Command command, HandleCommandMessage message) {
    //if game is against AI and the current player is after the AI:
    int moveWasComputerMove = (game->gameMode == PlayerVsComputer
                               && game->currentPlayer == Player1);
    if (moveWasComputerMove) {
        printf(COMPUTER_MOVE_FORMAT_STRING,
               getPieceTypeName(message.argument[0]), command.argument[0],
               command.argument[1], command.argument[2], command.argument[3]);
    }

    handlePrintCheckmate(getCheckmate(game), moveWasComputerMove);
}

// Print a single get move line:
void printSingleGetMoveMessage(int row, int col, int isPossible, int isThreatened, int isCapturing) {
    if (isPossible) {
        printf(GET_MOVES_STANDART_MOVE_FORMAT_STRING, row, col);
        if (isThreatened) printf("%s", "*");
        if (isCapturing) printf("%s", "^");
        printf("%s", "\n");
    }
}

void handlePrintGetMoves(Game *game, Command command,
                         HandleCommandMessage message) {
    int currentIndex;
    char row, col;
    int isPossible, isThreatened, isCapturing, isCastle;
    for (row = '1'; row <= '8'; ++row) {
        for (col = 'A'; col <= 'H'; ++col) {
            currentIndex = rowColToLocationIndex(row, col);
            isPossible
                    = message.getMovesResponse.allMoves.legalMovesArray[currentIndex];
            isThreatened
                    = message.getMovesResponse.threatenedByOpponentMoves.legalMovesArray[currentIndex];
            isCapturing
                    = message.getMovesResponse.opponentAtLocationMoves.legalMovesArray[currentIndex];
            printSingleGetMoveMessage(row, col, isPossible, isThreatened, isCapturing);
        }
    }
}

void handlePrintCheckmate(CheckmateType checkmateType, int moveWasComputerMove) {
    switch (checkmateType) {
        case blackChecked:
            if (moveWasComputerMove) {
                printf("%s", COMPUTER_CHECK_STRING);
            } else {
                printf("%s", BLACK_CHECK_STRING);
            }
            break;
        case whiteChecked:
            if (moveWasComputerMove) {
                printf("%s", COMPUTER_CHECK_STRING);
            } else {
                printf("%s", WHITE_CHECK_STRING);
            }
            break;
        case blackCheckmated:
            printf("%s", BLACK_CHECKMATED_STRING);
            break;
        case whiteCheckmated:
            printf("%s", WHITE_CHECKMATED_STRING);
            break;
        case tie:
            printf("%s", TIE_STRING);
            break;
        default:
            return;
    }
}

void handleCheckmates(Game *game, commandLineState *state) {
    if (*state == gameCommandState) {
        CheckmateType checkmateType = getCheckmate(game);
        if (checkmateType == whiteCheckmated || checkmateType
                                                == blackCheckmated || checkmateType == tie) {
            *state = gameEndedCommandState;
        }
    }
}

void switchStateIfNeeded(Command command, commandLineState *state) {
    if (command.commandType == resetGame) {
        *state = settingCommandState;
    } else if (command.commandType == startGame) {
        *state = gameCommandState;
    }
}

void setGameDefaultValue(Game *game) {
    Command command;
    command.commandType = loadDefaultSettings;
    handleCommand(command, game);
}

void printCommandLineMessages(Game *game, Command command,
                              HandleCommandMessage message) {
    switch (message.messageType) {
        case successMessage:
            break;
        case setGameModeMessage:
            if (message.argument[0] == '1') {
                printf(SET_GAME_MODE_1_STRING);
            } else {
                printf(SET_GAME_MODE_2_STRING);
            }
            break;
        case errorSetGameModeMessage:
            printf("%s", SET_GAME_MODE_ERROR_STRING);
            break;
        case errorExpertSetDifficultyMessage:
            printf("%s", SET_DIFFICULTY_EXPERT_ERROR_STRING);
            break;
        case errorSetDifficultyMessage:
            printf("%s", SET_DIFFICULTY_ERROR_STRING);
            break;
        case errorLoadMessage:
            printf("%s", LOAD_SETTING_ERROR_STRING);
            break;
        case printSettingMessage:
            handlePrintSettingMessage(message);
            break;
        case errorSetMovePositionsMessage:
            printf("%s", SET_MOVE_POSITION_ERROR_STRING);
            break;
        case errorSetMoveNotYourPieceMessage:
            printf("%s", SET_MOVE_WRONG_PIECE_COLOR_ERROR_STRING);
            break;
        case errorIllegalMoveMessage:
            printf("%s", SET_MOVE_ILLEGAL_MOVE_ERROR_STRING);
            break;
        case setMoveMessage:
            handlePrintMove(game, command, message);
            break;
        case getMovesMessage:
            handlePrintGetMoves(game, command, message);
            break;
        case errorGetMovesInvalidPositionMessage:
            printf("%s", GET_MOVES_INVALID_POSITION_ERROR_STRING);
            break;
        case errorGetMovesNotYourPieceMessage:
            printf(GET_MOVES_NOT_YOUR_PIECE_ERROR_FORMAT_STRING,
                   getColorName(getCurrentPlayerColor(game)));
            break;
        case errorSaveMessage:
            printf("%s", SAVE_SETTING_ERROR_STRING);
            break;
        case errorUndo2PlayerModeMessage:
            printf("%s", UNDO_FOR_2_PLAYERS_ERROR_STRING);
            break;
        case errorUndoEmptyHistoryMessage:
            printf("%s", UNDO_EMPTY_HISTORY_ERROR_STRING);
            break;
        case undoMessage:
            handlePrintUndoMessage(game, message);
            break;
        case resetMessage:
            printf("%s", RESTARTING_STRING);
            break;
        case quitMessage:
            printf("%s", QUITING_STRING);
            break;
        case invalidCommandMessage:
            printf("%s",
                   "Invalid command\n"); //TODO: this wasn't in the PDF so we need to check if we actually need this.
            break;
    }
}
