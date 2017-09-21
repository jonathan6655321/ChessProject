#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_
#include <SDL.h>
#include "Events.h"
#include "SDLHelperFunctions.h"
#include "BMPPathConstants.h"


static int newGameMainWindowRectangle[4] = { 75, 250, 50, 150 };
static int loadGameMainWindowRectangle[4] = { 75, 250, 175, 275 };
static int quitGameMainWindowRectangle[4] = { 75, 250, 300, 400 };
static int backgroundMainWindowRectangle[4] = { 0, 400, 0, 450 };

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
