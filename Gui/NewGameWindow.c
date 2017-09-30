#include "NewGameWindow.h"
// the new game windows element locations:
static int onePlayerGameModeButtonNewGameWindowRectangle[4] = { 120, 280, 50,
		150 };
static int twoPlayerGameModeButtonNewGameWindowRectangle[4] = { 120, 280, 200,
		300 };
static int whiteUserColorButtonNewGameWindowRectangle[4] =
		{ 150, 250, 50, 150 };
static int blackUserColorButtonNewGameWindowRectangle[4] =
		{ 150, 250, 200, 300 };
static int noobDifficultyModeNewGameWindowRectangle[4] = { 120, 280, 50, 100 };
static int easyDifficultyModeNewGameWindowRectangle[4] = { 120, 280, 110, 160 };
static int modarateDifficultyModeNewGameWindowRectangle[4] = { 120, 280, 170,
		230 };
static int hardDifficultyModeNewGameWindowRectangle[4] = { 120, 280, 240, 290 };
static int expertDifficultyModeNewGameWindowRectangle[4] =
		{ 120, 280, 300, 350 };
static int backButtonNewGameWindowRectangle[4] = { 50, 175, 380, 430 };
static int startNewGameButtonNewGameWindowRectangle[4] = { 225, 350, 380, 430 };
static int backgroundNewGameWindowRectangle[4] = { 0, 400, 0, 450 };

// check on which element the click was on.
NewGameWindowElement ClickWasOnNewGameWindow(NewGameWindow *src, int x, int y) {
	if (PointInsideRectangle(x, y, startNewGameButtonNewGameWindowRectangle))
		return NextStartNewGameNewGameWindowButtonElement;
	if (PointInsideRectangle(x, y, backButtonNewGameWindowRectangle))
		return BackButtonNewGameWindowElement;

	switch (src->state) {
	case GameModeNewGameWindowState:
		if (PointInsideRectangle(x, y,
				onePlayerGameModeButtonNewGameWindowRectangle))
			return OnePlayerGameModeNewGameWindowButtonElement;
		if (PointInsideRectangle(x, y,
				twoPlayerGameModeButtonNewGameWindowRectangle))
			return TwoPlayerGameModeNewGameWindowButtonElement;
		break;
	case DifficultyNewGameWindowState:
		if (PointInsideRectangle(x, y, noobDifficultyModeNewGameWindowRectangle))
			return NoobDifficultyModeNewGameWindowButtonElement;
		else if (PointInsideRectangle(x, y,
				easyDifficultyModeNewGameWindowRectangle))
			return EasyDifficultyModeNewGameWindowButtonElement;
		else if (PointInsideRectangle(x, y,
				modarateDifficultyModeNewGameWindowRectangle))
			return ModerateDifficultyModeNewGameWindowButtonElement;
		else if (PointInsideRectangle(x, y,
				hardDifficultyModeNewGameWindowRectangle))
			return HardDifficultyModeNewGameWindowButtonElement;
		else if (PointInsideRectangle(x, y,
				expertDifficultyModeNewGameWindowRectangle))
			return ExpertDifficultyModeNewGameWindowButtonElement;
		break;
	case PlayerColorNewGameWindowState:
		if (PointInsideRectangle(x, y,
				whiteUserColorButtonNewGameWindowRectangle))
			return WhiteUserColorNewGameWindowButtonElement;
		if (PointInsideRectangle(x, y,
				blackUserColorButtonNewGameWindowRectangle))
			return BlackUserColorModeNewGameWindowButtonElement;
		break;
	}

	return BackgroundNewGameWindowElement;
}

// create the new game window's window
void CreateNewGameWindow(NewGameWindow *src) {
	// Create an application window with the following settings:
	src->newGameWindow = SDL_CreateWindow("Create New Game", // window title
			SDL_WINDOWPOS_CENTERED, // initial x position
			SDL_WINDOWPOS_CENTERED, // initial y position
			backgroundNewGameWindowRectangle[1], // width, in pixels
			backgroundNewGameWindowRectangle[3], // height, in pixels
			SDL_WINDOW_OPENGL);
}

NewGameWindow *NewGameWindowCreate() {
	NewGameWindow *newNewGameWindow = (NewGameWindow *) calloc(
			sizeof(NewGameWindow), sizeof(char));

	if (newNewGameWindow == NULL) {
		printf("malloc: Error\n");
		return NULL;
	}

	CreateNewGameWindow(newNewGameWindow);
	// Check that the window was successfully created
	if (newNewGameWindow->newGameWindow == NULL) {
		NewGameWindowDestroy(newNewGameWindow);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL;
	}

	int success = 1;
	success &= LoadSurface(&(newNewGameWindow->startNewGameButtonSurface),
			START_NEW_GAME_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(&(newNewGameWindow->nextButtonSurface),
			NEXT_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(&(newNewGameWindow->whiteButtonSurface),
			WHITE_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(&(newNewGameWindow->whiteButtonPressedSurface),
			WHITE_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
	success &= LoadSurface(&(newNewGameWindow->blackButtonSurface),
			BLACK_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(&(newNewGameWindow->blackButtonPressedSurface),
			BLACK_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
	success &= LoadSurface(&(newNewGameWindow->onePlayerButtonSurface),
			ONE_PLAYER_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(&(newNewGameWindow->onePlayerButtonPressedSurface),
			ONE_PLAYER_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
	success &= LoadSurface(&(newNewGameWindow->twoPlayerButtonSurface),
			TWO_PLAYER_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(&(newNewGameWindow->twoPlayerButtonPressedSurface),
			TWO_PLAYER_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
	success &= LoadSurface(&(newNewGameWindow->noobDifficultyButtonSurface),
			NOOB_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(
			&(newNewGameWindow->noobDifficultyButtonPressedSurface),
			NOOB_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
	success &= LoadSurface(&(newNewGameWindow->easyDifficultyButtonSurface),
			EASY_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(
			&(newNewGameWindow->easyDifficultyButtonPressedSurface),
			EASY_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
	success &= LoadSurface(
			&(newNewGameWindow->moderateDifficultyButtonSurface),
			MODERATE_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(
			&(newNewGameWindow->moderateDifficultyButtonPressedSurface),
			MODERATE_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
	success &= LoadSurface(&(newNewGameWindow->hardDifficultyButtonSurface),
			HARD_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(
			&(newNewGameWindow->hardDifficultyButtonPressedSurface),

			HARD_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
	success &= LoadSurface(&(newNewGameWindow->expertDifficultyButtonSurface),

	EXPERT_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(
			&(newNewGameWindow->expertDifficultyButtonPressedSurface),
			EXPERT_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
	success &= LoadSurface(&(newNewGameWindow->backButtonSurface),
			BACK_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(
			&(newNewGameWindow->backgroundSurfaceChoosingGameMode),
			BACKGROUND_GAME_MODE_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(
			&(newNewGameWindow->backgroundSurfaceChoosingDifficulty),
			BACKGROUND_DIFFICULTY_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadSurface(
			&(newNewGameWindow->backgroundSurfaceChoosingUserColor),
			BACKGROUND_USER_COLOR_NEW_GAME_WINDOW_TEXTURE_PATH);

	if (!success) {
		NewGameWindowDestroy(newNewGameWindow);
		return NULL;
	}

	newNewGameWindow->state = GameModeNewGameWindowState;

	newNewGameWindow->gameMode = 1;
	newNewGameWindow->difficulty = 2;
	newNewGameWindow->userColor = 1;

	return newNewGameWindow;
}

void NewGameWindowDestroy(NewGameWindow *src) {
	if (src->backgroundSurfaceChoosingGameMode != NULL)
		SDL_FreeSurface(src->backgroundSurfaceChoosingGameMode);
	if (src->backgroundSurfaceChoosingDifficulty != NULL)
		SDL_FreeSurface(src->backgroundSurfaceChoosingDifficulty);
	if (src->backgroundSurfaceChoosingUserColor != NULL)
		SDL_FreeSurface(src->backgroundSurfaceChoosingUserColor);
	if (src->nextButtonSurface != NULL)
		SDL_FreeSurface(src->nextButtonSurface);
	if (src->startNewGameButtonSurface != NULL)
		SDL_FreeSurface(src->startNewGameButtonSurface);
	if (src->whiteButtonSurface != NULL)
		SDL_FreeSurface(src->whiteButtonSurface);
	if (src->whiteButtonPressedSurface != NULL)
		SDL_FreeSurface(src->whiteButtonPressedSurface);
	if (src->blackButtonSurface != NULL)
		SDL_FreeSurface(src->blackButtonSurface);
	if (src->blackButtonPressedSurface != NULL)
		SDL_FreeSurface(src->blackButtonPressedSurface);
	if (src->onePlayerButtonSurface != NULL)
		SDL_FreeSurface(src->onePlayerButtonSurface);
	if (src->onePlayerButtonPressedSurface != NULL)
		SDL_FreeSurface(src->onePlayerButtonPressedSurface);
	if (src->twoPlayerButtonSurface != NULL)
		SDL_FreeSurface(src->twoPlayerButtonSurface);
	if (src->twoPlayerButtonPressedSurface != NULL)
		SDL_FreeSurface(src->twoPlayerButtonPressedSurface);
	if (src->noobDifficultyButtonSurface != NULL)
		SDL_FreeSurface(src->noobDifficultyButtonSurface);
	if (src->noobDifficultyButtonPressedSurface != NULL)
		SDL_FreeSurface(src->noobDifficultyButtonPressedSurface);
	if (src->easyDifficultyButtonSurface != NULL)
		SDL_FreeSurface(src->easyDifficultyButtonSurface);
	if (src->easyDifficultyButtonPressedSurface != NULL)
		SDL_FreeSurface(src->easyDifficultyButtonPressedSurface);
	if (src->moderateDifficultyButtonSurface != NULL)
		SDL_FreeSurface(src->moderateDifficultyButtonSurface);
	if (src->moderateDifficultyButtonPressedSurface != NULL)
		SDL_FreeSurface(src->moderateDifficultyButtonPressedSurface);
	if (src->hardDifficultyButtonSurface != NULL)
		SDL_FreeSurface(src->hardDifficultyButtonSurface);
	if (src->hardDifficultyButtonPressedSurface != NULL)
		SDL_FreeSurface(src->hardDifficultyButtonPressedSurface);
	if (src->expertDifficultyButtonSurface != NULL)
		SDL_FreeSurface(src->expertDifficultyButtonSurface);
	if (src->expertDifficultyButtonPressedSurface != NULL)
		SDL_FreeSurface(src->expertDifficultyButtonPressedSurface);
	if (src->backButtonSurface != NULL)
		SDL_FreeSurface(src->backButtonSurface);
	if (src->backButtonPressedSurface != NULL)
		SDL_FreeSurface(src->backButtonPressedSurface);
	if (src->newGameWindow != NULL)
		SDL_DestroyWindow(src->newGameWindow);
	free(src);
}

// draw new game windows in difficulty choosing state.
void NewGameWindowDrawDifficultyWindow(NewGameWindow *src) {
	SDL_Rect nextR = CreateSDLRectFromIntArray(
			startNewGameButtonNewGameWindowRectangle);
	SDL_Rect backR =
			CreateSDLRectFromIntArray(backButtonNewGameWindowRectangle);
	SDL_Rect noobR = CreateSDLRectFromIntArray(
			noobDifficultyModeNewGameWindowRectangle);
	SDL_Rect easyR = CreateSDLRectFromIntArray(
			easyDifficultyModeNewGameWindowRectangle);
	SDL_Rect moderateR = CreateSDLRectFromIntArray(
			modarateDifficultyModeNewGameWindowRectangle);
	SDL_Rect hardR = CreateSDLRectFromIntArray(
			hardDifficultyModeNewGameWindowRectangle);
	SDL_Rect expertR = CreateSDLRectFromIntArray(
			expertDifficultyModeNewGameWindowRectangle);
	SDL_Rect backgroundR = CreateSDLRectFromIntArray(
			backgroundNewGameWindowRectangle);

	SDL_Surface* screen = SDL_GetWindowSurface(src->newGameWindow);

	SDL_BlitScaled(src->backgroundSurfaceChoosingDifficulty, NULL, screen,
			&backgroundR);
	if (src->difficulty != 1) {
		SDL_BlitScaled(src->noobDifficultyButtonSurface, NULL, screen, &noobR);
	} else {
		SDL_BlitScaled(src->noobDifficultyButtonPressedSurface, NULL, screen,
				&noobR);
	}
	if (src->difficulty != 2) {
		SDL_BlitScaled(src->easyDifficultyButtonSurface, NULL, screen, &easyR);
	} else {
		SDL_BlitScaled(src->easyDifficultyButtonPressedSurface, NULL, screen,
				&easyR);
	}
	if (src->difficulty != 3) {
		SDL_BlitScaled(src->moderateDifficultyButtonSurface, NULL, screen,
				&moderateR);
	} else {
		SDL_BlitScaled(src->moderateDifficultyButtonPressedSurface, NULL,
				screen, &moderateR);
	}
	if (src->difficulty != 4) {
		SDL_BlitScaled(src->hardDifficultyButtonSurface, NULL, screen, &hardR);
	} else {
		SDL_BlitScaled(src->hardDifficultyButtonPressedSurface, NULL, screen,
				&hardR);
	}
	if (src->difficulty != 5) {
		SDL_BlitScaled(src->expertDifficultyButtonSurface, NULL, screen,
				&expertR);
	} else {
		SDL_BlitScaled(src->expertDifficultyButtonPressedSurface, screen, NULL,
				&expertR);
	}
	SDL_BlitScaled(src->nextButtonSurface, NULL, screen, &nextR);
	SDL_BlitScaled(src->backButtonSurface, NULL, screen, &backR);
	SDL_UpdateWindowSurface(src->newGameWindow);
	SDL_FreeSurface(screen);
}

// draws new game windows in game mode choosing state.
void NewGameWindowDrawGameModeWindow(NewGameWindow *src) {
	SDL_Rect startGameNextR = CreateSDLRectFromIntArray(
			startNewGameButtonNewGameWindowRectangle);
	SDL_Rect oneR = CreateSDLRectFromIntArray(
			onePlayerGameModeButtonNewGameWindowRectangle);
	SDL_Rect twoR = CreateSDLRectFromIntArray(
			twoPlayerGameModeButtonNewGameWindowRectangle);
	SDL_Rect backR =
			CreateSDLRectFromIntArray(backButtonNewGameWindowRectangle);
	SDL_Rect backgroundR = CreateSDLRectFromIntArray(
			backgroundNewGameWindowRectangle);

	SDL_Surface* screen = SDL_GetWindowSurface(src->newGameWindow);

	SDL_BlitScaled(src->backgroundSurfaceChoosingGameMode, NULL, screen,
			&backgroundR);
	if (src->gameMode == 1) {
		SDL_BlitScaled(src->onePlayerButtonPressedSurface, NULL, screen, &oneR);
		SDL_BlitScaled(src->twoPlayerButtonSurface, NULL, screen, &twoR);
		SDL_BlitScaled(src->nextButtonSurface, NULL, screen, &startGameNextR);
	} else {
		SDL_BlitScaled(src->onePlayerButtonSurface, NULL, screen, &oneR);
		SDL_BlitScaled(src->twoPlayerButtonPressedSurface, NULL, screen, &twoR);
		SDL_BlitScaled(src->startNewGameButtonSurface, NULL, screen,
				&startGameNextR);
	}
	SDL_BlitScaled(src->backButtonSurface, NULL, screen, &backR);
	SDL_UpdateWindowSurface(src->newGameWindow);
	SDL_FreeSurface(screen);
}

// draws new game windows in user color choosing state.
void NewGameWindowDrawUserColorWindow(NewGameWindow *src) {
	SDL_Rect startGameR = CreateSDLRectFromIntArray(
			startNewGameButtonNewGameWindowRectangle);
	SDL_Rect backR =
			CreateSDLRectFromIntArray(backButtonNewGameWindowRectangle);
	SDL_Rect whiteR = CreateSDLRectFromIntArray(
			whiteUserColorButtonNewGameWindowRectangle);
	SDL_Rect blackR = CreateSDLRectFromIntArray(
			blackUserColorButtonNewGameWindowRectangle);
	SDL_Rect backgroundR = CreateSDLRectFromIntArray(
			backgroundNewGameWindowRectangle);

	SDL_Surface* screen = SDL_GetWindowSurface(src->newGameWindow);

	SDL_BlitScaled(src->backgroundSurfaceChoosingUserColor, NULL, screen,
			&backgroundR);
	if (src->userColor == 1) {
		SDL_BlitScaled(src->whiteButtonPressedSurface, NULL, screen, &whiteR);
		SDL_BlitScaled(src->blackButtonSurface, NULL, screen, &blackR);
	} else {
		SDL_BlitScaled(src->whiteButtonSurface, NULL, screen, &whiteR);
		SDL_BlitScaled(src->blackButtonPressedSurface, screen, NULL, &blackR);
	}
	SDL_BlitScaled(src->startNewGameButtonSurface, NULL, screen, &startGameR);
	SDL_BlitScaled(src->backButtonSurface, NULL, screen, &backR);
	SDL_UpdateWindowSurface(src->newGameWindow);
	SDL_FreeSurface(screen);
}

void NewGameWindowDraw(NewGameWindow *src) {
	switch (src->state) {
	case GameModeNewGameWindowState:
		NewGameWindowDrawGameModeWindow(src);
		break;
	case DifficultyNewGameWindowState:
		NewGameWindowDrawDifficultyWindow(src);
		break;
	case PlayerColorNewGameWindowState:
		NewGameWindowDrawUserColorWindow(src);
		break;
	}
}

void NewGameWindowHide(NewGameWindow *src) {
	SDL_HideWindow(src->newGameWindow);
}

void NewGameWindowShow(NewGameWindow *src) {
	SDL_ShowWindow(src->newGameWindow);
}

EventStruct NewGameWindowHandleEvent(NewGameWindow *src, SDL_Event *event) {
	EventStruct eventStruct = { EmptyEvent, { 0 } };
	if (event == NULL) {
		return eventStruct;
	}

	switch (ClickWasOnNewGameWindow(src, event->button.x, event->button.y)) {
	case NextStartNewGameNewGameWindowButtonElement:
		switch (src->state) {
		case GameModeNewGameWindowState:
			if (src->gameMode == 2) {
				eventStruct.eventType = StartGameButtonNewGameWindowClickEvent;
				eventStruct.eventArgument[0] = src->gameMode;
			} else {
				src->state = DifficultyNewGameWindowState;
			}
			break;
		case DifficultyNewGameWindowState:
			src->state = PlayerColorNewGameWindowState;
			break;
		case PlayerColorNewGameWindowState:
			eventStruct.eventType = StartGameButtonNewGameWindowClickEvent;
			eventStruct.eventArgument[0] = src->gameMode;
			eventStruct.eventArgument[1] = src->difficulty;
			eventStruct.eventArgument[2] = src->userColor;
			break;
		}
		break;
	case WhiteUserColorNewGameWindowButtonElement:
		src->userColor = 1;
		break;
	case BlackUserColorModeNewGameWindowButtonElement:
		src->userColor = 0;
		break;
	case OnePlayerGameModeNewGameWindowButtonElement:
		src->gameMode = 1;
		break;
	case TwoPlayerGameModeNewGameWindowButtonElement:
		src->gameMode = 2;
		break;
	case NoobDifficultyModeNewGameWindowButtonElement:
		src->difficulty = 1;
		break;
	case EasyDifficultyModeNewGameWindowButtonElement:
		src->difficulty = 2;
		break;
	case ModerateDifficultyModeNewGameWindowButtonElement:
		src->difficulty = 3;
		break;
	case HardDifficultyModeNewGameWindowButtonElement:
		src->difficulty = 4;
		break;
	case ExpertDifficultyModeNewGameWindowButtonElement:
		src->difficulty = 5;
		break;
	case BackButtonNewGameWindowElement:
		switch (src->state) {
		case GameModeNewGameWindowState:
			eventStruct.eventType = BackButtonNewGameWindowClickEvent;
			break;
		case DifficultyNewGameWindowState:
			src->state = GameModeNewGameWindowState;
			break;
		case PlayerColorNewGameWindowState:
			src->state = DifficultyNewGameWindowState;
			break;
		}
		break;
	default:
		break;
	}
	return eventStruct;
}
