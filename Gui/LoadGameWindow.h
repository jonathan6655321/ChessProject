#ifndef LOADWINDOW_H_
#define LOADWINDOW_H_
#include <SDL.h>
#include "Events.h"
#include "BMPPathConstants.h"
#include "SDLHelperFunctions.h"

//TODO^ edit this! just load untill no file found


///Change windows size whenadd buttons
int backButtonLoadWindowRectangle[4] = { 75,250,400,500 };
int backgroundLoadWindowRectangle[4] = { 0, 			400, 			0,450 };

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
