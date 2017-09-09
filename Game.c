/*
 * Game.c
 *
 *  Created on: 19 ???? 2017
 *      Author: kessi
 */
#include "Game.h"

HandleCommandMessage handleCommand(Command command, Game *game) {
    HandleCommandMessage message;
    switch (command.commandType) {
        case setGameMode:
            return handleSetGameMode(command, game);
        case loadDefaultSettings:
            return handleSetDefault(game);
        case setDifficulty:
            return handleSetDifficulty(command, game);
        case setUserColor:
            return handleSetUserColor(command, game);
        case loadSettings:
            return handleLoadSettings(command, game);
        case printSettings:
            return handlePrintSettings(game);
        case startGame:
            return handleStartGame(game);
        case setMove:
            return handleSetMove(command, game);
        case getMoves:
            return handleGetMoves(command, game);
        case castleMove:
            return handleCastleMove(command, game);
        case saveGame:
            return handleSaveGame(command, game);
        case undoMove:
            return handleUndoMove(game);
        case resetGame:
            message.messageType = resetMessage;
            return message;
        case quitGame:
            message.messageType = quitMessage;
            return message;
        default:
            message.messageType = invalidCommandMessage;
            return message;
    }

}

HandleCommandMessage handleSetGameMode(Command command, Game *game) {
    HandleCommandMessage message;
    char gameModeChar = command.stringArgument[0];
    message.argument[0] = gameModeChar;
    if (command.numberOfArgs == 1 && '1' <= gameModeChar
        && gameModeChar <= '2') {
        message.messageType = setGameModeMessage;
        game->gameMode = gameModeChar;
    } else {
        message.messageType = errorSetGameModeMessage;
    }
    return message;
}

HandleCommandMessage handleSetDefault(Game *game) {
    game->gameMode = DEFAULT_GAME_MODE;
    game->difficulty = DEFAULT_DIFFICULTY;
    game->currentPlayer = DEFAULT_CURRENT_PLAYER;
    game->player1Color = DEFAULT_USER_COLOR;

    HandleCommandMessage message;
    message.messageType = successMessage;
    return message;
}

HandleCommandMessage handleSetDifficulty(Command command, Game *game) {
    HandleCommandMessage message;
    char difficulty = command.stringArgument[0];
    message.argument[0] = command.stringArgument[0];
    if (command.numberOfArgs == 1 && '1' <= difficulty && difficulty <= '5') {
        if (difficulty == '5' && !(CAN_HANDLE_EXPERT_DIFFICULTY)) {
            message.messageType = errorExpertSetDifficultyMessage;
        } else {
            message.messageType = successMessage;
            game->difficulty = difficulty;
        }
    } else {
        message.messageType = errorSetDifficultyMessage;
    }
    return message;
}

HandleCommandMessage handleSetUserColor(Command command, Game *game) {
    HandleCommandMessage message;
    char color = command.stringArgument[0];
    if (command.numberOfArgs == 1 && game->gameMode != PlayerVsPlayer
        && '0' <= color && color <= '1') {
        game->player1Color = color;
        message.messageType = successMessage;
    } else {
        message.messageType = invalidCommandMessage;
    }
    return message;
}

HandleCommandMessage handleLoadSettings(Command command, Game *game) {
    HandleCommandMessage message;
    message.messageType = errorLoadMessage;
//TODO: implement load from file.
    return message;
}

HandleCommandMessage handlePrintSettings(Game *game) {
    HandleCommandMessage message;
    message.messageType = printSettingMessage;
    message.argument[0] = game->gameMode;
    message.argument[1] = game->difficulty;
    message.argument[2] = game->player1Color;
    return message;
}

HandleCommandMessage handleStartGame(Game *game) {
    game->needToReprintBoard = 1;
    if (game->gameMode == PlayerVsPlayer) {
        game->currentPlayer = Player1;
        game->player1Color = White;
    }
    //TODO: if loaded don't init...
    initGame(&(game->board), game->player1Color);
    //TODO: if loaded don't init history.
    initHistoryArray(game);

    HandleCommandMessage message;
    message.messageType = successMessage;
    return message;
}

HandleCommandMessage handleSetMove(Command command, Game *game) {
    char rowFrom = command.argument[0];
    char colFrom = command.argument[1];
    char rowTo = command.argument[2];
    char colTo = command.argument[3];
    Piece pieceAtDestinationBefore;
    Piece pieceAtDestinationAfter;
    HandleCommandMessage message;
    ResponseType response = executeUserMoveCommand(rowFrom, colFrom, rowTo, colTo,
                                               &(game->board), game->currentPlayer, &pieceAtDestinationBefore,
                                               &pieceAtDestinationAfter);
    switch (response) {
        //case where no move should be done:
        case InvalidPosition:
            message.messageType = errorSetMovePositionsMessage;
            return message;
        case NotYourPiece:
            message.messageType = errorSetMoveNotYourPieceMessage;
            return message;
        case IllegalMove:
            message.messageType = errorIllegalMoveMessage;
            return message;
        case PawnPromotionNeeded:
            message.messageType = pawnPromoteNeededMessage;
            return message;

            //cases where a move should be done:
        case AteOpponentsPiece_PawnPromote:
            message.messageType = pawnPromoteMessage;
            game->historyNumberOfPieceToSet[game->historyIndex] = 2;
            break;
        case AteOpponentsPiece:
            message.messageType = setMoveMessage;
            game->historyNumberOfPieceToSet[game->historyIndex] = 2;
            break;
        case MadeMove_Pawn_Promote:
            message.messageType = pawnPromoteMessage;
            game->historyNumberOfPieceToSet[game->historyIndex] = 1;
            break;
        case MadeMove:
            message.messageType = setMoveMessage;
            game->historyNumberOfPieceToSet[game->historyIndex] = 1;
            break;
    }
    game->needToReprintBoard = 1;
    message.argument[0] = pieceAtDestinationBefore.type;
    message.argument[1] = pieceAtDestinationAfter.type;
    game->historyIndex++;
    if (game->historyIndex >= MAX_HISTORY_SIZE) game->historyIndex -= MAX_HISTORY_SIZE; //loop array;
    game->historyPiecesAfter[game->historyIndex] = pieceAtDestinationAfter;
    game->historyPiecesBefore[game->historyIndex] = pieceAtDestinationBefore;
    game->historyPositions[game->historyIndex][0] = rowFrom;
    game->historyPositions[game->historyIndex][1] = colFrom;
    game->historyPositions[game->historyIndex][2] = rowTo;
    game->historyPositions[game->historyIndex][3] = colTo;
    switchPlayer(game);
    return message;
}

HandleCommandMessage handleCastleMove(Command command, Game *game) {
    HandleCommandMessage message;
    message.messageType = errorCastleMoveIllegalMoveMessage;
    return message;
//TODO: handle castle move
}

HandleCommandMessage handleGetMoves(Command command, Game *game) {
    HandleCommandMessage message;
    message.messageType = errorGetMovesInvalidPositionMessage;
    return message;
//TODO: return in new struct from Somer the get moves
}

HandleCommandMessage handleSaveGame(Command command, Game *game) {
    HandleCommandMessage message;
    message.messageType = errorLoadMessage;
//TODO: implement save to file.
    return message;
}

HandleCommandMessage handleUndoMove(Game *game) {
    HandleCommandMessage message;
    if (game->gameMode == PlayerVsPlayer && !(CAN_UNDO_IN_2_PLAYER_MODE)) {
        message.messageType = errorUndo2PlayerModeMessage;
    } else if (game->historyNumberOfPieceToSet[game->historyIndex] == 0) {
        message.messageType = errorUndoEmptyHistoryMessage;
    } else {
        game->needToReprintBoard = 1;
        char row, col;
        Piece *piece;
        for (int i = 0; i < 2; i++) {
            row = message.argument[4 * i + 2] = game->historyPositions[game->historyIndex][2];
            col = message.argument[4 * i + 3] = game->historyPositions[game->historyIndex][3];
            if (game->historyNumberOfPieceToSet[game->historyIndex] == 2) {
                piece = &(game->historyPiecesBefore[game->historyIndex]);
                executeSetPieceAt(row, col, piece, &(game->board));
            } else {
                //TODO: tell Somer to make a remove piece at that is interfaced - execute remove piece at.
                removePieceAt(row, col, &(game->board));
            }
            row = message.argument[4 * i + 0] = game->historyPositions[game->historyIndex][0];
            col = message.argument[4 * i + 1] = game->historyPositions[game->historyIndex][1];
            piece = &(game->historyPiecesAfter[game->historyIndex]);
            executeSetPieceAt(row, col, piece, &(game->board));
            game->historyNumberOfPieceToSet[game->historyIndex] = 0;
            game->historyIndex--;
            if (game->historyIndex < 0) game->historyIndex += MAX_HISTORY_SIZE;
        }
        message.messageType = undoMessage;
    }
    return message;
}

Command getComputerMove(Game *game) {
    Command command;
//TODO: implement createComputerMove.
    return command;
}

CheckmateType getCheckmate(Game *game) {
    return noCheck;
//TODO: return checkmate from game board somer version.
}

void printGame(Game *game) {
    printBoard(&(game->board), game->player1Color);
}

void switchPlayer(Game *game) {
    if (game->currentPlayer == Player1) {
        game->currentPlayer = Player2;
    } else {
        game->currentPlayer = Player1;
    }
}

Color getCurrentPlayerColor(Game *game) {
    if (game->currentPlayer == Player1) {
        if (game->player1Color == White) {
            return White;
        } else {
            return Black;
        }
    } else {
        if (game->player1Color == White) {
            return Black;
        } else {
            return White;
        }
    }
}

void initHistoryArray(Game *game) {
    memset(game->historyPiecesBefore, 0, sizeof(game->historyPiecesBefore));
    memset(game->historyPiecesAfter, 0, sizeof(game->historyPiecesAfter));
    memset(game->historyPositions, 0, sizeof(game->historyPositions));
    memset(game->historyNumberOfPieceToSet, 0, sizeof(game->historyNumberOfPieceToSet));
    game->historyIndex = 0;
}


