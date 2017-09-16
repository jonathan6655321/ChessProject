#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_
#include <SDL.h>
#include "Events.h"
#include "SDLHelperFunctions.h"

const int newGameButtonMainWindowMinX = 	75, newGameButtonMainWindowMaxX = 	250, newGameButtonMainWindowMinY = 	100, newGameButtonMainWindowMaxY = 	200;
const int loadGameButtonMainWindowMinX =	75, loadGameButtonMainWindowMaxX = 	250, loadGameButtonMainWindowMinY = 	250, loadGameButtonMainWindowMaxY = 	350;
const int quitButtonMainWindowMinX = 				75, quitButtonMainWindowMaxX = 			250, quitButtonMainWindowMinY = 			400, quitButtonMainWindowMaxY = 				500;
const int backgroundMainWindowMinX = 			0  , backgroundMainWindowMaxX = 			400, backgroundMainWindowMinY = 			0    , backgroundMainWindowMaxY = 			450;

const int[] newGameMainWindowRentangle = 		{newGameButtonMainWindowMinX, 	newGameButtonMainWindowMaxX, 	newGameButtonMainWindowMinY, 	newGameButtonMainWindowMaxY};
const int[] loadGameMainWindowRentangle = 		{loadGameButtonMainWindowMinX, 	loadGameButtonMainWindowMaxX, 	loadGameButtonMainWindowMinY, 	loadGameButtonMainWindowMaxY};
const int[] quitGameMainWindowRentangle = 		{quitButtonMainWindowMinX, 			quitButtonMainWindowMaxX, 			quitButtonMainWindowMinY, 				quitButtonMainWindowMaxY};
const int[] backgroundMainWindowRentangle = 	{backgroundMainWindowMinX, 			backgroundMainWindowMaxX, 			backgroundMainWindowMinY, 			backgroundMainWindowMaxY};

typedef enum{
	NewGameMainWindowButtonElement,
	LoadGameMainWindowButtonElement,
	QuitMainWindowButtonElement,
	BackgroundMainWindowElement
} MainWindowElement;

typedef struct {
	SDL_Window* 	mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Texture* 	backgroundTexture;
	SDL_Texture* 	newGameTexture;
	SDL_Texture* 	loadGameTexture;
	SDL_Texture* 	quitTexture;
} MainWindow;

MainWindow* MainWindowCreate();

void MainWindowDraw		(MainWindow* src);
void MainWindowDestroy	(MainWindow* src);
void MainWindowHide		(MainWindow* src);
void MainWindowShow		(MainWindow* src);

EventStruct MainWindowHandleEvent						(MainWindow* src, SDL_Event* event) ;

#endif
