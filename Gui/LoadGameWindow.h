#ifndef LOADWINDOW_H_
#define LOADWINDOW_H_
#include <SDL.h>
#include <stdio.h>
#include "Events.h"
#include "Constants.h"
#include "SDLHelperFunctions.h"

typedef enum {
	LoadGameButtonLoadWindowElement,
	BackButtonLoadWindowElement,
	BackgroundLoadWindowElement
} LoadWindowElement;

typedef struct {
	LoadWindowElement element;
	int argument;
} LoadWindowElementStruct;

typedef struct {
	SDL_Window* loadWindow;
	SDL_Renderer* loadRenderer;
	SDL_Texture* backgroundTexture;

	int numberOfOptions;
	int selectedOption;

	SDL_Texture* loadButtonTexture[NUMBER_OF_SAVE_LOAD_SLOT][2];
	SDL_Texture* backButtonTexture;
	SDL_Texture* loadloadButtonTexture;
	SDL_Texture* loadloadUnavailableButtonTexture;
} LoadWindow;

LoadWindow* LoadWindowCreate();

void LoadWindowDraw(LoadWindow* src);
void LoadWindowDestroy(LoadWindow* src);
void LoadWindowHide(LoadWindow* src);
void LoadWindowShow(LoadWindow* src);

EventStruct LoadWindowHandleEvent(LoadWindow* src, SDL_Event* event);

#endif
