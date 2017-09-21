#ifndef NewGameWindow_H_
#define NewGameWindow_H_
#include <SDL.h>
#include "Events.h"
#include "BMPPathConstants.h"
#include "SDLHelperFunctions.h"

 static int startNewGameButtonNewGameWindowRectangle[4] = { 250, 350, 300, 400 };
 static int whiteUserColorButtonNewGameWindowRectangle[4] = { 50, 150, 110, 160 };
 static int blackUserColorButtonNewGameWindowRectangle[4] = { 250, 350, 110, 160 };
 static int onePlayerGameModeButtonNewGameWindowRectangle[4] = { 50, 150, 10, 70 };
 static int twoPlayerGameModeButtonNewGameWindowRectangle[4] = { 250, 350, 10, 7 };
 static int noobDifficultyModeNewGameWindowRectangle[4] = { 10, 70, 200, 250 };
 static int easyDifficultyModeNewGameWindowRectangle[4] = { 90, 150, 200, 250 };
 static int modarateDifficultyModeNewGameWindowRectangle[4] = { 170, 230, 200, 250 };
 static int hardDifficultyModeNewGameWindowRectangle[4] = { 250, 310, 200, 250 };
 static int expertDifficultyModeNewGameWindowRectangle[4] = { 330, 380, 200, 250 };
 static int backButtonNewGameWindowRectangle[4] = { 50, 150, 300, 400 };
 static int backgroundNewGameWindowRectangle[4] = { 0, 400, 0, 400 };

typedef enum {
	StartNewGameNewGameWindowButtonElement,
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

typedef struct {
	SDL_Window* newGameWindow;
	SDL_Renderer* newGameRenderer;
	SDL_Texture* backgroundTexture;

	char gameMode;
	char difficulty;
	char userColor;

	SDL_Texture* startNewGameButtonTexture;
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
