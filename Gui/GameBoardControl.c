#include "GameBoardControl.h"

// Create a default game board control.
GameBoardControl *GameBoardControlDefaultCreator() {
	int i, j;
	GameBoardControl *newGameBoardControl = (GameBoardControl *) calloc(
			sizeof(GameBoardControl), sizeof(char));

	if (newGameBoardControl == NULL) {
		printf("malloc: Error\n");
		return NULL;
	}

	char buff[1024];
	int success = 1;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 2; j++) {
			sprintf(buff, PIECE_TEXTURE_PATH_FORMAT, i, j);
			success &= LoadSurface(&(newGameBoardControl->piecesSurface[i][j]),
					buff);
		}
	}

	for (i = 0; i < 5; i++) {
		sprintf(buff, GAME_BOARD_TEXTURE_PATH_FORMAT, i);
		success &= LoadSurface(&(newGameBoardControl->boardSurfaces[i]), buff);
	}

	if (!success) {
		GameBoardControlDestroy(newGameBoardControl);
		return NULL;
	}

	newGameBoardControl->game = EmptyGame;
	newGameBoardControl->gameHistory = EmptyGameHistory;
	newGameBoardControl->game.gameHistory = &(newGameBoardControl->gameHistory);
	newGameBoardControl->gameStateIsSaved = 1;
	newGameBoardControl->rightClick = 0;
	newGameBoardControl->currentPieceSelectedRow = -1;
	newGameBoardControl->currentPieceSelectedCol = -1;
	return newGameBoardControl;
}

// Set the game mode of the game board control specified.
void SetGameMode(GameBoardControl *src, char gameMode) {
	Command command;
	command.commandType = setGameMode;
	command.argument[0] = gameMode;
	command.numberOfArgs = 1;

	handleCommand(command, &(src->game));
}

// Set the player color of the game board control specified.
void SetPlayerColor(GameBoardControl *src, char player1Color) {
	Command command;
	command.commandType = setUserColor;
	command.argument[0] = player1Color;
	command.numberOfArgs = 1;

	handleCommand(command, &(src->game));
}

// Set the game difficulty of the game board control specified.
void SetGameDifficulty(GameBoardControl *src, char gameDifficulty) {
	Command command;
	command.commandType = setDifficulty;
	command.argument[0] = gameDifficulty;
	command.numberOfArgs = 1;

	handleCommand(command, &(src->game));
}

// check whether now is the computer move.
int IsComputerTurnGameBoardControl(GameBoardControl *src) {
	return (getCurrentPlayerColor(&(src->game)) != src->game.player1Color
			&& src->game.gameMode == PlayerVsComputer);
}

// hanle finishing game print
void HandleFinishGameGameBoardControl(GameBoardControl *src) {
	CheckmateType checkmateType = getCheckmate(&(src->game));
	if (checkmateType == whiteCheckmated) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "White Checkmated!",
				"Black Player Wins!", NULL);

	} else if (checkmateType == blackCheckmated) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Black Checkmated!",
				"White Player Wins!", NULL);
	} else if (checkmateType == tie) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Tie!",
				"The Game Is Tied!", NULL);
	}
}

// handle checks prints
void HandleCheckPrintsIfNeeded(GameBoardControl *src) {
	CheckmateType checkmateType = getCheckmate(&(src->game));
	if (checkmateType == whiteChecked) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "White Checked!",
				"White King Is Threatened.", NULL);

	} else if (checkmateType == blackChecked) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Black Checked!",
				"Black King Is Threatened.", NULL);
	}
}

// check whether the game is completed.
int IsGameCompletedGameBoardControl(GameBoardControl *src) {
	switch (getCheckmate(&(src->game))) {
	case whiteCheckmated:
	case blackCheckmated:
	case tie:
		return 1;
	default:
		break;
	}
	return 0;
}

// handles computer move.
void HandleComputerMoveGameBoardControl(GameBoardControl *src) {
	Command command = getComputerMove(&(src->game));
	handleCommand(command, &(src->game));
}

// start the game | end setting phase.
void GameBoardControlStartGame(GameBoardControl *src) {
	Command command;
	command.commandType = startGame;
	handleCommand(command, &(src->game));
}

// set up new game using specified game mode, game color, game difficulty.
void GameBoardControlSetUpNewGame(GameBoardControl *src, char gameMode,
		char player1Color, char gameDifficulty) {
	src->game = EmptyGame;
	src->gameHistory = EmptyGameHistory;
	src->game.gameHistory = &(src->gameHistory);

	SetGameMode(src, gameMode);
	SetPlayerColor(src, player1Color);
	SetGameDifficulty(src, gameDifficulty);

	GameBoardControlStartGame(src);
	src->gameStateIsSaved = 1;
	if (IsComputerTurnGameBoardControl(src)) {
		HandleComputerMoveGameBoardControl(src);
	}
}

GameBoardControl *GameBoardControlCreate(char gameMode, char player1Color,
		char gameDifficulty) {
	GameBoardControl *newGameBoardControl = GameBoardControlDefaultCreator();

	if (newGameBoardControl == NULL) {
		return NULL;
	}

	Command command;
	command.commandType = loadDefaultSettings;
	handleCommand(command, &(newGameBoardControl->game));

	if (gameMode == 1) {
		gameMode = PlayerVsComputer;
		if (player1Color == 0) {
			player1Color = Black;
		} else {
			player1Color = White;
		}
	} else {
		gameMode = PlayerVsPlayer;
		player1Color = White;
	}
	gameDifficulty += '0';
	GameBoardControlSetUpNewGame(newGameBoardControl, gameMode, player1Color,
			gameDifficulty);

	return newGameBoardControl;
}

// check if an error occured in the loading phase.
int LoadGameErrorOccuredGameBoardControl(HandleCommandMessage message) {
	return (message.messageType == errorLoadMessage);
}

// print error of loading
void PrintLoadErrorGameBoardControl(HandleCommandMessage message) {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Can't Load Game",
			"Failed to Load Game: Couldn't open file.", NULL);
}

// handle loading game. 1 on success, 0 on falure.
int GameBoardControlLoadGame(GameBoardControl *src, int loadSlotSelected) {
	Command command;
	command.commandType = loadSettings;
	sprintf(command.stringArgument, SAVE_LOAD_PATH_FORMAT, loadSlotSelected);
	HandleCommandMessage message = handleCommand(command, &(src->game));
	if (LoadGameErrorOccuredGameBoardControl(message)) {
		PrintLoadErrorGameBoardControl(message);
		return 1;
	} else {
		src->gameStateIsSaved = 1;
	}

	GameBoardControlStartGame(src);

	if (IsComputerTurnGameBoardControl(src)) {
		HandleComputerMoveGameBoardControl(src);
	}

	return 0;
}

GameBoardControl *GameBoardControlLoad(int loadSlotSelected) {
	GameBoardControl *newGameBoardControl = GameBoardControlDefaultCreator();

	if (newGameBoardControl == NULL) {
		return NULL;
	}

	if (GameBoardControlLoadGame(newGameBoardControl, loadSlotSelected)) {
		GameBoardControlDestroy(newGameBoardControl);
		return NULL;
	}

	return newGameBoardControl;
}

void GameBoardControlDestroy(GameBoardControl *src) {
	int i, j;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 2; j++) {
			if (src->piecesSurface[i][j] != NULL) {
				SDL_FreeSurface(src->piecesSurface[i][j]);
			}
		}
	}
	for (i = 0; i < 5; i++) {
		if (src->boardSurfaces[i] != NULL) {
			SDL_FreeSurface(src->boardSurfaces[i]);
		}
	}
	free(src);
}

// get the board color in specific location
int GetColorInLocation(GameBoardControl *src, int row, int col) {
	char rowC = '1' + row;
	char colC = 'A' + col;
	int colorInThisLocation = (row + col) % 2;
	int locationInBoardOfRowCol = rowColToLocationIndex(rowC, colC);
	if ((src->rightClick && (src->game.gameMode == PlayerVsPlayer
			|| src->game.difficulty <= '2'))
			&& ((src->currentPieceSelectedRow != -1
					&& src->availableMovesOfSelectedPiece.allMoves.legalMovesArray[locationInBoardOfRowCol])
					|| (row == src->currentPieceSelectedRow && col
							== src->currentPieceSelectedCol))) {
		if (src->availableMovesOfSelectedPiece.threatenedByOpponentMoves.legalMovesArray[locationInBoardOfRowCol]) {
			colorInThisLocation = 2;
		} else if (src->availableMovesOfSelectedPiece.opponentAtLocationMoves.legalMovesArray[locationInBoardOfRowCol]) {
			colorInThisLocation = 4;
		} else {
			colorInThisLocation = 3;
		}
	}
	return colorInThisLocation;
}

// get the soldier color in specific location.
int GetNeededSurfaceInSpecificPositionOnBoard(GameBoardControl *src, int row,
		int col) {
	Piece piece;
	char rowC = '1' + row;
	char colC = 'A' + col;
	int getPieceResult = getPieceAt(rowC, colC, &(src->game.board), &piece);
	int pieceNumber = 0;
	int pieceColor = 0;
	if (getPieceResult != -1) {
		switch (piece.type) {
		case Pawn:
			pieceNumber = 1;
			break;
		case Bishop:
			pieceNumber = 2;
			break;
		case Rook:
			pieceNumber = 3;
			break;
		case Knight:
			pieceNumber = 4;
			break;
		case Queen:
			pieceNumber = 5;
			break;
		case King:
			pieceNumber = 6;
			break;
		default:
			break;
		}
		if (piece.player == Player1) {
			if (src->game.player1Color == Black) {
				pieceColor = 1;
			}
		} else {
			if (src->game.player1Color == White) {
				pieceColor = 1;
			}
		}
	}
	return (pieceNumber << 1) + pieceColor;
}

void GameBoardControlDraw(SDL_Surface* screen, GameBoardControl *src,
		int *Rectangle) {
	int row, col;
	SDL_Rect sdlRect;
	int boardRect[4];
	int neededSurfaceIndex;
	int colorInThisLocation;
	for (row = 0; row < 8; row++) {
		for (col = 0; col < 8; col++) {
			boardRect[0] = Rectangle[0] + (col * (Rectangle[1] - Rectangle[0]))
					/ 8;
			boardRect[1] = boardRect[0] + (Rectangle[1] - Rectangle[0]) / 8;
			boardRect[2] = Rectangle[2] + ((7 - row) * (Rectangle[3]
					- Rectangle[2])) / 8;
			boardRect[3] = boardRect[2] + (Rectangle[3] - Rectangle[2]) / 8;
			sdlRect = CreateSDLRectFromIntArray(boardRect);

			colorInThisLocation = GetColorInLocation(src, row, col);
			neededSurfaceIndex = GetNeededSurfaceInSpecificPositionOnBoard(src,
					row, col);
			SDL_BlitScaled(src->boardSurfaces[colorInThisLocation], NULL,
					screen, &sdlRect);
			if (((neededSurfaceIndex >> 1) != 0) && (!(src->leftDown && row
					== src->currentPieceSelectedRow && col
					== src->currentPieceSelectedCol))) {
				SDL_BlitScaled(
						src->piecesSurface[(neededSurfaceIndex >> 1) - 1][neededSurfaceIndex
								& 1], NULL, screen, &sdlRect);
			}
		}
	}
	if (src->currentPieceSelectedRow != -1 && src->leftDown) {
		boardRect[0] = Rectangle[0] + (src->currentPieceSelectedCol
				* (Rectangle[1] - Rectangle[0])) / 8;
		boardRect[1] = boardRect[0] + (Rectangle[1] - Rectangle[0]) / 8;
		boardRect[2] = Rectangle[2] + ((7 - src->currentPieceSelectedRow)
				* (Rectangle[3] - Rectangle[2])) / 8;
		boardRect[3] = boardRect[2] + (Rectangle[3] - Rectangle[2]) / 8;
		int x = (boardRect[1] + boardRect[0]) / 2;
		int y = (boardRect[3] + boardRect[2]) / 2;
		x -= src->mousePosition[0];
		y -= src->mousePosition[1];
		boardRect[0] -= x;
		boardRect[1] -= x;
		boardRect[2] -= y;
		boardRect[3] -= y;

		sdlRect = CreateSDLRectFromIntArray(boardRect);

		neededSurfaceIndex = GetNeededSurfaceInSpecificPositionOnBoard(src,
				src->currentPieceSelectedRow, src->currentPieceSelectedCol);
		if (((neededSurfaceIndex >> 1) != 0))
			SDL_BlitScaled(
					src->piecesSurface[(neededSurfaceIndex >> 1) - 1][neededSurfaceIndex
							& 1], NULL, screen, &sdlRect);
	}
}

// not implemented.
char AskPlayerForPawnPromotionOption() {
	//TODO pawn promotion
	return Queen;
}

// not implemented.
void HandlePawnPromotion(GameBoardControl *src, char rowFrom, char colFrom,
		char rowTo, char colTo) {
	Command command;
	command.commandType = setMove;
	command.argument[0] = rowFrom;
	command.argument[1] = colFrom;
	command.argument[2] = rowTo;
	command.argument[3] = colTo;
	command.argument[4] = AskPlayerForPawnPromotionOption();
	handleCommand(command, &(src->game));
}

// make move row col from -> row col to.
void MakeMoveGameBoardControl(GameBoardControl *src, char rowFrom,
		char colFrom, char rowTo, char colTo) {
	Command command;
	command.commandType = setMove;
	command.argument[0] = rowFrom;
	command.argument[1] = colFrom;
	command.argument[2] = rowTo;
	command.argument[3] = colTo;
	command.argument[4] = 0;
	HandleCommandMessage message = handleCommand(command, &(src->game));
	if (message.messageType == pawnPromoteNeededMessage) {
		HandlePawnPromotion(src, rowFrom, colFrom, rowTo, colTo);
	}
}

// not implemented.
int ChechIfMoveIsCastleMoveGameBoardControl(GameBoardControl *src,
		char rowFrom, char colFrom, char rowTo, char colTo) {
	//TODO castle move
	return 0;
}

// not implemented.
void MakeCastleMoveGameBoardControl(GameBoardControl *src, char rowFrom,
		char colFrom, char rowTo, char colTo) {
	//TODO castle move
}

EventStruct GameBoardControlHandleMoveEvent(GameBoardControl *src, int row,
		int col) {
	EventStruct eventStruct = { EmptyEvent, { 0 } };
	if (IsComputerTurnGameBoardControl(src)) {
		return eventStruct;
	}
	src->gameStateIsSaved = 0;
	char rowFrom = (char) ('1' + src->currentPieceSelectedRow);
	char colFrom = (char) ('A' + src->currentPieceSelectedCol);
	char rowTo = (char) ('1' + row);
	char colTo = (char) ('A' + col);

	if (ChechIfMoveIsCastleMoveGameBoardControl(src, rowFrom, colFrom, rowTo,
			colTo)) {
		MakeCastleMoveGameBoardControl(src, rowFrom, colFrom, rowTo, colTo);
	} else {
		MakeMoveGameBoardControl(src, rowFrom, colFrom, rowTo, colTo);
	}

	if (IsGameCompletedGameBoardControl(src)) {
		HandleFinishGameGameBoardControl(src);
		eventStruct.eventType = QuitEvent;
		return eventStruct;
	} else {
		HandleCheckPrintsIfNeeded(src);
	}

	src->currentPieceSelectedRow = -1;
	src->currentPieceSelectedCol = -1;
	if (IsComputerTurnGameBoardControl(src)) {
		HandleComputerMoveGameBoardControl(src);
		if (IsGameCompletedGameBoardControl(src)) {
			HandleFinishGameGameBoardControl(src);
			eventStruct.eventType = QuitEvent;
		} else {
			HandleCheckPrintsIfNeeded(src);
		}
	}
	return eventStruct;
}

// check whether the piece in this row col is the current user piece.
int PieceInRowColIsCurrentPlayerPiece(GameBoardControl *src, int row, int col) {
	char rowC = '1' + row;
	char colC = 'A' + col;
	int indexOfRowCol = rowColToLocationIndex(rowC, colC);
	int pieceNumber =
			src->game.board.mapLocationOnBoardToPieceIndex[indexOfRowCol];
	if (pieceNumber < 0) {
		return 0;
	}
	if (getPlayerFromIndex(pieceNumber) == src->game.currentPlayer) {
		return 1;
	} else {
		return 0;
	}
}

// update the available moves to the current selected piece moves.
void UpdateCurrentAvailableMoves(GameBoardControl *src) {
	Command command;
	command.commandType = getMoves;
	command.argument[0] = (char) ('1' + src->currentPieceSelectedRow);
	command.argument[1] = (char) ('A' + src->currentPieceSelectedCol);
	HandleCommandMessage message = handleGetMoves(command, &(src->game));
	src->availableMovesOfSelectedPiece = message.getMovesResponse;
}

EventStruct GameBoardControlHandleNewPieceChoosenEvent(GameBoardControl *src,
		int row, int col) {
	EventStruct eventStruct = { EmptyEvent, { 0 } };
	if (IsComputerTurnGameBoardControl(src)) {
		return eventStruct;
	}
	src->currentPieceSelectedRow = -1;
	src->currentPieceSelectedCol = -1;
	if (PieceInRowColIsCurrentPlayerPiece(src, row, col)) {
		src->currentPieceSelectedRow = row;
		src->currentPieceSelectedCol = col;
		UpdateCurrentAvailableMoves(src);
	}
	return eventStruct;
}

// print undo moves error.
void PrintUndoMoveErrorsGameBoardControl(HandleCommandMessage message) {
	char *errorString = NULL;
	if (message.messageType == errorUndo2PlayerModeMessage) {
		errorString = "Can't Undo Moves In Two Player Mode.";
	} else if (message.messageType == errorUndoEmptyHistoryMessage) {
		errorString = "Can't Undo Move: Empty History.";
	} else {
		errorString = "Unknown Error Occurred!";
	}
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Can't Undo Moves",
			errorString, NULL);
}

// check if undo move error occured.
int UndoMoveErrorOccuredGameBoardControl(HandleCommandMessage message) {
	return (message.messageType == errorUndo2PlayerModeMessage
			|| message.messageType == errorUndoEmptyHistoryMessage);
}

EventStruct GameBoardControlHandleUndoMove(GameBoardControl *src) {
	EventStruct eventStruct = { EmptyEvent, { 0 } };
	if (IsComputerTurnGameBoardControl(src)) {
		return eventStruct;
	}
	Command command;
	command.commandType = undoMove;
	HandleCommandMessage message = handleCommand(command, &(src->game));
	if (UndoMoveErrorOccuredGameBoardControl(message)) {
		PrintUndoMoveErrorsGameBoardControl(message);
	} else {
		src->gameStateIsSaved = 0;
		src->currentPieceSelectedCol = -1;
		src->currentPieceSelectedRow = -1;
	}
	return eventStruct;
}

// print save error.
void PrintSaveErrorGameBoardControl(HandleCommandMessage message) {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Can't Save Game",
			"Error While Trying to saving the Game.", NULL);
}

// check whether save error occured.
int SaveGameErrorOccuredGameBoardControl(HandleCommandMessage message) {
	return (message.messageType == errorSaveMessage);
}

//  shift all save files +1.
void ShiftAllSaves() {
	FILE *fp1, *fp2;
	char ch;
	char filepath1[BUFSIZ], filepath2[BUFSIZ];
	int i;
	for (i = NUMBER_OF_SAVE_LOAD_SLOT; i > 1; i--) {
		sprintf(filepath1, SAVE_LOAD_PATH_FORMAT, i - 1);
		sprintf(filepath2, SAVE_LOAD_PATH_FORMAT, i);
		fp1 = fopen(filepath1, "r");
		if (fp1 != NULL) {
			fp2 = fopen(filepath2, "w");
			if (fp2 != NULL) {
				while (1) {
					ch = fgetc(fp1);

					if (ch == EOF)
						break;
					else
						putc(ch, fp2);
				}
				fclose(fp2);
			}
			fclose(fp1);
		}
	}
}

EventStruct GameBoardControlHandleSaveGame(GameBoardControl *src) {
	EventStruct eventStruct = { EmptyEvent, { 0 } };
	ShiftAllSaves();
	Command command;
	command.commandType = saveGame;
	sprintf(command.stringArgument, SAVE_LOAD_PATH_FORMAT, 1);
	HandleCommandMessage message = handleCommand(command, &(src->game));
	if (SaveGameErrorOccuredGameBoardControl(message)) {
		PrintSaveErrorGameBoardControl(message);
	} else {
		src->gameStateIsSaved = 1;
	}
	return eventStruct;
}

// hanldle unsaved game data - ask user whether to save them. return 1 if can go on and exit.
int CheckIfUserWantToSaveGameIfNeeded_OrCancelAction(GameBoardControl *src) {
	if (src->gameStateIsSaved)
		return 1;
	const SDL_MessageBoxButtonData buttons[] = { { /* .flags, .buttonid, .text */
	0, 0, "no" }, { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" }, {
			SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" }, };
	const SDL_MessageBoxColorScheme colorScheme = { { /* .colors (.r, .g, .b) */
	/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
	{ 255, 0, 0 },
	/* [SDL_MESSAGEBOX_COLOR_TEXT] */
	{ 0, 255, 0 },
	/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
	{ 255, 255, 0 },
	/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
	{ 0, 0, 255 },
	/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
	{ 255, 0, 255 } } };
	const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, /* .flags */
	NULL, /* .window */
	"You are going to lose you unsaved game!", /* .title */
	"Do you want to save the current game?", /* .message */
	SDL_arraysize(buttons), /* .numbuttons */
	buttons, /* .buttons */
	&colorScheme /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box - unsave game is lost");
		return 1;
	}
	if (buttonid == -1 || buttonid == 2) {
		//SDL_Log("no selection");
		//SDL_Log("canel button");
		return 0;
	} else if (buttonid == 1) {
		GameBoardControlHandleSaveGame(src);
	}
	return 1;

}

EventStruct GameBoardControlHandleRestartGame(GameBoardControl *src) {
	EventStruct eventStruct = { EmptyEvent, { 0 } };
	char gameMode, player1Color, gameDifficulty;
	if (CheckIfUserWantToSaveGameIfNeeded_OrCancelAction(src)) {
		gameMode = src->game.gameMode;
		player1Color = src->game.player1Color;
		gameDifficulty = src->game.difficulty;
		GameBoardControlSetUpNewGame(src, gameMode, player1Color,
				gameDifficulty);
		src->game.isLoaded = 0;
	}
	return eventStruct;
}

EventStruct GameBoardControlHandleGoToMainWindow(GameBoardControl *src) {
	EventStruct eventStruct = { EmptyEvent, { 0 } };
	if (CheckIfUserWantToSaveGameIfNeeded_OrCancelAction(src)) {
		eventStruct.eventType = GoToMainWindowButtonGameWindowClickEvent;
	}
	return eventStruct;
}

EventStruct GameBoardControlHandleQuitGame(GameBoardControl *src) {
	EventStruct eventStruct = { EmptyEvent, { 0 } };
	if (CheckIfUserWantToSaveGameIfNeeded_OrCancelAction(src)) {
		eventStruct.eventType = QuitEvent;
	}
	return eventStruct;
}

// get the game row the click was on.
int ClickWasOnGameRow(SDL_Event *event, int *Rectangle) {
	int y = event->button.y;
	y -= Rectangle[2];
	return 7 - (y / ((Rectangle[3] - Rectangle[2]) / 8));
}

// git the game col the click was on.
int ClickWasOnGameCol(SDL_Event *event, int *Rectangle) {
	int x = event->button.x;
	x -= Rectangle[0];
	return x / ((Rectangle[1] - Rectangle[0]) / 8);
}

// check whther a move is valid for the current selected piece.
int IsValidMoveForCurrentSelectedPiece(GameBoardControl *src, int row, int col) {
	if (src->currentPieceSelectedRow == -1) {
		return 0;
	}
	char rowC = '1' + row;
	char colC = 'A' + col;
	if (src->availableMovesOfSelectedPiece.allMoves.legalMovesArray[rowColToLocationIndex(
			rowC, colC)]) {
		return 1;
	} else {
		return 0;
	}
}

EventStruct GameBoardControlHandleEvent(GameBoardControl *src,
		SDL_Event *event, int *Rectangle) {
	EventStruct eventStruct = { EmptyEvent, { 0 } };
	if (event == NULL) {
		return eventStruct;
	}

	if (IsComputerTurnGameBoardControl(src)) {
		return eventStruct;
	}

	if (event->type == SDL_MOUSEBUTTONUP) {
		int row = ClickWasOnGameRow(event, Rectangle);
		int col = ClickWasOnGameCol(event, Rectangle);
		if (event->button.button == SDL_BUTTON_RIGHT) {
			src->rightClick = 1;
			return GameBoardControlHandleNewPieceChoosenEvent(src, row, col);
		} else if (event->button.button == SDL_BUTTON_LEFT) {
			src->leftDown = 0;
			if (IsValidMoveForCurrentSelectedPiece(src, row, col)) {
				return GameBoardControlHandleMoveEvent(src, row, col);
			}
		}
	} else if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button
			== SDL_BUTTON_LEFT) {
		int row = ClickWasOnGameRow(event, Rectangle);
		int col = ClickWasOnGameCol(event, Rectangle);
		src->rightClick = 0;
		src->leftDown = 1;
		return GameBoardControlHandleNewPieceChoosenEvent(src, row, col);
	} else if (event->type == SDL_MOUSEMOTION) {
		src ->mousePosition[0] = event->button.x;
		src ->mousePosition[1] = event->button.y;
	}
	return eventStruct;
}
