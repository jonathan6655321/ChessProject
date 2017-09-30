#ifndef GUIMANAGER_H_
#define GUIMANAGER_H_

#include <SDL.h>
#include "Events.h"
#include "GameWindow.h"
#include "MainWindow.h"
#include "LoadGameWindow.h"
#include "NewGameWindow.h"

// gui manager state:
typedef enum {
	MainWindowState,
	GameWindowState,
	NewGameWindowState,
	LoadWindowState
} WindowsStateEnum;

/*!
 * Gui manager structure holding all it's necessery information.
 */
typedef struct {
	MainWindow* mainWindow;
	NewGameWindow* newGameWindow;
	LoadWindow* loadWindow;
	GameWindow* gameWindow;
	// the last state that the gui manager was showing
	WindowsStateEnum lastState;
	// the current stete that the gui manager is showing.
	WindowsStateEnum currentState;
} GuiManager;

/*!
 * @return a new gui manager or null on failure.
 */
GuiManager* GuiManagerCreate();

/*!
 * destroy a gui manager instance.
 */
void GuiManagerDestroy(GuiManager* src);

/*!
 * Draw the current window
 */
void GuiManagerDraw(GuiManager* src);

/*!
 * Hide the current window
 */
void GuiManagerHideCurrentWindow(GuiManager* src);

/*!
 * Show the current window.
 */
void GuiManagerShowCurrentWindow(GuiManager* src);

/*!
 * Handle sdl event.
 * @return empty event or exit event of exit is needed.
 */
EventStruct GuiManagerHandleEvent(GuiManager* src, SDL_Event* event);

#endif
