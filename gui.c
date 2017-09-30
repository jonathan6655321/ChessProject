/*
 * gui.c
 *
 *  Created on: Sep 7, 2017
 *      Author: emilmousa
 */

#include "gui.h"
#include "guiManager.h"
#include <stdbool.h>
#include "chessgame.h"
#include "staticFunctions.h"
#include "AI.h"

int currentColor;
bool checkWindow(Node UI_Tree) {
	Node panel;
	Control lbl;
	SDL_Surface *surface;
	SDL_Rect check = { 35, 50, 180, 40 };

	panel = createNode(
			buildPanel(0, 0, WIN_W, WIN_H, NULL,
					createLL()));
	insertTail(UI_Tree->control->sons, panel);

	if (!getNewSurface(180, 40, &surface))
		return false;
	applySurface(0, 0, checkMateSurface, surface, &check);
	lbl = buildLabel(350, 220, surface, &check);
	insertTail(panel->control->sons, createNode(lbl));

	paindUpdateWindow(UI_Tree);

	SDL_Delay(2000);

	deleteTail(UI_Tree->control->sons);

	return paindUpdateWindow(UI_Tree);
}

bool checkMateWindow(Node UI_Tree) {

	Node panel;
	Control lbl;
	SDL_Surface *surface;
	SDL_Rect check = {35, 50, 180, 90};

	SDL_Surface *temp_surface = SDL_CreateRGBSurface(0, WIN_W, WIN_H,
			RPOGRAM_BPP, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	SDL_FillRect(temp_surface, &((SDL_Rect ) { 0, 0, WIN_W, WIN_H } ),
			SDL_MapRGBA(screen->format, 0, 0, 0, 50));

	panel = createNode(buildPanel(0, 0, WIN_W, WIN_H, temp_surface, createLL()));
	insertTail(UI_Tree->control->sons, panel);

	if (!getNewSurface(180, 90, &surface))
		return false;
	applySurface(0, 0, checkMateSurface, surface, &check);
	lbl = buildButton(350, 220, surface, &check, restart, NULL, 1);
	insertTail(panel->control->sons, createNode(lbl));

	paindUpdateWindow(UI_Tree);

	SDL_Delay(5000);

	initial_board(board);

	paindUpdateWindow(UI_Tree);

	currentColor = WHITE;
	return true;

}

int guiMain() {

	Node UI_Tree;
	bool flag = false;
	SDL_Event event;
	Node temp;
	const Uint8 *keys;
	settingsArr = (int*)calloc(3,sizeof(int));
    undos = (history*)calloc(1,sizeof(history));
    undoAmount = 0;

	GUI_MODE = 1;
	PROMOTENEEDED = 0;

	currentColor = USER_CLR = WHITE ;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);
	if (!initializeAllSurfaces()) {
		printf("ERROR: unable to create surfaces: %s\n", SDL_GetError());
		return 1;
	}
	atexit(freeAllSurfaces);
	window = SDL_CreateWindow("ChessGame", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, SDL_WINDOW_OPENGL);


	screen = SDL_GetWindowSurface(window);

	//initialize the board
	initial_board(board);
	UI_Tree = createNode(buildWindow(0, 0, WIN_W, WIN_H, initialMenu, createLL()));

	mainMenuBranch(UI_Tree);

	if (!paintTree(screen, UI_Tree, 0, 0)) {
		perror("Couldn't create the main menu since painting the tree failed.\n");
		return 1;
	}

	SDL_UpdateWindowSurface(window);

	while (SDL_WaitEvent(&event) >= 0) {

		switch (event.type) {
		case SDL_MOUSEBUTTONDOWN: {
			Uint8 * keys;

			if (event.button.button == SDL_BUTTON_LEFT) {
				//Untill we finish handling the current click, we disable further button events
				SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);

				//Find the current control we pressed on, and the press's coordinates.
				temp = NULL;
				locateClick(event.button, UI_Tree, &(temp));

				if (temp->control->controlType == BUTTON) {

					if (temp->control->command && !game_active) {

						//Execute the command of the button
						temp->control->command(temp->control->serialNum,
								&UI_Tree, board);


						//mouse events.
						SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);
						continue;
					}
				}
				if (temp->control->command != NULL && game_active) { // check if we are in the game
					if (GAME_MODE == 1 && currentColor == USER_CLR) { // player vs. computer, player's turn
					//Execute the command of the button
						//GAME_MODE = 10;
						temp->control->command(temp->control->serialNum, &UI_Tree, board);
						//enable mouse events.
						SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);

					}
					if (GAME_MODE == 2) { // Player vs. Player
						//Execute the command of the button
						temp->control->command(temp->control->serialNum, &UI_Tree, board);
						//enable mouse events.
						SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);
					}
				}
				if(PROMOTENEEDED == 1){
					upGradeSoldier(UI_Tree, currentColor, currentMove[2],
							currentMove[3]);
					PROMOTENEEDED = 0;
					paindUpdateWindow(UI_Tree);

					//enable mouse event
					SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);
					while (SDL_WaitEvent(&event) >= 0) {
						switch (event.type) {
						case SDL_MOUSEBUTTONDOWN:
							if (event.button.button == SDL_BUTTON_LEFT) {
								temp = NULL;
								locateClick(event.button, UI_Tree, &(temp));
								if (temp->control->controlType == BUTTON) {
									temp->control->command(
											temp->control->serialNum,
											&UI_Tree, board);
									flag = true;
								}
							}
							break;
						}
						if (flag) {
							flag = false;
							deleteTail(UI_Tree->control->sons);
							break;
						}
					}
					SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
				}
				if (isCheck(board, currentColor) == 1
						&& !somethingHighlighted()) { // check if CHECK
					if (!checkWindow(UI_Tree))
						exit(0);
				}
				if (isCheck(board, currentColor) == 2) { // check if CHECKMATE
					if (!checkMateWindow(UI_Tree))
						exit(0);
					newGame(0, &UI_Tree, board);
					//enable mouse event
					SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);
					continue;
				}

				if (game_active && (currentColor != USER_CLR)
						&& GAME_MODE == 1) { // computer's turn

					computerMove(board, currentColor, level,currentMove,false);
					if (currentColor == WHITE)
						currentColor = BLACK;
					else
						currentColor = WHITE;
					freeUITREE(UI_Tree);
					SDL_FreeSurface(screen);


					screen = SDL_GetWindowSurface(window);

					UI_Tree = createNode(
							buildWindow(0, 0, WIN_W, WIN_H, defaultBG,
									createLL()));
					createBoardBranch(board, UI_Tree);
					createSideMenu(UI_Tree);
					SDL_Delay(500);
					paindUpdateWindow(UI_Tree);

					SDL_UpdateWindowSurface(window);

					if (isCheck(board, currentColor) == 1) { // check if CHECK
						if (!checkWindow(UI_Tree))
							exit(0);
					}
					if (isCheck(board, currentColor) == 2) { // check if CHECKMATE
						if (!checkMateWindow(UI_Tree))
							exit(0);
						newGame(0, &UI_Tree, board);
					}
					//enable mouse event
					SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);
				}
			}
			SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);
		}

			keys = SDL_GetKeyboardState(NULL );
			if (keys[SDLK_ESCAPE] == SDL_PRESSED) {
				exit(0);
			}

			break;

		case SDL_QUIT: {
			freeAllSurfaces();
			free(undos);
			free(settingsArr);
			exit(0);
		}
			break;
		}
	}
	free(undos);
	free(settingsArr);
	freeAllSurfaces();
	return 0;

}

bool initializeAllSurfaces() {
	chessGrid = SDL_LoadBMP("pictures/chessGrid.bmp");
	if (!chessGrid)
		return false;
	SDL_SetColorKey(chessGrid, SDL_TRUE, 0x00ffff);

	hightLighted = SDL_LoadBMP("pictures/highligh.bmp");
	if(!hightLighted)
		return false;
	defaultBG = SDL_LoadBMP("./pictures/defa.bmp");
	if (!defaultBG)
		return false;
	gameMenuSurface = SDL_LoadBMP("./pictures/GameMenu.bmp");
	if (!gameMenuSurface)
		return false;
	initialMenu = SDL_LoadBMP("./pictures/chess-game.bmp");
	if (!initialMenu)
		return false;
	numOfPSurface = SDL_LoadBMP("./pictures/NumOfPlayers.bmp");
	if (!numOfPSurface)
		return false;
	backSurface = SDL_LoadBMP("./pictures/back.bmp");
	if(!backSurface)
		return false;
	mainMenu = SDL_LoadBMP("./pictures/main_menu.bmp");
	if (!chessGrid)
		return false;
	onePlayerSurface = SDL_LoadBMP("./pictures/1Player.bmp");
	if (!onePlayerSurface)
		return false;
	twoPlayersSurface = SDL_LoadBMP("./pictures/2Players.bmp");
	if (!twoPlayersSurface)
		return false;
	blackBoard = SDL_LoadBMP("./pictures/black.bmp");
	if (!blackBoard)
		return false;
	whiteBoard = SDL_LoadBMP("./pictures/white.bmp");
	if (!whiteBoard)
		return false;
	checkMateSurface = SDL_LoadBMP("./pictures/checkmate.bmp");
	if (!checkMateSurface)
		return false;
	numbersSurface =  SDL_LoadBMP("./pictures/numbers.bmp");
	if (!checkMateSurface)
		return false;
	return true;
}

void freeAllSurfaces() {
	if (chessGrid) {
		SDL_FreeSurface(chessGrid);
		chessGrid = 0;
	}
	if(hightLighted){
		SDL_FreeSurface(hightLighted);
		hightLighted = 0;
	}
	if(defaultBG){
		SDL_FreeSurface(defaultBG);
		defaultBG = 0;
	}
	if (gameMenuSurface) {
		SDL_FreeSurface(gameMenuSurface);
		gameMenuSurface = 0;
	}
	if (initialMenu) {
		SDL_FreeSurface(initialMenu);
		initialMenu = 0;
	}
	if (numOfPSurface) {
		SDL_FreeSurface(numOfPSurface);
		numOfPSurface = 0;
	}
	if(backSurface){
		SDL_FreeSurface(backSurface);
		backSurface = 0;
	}
	if (mainMenu) {
		SDL_FreeSurface(mainMenu);
		mainMenu = 0;
	}
	if (onePlayerSurface) {
		SDL_FreeSurface(onePlayerSurface);
		onePlayerSurface = 0;
	}
	if (twoPlayersSurface) {
		SDL_FreeSurface(twoPlayersSurface);
		twoPlayersSurface = 0;
	}
	if (blackBoard) {
		SDL_FreeSurface(blackBoard);
		blackBoard = 0;
	}
	if (whiteBoard) {
		SDL_FreeSurface(whiteBoard);
		whiteBoard = 0;
	}
	if (checkMateSurface) {
		SDL_FreeSurface(checkMateSurface);
		checkMateSurface = 0;
	}
	if (numbersSurface) {
		SDL_FreeSurface(numbersSurface);
		numbersSurface = 0;
	}
}

bool createBoardBranch(char board[SQR][SQR], Node ui_tree) {
	int i, j, x, y, num = 0;
	Control ctl;
	Node panel1;
	SDL_Surface * surf;
	panel1 = createNode(buildPanel(MENU_WIDTH, 0, WIN_W - MENU_WIDTH / 2, WIN_H, NULL, createLL()));
	insertTail(ui_tree->control->sons, panel1);
	SDL_Rect source_white = { 20, 11, BOARDSQUARE, BOARDSQUARE };
	SDL_Rect source_black = { 73, 67, BOARDSQUARE, BOARDSQUARE };

	for (i = 0; i < SQR; i++) {
		for (j = 0; j < SQR; j++) {

			if (!getNewSurface(BOARDSQUARE, BOARDSQUARE, &surf))
				return false;

			applySurface(0, 0, (i + j) % 2 ? whiteBoard : blackBoard
					, surf, (i + j) % 2 ? &source_white : &source_black);

			x = i * BOARDSQUARE;

			y = (SQR - 1 - j) * BOARDSQUARE;

			ctl = buildButton(x, y, surf,
					(i + j) % 2 ? &source_white : &source_black,
					getSoldierMoves, moveSoldier, num);

			insertTail(panel1->control->sons, createNode(ctl));

			num++;
		}
	}
	createSoldierBranch(board, panel1);
	return true;

}

bool createSideMenu(Node ui_tree) {
	Control ctl = NULL;
	Control lbl = NULL;
	Node panel1 = NULL;
	SDL_Surface* surf;

	SDL_Rect tempRestart = { 40, 35, 200, 38 };
	SDL_Rect tempSave = { 40, 111, 200, 38 };
	SDL_Rect tempLoad = { 40, 189, 200, 38 };
	SDL_Rect tempUndo = { 40, 265, 200, 38 };
	SDL_Rect tempMain = { 40, 552, 200, 38 };
	SDL_Rect tempExit = { 40, 625, 200, 38 };

	panel1 = createNode(
			buildPanel(0, 0, MENU_WIDTH, WIN_H, gameMenuSurface,
					createLL()));
	insertTail(ui_tree->control->sons, panel1);

	if (!getNewSurface(200, 38, &surf))
		return false;
	ctl = buildButton(40, 35, surf, &tempRestart, restart, NULL, 3);
	insertTail(panel1->control->sons, createNode(ctl));

	if (!getNewSurface(200, 38, &surf))
		return false;
	ctl = buildButton(40, 111, surf, &tempSave, saveScreen, NULL, 1);
	insertTail(panel1->control->sons, createNode(ctl));

	if (!getNewSurface(200, 38, &surf))
		return false;
	ctl = buildButton(40, 189, surf, &tempLoad, loadScreen, NULL, 4);
	insertTail(panel1->control->sons, createNode(ctl));

	if (!getNewSurface(200, 38, &surf))
		return false;
	ctl = buildButton(40, 265, surf, &tempUndo, undoFunc, NULL, 3);
	insertTail(panel1->control->sons, createNode(ctl));

	if (!getNewSurface(200, 38, &surf))
		return false;
	ctl = buildButton(40, 552, surf, &tempMain, cancelFunc, NULL, 22);
	insertTail(panel1->control->sons, createNode(ctl));

	if (!getNewSurface(200, 38, &surf))
		return false;
	ctl = buildButton(40, 625, surf, &tempExit, funcExit, NULL, 4);
	insertTail(panel1->control->sons, createNode(ctl));

	return true;

}

bool createSoldierBranch(char board[SQR][SQR], Node root) {
	int i, j, unit_x, unit_y, num = 0;
	SDL_Rect r;
	SDL_Surface *surface;
	for (j = 0; j < SQR; j++) {
		for (i = 0; i < SQR; i++) {
			if (board[i][j] != '_' && board[i][j] != 'H') {
				unit_x = j * BOARDSQUARE + (BOARDSQUARE - 40) / 2;
				unit_y = (SQR - 1 - i) * BOARDSQUARE + (BOARDSQUARE - 40) / 2;
				r = getPiece(board[i][j]);
				if (!getNewSurface(40, 40, &surface))
					return false;
				applySurface(0, 0, chessGrid, surface, &r);
				if (!insertTail(root->control->sons,
						createNode(
								buildButton(unit_x, unit_y, surface, &r,
										getSoldierMoves, moveSoldier, num)))){

					return false;
				}
			}
			num++;
		}
	}
	return true;

}
/*
 * menu to select the number of players
 * one player vs the computer or
 * player vs player
 */
bool playersSelectionBranch(Node root) {
	Control ctl = NULL;
	Node panel1 = NULL;
	SDL_Rect source1 = { 60, 340, 280, 50 }; //player1
	SDL_Rect source2 = { 60, 450, 280, 50 }; //player2
	SDL_Rect source3 = { 60, 580, 280, 50 }; //cancel
	SDL_Surface *surface;
	panel1 = createNode(
			buildPanel(0, 0, WIN_W, WIN_H, numOfPSurface,
					createLL()));
	insertTail(root->control->sons, panel1);

	if (!getNewSurface(280, 50, &surface))
		return false;
	ctl = buildButton(60, 340, surface, &source1, settings, NULL, 1);
	if (!insertTail(panel1->control->sons, createNode(ctl)))
		return false;

	if (!getNewSurface(280, 50, &surface))
		return false;
	ctl = buildButton(60, 450, surface, &source2, settings, NULL, 2);
	if (!insertTail(panel1->control->sons, createNode(ctl)))
		return false;

	if (!getNewSurface(280, 50, &surface))
		return false;
	ctl = buildButton(60, 580, surface, &source3, cancelFunc, NULL, 0);
	if (!insertTail(panel1->control->sons, createNode(ctl)))
		return false;
	return true;

}

/*
 * the main menu setting
 * creating surface for main menu window
 */
bool mainMenuBranch(Node ui_tree) {
	Control ctl = NULL;
	Node panel1 = NULL;
	SDL_Rect source1 = { 506, 60, 210, 55 }; //new Game
	SDL_Rect source2 = { 506, 172, 210, 55 }; // load Game
	SDL_Rect source3 = { 506, 513, 210, 55 }; // Quit
	SDL_Surface *surface;

	panel1 = createNode(
			buildPanel(0, 0, WIN_H, WIN_W, NULL, createLL()));

	insertTail(ui_tree->control->sons, panel1);

	if (!getNewSurface(210, 55, &surface))
		return false;
	ctl = buildButton(506, 50, surface, &source1, playersSelection, NULL, 1);
	insertTail(panel1->control->sons, createNode(ctl));

	if (!getNewSurface(210, 55, &surface))
		return false;
	ctl = buildButton(506, 172, surface, &source2, loadScreen, NULL, 1);
	insertTail(panel1->control->sons, createNode(ctl));

	if (!getNewSurface(210, 55, &surface))
		return false;
	ctl = buildButton(506, 513, surface, &source3, funcExit, NULL, 3);
	insertTail(panel1->control->sons, createNode(ctl));

	return true;
}

/*
 * settings menu in if one player selected
 * to choose level and color then start
 */
bool settingsOnePlayer(Node root) {
	Control ctl = NULL;
	Node panel1 = NULL;
	SDL_Rect source1 = { 40, 470, 120, 120 }; //level 1
	SDL_Rect source2 = { 210, 470, 120, 120 }; // level 2
	SDL_Rect source3 = { 385, 470, 120, 120 };	// level 3
	SDL_Rect source4 = { 580, 470, 120, 120 }; //level 4
	SDL_Rect start = { 550, 615, 260, 60 };
	SDL_Rect white_player = { 360, 80, 140, 170 };
	SDL_Rect black_player = { 25, 80, 140, 170 };
	SDL_Surface *surface;

	panel1 = createNode(
			buildPanel(0, 0, WIN_W, WIN_H , onePlayerSurface,
					createLL()));
	insertTail(root->control->sons, panel1);

	if (!getNewSurface(120, 120, &surface))
		return false;
	ctl = buildButton(40, 470, surface, &source1, difficulty,
			NULL, 1);
	if (!insertTail(panel1->control->sons, createNode(ctl)))
		return false;

	if (!getNewSurface(120, 120, &surface))
		return false;
	ctl = buildButton(210, 470, surface, &source2, difficulty,
			NULL, 2);
	if (!insertTail(panel1->control->sons, createNode(ctl)))
		return false;

	if (!getNewSurface(75, 75, &surface))
		return false;
	ctl = buildButton(385,470, surface, &source3, difficulty,
			NULL, 3);
	if (!insertTail(panel1->control->sons, createNode(ctl)))
		return false;

	if (!getNewSurface(75, 75, &surface))
		return false;
	ctl = buildButton(580,470, surface, &source4, difficulty,
			NULL, 4);
	if (!insertTail(panel1->control->sons, createNode(ctl)))
		return false;


	if (!getNewSurface(260, 60, &surface))
		return false;
	ctl = buildButton(550, 615 , surface, &start, newGame,
			NULL, 32);
	if (!insertTail(panel1->control->sons, createNode(ctl)))
		return false;

	if (!getNewSurface(140, 170, &surface))
		return false;
	ctl = buildButton(25, 80, surface, &black_player, choosePlayerColor, NULL, 0);
	if (!insertTail(panel1->control->sons, createNode(ctl)))
		return false;

	if (!getNewSurface(140, 170, &surface))
		return false;
	ctl = buildButton(360, 80, surface, &white_player, choosePlayerColor, NULL,
			1);
	if (!insertTail(panel1->control->sons, createNode(ctl)))
		return false;
	return true;
}

/*
 * settings page for two players
 */
bool settingsTwoPlayers(Node root) {
	Control ctl = NULL;
	Node panel1 = NULL;
	SDL_Rect start = { 56, 340, 295, 50 };
	SDL_Rect cancel = { 56, 580, 295, 50 };
	SDL_Surface *surface;
	panel1 = createNode(
			buildPanel(0, 0, WIN_W, WIN_H, twoPlayersSurface,
					createLL()));
	insertTail(root->control->sons, panel1);

	if (!getNewSurface(295, 50, &surface))
		return false;
	ctl = buildButton(56, 340, surface, &start, newGame, NULL, 32);
	if (!insertTail(panel1->control->sons, createNode(ctl)))
		return false;

	if (!getNewSurface(295, 50, &surface))
		return false;
	applySurface(56, 580, twoPlayersSurface, surface, &cancel);
	ctl = buildButton(56, 580, surface, &cancel, cancelFunc, NULL, 0);
	if (!insertTail(panel1->control->sons, createNode(ctl)))
		return false;
	return true;
}

bool somethingHighlighted() {
	int i, j;
	for (i = 0; i < SQR; i++)
		for (j = 0; j < SQR; j++)
			if (board[i][j] == 'H')
				return true;
	return false;
}

bool newGame(int param, Node * UI_Tree, char board[SQR][SQR]) {
	bool flag = true;
	freeUITREE(*UI_Tree);
	SDL_FreeSurface(screen);

	screen = SDL_GetWindowSurface(window);

	*UI_Tree = createNode(
			buildWindow(0, 0, WIN_W, WIN_H, defaultBG,
					createLL()));
	createBoardBranch(board, *UI_Tree);
	createSideMenu(*UI_Tree);
	game_active = true;

	currentColor = (currentColor == WHITE) ? WHITE : BLACK;
	flag = paindUpdateWindow(*UI_Tree);
	return flag;
}

bool upGradeSoldier(Node UI_Tree, int color, int i, int j) {
	Node panel, panel_son;
	Control ctl;
	SDL_Surface *surface;
	SDL_Surface *temp_surface = SDL_CreateRGBSurface(0, WIN_W, WIN_H,
			RPOGRAM_BPP, 0x00000000, 0x00000000, 0x00000000, 0x00000000);
	SDL_FillRect(temp_surface, &((SDL_Rect ) { 0, 0, WIN_W, WIN_H } ),
			SDL_MapRGB(screen->format, 0, 0, 0));

	panel = createNode(
			buildPanel(0, 0, WIN_W, WIN_H, NULL, createLL()));
	insertTail(UI_Tree->control->sons, panel);

	panel_son = createNode(
			buildPanel(250, 250, 260, 80, temp_surface,
					createLL()));
	insertTail(panel->control->sons, panel_son);

	if (color == BLACK) {
		if (!getNewSurface(40, 40, &surface))
			return false;
		applySurface(0, 0, chessGrid, surface,
				&(SDL_Rect ) { 263, 159, 40, 40 });
		ctl = buildButton(20, 20, surface, &(SDL_Rect ) { 263, 159, 40, 40 },
				changeSoldier, NULL, 'n');
		if (!insertTail(panel_son->control->sons, createNode(ctl)))
			return false;

		if (!getNewSurface(40, 40, &surface))
			return false;
		applySurface(0, 0, chessGrid, surface,
				&(SDL_Rect ) { 200, 159, 40, 40 });
		ctl = buildButton(80, 20, surface, &(SDL_Rect ) { 200, 159, 40, 40 },
				changeSoldier, NULL, 'b');
		if (!insertTail(panel_son->control->sons, createNode(ctl)))
			return false;

		if (!getNewSurface(40, 40, &surface))
			return false;
		applySurface(0, 0, chessGrid, surface,
				&(SDL_Rect ) { 142, 159, 40, 40 });
		ctl = buildButton(140, 20, surface,
				&(SDL_Rect ) { 142, 159, 40, 40 }, changeSoldier, NULL,
				'r');
		if (!insertTail(panel_son->control->sons, createNode(ctl)))
			return false;

		if (!getNewSurface(40, 40, &surface))
			return false;
		applySurface(0, 0, chessGrid, surface,
				&(SDL_Rect ) { 79, 159, 40, 40 });
		ctl = buildButton(200, 20, surface, &(SDL_Rect ) { 79, 159, 40, 40 },
				changeSoldier, NULL, 'q');
		if (!insertTail(panel_son->control->sons, createNode(ctl)))
			return false;

	} else {
		if (!getNewSurface(40, 40, &surface))
			return false;
		applySurface(0, 0, chessGrid, surface,
				&(SDL_Rect ) { 263, 226, 40, 40 });
		ctl = buildButton(20, 20, surface, &(SDL_Rect ) { 263, 226, 40, 40 },
				changeSoldier, NULL, 'N');
		if (!insertTail(panel_son->control->sons, createNode(ctl)))
			return false;

		if (!getNewSurface(40, 40, &surface))
			return false;
		applySurface(0, 0, chessGrid, surface,
				&(SDL_Rect ) { 200, 226, 40, 40 });
		ctl = buildButton(80, 20, surface, &(SDL_Rect ) { 200, 226, 40, 40 },
				changeSoldier, NULL, 'B');
		if (!insertTail(panel_son->control->sons, createNode(ctl)))
			return false;

		if (!getNewSurface(40, 40, &surface))
			return false;
		applySurface(0, 0, chessGrid, surface,
				&(SDL_Rect ) { 142, 226, 40, 40 });
		ctl = buildButton(140, 20, surface,
				&(SDL_Rect ) { 142, 226, 40, 40 }, changeSoldier, NULL,
				'R');
		if (!insertTail(panel_son->control->sons, createNode(ctl)))
			return false;

		if (!getNewSurface(40, 40, &surface))
			return false;
		applySurface(0, 0, chessGrid, surface,
				&(SDL_Rect ) { 77, 223, 40, 40 });
		ctl = buildButton(200, 20, surface, &(SDL_Rect ) { 77, 223, 40, 40 },
				changeSoldier, NULL, 'Q');
		if (!insertTail(panel_son->control->sons, createNode(ctl)))
			return false;
	}
	return true;
}

bool restart(int param, Node *UI_Tree, char board[SQR][SQR]) {
	bool flag = false;
	initial_board(board);
	freeUITREE(*UI_Tree);
	SDL_FreeSurface(screen);

	screen = SDL_GetWindowSurface(window);

	*UI_Tree = createNode(
			buildWindow(0, 0, WIN_W, WIN_H, defaultBG,
					createLL()));
	createBoardBranch(board, *UI_Tree);
	createSideMenu(*UI_Tree);
	game_active = true;
	currentColor = WHITE;
	flag = paindUpdateWindow(*UI_Tree);

	return flag;
}

void clearBoard() {
	int i, j;
	for (i = 0; i < SQR; i++)
		for (j = 0; j < SQR; j++)
			if (board[i][j] == 'H')
				board[i][j] = copy[i][j];
}

void clearSurfaces(Node *R) {
	int i, j, x, y;
	Node button;
	SDL_Rect source_white = { 20, 11, BOARDSQUARE, BOARDSQUARE };
	SDL_Rect source_black = { 73, 67, BOARDSQUARE, BOARDSQUARE };
	for (i = 0; i < SQR; i++) {
		for (j = 0; j < SQR; j++) {
			y = (SQR - 1 - i) * BOARDSQUARE + 2;
			x = (j) * BOARDSQUARE + MENU_WIDTH + 2;
			locateClick1(x, y, *R, &button);
			applySurface(0, 0, (i + j) % 2 ? whiteBoard : blackBoard, button->control->surface,
					(i + j) % 2 ? &source_white : &source_black);
		}
	}


}

int countAll(char board [SQR][SQR]){
	int counter = 0;
	int i,j;
	for(i = 0 ; i < SQR; i++)
		for(j = 0; j < SQR; j++)
			if(board[i][j] != '_' && board[i][j] != 'H')
				counter++;
	return counter;
}
