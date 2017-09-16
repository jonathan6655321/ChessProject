#ifndef CHESSGAMEBOARD_H
#define CHESSGAMEBOARD_H
#include <SDL.h>
#include <stdio.h>
#include "Events.h"
#include "SDLHelperFunctions.h"
#include "../Game.h"
TODO: #include <SDL_video.h>
TODO: #include "SPTicTacToeWindow.h"

typedef struct {
	int 					lastPieceChoosen;
	int 					availableMovesOfLastPiece[];
	
	SDL_Texture* 	textures[NUMBER_OF_GAME_BOARD_TEXTURES]; // type of pieces + empty pieces  * white&black&blue&darkerBlue
	Game 				game;
	GameHistory 	gameHistory;
} GameBoardControl;

GameBoardControl* GameBoardControlCreate	(SDL_Renderer* renderer, char gameMode, char player1Color, char gameDifficulty);
GameBoardControl* GameBoardControlLoad	(SDL_Renderer* renderer, char loadSlotSelected);

void GameBoardControlDraw		(GameBoardControl* src, SDL_Renderer* renderer, int[] rentangle);
void GameBoardControlDestroy	(GameBoardControl* src);

EventStruct GameBoardControlHandleMoveEvent						(GameBoardControl* src, int boardLocationClick);
EventStruct GameBoardControlHandleNewPieceChoosenEvent	(GameBoardControl* src, int boardLocationClick);
EventStruct GameBoardControlHandleUndoMove						(GameBoardControl* src);
EventStruct GameBoardControlHandleSaveGame						(GameBoardControl* src);
EventStruct GameBoardControlHandleRestartGame					(GameBoardControl* src);
EventStruct GameBoardControlHandleQuitGame						(GameBoardControl* src);
EventStruct GameBoardControlHandleEvent								(GameBoardControl* src, SDL_Event* event, int[] rentangle) ;

#endif

#include "GameBoardControl.h"

GameBoardControl* GameBoardControlDefaultCreator(){
	GameBoardControl* newGameBoardControl = (GameBoardControl*) calloc(sizeof(GameBoardControl), sizeof(char));
	
	if (newGameBoardControl == NULL ) {
		printf("malloc: Error\n");
		return NULL ;
	}

	char buff[1024];
	int success = 1;
	for(int i = 0; i<NUMBER_OF_GAME_BOARD_TEXTURES; i++){
		sprintf(str, GAME_BOARD_TEXTURE_PATH_FORMAT, i);
		success &= LoadTexture(&(newGameBoardControl->textures[i]),  			newGameWindow->gameRenderer, 	buff);
	}
	
	if (!success) {
		GameBoardControlDestroy(newGameBoardControl);
		return NULL ;
	}
	
	newGameBoardControl->game = EmptyGame;
	newGameBoardControl->gameHistory = EmptyGameHistory;
	newGameBoardControl->game.gameHistory = &(newGameBoardControl->gameHistory);
	newGameBoardControl->gameStateIsSaved = 1;
	GameBoardControl->currentPieceSelectedRow = -1;
	GameBoardControl->currentPieceSelectedCol = -1;
	return newGameWindow;
}

void SetGameMode(GameBoardControl* src, char gameMode){
	Command command;
	command.commandType = setGameMode;
	command.argument[0] = gameMode;
	command.numberOfArgs = 1;
	
	handleCommand(command, &(src-game));
}

void SetPlayerColor(GameBoardControl* src, char player1Color){
	Command command;
	command.commandType = setUserColor;
	command.argument[0] = player1Color;
	command.numberOfArgs = 1;
	
	handleCommand(command, &(src-game));
}

void SetGameDifficulty(GameBoardControl* src, char gameDifficulty){
	Command command;
	command.commandType = setDifficulty;
	command.argument[0] = gameDifficulty;
	command.numberOfArgs = 1;
	
	handleCommand(command, &(src-game));
}

int IsComputerTurnGameBoardControl(GameBoardControl* src){
	//TODO
	return 0;
}

void HandleComputerMoveGameBoardControl(GameBoardControl* src){
	//TODO;
}

void GameBoardControlSetUpNewGame(GameBoardControl* src, char gameMode, char player1Color, char gameDifficulty){
	src->game = EmptyGame;
	src->gameHistory = EmptyGameHistory;
	src->game.gameHistory = &(src->gameHistory);
	
	SetGameMode(src, gameMode);
	SetPlayerColor(src, player1Color);
	SetGameDifficulty(src, gameDifficulty);

	if(IsComputerTurnGameBoardControl(src){
		HandleComputerMoveGameBoardControl(src);
	}
}

GameBoardControl* GameBoardControlCreate(SDL_Renderer* renderer ,char gameMode, char player1Color, char gameDifficulty){
	GameBoardControl* newGameBoardControl = GameBoardControlDefaultCreator();
	
	if (newGameBoardControl == NULL ) {
		return NULL ;
	}
	
	GameBoardControlSetUpNewGame(src, gameMode, player1Color, gameDifficulty);	
	
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

int GetNeededTextureInSpecificPositionOnBoard(GameBoardControl* src, int row, int col){
	//TODO
	return 0;
}

void GameBoardControlDraw (GameBoardControl* src, SDL_Renderer* renderer, int[] rentangle){
	SDL_Rect sdlRect;
	int boardRect[4];
	int neededTextureIndex;
	for(int row = 0; row < 8; row++){
		for(int col = 0; col < 8; col++){
			boardRect[0] = rentangle[0] + (col* (rentangle[1]-rentangle[0]))/8;
			boardRect[1] = (rentangle[1]-rentangle[0])/8;
			boardRect[2] = rentangle[2] + (row* (rentangle[3]-rentangle[2]))/8;
			boardRect[1] = (rentangle[3]-rentangle[2])/8;
			sdlRect = CreateSDLRectFromIntArray(rect);
			neededTextureIndex = GetNeededTextureInSpecificPositionOnBoard(src, row, col);
			SDL_RenderCopy(renderer, src->texture[neededTextureIndex], NULL, &sdlRect);
		}
	}
}

char AskPlayerForPawnPromotionOption(){
	
}

void HandlePawnPromotion(GameBoardControl* src, char rowFrom, char colFrom, char rowTo, char colTo){
	Command command;
	command.commandType = setMove;
	command.argument[0] = rowFrom;
	command.argument[1] = rowFrom;
	command.argument[2] = rowFrom;
	command.argument[3] = rowFrom;
	command.argument[4] = AskPlayerForPawnPromotionOption();
	handleCommand(command, &(src->game));
}

void MakeMoveGameBoardControl(GameBoardControl* src, char rowFrom, char colFrom, char rowTo, char colTo){
	Command command;
	command.commandType = setMove;
	command.argument[0] = rowFrom;
	command.argument[1] = rowFrom;
	command.argument[2] = rowFrom;
	command.argument[3] = rowFrom;
	command.argument[4] = 0;
	HandleCommandMessage message = handleCommand(command, &(src->game));
	if(message.messageType == pawnPromoteNeededMessage){
		HandlePawnPromotion(src, rowFrom, colFrom, rowTo, colTo);
	}
}

int ChechIfMoveIsCastleMoveGameBoardControl(GameBoardControl* src, char rowFrom, char colFrom, char rowTo, char colTo){
	
}

void MakeCastleMoveGameBoardControl(GameBoardControl* src, char rowFrom, char colFrom, char rowTo, char colTo){
		
}

EventStruct GameBoardControlHandleMoveEvent	(GameBoardControl* src, int row, int col){
	EventStruct eventStruct = {EmptyEvent,0};
	if(IsComputerTurnGameBoardControl(src)){
		return eventStruct;
	}
	newGameBoardControl->gameStateIsSaved = 0;
	char rowFrom = (char) ('1' + GameBoardControl->currentPieceSelectedRow);
	char colFrom = (char)( 'A' + GameBoardControl->currentPieceSelectedCol);
	char rowTo = (char) ('1' + row);
	char colTo = (char) ('A' + col);

	if(ChechIfMoveIsCastleMoveGameBoardControl(src, rowFrom, colFrom, rowTo, colTo)){
		MakeCastleMoveGameBoardControl(src, rowFrom, colFrom, rowTo, colTo);
	}else{
		MakeMoveGameBoardControl(src, rowFrom, colFrom, rowTo, colTo);
	}
	
	GameBoardControl->currentPieceSelectedRow = -1;
	GameBoardControl->currentPieceSelectedCol = -1;
	if(IsComputerTurnGameBoardControl(src)){
		HandleComputerMoveGameBoardControl(src);
	}
}

EventStruct GameBoardControlHandleNewPieceChoosenEvent	(GameBoardControl* src, int row, int col){
	EventStruct eventStruct = {EmptyEvent,0};
	if(IsComputerTurnGameBoardControl(src)){
		return eventStruct;
	}
	
}

EventStruct GameBoardControlHandleUndoMove	(GameBoardControl* src){
	EventStruct eventStruct = {EmptyEvent,0};
	if (IsComputerTurnGameBoardControl(src)) {
		return eventStruct;
	}
	Command command;
	command.commandType = setMove;
	command.argument[0] = rowFrom;
	command.argument[1] = rowFrom;
	command.argument[2] = rowFrom;
	command.argument[3] = rowFrom;
	command.argument[4] = 0;
	HandleCommandMessage message = handleCommand(command, &(src->game));

	newGameBoardControl->gameStateIsSaved = 0;
}

EventStruct GameBoardControlHandleSaveGame (GameBoardControl* src){
	EventStruct eventStruct = {EmptyEvent,0};
	newGameBoardControl->gameStateIsSaved = 1;
}

int CheckIfUserWantToSaveGameIfNeeded_OrCancelAction(GameBoardControl* src){
	if(src->gameStateIsSaved)
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
	} else if (buttonid == 1){
       GameBoardControlHandleSaveGame(src);
    }
    return 1;

}

EventStruct GameBoardControlHandleRestartGame	(GameBoardControl* src){
	EventStruct eventStruct = {EmptyEvent,0};
	char gameMode, player1Color, gameDifficulty;
	if(CheckIfUserWantToSaveGameIfNeeded_OrCancelAction(src)){
		gameMode = src->game.gameMode;
		player1Color = src->game.player1Color;
		gameDifficulty = src->game.difficulty;
		GameBoardControlSetUpNewGame(src, gameMode, player1Color, gameDifficulty);
	}
	return eventStruct;
}

EventStruct GameBoardControlHandleQuitGame (GameBoardControl* src){
	EventStruct eventStruct = {EmptyEvent,0};
	if(CheckIfUserWantToSaveGameIfNeeded_OrCancelAction(src)){
		eventStruct.eventType = QuitEvent;
	}
	return eventStruct;	
}

int ClickWasOnGameRow(SDL_Event* event, int[] rentangle){
	int y = event->button.y;
	y -= rentangle[2];
	return y / ((rentangle[3]-rentangle[2])/8);
}

int ClickWasOnGameCol(SDL_Event* event, int[] rentangle){
	int x = event->button.x;
	x -= rentangle[0];
	return x / ((rentangle[1]-rentangle[0])/8);
}

int IsValidMoveForCurrentSelectedPiece(GameBoardControl* src, int row, int col){
	if(GameBoardControl->currentPieceSelectedRow == -1){
		return 0;
	}
}

EventStruct GameBoardControlHandleEvent (GameBoardControl* src, SDL_Event* event, int[] rentangle) {
	EventStruct eventStruct = {EmptyEvent,0};
	if (event == NULL){
		return eventStruct;
	}
	
	if(IsComputerTurnGameBoardControl(src)){
		return eventStruct;
	}
	
	int row = ClickWasOnGameRow(event, rentangle);
	int col = ClickWasOnGameCol(event, rentangle);
	
	if(IsValidMoveForCurrentSelectedPiece(src, row, col){
		return GameBoardControlHandleMoveEvent(src, row, col);
	}else{
		return GameBoardControlHandleNewPieceChoosenEvent(src, row, col);
	}
}