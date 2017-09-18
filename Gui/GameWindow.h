#ifndef CHESSGAMEWINDOW_H
#define CHESSGAMEWINDOW_H
#include <SDL.h>
#include "Events.h"
#include "GameBoardControl.h"
#include "SDLHelperFunctions.h"
TODO: #include <SDL_video.h>
	TODO : #include "SPTicTacToeWindow.h"
	TODO : #include "../SPTicTacToe.h"

	const int gameBoardGameWindowMinX = 0, gameBoardGameWindowMaxX = 400, gameBoardGameWindowMinY = 0, gameBoardGameWindowMaxY = 450;
	  const int saveGameButtonGameWindowMinX = 75, saveGameButtonGameWindowMaxX = 250, saveGameButtonGameWindowMinY = 100, saveGameButtonGameWindowMaxY = 200;
	  const int loadGameButtonGameWindowMinX = 75, loadGameButtonGameWindowMaxX = 250, loadGameButtonGameWindowMinY = 250, loadGameButtonGameWindowMaxY = 350;
	  const int undoButtonGameWindowMinX = 0, undoButtonGameWindowMaxX = 400, undoButtonGameWindowMinY = 0, undoButtonGameWindowMaxY = 450;
	  const int goToMainWindowButtonGameWindowMinX = 0, goToMainWindowButtonGameWindowMaxX = 400, goToMainWindowButtonGameWindowMinY = 0, goToMainWindowButtonGameWindowMaxY = 450;
	  const int restartButtonGameWindowMinX = 0, restartButtonGameWindowMaxX = 400, restartButtonGameWindowMinY = 0, restartButtonGameWindowMaxY = 450;
	  const int quitButtonGameWindowMinX = 75, quitButtonGameWindowMaxX = 250, quitButtonGameWindowMinY = 400, quitButtonGameWindowMaxY = 500;
	  const int backgroundGameWindowMinX = 0, backgroundGameWindowMaxX = 400, backgroundGameWindowMinY = 0, backgroundGameWindowMaxY = 450;


	  const int[] gameBoardGameWindowRentangle = { gameBoardGameWindowMinX, 					gameBoardGameWindowMaxX, 					gameBoardGameWindowMinY, 						gameBoardGameWindowMaxY };
	  const int[] saveGameGameWindowRentangle = { saveGameButtonGameWindowMinX, 			saveGameButtonGameWindowMaxX,		 	saveGameButtonGameWindowMinY, 			saveGameButtonGameWindowMaxY };
	  const int[] loadGameGameWindowRentangle = { loadGameButtonGameWindowMinX, 			loadGameButtonGameWindowMaxX, 			loadGameButtonGameWindowMinY, 				loadGameButtonGameWindowMaxY };
	  const int[] undoButtonGameWindowRentangle = { undoButtonGameWindowMinX, 					undoButtonGameWindowMaxX, 					undoButtonGameWindowMinY, 						undoButtonGameWindowMaxY };
	  const int[] goToMainWindowButtonGameWindowRentangle = { goToMainWindowButtonGameWindowMinX, goToMainWindowButtonGameWindowMaxX, 	goToMainWindowButtonGameWindowMinY, 	goToMainWindowButtonGameWindowMaxY };
	  const int[] restartButtonGameWindowRentangle = { restartButtonGameWindowMinX, 				restartButtonGameWindowMaxX, 					restartButtonGameWindowMinY, 					restartButtonGameWindowMaxY };
	  const int[] quitGameGameWindowRentangle = { quitButtonGameWindowMinX, 						quitButtonGameWindowMaxX, 						quitButtonGameWindowMinY, 						quitButtonGameWindowMaxY };
	  const int[] backgroundGameWindowRentangle = { backgroundGameWindowMinX, 					backgroundGameWindowMaxX, 					backgroundGameWindowMinY, 						backgroundGameWindowMaxY };


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
		  SDL_Window* 			gameWindow;
		  SDL_Renderer*		 	gameRenderer;
		  SDL_Texture* 			backgroundTexture;

		  SDL_Texture* 			saveGameTexture;
		  SDL_Texture* 			loadGameTexture;
		  SDL_Texture* 			undoTexture;
		  SDL_Texture* 			goToMainWindowTexture;
		  SDL_Texture* 			restartTexture;
		  SDL_Texture* 			quitTexture;
		  GameBoardControl* gameControl;
	  } GameWindow;

	  GameWindow* GameWindowCreate(char gameMode, char player1Color, char gameDifficulty);
	  GameWindow* GameWindowLoad(char loadSlotSelected);

	  void GameWindowDraw(GameWindow* src);
	  void GameWindowDestroy(GameWindow* src);
	  void GameWindowHide(GameWindow* src);
	  void GameWindowShow(GameWindow* src);

	  EventStruct GameWindowHandleEvent(GameWindow* src, SDL_Event* event);

#endif
