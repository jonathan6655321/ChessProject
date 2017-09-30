#ifndef NewGameWindow_H_
#define NewGameWindow_H_
#include <SDL.h>
#include "Events.h"
#include "Constants.h"
#include "SDLHelperFunctions.h"

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

typedef enum {
	GameModeNewGameWindowState,
	DifficultyNewGameWindowState,
	PlayerColorNewGameWindowState,
} NewGameWindowStateType;

typedef struct {
	SDL_Window* newGameWindow;
	SDL_Renderer* newGameRenderer;
	SDL_Texture* backgroundTextureChoosingGameMode;
	SDL_Texture* backgroundTextureChoosingDifficulty;
	SDL_Texture* backgroundTextureChoosingUserColor;

	char gameMode;
	char difficulty;
	char userColor;

	NewGameWindowStateType state;

	SDL_Texture* startNewGameButtonTexture;
	SDL_Texture* nextButtonTexture;
	SDL_Texture* whiteButtonTexture;
	SDL_Texture* whiteButtonPressedTexture;
	SDL_Texture* blackButtonTexture;
	SDL_Texture* blackButtonPressedTexture;
	SDL_Texture* onePlayerButtonTexture;
	SDL_Texture* onePlayerButtonPressedTexture;
	SDL_Texture* twoPlayerButtonTexture;
	SDL_Texture* twoPlayerButtonPressedTexture;
	SDL_Texture* noobDifficultyButtonTexture;
	SDL_Texture* noobDifficultyButtonPressedTexture;
	SDL_Texture* easyDifficultyButtonTexture;
	SDL_Texture* easyDifficultyButtonPressedTexture;
	SDL_Texture* moderateDifficultyButtonTexture;
	SDL_Texture* moderateDifficultyButtonPressedTexture;
	SDL_Texture* hardDifficultyButtonTexture;
	SDL_Texture* hardDifficultyButtonPressedTexture;
	SDL_Texture* expertDifficultyButtonTexture;
	SDL_Texture* expertDifficultyButtonPressedTexture;
	SDL_Texture* backButtonTexture;
	SDL_Texture* backButtonPressedTexture;
} NewGameWindow;

NewGameWindow* NewGameWindowCreate();

void NewGameWindowDraw(NewGameWindow* src);
void NewGameWindowDestroy(NewGameWindow* src);
void NewGameWindowHide(NewGameWindow* src);
void NewGameWindowShow(NewGameWindow* src);

EventStruct NewGameWindowHandleEvent(NewGameWindow* src, SDL_Event* event);

#endif
