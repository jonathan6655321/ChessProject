#ifndef CHESSGAMEBOARD_H
#define CHESSGAMEBOARD_H

#include <SDL.h>
#include <stdio.h>
#include "Events.h"
#include "SDLHelperFunctions.h"
#include "Constants.h"
#include "../Game.h"

/*!
 * The struct that is used to represent a game board control.
 */
typedef struct {
	// current selected index;
	int currentPieceSelectedRow;
	int currentPieceSelectedCol;
	// is true when the current selected index was choosen with a right click.
	int rightClick;
	// is true when the left mouse is down.
	int leftDown;
	int mousePosition[2];
	// arrays containing the data from the "get_move" response.
	// indicate that a move is possible and if it's threatened ot not.
	ExecuteGetMovesResponse availableMovesOfSelectedPiece;
	// is true when the current game state is saved.
	int gameStateIsSaved;
	// pieces Surfaces
	SDL_Surface *piecesSurface[6][2];
	// board Surfaces
	SDL_Surface *boardSurfaces[5];
	// game element
	Game game;
	// game history element
	GameHistory gameHistory;
} GameBoardControl;

/*!
 * Creates a new game board control
 * @param gameMode the game mode specified.
 * @param player1Color the player 1 color specified.
 * @param gameDifficulty the game difficulty specified.
 * @return a new game board control instance.
 * 			or null on failure.
 */
GameBoardControl *GameBoardControlCreate(char gameMode, char player1Color,
		char gameDifficulty);

/*!
 * Creates a new game board from a save file. print error if needed.
 * @param loadSlotSelected the game slot specified.
 * @return a new game board from the save file,
 * 			or null on failure.
 */
GameBoardControl *GameBoardControlLoad(int loadSlotSelected);

/*!
 * Draw the game board control on the specified window.
 * @param screen the windows screen to draw to.
 * @param src the game board control to draw.
 * @param Rectangle the rentangle it should draw on.
 */
void GameBoardControlDraw(SDL_Surface* screen, GameBoardControl *src,
		int *Rectangle);

/*!
 * destroy the game board control specified.
 * @param src
 */
void GameBoardControlDestroy(GameBoardControl *src);

/*!
 * Handle move piece event
 * @param src the game board
 * @param row,col the row and col the piece needs to go to.
 * @return empty event, or Quit event if game is over.
 */
EventStruct GameBoardControlHandleMoveEvent(GameBoardControl *src, int row,
		int col);

/*!
 * Handle choosing new piece on board
 * @param src the game board
 * @param row,col of the new piece
 * @return empty event.
 */
EventStruct GameBoardControlHandleNewPieceChoosenEvent(GameBoardControl *src,
		int row, int col);

/*!
 * undo the last move. print error if needed.
 * @param src the game board
 * @return empty event
 */
EventStruct GameBoardControlHandleUndoMove(GameBoardControl *src);

/*!
 * Save game, print error if needed.
 * change game saved state to true.
 * @param src the game board
 * @return empty event.
 */
EventStruct GameBoardControlHandleSaveGame(GameBoardControl *src);

/*!
 * restart the game with the current setting.
 * promote user to save in case the game state is unsaved.
 * @param src the game board
 * @return empty event.
 */
EventStruct GameBoardControlHandleRestartGame(GameBoardControl *src);

/*!
 * Go back to main window.
 * promote user to save in case the game state is unsaved.
 * @param src the game board
 * @return go back to main window event or empty event if canceled.
 */
EventStruct GameBoardControlHandleGoToMainWindow(GameBoardControl *src);

/*!
 * Quit game handler. promote user to save in case the game state is unsaved.
 * @param src the game board
 * @return Quit event ot empty event if canceled.
 */
EventStruct GameBoardControlHandleQuitGame(GameBoardControl *src);

/*!
 *
 * @param src the game board.
 * @param event the SDL event to handle.
 * @param Rectangle the game board rectangle on the windows.
 * @return Event relevent to the GUI Manager if needed, or empty events.
 */
EventStruct GameBoardControlHandleEvent(GameBoardControl *src,
		SDL_Event *event, int *Rectangle);

#endif
