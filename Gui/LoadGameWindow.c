#include "LoadGameWindow.h"

//the windows elements specification.
static int backButtonLoadWindowRectangle[4] = { 0, 100, 0, 50 };
static int loadloadButtonLoadWindowRectangle[4] = { 300, 400, 0, 50 };
static int loadButtonLoadWindowRectangleTemplate[4] = { 100, 300, 75, 135 };
static int backgroundLoadWindowRectangle[4] = { 0, 400, 0, 150 };

// check on which element the a x,y point is on.
LoadWindowElementStruct ClickWasOnLoadWindow(LoadWindow *src, int x, int y) {
	int i;
	LoadWindowElementStruct emptyStruct = { BackgroundLoadWindowElement, 0 };
	if (PointInsideRectangle(x, y, backButtonLoadWindowRectangle)) {
		emptyStruct.element = BackButtonLoadWindowElement;
	} else if (PointInsideRectangle(x, y, loadloadButtonLoadWindowRectangle)) {
		emptyStruct.element = LoadLoadGameButtonLoadWindowElement;
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
				emptyStruct.argument = i;
			}
		}
	}
	return emptyStruct;
}

// check whether a file exists.
int exists(const char *fname) {
	FILE *file;
	if ((file = fopen(fname, "r"))) {
		fclose(file);
		return 1;
	}
	return 0;
}

// return the number of available load files
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

// creates new load window's window.
void CreateNewLoadWindow(LoadWindow *src) {
	// Create an application window with the following settings:
	src->loadWindow = SDL_CreateWindow("Load Existing Game", // window title
			SDL_WINDOWPOS_CENTERED, // initial x position
			SDL_WINDOWPOS_CENTERED, // initial y position
			backgroundLoadWindowRectangle[1], // width, in pixels
			backgroundLoadWindowRectangle[3] * src->numberOfOptions, // height, in pixels
			SDL_WINDOW_OPENGL);
}

LoadWindow *LoadWindowCreate() {
	LoadWindow *newLoadWindow = (LoadWindow *) calloc(sizeof(LoadWindow),
			sizeof(char));
	if (newLoadWindow == NULL) {
		printf("malloc: Error\n");
		return NULL;
	}

	newLoadWindow->numberOfOptions = GetNumberOfSaveFiles();
	newLoadWindow->selectedOption = -1;

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

	int i, success = 1;
	char str[BUFSIZ];
	for (i = 1; i <= newLoadWindow->numberOfOptions; i++) {
		sprintf(str, LOAD_SLOT_BUTTON_LOAD_WINDOW_TEXTURE_PATH_FORMAT, i);
		success &= LoadSurface(&(newLoadWindow->loadButtonSurface[i - 1][0]),
				str);
		sprintf(str, LOAD_SLOT_BUTTON_SELECTED_LOAD_WINDOW_TEXTURE_PATH_FORMAT,
				i);
		success &= LoadSurface(&(newLoadWindow->loadButtonSurface[i - 1][1]),
				str);
	}
	success &= LoadSurface(&(newLoadWindow->backButtonSurface),
			BACK_BUTTON_LOAD_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(&(newLoadWindow->loadloadButtonSurface),
			LOAD_BUTTON_LOAD_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(&(newLoadWindow->loadloadUnavailableButtonSurface),
			LOAD_UNAVAILABLE_BUTTON_LOAD_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(&(newLoadWindow->backgroundSurface),
			BACKGROUND_LOAD_WINDOW_TEXTURE_PATH);

	if (!success) {
		LoadWindowDestroy(newLoadWindow);
		return NULL;
	}

	return newLoadWindow;
}

void LoadWindowDraw(LoadWindow *src) {
	SDL_Rect backR = CreateSDLRectFromIntArray(backButtonLoadWindowRectangle);
	SDL_Rect loadloadR = CreateSDLRectFromIntArray(
			loadloadButtonLoadWindowRectangle);
	SDL_Rect loadR[NUMBER_OF_SAVE_LOAD_SLOT];
	int i, j, loadTemplate[4];
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

	SDL_Surface *screen = SDL_GetWindowSurface(src->loadWindow);

	SDL_BlitScaled(src->backgroundSurface, NULL, screen, &backgroundR);
	for (i = 0; i < src->numberOfOptions; i++) {
		j = (src->selectedOption == i) ? 1 : 0;
		SDL_BlitScaled(src->loadButtonSurface[i][j], NULL, screen, &(loadR[i]));

	}
	if (src->selectedOption == -1) {
		SDL_BlitScaled(src->loadloadUnavailableButtonSurface, NULL, screen,
				&loadloadR);
	} else {
		SDL_BlitScaled(src->loadloadButtonSurface, NULL, screen, &loadloadR);
	}
	SDL_BlitScaled(src->backButtonSurface, NULL, screen, &backR);
	SDL_UpdateWindowSurface(src->loadWindow);
	SDL_FreeSurface(screen);
}

void LoadWindowDestroy(LoadWindow *src) {
	int i, j;
	if (src->backgroundSurface != NULL)
		SDL_FreeSurface(src->backgroundSurface);
	if (src->backButtonSurface != NULL)
		SDL_FreeSurface(src->backButtonSurface);
	if (src->loadloadButtonSurface != NULL)
		SDL_FreeSurface(src->loadloadButtonSurface);
	if (src->loadloadUnavailableButtonSurface != NULL)
		SDL_FreeSurface(src->loadloadUnavailableButtonSurface);
	for (i = 0; i < src->numberOfOptions; i++) {
		for (j = 0; j < 2; j++) {
			if (src->loadButtonSurface[i][j] != NULL)
				SDL_FreeSurface(src->loadButtonSurface[i][j]);
		}
	}
	if (src->loadWindow != NULL)
		SDL_DestroyWindow(src->loadWindow);
	free(src);
}

void LoadWindowHide(LoadWindow *src) {
	SDL_HideWindow(src->loadWindow);
}

void LoadWindowShow(LoadWindow *src) {
	SDL_ShowWindow(src->loadWindow);
}

EventStruct LoadWindowHandleEvent(LoadWindow *src, SDL_Event *event) {
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
		src->selectedOption = windowsEventStruct.argument;
		break;
	case LoadLoadGameButtonLoadWindowElement:
		if (src->selectedOption != -1) {
			eventStruct.eventType = GameLoadOptionLoadWindowClickEvent;
			eventStruct.eventArgument[0] = src->selectedOption + 1;
		}
		break;
	default:
		break;
	}
	return eventStruct;
}
