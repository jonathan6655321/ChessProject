#ifndef NewGameWindow_H_
#define NewGameWindow_H_
#include <SDL.h>
#include "Events.h"
#include "SDLHelperFunctions.h"

const int whiteUserColorButtonNewGameWindowMinX = 				75, whiteUserColorButtonNewGameWindowMaxX = 				250, whiteUserColorButtonNewGameWindowMinY = 				100, whiteUserColorButtonNewGameWindowMaxY = 			200;
const int blackUserColorButtonNewGameWindowMinX = 				75, blackUserColorButtonNewGameWindowMaxX = 				250, blackUserColorButtonNewGameWindowMinY = 				100, blackUserColorButtonNewGameWindowMaxY = 			200;
const int onePlayerGameModeButtonNewGameWindowMinX = 		75, onePlayerGameModeButtonNewGameWindowMaxX = 	250, onePlayerGameModeButtonNewGameWindowMinY = 	100, onePlayerGameModeButtonNewGameWindowMaxY = 	200;
const int twoPlayerGameModeButtonNewGameWindowMinX = 		75, twoPlayerGameModeButtonNewGameWindowMaxX = 	250, twoPlayerGameModeButtonNewGameWindowMinY = 	100, twoPlayerGameModeButtonNewGameWindowMaxY = 	200;
const int noobDifficultyModeButtonNewGameWindowMinX =			75, noobDifficultyModeButtonNewGameWindowMaxX = 		250, noobDifficultyModeButtonNewGameWindowMinY = 		250, noobDifficultyModeButtonNewGameWindowMaxY = 		350;
const int easyDifficultyModeButtonNewGameWindowMinX =			75, easyDifficultyModeButtonNewGameWindowMaxX = 		250, easyDifficultyModeButtonNewGameWindowMinY = 		250, easyDifficultyModeButtonNewGameWindowMaxY = 		350;
const int modarateDifficultyModeButtonNewGameWindowMinX =	75, modarateDifficultyModeButtonNewGameWindowMaxX = 	250, modarateDifficultyModeButtonNewGameWindowMinY = 250, modarateDifficultyModeButtonNewGameWindowMaxY=	350;
const int hardDifficultyModeButtonNewGameWindowMinX =			75, hardDifficultyModeButtonNewGameWindowMaxX = 			250, hardDifficultyModeButtonNewGameWindowMinY = 		250, hardDifficultyModeButtonNewGameWindowMaxY = 		350;
const int expertDifficultyModeButtonNewGameWindowMinX =		75, expertDifficultyModeButtonNewGameWindowMaxX = 		250, expertDifficultyModeButtonNewGameWindowMinY = 		250, expertDifficultyModeButtonNewGameWindowMaxY = 	350;
const int backButtonNewGameWindowMinX = 								75, backButtonNewGameWindowMaxX = 								250, backButtonNewGameWindowMinY = 							400, backButtonNewGameWindowMaxY = 							500;
const int backgroundNewGameWindowMinX = 								0  , backgroundNewGameWindowMaxX = 								400, backgroundNewGameWindowMinY = 							0    , backgroundNewGameWindowMaxY = 							450;

const int[] whiteUserColorButtonNewGameWindowRentangle = 		{whiteUserColorButtonNewGameWindowMinX, 				whiteUserColorButtonNewGameWindowMaxX, 				whiteUserColorButtonNewGameWindowMinY,	 			whiteUserColorButtonNewGameWindowMaxY};
const int[] blackUserColorButtonNewGameWindowRentangle = 			{blackUserColorButtonNewGameWindowMinX, 				blackUserColorButtonNewGameWindowMaxX, 				blackUserColorButtonNewGameWindowMinY,	 			blackUserColorButtonNewGameWindowMaxY};
const int[] onePlayerGameModeButtonNewGameWindowRentangle ={onePlayerGameModeButtonNewGameWindowMinX, 	onePlayerGameModeButtonNewGameWindowMaxX, 		onePlayerGameModeButtonNewGameWindowMinY,	 	onePlayerGameModeButtonNewGameWindowMaxY};
const int[] twoPlayerGameModeButtonNewGameWindowRentangle ={twoPlayerGameModeButtonNewGameWindowMinX, 	twoPlayerGameModeButtonNewGameWindowMaxX, 	twoPlayerGameModeButtonNewGameWindowMinY,	 	twoPlayerGameModeButtonNewGameWindowMaxY};
const int[] noobDifficultyModeNewGameWindowRentangle = 				{noobDifficultyModeButtonNewGameWindowMinX, 		noobDifficultyModeButtonNewGameWindowMaxX, 		noobDifficultyModeButtonNewGameWindowMinY,		 	noobDifficultyModeButtonNewGameWindowMaxY};
const int[] easyDifficultyModeNewGameWindowRentangle = 				{easyDifficultyModeButtonNewGameWindowMinX, 		easyDifficultyModeButtonNewGameWindowMaxX,		 	easyDifficultyModeButtonNewGameWindowMinY, 			easyDifficultyModeButtonNewGameWindowMaxY};
const int[] modarateDifficultyModeNewGameWindowRentangle = 		{modarateDifficultyModeButtonNewGameWindowMinX, modarateDifficultyModeButtonNewGameWindowMaxX, 	modarateDifficultyModeButtonNewGameWindowMinY, 	modarateDifficultyModeButtonNewGameWindowMaxY};
const int[] hardDifficultyModeNewGameWindowRentangle = 				{hardDifficultyModeButtonNewGameWindowMinX, 		hardDifficultyModeButtonNewGameWindowMaxX, 			hardDifficultyModeButtonNewGameWindowMinY, 			hardDifficultyModeButtonNewGameWindowMaxY};
const int[] expertDifficultyModeNewGameWindowRentangle = 			{expertDifficultyModeButtonNewGameWindowMinX, 		expertDifficultyModeButtonNewGameWindowMaxX, 		expertDifficultyModeButtonNewGameWindowMinY, 		expertDifficultyModeButtonNewGameWindowMaxY};
const int[] backButtonNewGameWindowRentangle = 						{backButtonNewGameWindowMinX, 								backButtonNewGameWindowMaxX, 								backButtonNewGameWindowMinY,				 				backButtonNewGameWindowMaxY};
const int[] backgroundNewGameWindowRentangle = 						{backgroundNewGameWindowMinX, 							backgroundNewGameWindowMaxX, 								backgroundNewGameWindowMinY, 								backgroundNewGameWindowMaxY};

typedef enum{
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
	SDL_Window* 	newGameWindow;
	SDL_Renderer* newGameRenderer;
	SDL_Texture* 	backgroundTexture;
	
	char gameMode;
	char difficulty;
	char userColor;
	
	SDL_Texture* 	whiteButtonTexture;
	SDL_Texture* 	blackButtonTexture;
	SDL_Texture* 	onePlayerButtonTexture;
	SDL_Texture* 	onePlayerButtonTexture;
	SDL_Texture* 	twoPlayerButtonTexture;
	SDL_Texture* 	noobDifficultyButtonTexture;
	SDL_Texture* 	easyDifficultyButtonTexture;
	SDL_Texture* 	moderateDifficultyButtonTexture;
	SDL_Texture* 	hardDifficultyButtonTexture;
	SDL_Texture* 	expertDifficultyButtonTexture;
	SDL_Texture* 	backButtonTexture;
} NewGameWindow;

NewGameWindow* NewGameWindowCreate();

void NewGameWindowDraw		(NewGameWindow* src);
void NewGameWindowDestroy	(NewGameWindow* src);
void NewGameWindowHide		(NewGameWindow* src);
void NewGameWindowShow		(NewGameWindow* src);

EventStruct NewGameWindowHandleStartGameEvent				(NewGameWindow* src);
EventStruct NewGameWindowHandleDifficultyModeEvent			(NewGameWindow* src);
EventStruct NewGameWindowHandleGameModeEvent				(NewGameWindow* src);
EventStruct NewGameWindowHandleEvent								(NewGameWindow* src, SDL_Event* event) ;

#endif
