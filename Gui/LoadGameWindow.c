#include "LoadGameWindow.h"

static int backButtonLoadWindowRectangle[4] = { 0, 100, 0, 50 };
static int loadloadButtonLoadWindowRectangle[4] = { 300, 400, 0, 50 };
static int loadButtonLoadWindowRectangleTemplate[4] = { 150, 350, 75, 135 };
static int backgroundLoadWindowRectangle[4] = { 0, 400, 0, 150 };

LoadWindowElementStruct ClickWasOnLoadWindow(LoadWindow* src, int x, int y) {
	int i;
	LoadWindowElementStruct emptyStruct = { BackgroundLoadWindowElement, 0 };
	if (PointInsideRectangle(x, y, backButtonLoadWindowRectangle)) {
		emptyStruct.element = BackButtonLoadWindowElement;
	} else {
		int loadTemplate[4];
		loadTemplate[0] = loadButtonLoadWindowRectangleTemplate[0];
		loadTemplate[1] = loadButtonLoadWindowRectangleTemplate[1];
		for (i = 0; i < src->numberOfOptions; i++) {
			loadTemplate[2] = i * backgroundLoadWindowRectangle[3]
					+ loadButtonLoadWindowRectangleTemplate[2];
			loadTemplate[3] = i * backgroundLoadWindowRectangle[3]
					+ loadButtonLoadWindowRectangleTemplate[3];
			if (PointInsideRectangle(x, y, loadTemplate)) {
				emptyStruct.element = LoadGameButtonLoadWindowElement;
				emptyStruct.argument = i + 1;
			}
		}
	}
	return emptyStruct;
}

int exists(const char *fname) {
	FILE *file;
	if ((file = fopen(fname, "r"))) {
		fclose(file);
		return 1;
	}
	return 0;
}

int GetNumberOfSaveFiles() {
	char str[BUFSIZ];
	int i;
	for (i = 1; i <= NUMBER_OF_SAVE_LOAD_SLOT; i++) {
		sprintf(str, SAVE_LOAD_PATH_FORMAT, i);
		if (!exists(str)) {
			break;
		}
	}
	i--;
	return i;
}

void CreateNewLoadWindow(LoadWindow* src) {
	// Create an application window with the following settings:
	src->loadWindow = SDL_CreateWindow("Load Existing Game", // window title
			SDL_WINDOWPOS_CENTERED, // initial x position
			SDL_WINDOWPOS_CENTERED, // initial y position
			backgroundLoadWindowRectangle[1], // width, in pixels
			backgroundLoadWindowRectangle[3] * src->numberOfOptions, // height, in pixels
			SDL_WINDOW_OPENGL);
}

LoadWindow* LoadWindowCreate() {
	LoadWindow* newLoadWindow = (LoadWindow*) calloc(sizeof(LoadWindow),
			sizeof(char));
	if (newLoadWindow == NULL) {
		printf("malloc: Error\n");
		return NULL;
	}

	newLoadWindow->numberOfOptions = GetNumberOfSaveFiles();

	if (newLoadWindow->numberOfOptions == 0) {
		newLoadWindow->numberOfOptions = 1;
		CreateNewLoadWindow(newLoadWindow);
		newLoadWindow->numberOfOptions = 0;
	} else {
		CreateNewLoadWindow(newLoadWindow);
	}

	// Check that the window was successfully created
	if (newLoadWindow->loadWindow == NULL) {
		LoadWindowDestroy(newLoadWindow);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL;
	}

	newLoadWindow->loadRenderer = SDL_CreateRenderer(newLoadWindow->loadWindow,
			-1, SDL_RENDERER_ACCELERATED);
	// Check that the window renerer was created
	if (newLoadWindow->loadRenderer == NULL) {
		LoadWindowDestroy(newLoadWindow);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL;
	}

	int i, success = 1;
	char str[BUFSIZ];
	for (i = 1; i <= newLoadWindow->numberOfOptions; i++) {
		sprintf(str, LOAD_SLOT_BUTTON_LOAD_WINDOW_TEXTURE_PATH_FORMAT, i);
		success &= LoadTexture(&(newLoadWindow->loadButtonTexture[i - 1]),
				newLoadWindow->loadRenderer, str);
	}
	success &= LoadTexture(&(newLoadWindow->backButtonTexture),
			newLoadWindow->loadRenderer, BACK_BUTTON_LOAD_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newLoadWindow->backgroundTexture),
			newLoadWindow->loadRenderer, BACKGROUND_LOAD_WINDOW_TEXTURE_PATH);

	if (!success) {
		LoadWindowDestroy(newLoadWindow);
		return NULL;
	}

	return newLoadWindow;
}

void LoadWindowDraw(LoadWindow* src) {
	SDL_Rect backR = CreateSDLRectFromIntArray(backButtonLoadWindowRectangle);
	SDL_Rect loadR[NUMBER_OF_SAVE_LOAD_SLOT];
	int i, loadTemplate[4];
	loadTemplate[0] = loadButtonLoadWindowRectangleTemplate[0];
	loadTemplate[1] = loadButtonLoadWindowRectangleTemplate[1];
	for (i = 0; i < src->numberOfOptions; i++) {
		loadTemplate[2] = i * backgroundLoadWindowRectangle[3]
				+ loadButtonLoadWindowRectangleTemplate[2];
		loadTemplate[3] = i * backgroundLoadWindowRectangle[3]
				+ loadButtonLoadWindowRectangleTemplate[3];
		loadR[i] = CreateSDLRectFromIntArray(loadTemplate);
	}
	int backgroundRenct[4];
	for (i = 0; i < 3; i++) {
		backgroundRenct[i] = backgroundLoadWindowRectangle[i];
	}
	backgroundRenct[3] = ((src->numberOfOptions == 0) ? 1
			: src->numberOfOptions) * backgroundLoadWindowRectangle[3];

	SDL_Rect backgroundR = CreateSDLRectFromIntArray(backgroundRenct);
	SDL_SetRenderDrawColor(src->loadRenderer, 255, 255, 255, 255);

	SDL_RenderClear(src->loadRenderer);
	SDL_RenderCopy(src->loadRenderer, src->backgroundTexture, NULL,
			&backgroundR);
	for (i = 0; i < src->numberOfOptions; i++) {
		SDL_RenderCopy(src->loadRenderer, src->loadButtonTexture[i], NULL,
				&(loadR[i]));
	}
	SDL_RenderCopy(src->loadRenderer, src->backButtonTexture, NULL, &backR);
	SDL_RenderPresent(src->loadRenderer);
}
void LoadWindowDestroy(LoadWindow* src) {
	int i;
	if (src->backgroundTexture != NULL)
		SDL_DestroyTexture(src->backgroundTexture);
	if (src->backButtonTexture != NULL)
		SDL_DestroyTexture(src->backButtonTexture);
	for (i = 0; i < src->numberOfOptions; i++) {
		if (src->loadButtonTexture[i] != NULL)
			SDL_DestroyTexture(src->loadButtonTexture[i]);
	}
	if (src->loadRenderer != NULL)
		SDL_DestroyRenderer(src->loadRenderer);
	if (src->loadWindow != NULL)
		SDL_DestroyWindow(src->loadWindow);
	free(src);
}
void LoadWindowHide(LoadWindow* src) {
	SDL_HideWindow(src->loadWindow);
}
void LoadWindowShow(LoadWindow* src) {
	SDL_ShowWindow(src->loadWindow);
}

EventStruct LoadWindowHandleEvent(LoadWindow* src, SDL_Event* event) {
	EventStruct eventStruct = { EmptyEvent, { 0 } };
	if (event == NULL) {
		return eventStruct;
	}

	LoadWindowElementStruct windowsEventStruct = ClickWasOnLoadWindow(src,
			event->button.x, event->button.y);
	switch (windowsEventStruct.element) {
	case BackButtonLoadWindowElement:
		eventStruct.eventType = BackButtonLoadWindowClickEvent;
		break;
	case LoadGameButtonLoadWindowElement:
		eventStruct.eventType = GameLoadOptionLoadWindowClickEvent;
		eventStruct.eventArgument[0] = windowsEventStruct.argument;
	default:
		break;
	}
	return eventStruct;
}
