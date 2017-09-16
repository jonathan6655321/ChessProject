#include "GameWindow.h"

GameWindowElement ClickWasOnGameWindow(int x, int y){
		if (PointInsideRentangle(x,y,gameBoardGameWindowRentangle)) 
			return GameBoardGameWindowElement;
		else if(PointInsideRentangle(x,y,saveGameGameWindowRentangle))
			return SaveGameButtonGameWindowElement;
		else if(PointInsideRentangle(x,y,loadGameGameWindowRentangle))
			return LoadGameButtonGameWindowElement;
		else if(PointInsideRentangle(x,y,undoButtonGameWindowRentangle))
			return UndoButtonGameWindowElement;
		else if(PointInsideRentangle(x,y,goToMainWindowButtonGameWindowRentangle))
			return GoToMainWindowButtonGameWindowElement;
		else if(PointInsideRentangle(x,y,restartButtonGameWindowRentangle))
			return RestartGameButtonGameWindowElement;
		else if(PointInsideRentangle(x,y,quitGameGameWindowRentangle))
			return QuitButtonGameWindowElement;
		else
			return BackgroundGameWindowElement;
}

void CreateGameWindow(GameWindow* src){
	// Create an application window with the following settings:
	src->gameWindow = SDL_CreateWindow("Chess Game", 	// window title
			SDL_WINDOWPOS_CENTERED,           						// initial x position
			SDL_WINDOWPOS_CENTERED,    								// initial y position
			backgroundGameWindowMaxX,									// width, in pixels
			backgroundGameWindowMaxY,                               	// height, in pixels
			SDL_WINDOW_OPENGL                  							// TODO: what is this
			);
}

GameWindow* GameWindowDefaultCreator(){
	GameWindow* newGameWindow = (GameWindow*) calloc(sizeof(GameWindow), sizeof(char));
	
	if (newGameWindow == NULL ) {
		printf("malloc: Error\n");
		return NULL ;
	}

	createGameWindow(newGameWindow);
	// Check that the window was successfully created
	if (newGameWindow->gameWindow == NULL ) {
		GameWindowDestroy(newGameWindow);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	
	newGameWindow->gameRenderer = SDL_CreateRenderer(newGameWindow->gameWindow, -1, SDL_RENDERER_ACCELERATED);
	// Check that the window renerer was created
	if (newGameWindow->gameRenderer == NULL ) {
		GameWindowDestroy(newGameWindow);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	
	int success = 1;
	success &= LoadTexture(&(newGameWindow->backgroundTexture),  			newGameWindow->gameRenderer, 	BACKGROUND_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newGameWindow->saveGameTexture),  			newGameWindow->gameRenderer, 	SAVE_GAME_BUTTON_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newGameWindow->loadGameTexture),  			newGameWindow->gameRenderer, 	LOAD_GAME_BUTTON_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newGameWindow->undoTexture),  					newGameWindow->gameRenderer, 	UNDO_BUTTON_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newGameWindow->goToMainWindowTexture),  	newGameWindow->gameRenderer, 	GO_TO_MAIN_WINDOW_BUTTON_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newGameWindow->restartTexture),  					newGameWindow->gameRenderer, 	RESTART_GAME_BUTTON_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newGameWindow->quitTexture),  						newGameWindow->gameRenderer, 	QUIT_GAME_BUTTON_GAME_WINDOW_TEXTURE_PATH);

	if (!success) {
		GameWindowDestroy(newGameWindow);
		return NULL ;
	}
		
	return newGameWindow;
}

GameWindow* GameWindowLoad(char loadSlotSelected){
	GameWindow* newGameWindow = GameWindowDefaultCreator();
	
	if (newGameWindow == NULL ) {
		return NULL ;
	}

	newGameWindow->gameControl = GameBoardControlLoad(newGameWindow->gameRenderer, loadSlotSelected);
	if (newGameWindow->gameControl == NULL) {
		GameWindowDestroy(newGameWindow);
		return NULL ;
	}
	
	return newGameWindow;
}

GameWindow* GameWindowCreate(char gameMode, char player1Color, char gameDifficulty) {
	GameWindow* newGameWindow = GameWindowDefaultCreator();
	
	if (newGameWindow == NULL ) {
		return NULL ;
	}

	newGameWindow->gameControl = GameBoardControlCreate(newGameWindow->gameRenderer, gameMode, player1Color, gameDifficulty);
	if (newGameWindow->gameControl == NULL) {
		GameWindowDestroy(newGameWindow);
		return NULL ;
	}
	
	return newGameWindow;
}

void GameWindowDestroy(GameWindow* src) {
	if (src->backgroundTexture != NULL )
		SDL_DestroyTexture(src->backgroundTexture);
	if (src->saveGameTexture != NULL )
		SDL_DestroyTexture(src->saveGameTexture);
	if (src->loadGameTexture != NULL )
		SDL_DestroyTexture(src->loadGameTexture);
	if (src->undoTexture != NULL )
		SDL_DestroyTexture(src->undoTexture);
	if (src->goToMainWindowTexture != NULL )
		SDL_DestroyTexture(src->goToMainWindowTexture);
	if (src->restartTexture != NULL )
		SDL_DestroyTexture(src->restartTexture);
	if (src->quitTexture != NULL )
		SDL_DestroyTexture(src->quitTexture);
	
	if (src->gameControl != NULL )
		GameBoardControlDestroy(src->gameControl);
	
	if (src->gameRenderer != NULL )
		SDL_DestroyRenderer(src->gameRenderer);
	if (src->gameWindow != NULL ) 
		SDL_DestroyWindow(src->gameWindow);
	free(src);
}

void GameWindowDraw(GameWindow* src) {
	SDL_Rect saveGameR = CreateSDLRectFromIntArray(saveGameGameWindowRentangle);
	SDL_Rect loadGameR = CreateSDLRectFromIntArray(loadGameGameWindowRentangle);
	SDL_Rect undoR = CreateSDLRectFromIntArray(undoButtonGameWindowRentangle);
	SDL_Rect goToMainWindowR = CreateSDLRectFromIntArray(goToMainWindowButtonGameWindowRentangle);
	SDL_Rect restartR = CreateSDLRectFromIntArray(restartButtonGameWindowRentangle);
	SDL_Rect quitR = CreateSDLRectFromIntArray(quitGameGameWindowRentangle);
	SDL_Rect backgroundR = CreateSDLRectFromIntArray(backgroundGameWindowRentangle);
	
	SDL_SetRenderDrawColor(src->gameRenderer, 255, 255, 255, 255);

	SDL_RenderClear(src->gameRenderer);
	SDL_RenderCopy(src->gameRenderer, src->backgroundTexture, NULL, &backgroundR);
	SDL_RenderCopy(src->gameRenderer, src->saveGameTexture, NULL, &saveGameR);
	SDL_RenderCopy(src->gameRenderer, src->loadGameTexture, NULL, &loadGameR);
	SDL_RenderCopy(src->gameRenderer, src->undoTexture, NULL, &undoR);
	SDL_RenderCopy(src->gameRenderer, src->goToMainWindowTexture, NULL, &goToMainWindowR);
	SDL_RenderCopy(src->gameRenderer, src->restartTexture, NULL, &restartR);
	SDL_RenderCopy(src->gameRenderer, src->quitTexture, NULL, &quitR);

	GameBoardControlDraw(src->gameControl, src->gameRenderer, gameBoardGameWindowRentangle);
	
	SDL_RenderPresent(src->gameRenderer);
}

void GameWindowHide	(GameWindow* src) {
	SDL_HideWindow(src->gameWindow);
}

void GameWindowShow(GameWindow* src) {
	SDL_ShowWindow(src->gameWindow);
}

EventType GetGameWindowEvent(SDL_Event* event){
	switch(ClickWasOnGameWindow(event->button.x, event->button.y)){
		case SaveGameButtonGameWindowElement:
			return SaveGameButtonGameWindowClickEvent;
		case LoadGameButtonGameWindowElement:
			return LoadGameButtonGameWindowClickEvent;
		case UndoButtonGameWindowElement:
			return UndoButtonGameWindowClickEvent;
		case GoToMainWindowButtonGameWindowElement:
			return GoToMainWindowButtonGameWindowClickEvent;
		case RestartGameButtonGameWindowElement:
			return RestartGameButtonGameWindowClickEvent;
		case NewGameButtonElement:
			return NewGameButtonMainWindowClickEvent;
		case LoadGameButtonElement:
			return LoadGameButtonMainWindowClickEvent;
		case QuitButtonGameWindowElement:
			return QuitButtonGameWindowClickEvent;
		case GameBoardGameWindowElement:
			return BoardPositionButtonGameWindowClickEvent;
		default:
			return EmptyEvent;
	}
}

EventStruct GameWindowHandleEvent (GameWindow* src, SDL_Event* event) {
	EventStruct eventStruct = {EmptyEvent,0};
	if (event == NULL){
		return eventStruct;
	}
	
	eventStruct.eventType = GetGameWindowEvent(event);
	switch(eventStruct.eventType){
		case BoardPositionButtonGameWindowClickEvent:
			return GameBoardControlHandleEvent(src->gameControl ,event, gameBoardGameWindowRentangle);
		case UndoButtonGameWindowClickEvent:
			return GameBoardControlHandleUndoMove(src->gameControl);
		case SaveGameButtonGameWindowClickEvent:
			return GameBoardControlHandleSaveGame(src->gameControl);
		case RestartGameButtonGameWindowClickEvent:
			return GameBoardControlHandleRestartGame(src->gameControl);
		case QuitButtonGameWindowClickEvent:
			return GameBoardControlHandleQuitGame(src->gameControl);
		default:
			return eventStruct;
	}
}



void spGameWindowDraw(SPGameWin* src) {
	if(src == NULL){
		return;
	}
	SDL_Rect rec = { .x = 0, .y = 0, .w = 600, .h = 600 };
	SDL_SetRenderDrawColor(src->renderer, 255, 255, 255, 255);
	SDL_RenderClear(src->renderer);
	SDL_RenderCopy(src->renderer, src->bgTexture, NULL, &rec);

	int i = 0, j = 0;
	for (i = 0; i < SP_N_ROWS; i++) {
		for (j = 0; j < SP_N_COLUMNS; j++) {
			rec.x = j * 200;
			rec.y = i * 200;
			rec.h = 200;
			rec.w = 200;
			if (src->game->board[i][j] == SP_PLAYER_1_SYMBOL) {
				SDL_RenderCopy(src->renderer, src->xTexture, NULL, &rec);
			} else if (src->game->board[i][j] == SP_PLAYER_2_SYMBOL) {
				SDL_RenderCopy(src->renderer, src->oTexture, NULL, &rec);
			}
		}
	}
	SDL_RenderPresent(src->renderer);
}

SP_GAME_EVENT spGameWindowHandleEvent(SPGameWin* src, SDL_Event* event) {
	if (event == NULL || src == NULL ) {
		return SP_GAME_EVENT_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		spTicTacToeSetMove(src->game, event->button.y / 200,
				event->button.x / 200);
		char winner = spTicTacToeCheckWinner(src->game);
		if (winner == SP_PLAYER_1_SYMBOL) {
			return SP_GAME_EVENT_X_WON;
		} else if (winner == SP_PLAYER_2_SYMBOL) {
			return SP_GAME_EVENT_O_WON;
		} else if (spTicTacToeIsGameOver(src->game)) {
			return SP_GAME_EVENT_TIE;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_GAME_EVENT_QUIT;
		}
		break;
	default:
		return SP_GAME_EVENT_NONE;
	}
	return SP_GAME_EVENT_NONE;
}
