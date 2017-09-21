#ifndef LOADWINDOW_H_
#define LOADWINDOW_H_
#include <SDL.h>
#include "Events.h"
#include "SDLHelperFunctions.h"

//TODO^ edit this! just load untill no file found


///Change windows size whenadd buttons
const int backButtonLoadWindowMinX = 75, backButtonLoadWindowMaxX = 250, backButtonLoadWindowMinY = 400, backButtonLoadWindowMaxY = 500;
const int backgroundLoadWindowMinX = 0, backgroundLoadWindowMaxX = 400, backgroundLoadWindowMinY = 0, backgroundLoadWindowMaxY = 450;

const int[] backButtonLoadWindowRentangle = { backButtonLoadWindowMinX, 			backButtonLoadWindowMaxX, 			backButtonLoadWindowMinY, 			backButtonLoadWindowMaxY };
const int[] backgroundLoadWindowRentangle = { backgroundLoadWindowMinX, 			backgroundLoadWindowMaxX, 			backgroundLoadWindowMinY, 			backgroundLoadWindowMaxY };

typedef enum {
	LoadGameButtonLoadWindowElement,
	BackButtonButtonLoadWindowElement,
	BackgroundLoadWindowElement
} LoadWindowElement;

typedef struct {
	SDL_Window* 	loadWindow;
	SDL_Renderer* loadRenderer;
	SDL_Texture* 	backgroundTexture;

	int numberOfOptions;

	SDL_Texture* 	backButtonTexture;
	SDL_Texture* 	loadGameTexture;
} LoadWindow;

LoadWindow* LoadWindowCreate();

void LoadWindowDraw(LoadWindow* src);
void LoadWindowDestroy(LoadWindow* src);
void LoadWindowHide(LoadWindow* src);
void LoadWindowShow(LoadWindow* src);

EventStruct LoadWindowHandleBackToEvent(LoadWindow* src);
EventStruct LoadWindowHandleLoadGameEvent(LoadWindow* src);
EventStruct LoadWindowHandleEvent(LoadWindow* src, SDL_Event* event);

#endif
