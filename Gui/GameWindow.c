#include "GameWindow.h"
// the game windows specification and sizes:
static int gameBoardGameWindowRectangle[4] = { 50, 650, 100, 700 };
static int saveGameGameWindowRectangle[4] = { 700, 800, 100, 150 };
static int loadGameGameWindowRectangle[4] = { 700, 800, 200, 250 };
static int undoButtonGameWindowRectangle[4] = { 700, 800, 300, 350 };
static int goToMainWindowButtonGameWindowRectangle[4] = { 700, 800, 400, 450 };
static int restartButtonGameWindowRectangle[4] = { 700, 800, 500, 550 };
static int quitGameGameWindowRectangle[4] = { 700, 800, 600, 650 };
static int backgroundGameWindowRectangle[4] = { 0, 850, 0, 800 };

// return where is the button on right now.
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

// create a new game windows window.
void CreateGameWindow(GameWindow* src) {
	// Create an application window with the following settings:
	src->gameWindow = SDL_CreateWindow("Chess Game", // window title
			SDL_WINDOWPOS_CENTERED, // initial x position
			SDL_WINDOWPOS_CENTERED, // initial y position
			backgroundGameWindowRectangle[1], // width, in pixels
			backgroundGameWindowRectangle[3], // height, in pixels
			SDL_WINDOW_OPENGL);
}

// create the default game window. return null on failure.
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

	int success = 1;
	success &= LoadSurface(&(newGameWindow->backgroundSurface),
			BACKGROUND_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(&(newGameWindow->saveGameSurface),
			SAVE_GAME_BUTTON_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(&(newGameWindow->loadGameSurface),
			LOAD_GAME_BUTTON_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(&(newGameWindow->undoSurface),
			UNDO_BUTTON_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(&(newGameWindow->unavailableUndoSurface),
			UNAVAILABLE_UNDO_BUTTON_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(&(newGameWindow->goToMainWindowSurface),
			GO_TO_MAIN_WINDOW_BUTTON_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(&(newGameWindow->restartSurface),
			RESTART_GAME_BUTTON_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(&(newGameWindow->quitSurface),
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

	newGameWindow->gameControl = GameBoardControlLoad(loadSlotSelected);
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

	newGameWindow->gameControl = GameBoardControlCreate(gameMode, player1Color,
			gameDifficulty);
	if (newGameWindow->gameControl == NULL) {
		GameWindowDestroy(newGameWindow);
		return NULL;
	}
	return newGameWindow;
}

void GameWindowDestroy(GameWindow* src) {
	if (src->backgroundSurface != NULL)
		SDL_FreeSurface(src->backgroundSurface);
	if (src->saveGameSurface != NULL)
		SDL_FreeSurface(src->saveGameSurface);
	if (src->loadGameSurface != NULL)
		SDL_FreeSurface(src->loadGameSurface);
	if (src->undoSurface != NULL)
		SDL_FreeSurface(src->undoSurface);
	if (src->goToMainWindowSurface != NULL)
		SDL_FreeSurface(src->goToMainWindowSurface);
	if (src->restartSurface != NULL)
		SDL_FreeSurface(src->restartSurface);
	if (src->unavailableUndoSurface != NULL)
		SDL_FreeSurface(src->unavailableUndoSurface);
	if (src->quitSurface != NULL)
		SDL_FreeSurface(src->quitSurface);

	if (src->gameControl != NULL)
		GameBoardControlDestroy(src->gameControl);

	if (src->gameWindow != NULL)
		SDL_DestroyWindow(src->gameWindow);
	free(src);
}

// check whether undo is available.
int IsUndoAvailable(GameWindow* src) {
	return ((src->gameControl->gameHistory.lenght != 0)
			&& (src->gameControl->game.gameMode != PlayerVsPlayer));
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

	SDL_Surface *screen = SDL_GetWindowSurface(src->gameWindow);

	SDL_BlitScaled(src->backgroundSurface, NULL, screen, &backgroundR);
	SDL_BlitScaled(src->saveGameSurface, NULL, screen, &saveGameR);
	SDL_BlitScaled(src->loadGameSurface, NULL, screen, &loadGameR);
	if (IsUndoAvailable(src)) {
		SDL_BlitScaled(src->undoSurface, NULL, screen, &undoR);
	} else {
		SDL_BlitScaled(src->unavailableUndoSurface, NULL, screen, &undoR);
	}
	SDL_BlitScaled(src->goToMainWindowSurface, NULL, screen, &goToMainWindowR);
	SDL_BlitScaled(src->restartSurface, NULL, screen, &restartR);
	SDL_BlitScaled(src->quitSurface, NULL, screen, &quitR);
	GameBoardControlDraw(screen, src->gameControl, gameBoardGameWindowRectangle);

	SDL_UpdateWindowSurface(src->gameWindow);
	SDL_FreeSurface(screen);
}

void GameWindowHide(GameWindow* src) {
	SDL_HideWindow(src->gameWindow);
}

void GameWindowShow(GameWindow* src) {
	SDL_ShowWindow(src->gameWindow);
}

// get the current game window event to handle.
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
	if ((event->type == SDL_MOUSEBUTTONUP && event->button.button
			== SDL_BUTTON_LEFT) || eventStruct.eventType
			== BoardPositionButtonGameWindowClickEvent) {
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
			break;
		}
	} else {
		eventStruct.eventType = EmptyEvent;
	}
	return eventStruct;

}
