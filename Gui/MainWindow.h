#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <SDL.h>
#include "Events.h"
#include "SDLHelperFunctions.h"
#include "Constants.h"

/*!
 * Main window elements
 */
typedef enum {
    NewGameMainWindowButtonElement,
    LoadGameMainWindowButtonElement,
    QuitMainWindowButtonElement,
    BackgroundMainWindowElement
} MainWindowElement;

/*!
 * Represent a main window
 */
typedef struct {
    SDL_Window *mainWindow;
    SDL_Renderer *mainRenderer;
    SDL_Texture *backgroundTexture;
    SDL_Texture *newGameTexture;
    SDL_Texture *loadGameTexture;
    SDL_Texture *quitTexture;
} MainWindow;

/*!
 * @return a new main window, or null on failure.
 */
MainWindow *MainWindowCreate();

/*!
 *  draw the main window
 */
void MainWindowDraw(MainWindow *src);

/*!
 * destroy the main window
 */
void MainWindowDestroy(MainWindow *src);

/*!
 * hide the main window
 */
void MainWindowHide(MainWindow *src);

/*!
 * show the main window
 */
void MainWindowShow(MainWindow *src);

/*!
 * handles main window events
 * @return return empty event or events that the gui manager needs to hanle.
 */
EventStruct MainWindowHandleEvent(MainWindow *src, SDL_Event *event);

#endif
