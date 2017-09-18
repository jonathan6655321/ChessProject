#include "MainWindow.h"

MainWindowElement ClickWasOnMainWindow(int x, int y) {
	if (PointInsideRentangle(x, y, newGameMainWindowRentangle))
		return NewGameMainWindowButtonElement;
	else if (PointInsideRentangle(x, y, loadGameMainWindowRentangle))
		return LoadGameMainWindowButtonElement;
	else if (PointInsideRentangle(x, y, quitGameMainWindowRentangle))
		return QuitMainWindowButtonElement;
	else
		return BackgroundMainWindowElement;
}

void CreateMainWindow(MainWindow* src) {
	// Create an application window with the following settings:
	src->mainWindow = SDL_CreateWindow("Chess Game", // window title
		SDL_WINDOWPOS_CENTERED,			// initial x position
		SDL_WINDOWPOS_CENTERED,			// initial y position
		backgroundMainWindowMaxX,		// width, in pixels
		backgroundMainWindowMaxY,		// height, in pixels
		SDL_WINDOW_OPENGL				// TODO: what is this
	);
}

MainWindow* MainWindowCreate() {
	MainWindow* newMainWindow = (MainWindow*)calloc(sizeof(MainWindow), sizeof(char));

	if (newMainWindow == NULL) {
		printf("malloc: Error\n");
		return NULL;
	}

	createMainWindow(newMainWindow);
	// Check that the window was successfully created
	if (newMainWindow->mainWindow == NULL) {
		spMainWindowDestroy(newMainWindow);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL;
	}

	newMainWindow->mainRenderer = SDL_CreateRenderer(newMainWindow->mainWindow, -1, SDL_RENDERER_ACCELERATED);
	// Check that the window renerer was created
	if (newMainWindow->mainRenderer == NULL) {
		MainWindowDestroy(newMainWindow);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL;
	}

	int success = 1;
	success &= LoadTexture(&(newMainWindow->newGameTexture), newMainWindow->mainRenderer, NEW_GAME_BUTTON_MAIN_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newMainWindow->loadGameTexture), newMainWindow->mainRenderer, LOAD_GAME_BUTTON_MAIN_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newMainWindow->quitTexture), newMainWindow->mainRenderer, QUIT_GAME_BUTTON_MAIN_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newMainWindow->backgroundTexture), newMainWindow->mainRenderer, BACKGROUND_MAIN_WINDOW_TEXTURE_PATH);

	if (!success) {
		MainWindowDestroy(newMainWindow);
		return NULL;
	}

	return newMainWindow;
}

void MainWindowDestroy(MainWindow* src) {
	if (src->backgroundTexture != NULL)
		SDL_DestroyTexture(src->backgroundTexture);
	if (src->newGameTexture != NULL)
		SDL_DestroyTexture(src->newGameTexture);
	if (src->loadGameTexture != NULL)
		SDL_DestroyTexture(src->loadGameTexture);
	if (src->quitTexture != NULL)
		SDL_DestroyTexture(src->quitTexture);
	if (src->mainRenderer != NULL)
		SDL_DestroyRenderer(src->mainRenderer);
	if (src->mainWindow != NULL)
		SDL_DestroyWindow(src->mainWindow);
	free(src);
}

void MainWindowDraw(MainWindow* src) {
	SDL_Rect newGameR = CreateSDLRectFromIntArray(newGameRentangle);
	SDL_Rect loadGameR = CreateSDLRectFromIntArray(loadGameRentangle);
	SDL_Rect quitGameR = CreateSDLRectFromIntArray(quitGameRentangle);
	SDL_Rect backgroundR = CreateSDLRectFromIntArray(backgroundRentangle);
	SDL_SetRenderDrawColor(src->mainRenderer, 255, 255, 255, 255);

	SDL_RenderClear(src->mainRenderer);
	SDL_RenderCopy(src->mainRenderer, src->backgroundTexture, NULL, &backgroundR);
	SDL_RenderCopy(src->mainRenderer, src->newGameTexture, NULL, &newGameR);
	SDL_RenderCopy(src->mainRenderer, src->loadGameTexture, NULL, &loadGameR);
	SDL_RenderCopy(src->mainRenderer, src->quitTexture, NULL, &quitTextureR);
	SDL_RenderPresent(src->mainRenderer);
}

void MainWindowHide(MainWindow* src) {
	SDL_HideWindow(src->mainWindow);
}

void MainWindowShow(MainWindow* src) {
	SDL_ShowWindow(src->mainWindow);
}

EventType GetMainWindowEvent(SDL_Event* event) {
	switch (ClickWasOnMainWindow(event->button.x, event->button.y)) {
	case NewGameMainWindowButtonElement:
		return NewGameButtonMainWindowClickEvent;
	case LoadGameMainWindowButtonElement:
		return LoadGameButtonMainWindowClickEvent;
	case QuitMainWindowButtonElement:
		return QuitButtonMainWindowClickEvent;
	default:
		return EmptyEvent;
	}
}

EventStruct MainWindowHandleEvent(MainWindow* src, SDL_Event* event) {
	EventStruct eventStruct = { EmptyEvent,0 };
	if (event == NULL) {
		return eventStruct;
	}

	eventStruct.eventType = GetMainWindowEvent(event);
	return eventStruct;
}
