#ifndef LOADWINDOW_H_
#define LOADWINDOW_H_

#include <SDL.h>
#include <stdio.h>
#include "Events.h"
#include "Constants.h"
#include "SDLHelperFunctions.h"

/*!
 * the load window elements.
 */
typedef enum {
    LoadLoadGameButtonLoadWindowElement,
    LoadGameButtonLoadWindowElement,
    BackButtonLoadWindowElement,
    BackgroundLoadWindowElement
} LoadWindowElement;

/*!
 * a struct representing an element on the window
 */
typedef struct {
    LoadWindowElement element;
    // is used when pointing to a game slot, specifing the slot number.
    int argument;
} LoadWindowElementStruct;

/*!
 *  structure representing a Load windows and all it's necessery variables.
 */
typedef struct {
    // the window
    SDL_Window *loadWindow;

    // slots:
    int numberOfOptions;
    int selectedOption;

    // Windows Surfaces:
    SDL_Surface *loadButtonSurface[NUMBER_OF_SAVE_LOAD_SLOT][2];
    SDL_Surface *backgroundSurface;
    SDL_Surface *backButtonSurface;
    SDL_Surface *loadloadButtonSurface;
    SDL_Surface *loadloadUnavailableButtonSurface;
} LoadWindow;

/*!
 * @return a new default load windows, or null on failure
 */
LoadWindow *LoadWindowCreate();

/*!
 *  Draw load windows
 */
void LoadWindowDraw(LoadWindow *src);

/*!
 * Destroy load windows.
 */
void LoadWindowDestroy(LoadWindow *src);

/*!
 * Hide load windows
 */
void LoadWindowHide(LoadWindow *src);

/*!
 * show load windows
 */
void LoadWindowShow(LoadWindow *src);

/*!
 * handles Load window events.
 * @return  empty event or event for the gui manager to handle (load, back).
 */
EventStruct LoadWindowHandleEvent(LoadWindow *src, SDL_Event *event);

#endif
