#ifndef CHESSGAMEBOARD_H
#define CHESSGAMEBOARD_H
#include <SDL.h>
#include <stdio.h>
#include "Events.h"
#include "SDLHelperFunctions.h"
#include "../Game.h"
TODO: #include <SDL_video.h>
TODO: #include "SPTicTacToeWindow.h"

typedef struct {
	int 										currentPieceSelectedRow;
	int 										currentPieceSelectedCol;
	ExecuteGetMovesResponse 	availableMovesOfLastPiece;
	int 										gameStateIsSaved;
	
	SDL_Texture* 	textures[NUMBER_OF_GAME_BOARD_TEXTURES]; // type of pieces + empty pieces  * white&black&blue&darkerBlue
	Game 				game;
	GameHistory 	gameHistory;
} GameBoardControl;

GameBoardControl* GameBoardControlCreate	(SDL_Renderer* renderer, char gameMode, char player1Color, char gameDifficulty);
GameBoardControl* GameBoardControlLoad	(SDL_Renderer* renderer, char loadSlotSelected);

void GameBoardControlDraw		(GameBoardControl* src, SDL_Renderer* renderer, int[] rentangle);
void GameBoardControlDestroy	(GameBoardControl* src);

EventStruct GameBoardControlHandleMoveEvent						(GameBoardControl* src, int row, int col);
EventStruct GameBoardControlHandleNewPieceChoosenEvent	(GameBoardControl* src, int row, int col);
EventStruct GameBoardControlHandleUndoMove						(GameBoardControl* src);
EventStruct GameBoardControlHandleSaveGame						(GameBoardControl* src);
EventStruct GameBoardControlHandleRestartGame					(GameBoardControl* src);
EventStruct GameBoardControlHandleQuitGame						(GameBoardControl* src);
EventStruct GameBoardControlHandleEvent								(GameBoardControl* src, SDL_Event* event, int[] rentangle) ;

#endif
