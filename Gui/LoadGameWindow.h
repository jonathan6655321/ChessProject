#ifndef LOADWINDOW_H_
#define LOADWINDOW_H_
#include <SDL.h>
#include "Events.h"
#include "PathsConstants.h"
#include "SDLHelperFunctions.h"

typedef enum {
	LoadGameButtonLoadWindowElement,
	BackButtonButtonLoadWindowElement,
	BackgroundLoadWindowElement
} LoadWindowElement;

typedef struct {
	SDL_Window* loadWindow;
	SDL_Renderer* loadRenderer;
	SDL_Texture* backgroundTexture;

	int numberOfOptions;

	SDL_Texture* backButtonTexture;
	SDL_Texture* loadGameTexture;
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
