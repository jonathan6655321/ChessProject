#include "GameBoardControl.h"

GameBoardControl* GameBoardControlDefaultCreator(){
	GameBoardControl* newGameBoardControl = (GameBoardControl*) calloc(sizeof(GameBoardControl), sizeof(char));

	if (newGameBoardControl == NULL) {
		printf("malloc: Error\n");
		return NULL;
	}

	char buff[1024];
	int success = 1;
	for (int i = 0; i < NUMBER_OF_GAME_BOARD_TEXTURES; i++) {
		sprintf(str, GAME_BOARD_TEXTURE_PATH_FORMAT, i);
		success &= LoadTexture(&(newGameBoardControl->textures[i]), newGameWindow->gameRenderer, buff);
	}

	if (!success) {
		GameBoardControlDestroy(newGameBoardControl);
		return NULL;
	}

	newGameBoardControl->game = EmptyGame;
	newGameBoardControl->gameHistory = EmptyGameHistory;
	newGameBoardControl->game.gameHistory = &(newGameBoardControl->gameHistory);
	newGameBoardControl->gameStateIsSaved = 1;
	GameBoardControl->currentPieceSelectedRow = -1;
	GameBoardControl->currentPieceSelectedCol = -1;
	return newGameWindow;
}

void SetGameMode(GameBoardControl* src, char gameMode) {
	Command command;
	command.commandType = setGameMode;
	command.argument[0] = gameMode;
	command.numberOfArgs = 1;

	handleCommand(command, &(src - game));
}

void SetPlayerColor(GameBoardControl* src, char player1Color) {
	Command command;
	command.commandType = setUserColor;
	command.argument[0] = player1Color;
	command.numberOfArgs = 1;

	handleCommand(command, &(src - game));
}

void SetGameDifficulty(GameBoardControl* src, char gameDifficulty) {
	Command command;
	command.commandType = setDifficulty;
	command.argument[0] = gameDifficulty;
	command.numberOfArgs = 1;

	handleCommand(command, &(src - game));
}

int IsComputerTurnGameBoardControl(GameBoardControl* src){
	return (getCurrentPlayerColor(&(src->game)) != src->game.player1Color && src->game.gameMode == PlayerVsComputer);
}

void HandleFinishGameGameBoardControl(GameBoardControl* src){
	
}

void HandleCheckPrintsIfNeeded(GameBoardControl* src){
	
}

int IsGameCompletedGameBoardControl(GameBoardControl* src){
	
}

void HandleComputerMoveGameBoardControl(GameBoardControl* src){
	Command  command = getComputerMove(&(src->game));
	handleCommand(command, &(src->game));
}

void GameBoardControlSetUpNewGame(GameBoardControl* src, char gameMode, char player1Color, char gameDifficulty) {
	src->game = EmptyGame;
	src->gameHistory = EmptyGameHistory;
	src->game.gameHistory = &(src->gameHistory);

	SetGameMode(src, gameMode);
	SetPlayerColor(src, player1Color);
	SetGameDifficulty(src, gameDifficulty);

	if (IsComputerTurnGameBoardControl(src) {
		HandleComputerMoveGameBoardControl(src);
	}
}

GameBoardControl* GameBoardControlCreate(SDL_Renderer* renderer, char gameMode, char player1Color, char gameDifficulty) {
	GameBoardControl* newGameBoardControl = GameBoardControlDefaultCreator();

	if (newGameBoardControl == NULL) {
		return NULL;
	}

	GameBoardControlSetUpNewGame(src, gameMode, player1Color, gameDifficulty);

	return newGameWindow;
}

int GameBoardControlLoadGame(GameBoardControl* src, char loadSlotSelected){
	//TODO! need to handle errors here
	return 0;
}

GameBoardControl* GameBoardControlLoad	(SDL_Renderer* renderer, char loadSlotSelected){
	GameBoardControl* newGameBoardControl = GameBoardControlDefaultCreator();
	
	if (newGameBoardControl == NULL ) {
		return NULL ;
	}
	
	if(GameBoardControlLoadGame(src, loadSlotSelected)){
		GameBoardControlDestroy(newGameBoardControl);
		return NULL;
	}
	
	return newGameWindow;
}

void GameBoardControlDestroy(GameBoardControl* src){
	for(int i = 0; i<NUMBER_OF_GAME_BOARD_TEXTURES; i++){
		if(src->textures[i] != NULL){
			SDL_DestroyTexture(src->textures[i] );
		}
	}
	free(src);
}

int GetColorInLocation(GameBoardControl* src, int row, int col) {
	if (row == src->currentPieceSelectedRow && col == src->currentPieceSelectedCol) {
		return 2;
	}
	char rowC = '1' + row;
	char colC = 'A' + col;
	int colorInThisLocation = (row + col) % 2;
	int locationInBoardOfRowCol = rowColToLocationIndex(rowC, colC);
	if (src->availableMovesOfLastPiece.allMoves.legalMovesArray[locationInBoardOfRowCol]) {
		if (src->availableMovesOfLastPiece.threatenedByOpponentMoves.legalMovesArray[locationInBoardOfRowCol]) {
			colorInThisLocation = 2;
		}
		else {
			colorInThisLocation = 3;
		}
	}
	return colorInThisLocation;
}

int GetNeededTextureInSpecificPositionOnBoard(GameBoardControl* src, int row, int col) {
	Piece piece;
	char rowC = '1' + row;
	char colC = 'A' + col;
	int colorInThisLocation = GetColorInLocation(src, row, col);
	int getPieceResult = getPieceAt(rowC, colC, &(src->game.board), &piece);
	int pieceNumber = 0;
	int pieceColor = 0;
	if (getPieceResult != -1) {
		switch (piece.type)
		{
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
		}
		if (piece.player == Player1) {
			if (src->game.player1Color == Black) {
				pieceColor = 1;
			}
		}
		else {
			if (src->game.player1Color == White) {
				pieceColor = 1;
			}
		}
	}
	return pieceNumber * 8 + 4 * pieceColor + colorInThisLocation;
}

void GameBoardControlDraw(GameBoardControl* src, SDL_Renderer* renderer, int[] rentangle) {
	SDL_Rect sdlRect;
	int boardRect[4];
	int neededTextureIndex;
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			boardRect[0] = rentangle[0] + (col* (rentangle[1] - rentangle[0])) / 8;
			boardRect[1] = (rentangle[1] - rentangle[0]) / 8;
			boardRect[2] = rentangle[2] + (row* (rentangle[3] - rentangle[2])) / 8;
			boardRect[1] = (rentangle[3] - rentangle[2]) / 8;
			sdlRect = CreateSDLRectFromIntArray(rect);
			neededTextureIndex = GetNeededTextureInSpecificPositionOnBoard(src, row, col);
			SDL_RenderCopy(renderer, src->texture[neededTextureIndex], NULL, &sdlRect);
		}
	}
}

char AskPlayerForPawnPromotionOption() {

}

void HandlePawnPromotion(GameBoardControl* src, char rowFrom, char colFrom, char rowTo, char colTo) {
	Command command;
	command.commandType = setMove;
	command.argument[0] = rowFrom;
	command.argument[1] = rowFrom;
	command.argument[2] = rowFrom;
	command.argument[3] = rowFrom;
	command.argument[4] = AskPlayerForPawnPromotionOption();
	handleCommand(command, &(src->game));
}

void MakeMoveGameBoardControl(GameBoardControl* src, char rowFrom, char colFrom, char rowTo, char colTo) {
	Command command;
	command.commandType = setMove;
	command.argument[0] = rowFrom;
	command.argument[1] = rowFrom;
	command.argument[2] = rowFrom;
	command.argument[3] = rowFrom;
	command.argument[4] = 0;
	HandleCommandMessage message = handleCommand(command, &(src->game));
	if (message.messageType == pawnPromoteNeededMessage) {
		HandlePawnPromotion(src, rowFrom, colFrom, rowTo, colTo);
	}
}

int ChechIfMoveIsCastleMoveGameBoardControl(GameBoardControl* src, char rowFrom, char colFrom, char rowTo, char colTo){
	//TODO 
	return 0;
}

void MakeCastleMoveGameBoardControl(GameBoardControl* src, char rowFrom, char colFrom, char rowTo, char colTo) {
	//TODO
}

EventStruct GameBoardControlHandleMoveEvent(GameBoardControl* src, int row, int col) {
	EventStruct eventStruct = { EmptyEvent,0 };
	if (IsComputerTurnGameBoardControl(src)) {
		return eventStruct;
	}
	newGameBoardControl->gameStateIsSaved = 0;
	char rowFrom = (char)('1' + GameBoardControl->currentPieceSelectedRow);
	char colFrom = (char)('A' + GameBoardControl->currentPieceSelectedCol);
	char rowTo = (char)('1' + row);
	char colTo = (char)('A' + col);

	if (ChechIfMoveIsCastleMoveGameBoardControl(src, rowFrom, colFrom, rowTo, colTo)) {
		MakeCastleMoveGameBoardControl(src, rowFrom, colFrom, rowTo, colTo);
	}
	else {
		MakeMoveGameBoardControl(src, rowFrom, colFrom, rowTo, colTo);
	}

	if(IsGameCompletedGameBoardControl(src)){
		HandleFinishGameGameBoardControl(src);
		eventStruct.eventType = QuitEvent;
		return eventStruct;
	}
	
	GameBoardControl->currentPieceSelectedRow = -1;
	GameBoardControl->currentPieceSelectedCol = -1;
	if (IsComputerTurnGameBoardControl(src)) {
		HandleComputerMoveGameBoardControl(src);
		if(IsGameCompletedGameBoardControl(src)) {
			HandleFinishGameGameBoardControl(src);
			eventStruct.eventType = QuitEvent;
		}else{
			HandleCheckPrintsIfNeeded(src);
		}
	}
	return eventStruct;
}

int PieceInRowColIsCurrentPlayerPiece(GameBoardControl* src, int row, int col){
	
}

void UpdateCurrentAvailableMoves(GameBoardControl* src){
	Command command;
	command.commandType = getMoves;
	command.argument[0] = (char) ('1' + src->currentPieceSelectedRow);
	command.argument[1] = (char) ('A' + src->currentPieceSelectedCol);
	HandleCommandMessage message = handleGetMoves(Command command, Game *game);
	src->availableMovesOfSelectedPiece = message.getMovesResponse;
}

EventStruct GameBoardControlHandleNewPieceChoosenEvent (GameBoardControl* src, int row, int col){
	EventStruct eventStruct = {EmptyEvent,0};
	if(IsComputerTurnGameBoardControl(src)){
		return eventStruct;
	}
	if(PieceInRowColIsCurrentPlayerPiece(src, row, col)){
		src->currentPieceSelectedRow = row;
		src->currentPieceSelectedCol = col;
		UpdateCurrentAvailableMoves(src);
	}
	return eventStruct;
}

void PrintUndoMoveErrorsGameBoardControl(HandleCommandMessage message){
	char* errorString = NULL;
	if(message.messageType == errorUndo2PlayerModeMessage){
		//TODO
	}else if(message.messageType == errorUndoEmptyHistoryMessage){
		//TODO
	}else{
		errorString = "UnknownErrorOccured";
	}
	//TODO make message box with the error
}

int UndoMoveErrorOccuredGameBoardControl(HandleCommandMessage message){
	return (message.messageType == errorUndo2PlayerModeMessage || message.messageType == errorUndoEmptyHistoryMessage);
}

EventStruct GameBoardControlHandleUndoMove(GameBoardControl* src) {
	EventStruct eventStruct = { EmptyEvent,0 };
	if (IsComputerTurnGameBoardControl(src)) {
		return eventStruct;
	}
	Command command;
	command.commandType = undoMove;
	HandleCommandMessage message = handleCommand(command, &(src->game));
	if(UndoMoveErrorOccuredGameBoardControl(message)){
		PrintUndoMoveErrorsGameBoardControl(message);
	}else{
		newGameBoardControl->gameStateIsSaved = 0;
	}
	return eventStruct;
}

void PrintSaveErrorGameBoardControl(HandleCommandMessage message){
	//TODO print error message
}

int SaveGameErrorOccuredGameBoardControl(HandleCommandMessage message){
	return (message.messageType == errorSaveMessage);
}

EventStruct GameBoardControlHandleSaveGame (GameBoardControl* src){
	EventStruct eventStruct = {EmptyEvent,0};
	Command command;
	command.commandType = saveGame;
	HandleCommandMessage message = handleCommand(command, &(src->game));
	if(SaveGameErrorOccuredGameBoardControl(message){
		PrintSaveErrorIfNeededGameBoardControl(message);
	}else{
		newGameBoardControl->gameStateIsSaved = 1;
	}
	return eventStruct;
}

int CheckIfUserWantToSaveGameIfNeeded_OrCancelAction(GameBoardControl* src) {
	if (src->gameStateIsSaved)
		return 1;
	const SDL_MessageBoxButtonData buttons[] = {
		{ /* .flags, .buttonid, .text */        0, 0, "no" },
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" },
	};
	const SDL_MessageBoxColorScheme colorScheme = {
		{ /* .colors (.r, .g, .b) */
			/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
			{ 255,   0,   0 },
			/* [SDL_MESSAGEBOX_COLOR_TEXT] */
			{   0, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
			{ 255, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
			{   0,   0, 255 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
			{ 255,   0, 255 }
		}
	};
	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, /* .flags */
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
	}
	else if (buttonid == 1) {
		GameBoardControlHandleSaveGame(src);
	}
	return 1;

}

EventStruct GameBoardControlHandleRestartGame(GameBoardControl* src) {
	EventStruct eventStruct = { EmptyEvent,0 };
	char gameMode, player1Color, gameDifficulty;
	if (CheckIfUserWantToSaveGameIfNeeded_OrCancelAction(src)) {
		gameMode = src->game.gameMode;
		player1Color = src->game.player1Color;
		gameDifficulty = src->game.difficulty;
		GameBoardControlSetUpNewGame(src, gameMode, player1Color, gameDifficulty);
	}
	return eventStruct;
}

EventStruct GameBoardControlHandleQuitGame(GameBoardControl* src) {
	EventStruct eventStruct = { EmptyEvent,0 };
	if (CheckIfUserWantToSaveGameIfNeeded_OrCancelAction(src)) {
		eventStruct.eventType = QuitEvent;
	}
	return eventStruct;
}

int ClickWasOnGameRow(SDL_Event* event, int[] rentangle) {
	int y = event->button.y;
	y -= rentangle[2];
	return y / ((rentangle[3] - rentangle[2]) / 8);
}

int ClickWasOnGameCol(SDL_Event* event, int[] rentangle) {
	int x = event->button.x;
	x -= rentangle[0];
	return x / ((rentangle[1] - rentangle[0]) / 8);
}

int IsValidMoveForCurrentSelectedPiece(GameBoardControl* src, int row, int col) {
	if (GameBoardControl->currentPieceSelectedRow == -1) {
		return 0;
	}
	char rowC = '1' + row;
	char colC = 'A' + col;
	if (src->availableMovesOfLastPiece.allMoves.legalMovesArray[rowColToLocationIndex(rowC, colC)]) {
		return 1;
	}
	else {
		return 0;
	}
}

EventStruct GameBoardControlHandleEvent(GameBoardControl* src, SDL_Event* event, int[] rentangle) {
	EventStruct eventStruct = { EmptyEvent,0 };
	if (event == NULL) {
		return eventStruct;
	}

	if (IsComputerTurnGameBoardControl(src)) {
		return eventStruct;
	}

	int row = ClickWasOnGameRow(event, rentangle);
	int col = ClickWasOnGameCol(event, rentangle);

	if (IsValidMoveForCurrentSelectedPiece(src, row, col) {
		return GameBoardControlHandleMoveEvent(src, row, col);
	}
	else {
		return GameBoardControlHandleNewPieceChoosenEvent(src, row, col);
	}
}