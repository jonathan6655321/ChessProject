#ifndef CHESSGAMEWINDOW_H
#define CHESSGAMEWINDOW_H

#include <SDL.h>
#include "Events.h"
#include "GameBoardControl.h"
#include "Constants.h"
#include "SDLHelperFunctions.h"

/*!
 * the elements on the game window
 */
typedef enum {
    GameBoardGameWindowElement,
    RestartGameButtonGameWindowElement,
    SaveGameButtonGameWindowElement,
    LoadGameButtonGameWindowElement,
    UndoButtonGameWindowElement,
    GoToMainWindowButtonGameWindowElement,
    QuitButtonGameWindowElement,
    BackgroundGameWindowElement
} GameWindowElement;

/*!
 * structure representing a game window.
 */
typedef struct {
    // the game window
    SDL_Window *gameWindow;
    // the game control
    GameBoardControl *gameControl;

    // buttons Surfaces:
    SDL_Surface *saveGameSurface;
    SDL_Surface *backgroundSurface;
    SDL_Surface *loadGameSurface;
    SDL_Surface *undoSurface;
    SDL_Surface *unavailableUndoSurface;
    SDL_Surface *goToMainWindowSurface;
    SDL_Surface *restartSurface;
    SDL_Surface *quitSurface;
} GameWindow;

/*!
 * create new game windows with the specified settings.
 * @return the new game window. or null on failure.
 */
GameWindow *GameWindowCreate(char gameMode, char player1Color,
                             char gameDifficulty);

/*!
 * creates new game windows from the specified game slot.
 * @return return the game windows that was created from the game slot, or null on failure.
 */
GameWindow *GameWindowLoad(char loadSlotSelected);

/*!
 * draw the game windows
 */
void GameWindowDraw(GameWindow *src);

/*!
 * destroy the game windows
 */
void GameWindowDestroy(GameWindow *src);

/*!
 * Hide the game windows.
 */
void GameWindowHide(GameWindow *src);

/*!
 * Show the game windows.
 */
void GameWindowShow(GameWindow *src);

/*!
 * Handle a sdl event
 * @return an event for the gui manager to handle, or empty event.
 */
EventStruct GameWindowHandleEvent(GameWindow *src, SDL_Event *event);


#endif
