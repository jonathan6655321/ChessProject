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
    //the renderer
    SDL_Renderer *newGameRenderer;

    //the new game windows state:
    NewGameWindowStateType state;

    //the new game setting:
    char difficulty;
    char gameMode;
    char userColor;

    // textures:
    SDL_Texture *backgroundTextureChoosingGameMode;
    SDL_Texture *backgroundTextureChoosingDifficulty;
    SDL_Texture *backgroundTextureChoosingUserColor;
    SDL_Texture *startNewGameButtonTexture;
    SDL_Texture *nextButtonTexture;
    SDL_Texture *whiteButtonTexture;
    SDL_Texture *whiteButtonPressedTexture;
    SDL_Texture *blackButtonTexture;
    SDL_Texture *blackButtonPressedTexture;
    SDL_Texture *onePlayerButtonTexture;
    SDL_Texture *onePlayerButtonPressedTexture;
    SDL_Texture *twoPlayerButtonTexture;
    SDL_Texture *twoPlayerButtonPressedTexture;
    SDL_Texture *noobDifficultyButtonTexture;
    SDL_Texture *noobDifficultyButtonPressedTexture;
    SDL_Texture *easyDifficultyButtonTexture;
    SDL_Texture *easyDifficultyButtonPressedTexture;
    SDL_Texture *moderateDifficultyButtonTexture;
    SDL_Texture *moderateDifficultyButtonPressedTexture;
    SDL_Texture *hardDifficultyButtonTexture;
    SDL_Texture *hardDifficultyButtonPressedTexture;
    SDL_Texture *expertDifficultyButtonTexture;
    SDL_Texture *expertDifficultyButtonPressedTexture;
    SDL_Texture *backButtonTexture;
    SDL_Texture *backButtonPressedTexture;
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
