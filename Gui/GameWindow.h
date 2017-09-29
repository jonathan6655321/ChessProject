#ifndef CHESSGAMEWINDOW_H
#define CHESSGAMEWINDOW_H
#include <SDL.h>
#include "Events.h"
#include "GameBoardControl.h"
#include "Constants.h"
#include "SDLHelperFunctions.h"


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

typedef struct {
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	SDL_Texture* backgroundTexture;

	SDL_Texture* saveGameTexture;
	SDL_Texture* loadGameTexture;
	SDL_Texture* undoTexture;
	SDL_Texture* goToMainWindowTexture;
	SDL_Texture* restartTexture;
	SDL_Texture* quitTexture;
	GameBoardControl* gameControl;
} GameWindow;

GameWindow* GameWindowCreate(char gameMode, char player1Color,
		char gameDifficulty);
GameWindow* GameWindowLoad(char loadSlotSelected);

void GameWindowDraw(GameWindow* src);
void GameWindowDestroy(GameWindow* src);
void GameWindowHide(GameWindow* src);
void GameWindowShow(GameWindow* src);

EventStruct GameWindowHandleEvent(GameWindow* src, SDL_Event* event);

#endif
