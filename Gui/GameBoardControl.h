#ifndef CHESSGAMEBOARD_H
#define CHESSGAMEBOARD_H
#include <SDL.h>
#include <stdio.h>
#include "Events.h"
#include "SDLHelperFunctions.h"
#include "Constants.h"
#include "../Game.h"

typedef struct {
	int currentPieceSelectedRow;
	int currentPieceSelectedCol;
	ExecuteGetMovesResponse availableMovesOfSelectedPiece;
	int gameStateIsSaved;

	SDL_Texture* piecesTexture[6][2];
	SDL_Texture* boardTextures[5];

	Game game;
	GameHistory gameHistory;
} GameBoardControl;

GameBoardControl* GameBoardControlCreate(SDL_Renderer* renderer, char gameMode,
		char player1Color, char gameDifficulty);
GameBoardControl* GameBoardControlLoad(SDL_Renderer* renderer,
		int loadSlotSelected);

void GameBoardControlDraw(GameBoardControl* src, SDL_Renderer* renderer,
		int* Rectangle);
void GameBoardControlDestroy(GameBoardControl* src);

EventStruct GameBoardControlHandleMoveEvent(GameBoardControl* src, int row,
		int col);
EventStruct GameBoardControlHandleNewPieceChoosenEvent(GameBoardControl* src,
		int row, int col);
EventStruct GameBoardControlHandleUndoMove(GameBoardControl* src);
EventStruct GameBoardControlHandleSaveGame(GameBoardControl* src);
EventStruct GameBoardControlHandleRestartGame(GameBoardControl* src);
EventStruct GameBoardControlHandleGoToMainWindow(GameBoardControl* src);
EventStruct GameBoardControlHandleQuitGame(GameBoardControl* src);
EventStruct GameBoardControlHandleEvent(GameBoardControl* src,
		SDL_Event* event, int* Rectangle);

#endif
