#ifndef GUIMANAGER_H_
#define GUIMANAGER_H_

#include <SDL.h>
TODO #include "SPTicTacToeGameWin.h"
TODO #include "SPTicTacToeMainWin.h"

typedef enum {
	MainWindowState,
	GameWindowState,
	NewGameWindowState,
	LoadWindowState
} WindowsStateEnum;

typedef struct {
	MainWindow* mainWindow;
	NewGameWindow* newGameWindow;
	LoadWindow* loadWindow;
	GameWindow* gameWindow;
	WindowsStateEnum lastState;
	WindowsStateEnum currentState;
} GuiManager;

GuiManager* GuiManagerCreate();

void GuiManagerDestroy(GuiManager* src);

void GuiManagerDraw(GuiManager* src);

void GuiManagerHideCurrentWindow(GuiManager* src);

void GuiManagerShowCurrentWindow(GuiManager* src);

EventStruct GuiManagerHandleEvent(GuiManager* src, SDL_Event* event);

#endif
