#ifndef CHESSGAMEWINDOW_H
#define CHESSGAMEWINDOW_H
#include <SDL.h>
#include "Events.h"
#include "GameBoardControl.h"
#include "BMPPathConstants.h"
#include "SDLHelperFunctions.h"
//TODO: #include <SDL_video.h>
//	TODO : #include "SPTicTacToeWindow.h"
//	TODO : #include "../SPTicTacToe.h"


static int gameBoardGameWindowRectangle[4] = { 50, 650, 100, 700 };
static int saveGameGameWindowRectangle[4] = { 700, 800, 100, 150 };
static int loadGameGameWindowRectangle[4] = { 700, 800, 200, 250 };
static int undoButtonGameWindowRectangle[4] = { 700, 800, 300, 350 };
static int goToMainWindowButtonGameWindowRectangle[4] = { 700, 800, 400, 450 };
static int restartButtonGameWindowRectangle[4] = { 700, 800, 500, 550 };
static int quitGameGameWindowRectangle[4] = { 700, 800, 600, 650 };
static int backgroundGameWindowRectangle[4] = { 0, 850, 0, 800 };

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
