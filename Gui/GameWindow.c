#include "GameWindow.h"
static int gameBoardGameWindowRectangle[4] = { 50, 650, 100, 700 };
static int saveGameGameWindowRectangle[4] = { 700, 800, 100, 150 };
static int loadGameGameWindowRectangle[4] = { 700, 800, 200, 250 };
static int undoButtonGameWindowRectangle[4] = { 700, 800, 300, 350 };
static int goToMainWindowButtonGameWindowRectangle[4] = { 700, 800, 400, 450 };
static int restartButtonGameWindowRectangle[4] = { 700, 800, 500, 550 };
static int quitGameGameWindowRectangle[4] = { 700, 800, 600, 650 };
static int backgroundGameWindowRectangle[4] = { 0, 850, 0, 800 };

GameWindowElement ClickWasOnGameWindow(int x, int y) {
	if (PointInsideRectangle(x, y, gameBoardGameWindowRectangle))
		return GameBoardGameWindowElement;
	else if (PointInsideRectangle(x, y, saveGameGameWindowRectangle))
		return SaveGameButtonGameWindowElement;
	else if (PointInsideRectangle(x, y, loadGameGameWindowRectangle))
		return LoadGameButtonGameWindowElement;
	else if (PointInsideRectangle(x, y, undoButtonGameWindowRectangle))
		return UndoButtonGameWindowElement;
	else if (PointInsideRectangle(x, y, goToMainWindowButtonGameWindowRectangle))
		return GoToMainWindowButtonGameWindowElement;
	else if (PointInsideRectangle(x, y, restartButtonGameWindowRectangle))
		return RestartGameButtonGameWindowElement;
	else if (PointInsideRectangle(x, y, quitGameGameWindowRectangle))
		return QuitButtonGameWindowElement;
	else
		return BackgroundGameWindowElement;
}

void CreateGameWindow(GameWindow* src) {
	// Create an application window with the following settings:
	src->gameWindow = SDL_CreateWindow("Chess Game", // window title
			SDL_WINDOWPOS_CENTERED, // initial x position
			SDL_WINDOWPOS_CENTERED, // initial y position
			backgroundGameWindowRectangle[1], // width, in pixels
			backgroundGameWindowRectangle[3], // height, in pixels
			SDL_WINDOW_OPENGL
			);
}

GameWindow* GameWindowDefaultCreator() {
	GameWindow* newGameWindow = (GameWindow*) calloc(sizeof(GameWindow),
			sizeof(char));

	if (newGameWindow == NULL) {
		printf("malloc: Error\n");
		return NULL;
	}

	CreateGameWindow(newGameWindow);
	// Check that the window was successfully created
	if (newGameWindow->gameWindow == NULL) {
		GameWindowDestroy(newGameWindow);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL;
	}

	newGameWindow->gameRenderer = SDL_CreateRenderer(newGameWindow->gameWindow,
			-1, SDL_RENDERER_ACCELERATED);
	// Check that the window renerer was created
	if (newGameWindow->gameRenderer == NULL) {
		GameWindowDestroy(newGameWindow);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL;
	}

	int success = 1;
	success &= LoadTexture(&(newGameWindow->backgroundTexture),
			newGameWindow->gameRenderer, BACKGROUND_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newGameWindow->saveGameTexture),
			newGameWindow->gameRenderer,
			SAVE_GAME_BUTTON_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newGameWindow->loadGameTexture),
			newGameWindow->gameRenderer,
			LOAD_GAME_BUTTON_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newGameWindow->undoTexture),
			newGameWindow->gameRenderer, UNDO_BUTTON_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newGameWindow->goToMainWindowTexture),
			newGameWindow->gameRenderer,
			GO_TO_MAIN_WINDOW_BUTTON_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newGameWindow->restartTexture),
			newGameWindow->gameRenderer,
			RESTART_GAME_BUTTON_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newGameWindow->quitTexture),
			newGameWindow->gameRenderer,
			QUIT_GAME_BUTTON_GAME_WINDOW_TEXTURE_PATH);

	if (!success) {
		GameWindowDestroy(newGameWindow);
		return NULL;
	}

	return newGameWindow;
}

GameWindow* GameWindowLoad(char loadSlotSelected) {
	GameWindow* newGameWindow = GameWindowDefaultCreator();

	if (newGameWindow == NULL) {
		return NULL;
	}

	newGameWindow->gameControl = GameBoardControlLoad(
			newGameWindow->gameRenderer, loadSlotSelected);
	if (newGameWindow->gameControl == NULL) {
		GameWindowDestroy(newGameWindow);
		return NULL;
	}

	return newGameWindow;
}

GameWindow* GameWindowCreate(char gameMode, char player1Color,
		char gameDifficulty) {
	GameWindow* newGameWindow = GameWindowDefaultCreator();

	if (newGameWindow == NULL) {
		return NULL;
	}

	newGameWindow->gameControl
			= GameBoardControlCreate(newGameWindow->gameRenderer, gameMode,
					player1Color, gameDifficulty);
	if (newGameWindow->gameControl == NULL) {
		GameWindowDestroy(newGameWindow);
		return NULL;
	}
	return newGameWindow;
}

void GameWindowDestroy(GameWindow* src) {
	if (src->backgroundTexture != NULL)
		SDL_DestroyTexture(src->backgroundTexture);
	if (src->saveGameTexture != NULL)
		SDL_DestroyTexture(src->saveGameTexture);
	if (src->loadGameTexture != NULL)
		SDL_DestroyTexture(src->loadGameTexture);
	if (src->undoTexture != NULL)
		SDL_DestroyTexture(src->undoTexture);
	if (src->goToMainWindowTexture != NULL)
		SDL_DestroyTexture(src->goToMainWindowTexture);
	if (src->restartTexture != NULL)
		SDL_DestroyTexture(src->restartTexture);
	if (src->quitTexture != NULL)
		SDL_DestroyTexture(src->quitTexture);

	if (src->gameControl != NULL)
		GameBoardControlDestroy(src->gameControl);

	if (src->gameRenderer != NULL)
		SDL_DestroyRenderer(src->gameRenderer);
	if (src->gameWindow != NULL)
		SDL_DestroyWindow(src->gameWindow);
	free(src);
}

void GameWindowDraw(GameWindow* src) {
	SDL_Rect saveGameR = CreateSDLRectFromIntArray(saveGameGameWindowRectangle);
	SDL_Rect loadGameR = CreateSDLRectFromIntArray(loadGameGameWindowRectangle);
	SDL_Rect undoR = CreateSDLRectFromIntArray(undoButtonGameWindowRectangle);
	SDL_Rect goToMainWindowR = CreateSDLRectFromIntArray(
			goToMainWindowButtonGameWindowRectangle);
	SDL_Rect restartR = CreateSDLRectFromIntArray(
			restartButtonGameWindowRectangle);
	SDL_Rect quitR = CreateSDLRectFromIntArray(quitGameGameWindowRectangle);
	SDL_Rect backgroundR = CreateSDLRectFromIntArray(
			backgroundGameWindowRectangle);

	SDL_SetRenderDrawColor(src->gameRenderer, 255, 255, 255, 255);

	SDL_RenderClear(src->gameRenderer);
	SDL_RenderCopy(src->gameRenderer, src->backgroundTexture, NULL,
			&backgroundR);
	SDL_RenderCopy(src->gameRenderer, src->saveGameTexture, NULL, &saveGameR);
	SDL_RenderCopy(src->gameRenderer, src->loadGameTexture, NULL, &loadGameR);
	SDL_RenderCopy(src->gameRenderer, src->undoTexture, NULL, &undoR);
	SDL_RenderCopy(src->gameRenderer, src->goToMainWindowTexture, NULL,
			&goToMainWindowR);
	SDL_RenderCopy(src->gameRenderer, src->restartTexture, NULL, &restartR);
	SDL_RenderCopy(src->gameRenderer, src->quitTexture, NULL, &quitR);

	GameBoardControlDraw(src->gameControl, src->gameRenderer,
			gameBoardGameWindowRectangle);

	SDL_RenderPresent(src->gameRenderer);
}

void GameWindowHide(GameWindow* src) {
	SDL_HideWindow(src->gameWindow);
}

void GameWindowShow(GameWindow* src) {
	SDL_ShowWindow(src->gameWindow);
}

EventType GetGameWindowEvent(SDL_Event* event) {
	switch (ClickWasOnGameWindow(event->button.x, event->button.y)) {
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
	case QuitButtonGameWindowElement:
		return QuitButtonGameWindowClickEvent;
	case GameBoardGameWindowElement:
		return BoardPositionButtonGameWindowClickEvent;
	default:
		return EmptyEvent;
	}
}

EventStruct GameWindowHandleEvent(GameWindow* src, SDL_Event* event) {
	EventStruct eventStruct = { EmptyEvent, { 0 } };
	if (event == NULL) {
		return eventStruct;
	}

	eventStruct.eventType = GetGameWindowEvent(event);
	switch (eventStruct.eventType) {
	case BoardPositionButtonGameWindowClickEvent:
		return GameBoardControlHandleEvent(src->gameControl, event,
				gameBoardGameWindowRectangle);
	case UndoButtonGameWindowClickEvent:
		return GameBoardControlHandleUndoMove(src->gameControl);
	case SaveGameButtonGameWindowClickEvent:
		return GameBoardControlHandleSaveGame(src->gameControl);
	case RestartGameButtonGameWindowClickEvent:
		return GameBoardControlHandleRestartGame(src->gameControl);
	case GoToMainWindowButtonGameWindowClickEvent:
		return GameBoardControlHandleGoToMainWindow(src->gameControl);
	case QuitButtonGameWindowClickEvent:
		return GameBoardControlHandleQuitGame(src->gameControl);
	default:
		return eventStruct;
	}
}
