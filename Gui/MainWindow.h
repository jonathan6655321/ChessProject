#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_
#include <SDL.h>
#include "Events.h"
#include "SDLHelperFunctions.h"
#include "BMPPathConstants.h"


int newGameMainWindowRectangle[4] = { 75, 250, 100, 200 };
int loadGameMainWindowRectangle[4] = { 75, 250, 250, 350 };
int quitGameMainWindowRectangle[4] = { 75, 250, 400, 500 };
int backgroundMainWindowRectangle[4] = { 0, 400, 0, 450 };

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
