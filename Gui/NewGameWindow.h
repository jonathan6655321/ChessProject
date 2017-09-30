#ifndef NewGameWindow_H_
#define NewGameWindow_H_

#include <SDL.h>
#include "Events.h"
#include "Constants.h"
#include "SDLHelperFunctions.h"

/*!
 * elements of the new game windows.
 */
typedef enum {
    NextStartNewGameNewGameWindowButtonElement,
    WhiteUserColorNewGameWindowButtonElement,
    BlackUserColorModeNewGameWindowButtonElement,
    OnePlayerGameModeNewGameWindowButtonElement,
    TwoPlayerGameModeNewGameWindowButtonElement,
    NoobDifficultyModeNewGameWindowButtonElement,
    EasyDifficultyModeNewGameWindowButtonElement,
    ModerateDifficultyModeNewGameWindowButtonElement,
    HardDifficultyModeNewGameWindowButtonElement,
    ExpertDifficultyModeNewGameWindowButtonElement,
    BackButtonNewGameWindowElement,
    BackgroundNewGameWindowElement
} NewGameWindowElement;

/*!
 * State types of the new game windows.
 */
typedef enum {
    GameModeNewGameWindowState,
    DifficultyNewGameWindowState,
    PlayerColorNewGameWindowState,
} NewGameWindowStateType;

/*!
 * struct representing the new game windows.
 */
typedef struct {
    // the window
    SDL_Window *newGameWindow;

    //the new game windows state:
    NewGameWindowStateType state;

    //the new game setting:
    char difficulty;
    char gameMode;
    char userColor;

    // Surfaces:
    SDL_Surface *backgroundSurfaceChoosingGameMode;
    SDL_Surface *backgroundSurfaceChoosingDifficulty;
    SDL_Surface *backgroundSurfaceChoosingUserColor;
    SDL_Surface *startNewGameButtonSurface;
    SDL_Surface *nextButtonSurface;
    SDL_Surface *whiteButtonSurface;
    SDL_Surface *whiteButtonPressedSurface;
    SDL_Surface *blackButtonSurface;
    SDL_Surface *blackButtonPressedSurface;
    SDL_Surface *onePlayerButtonSurface;
    SDL_Surface *onePlayerButtonPressedSurface;
    SDL_Surface *twoPlayerButtonSurface;
    SDL_Surface *twoPlayerButtonPressedSurface;
    SDL_Surface *noobDifficultyButtonSurface;
    SDL_Surface *noobDifficultyButtonPressedSurface;
    SDL_Surface *easyDifficultyButtonSurface;
    SDL_Surface *easyDifficultyButtonPressedSurface;
    SDL_Surface *moderateDifficultyButtonSurface;
    SDL_Surface *moderateDifficultyButtonPressedSurface;
    SDL_Surface *hardDifficultyButtonSurface;
    SDL_Surface *hardDifficultyButtonPressedSurface;
    SDL_Surface *expertDifficultyButtonSurface;
    SDL_Surface *expertDifficultyButtonPressedSurface;
    SDL_Surface *backButtonSurface;
    SDL_Surface *backButtonPressedSurface;
} NewGameWindow;

/*!
 * @return a new created new game windows, or null on failure.
 */
NewGameWindow *NewGameWindowCreate();

/*!
 * draw the new game window
 */
void NewGameWindowDraw(NewGameWindow *src);

/*!
 * destroy the new game window
 */
void NewGameWindowDestroy(NewGameWindow *src);

/*!
 * hide the new game window
 */
void NewGameWindowHide(NewGameWindow *src);

/*!
 * show the new game window
 */
void NewGameWindowShow(NewGameWindow *src);

/*!
 * handle new game window event
 * @return  empty event, or event that are handled by the gui manager.
 */
EventStruct NewGameWindowHandleEvent(NewGameWindow *src, SDL_Event *event);

#endif
