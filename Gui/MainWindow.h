#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_
#include <SDL.h>
#include "Events.h"
#include "SDLHelperFunctions.h"
#include "PathsConstants.h"


typedef enum {
	NewGameMainWindowButtonElement,
	LoadGameMainWindowButtonElement,
	QuitMainWindowButtonElement,
	BackgroundMainWindowElement
} MainWindowElement;

typedef struct {
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Texture* backgroundTexture;
	SDL_Texture* newGameTexture;
	SDL_Texture* loadGameTexture;
	SDL_Texture* quitTexture;
} MainWindow;

MainWindow* MainWindowCreate();

void MainWindowDraw(MainWindow* src);
void MainWindowDestroy(MainWindow* src);
void MainWindowHide(MainWindow* src);
void MainWindowShow(MainWindow* src);

EventStruct MainWindowHandleEvent(MainWindow* src, SDL_Event* event);

#endif
