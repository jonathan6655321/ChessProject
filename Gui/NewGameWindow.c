#include "NewGameWindow.h"

NewGameWindowElement ClickWasOnNewGameWindow(int x, int y) {
	if (PointInsideRectangle(x, y, whiteUserColorButtonNewGameWindowRectangle))
		return WhiteUserColorNewGameWindowButtonElement;
	else if (PointInsideRectangle(x, y, startNewGameButtonNewGameWindowRectangle))
		return StartNewGameNewGameWindowButtonElement;
	else if (PointInsideRectangle(x, y, blackUserColorButtonNewGameWindowRectangle))
		return BlackUserColorModeNewGameWindowButtonElement;
	else if (PointInsideRectangle(x, y, onePlayerGameModeButtonNewGameWindowRectangle))
		return OnePlayerGameModeNewGameWindowButtonElement;
	else if (PointInsideRectangle(x, y, twoPlayerGameModeButtonNewGameWindowRectangle))
		return TwoPlayerGameModeNewGameWindowButtonElement;
	else if (PointInsideRectangle(x, y, noobDifficultyModeNewGameWindowRectangle))
		return NoobDifficultyModeNewGameWindowButtonElement;
	else if (PointInsideRectangle(x, y, easyDifficultyModeNewGameWindowRectangle))
		return EasyDifficultyModeNewGameWindowButtonElement;
	else if (PointInsideRectangle(x, y, modarateDifficultyModeNewGameWindowRectangle))
		return ModerateDifficultyModeNewGameWindowButtonElement;
	else if (PointInsideRectangle(x, y, hardDifficultyModeNewGameWindowRectangle))
		return HardDifficultyModeNewGameWindowButtonElement;
	else if (PointInsideRectangle(x, y, expertDifficultyModeNewGameWindowRectangle))
		return ExpertDifficultyModeNewGameWindowButtonElement;
	else if (PointInsideRectangle(x, y, backButtonNewGameWindowRectangle))
		return BackButtonNewGameWindowElement;
	else
		return BackgroundNewGameWindowElement;
}

void CreateNewGameWindow(NewGameWindow* src) {
	// Create an application window with the following settings:
	src->newGameWindow = SDL_CreateWindow("Create New Game", // window title
		SDL_WINDOWPOS_CENTERED,			// initial x position
		SDL_WINDOWPOS_CENTERED,			// initial y position
		backgroundNewGameWindowRectangle[1],		// width, in pixels
		backgroundNewGameWindowRectangle[3],		// height, in pixels
		SDL_WINDOW_OPENGL				// TODO: what is this
	);
}

NewGameWindow* NewGameWindowCreate() {
	NewGameWindow* newNewGameWindow = (NewGameWindow*)calloc(sizeof(NewGameWindow), sizeof(char));

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

	newNewGameWindow->newGameRenderer = SDL_CreateRenderer(newNewGameWindow->newGameWindow, -1, SDL_RENDERER_ACCELERATED);
	// Check that the window renerer was created
	if (newNewGameWindow->newGameRenderer == NULL) {
		NewGameWindowDestroy(newNewGameWindow);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL;
	}

	int success = 1;
	success &= LoadTexture(&(newNewGameWindow->startNewGameButtonTexture), 		newNewGameWindow->newGameRenderer, START_NEW_GAME_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->whiteButtonTexture), 		newNewGameWindow->newGameRenderer, WHITE_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->whiteButtonPressedTexture), 		newNewGameWindow->newGameRenderer, WHITE_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->blackButtonTexture), 		newNewGameWindow->newGameRenderer, BLACK_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->blackButtonPressedTexture), 		newNewGameWindow->newGameRenderer, BLACK_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->onePlayerButtonTexture), 	newNewGameWindow->newGameRenderer, ONE_PLAYER_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->onePlayerButtonPressedTexture), 	newNewGameWindow->newGameRenderer, ONE_PLAYER_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->twoPlayerButtonTexture), 	newNewGameWindow->newGameRenderer, TWO_PLAYER_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->twoPlayerButtonPressedTexture), 	newNewGameWindow->newGameRenderer, TWO_PLAYER_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->noobDifficultyButtonTexture), 	newNewGameWindow->newGameRenderer, NOOB_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->noobDifficultyButtonPressedTexture), 	newNewGameWindow->newGameRenderer, NOOB_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->easyDifficultyButtonTexture), 	newNewGameWindow->newGameRenderer, EASY_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->easyDifficultyButtonPressedTexture), 	newNewGameWindow->newGameRenderer, EASY_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->moderateDifficultyButtonTexture), 	newNewGameWindow->newGameRenderer, MODERATE_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->moderateDifficultyButtonPressedTexture), 	newNewGameWindow->newGameRenderer, MODERATE_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->hardDifficultyButtonTexture), 	newNewGameWindow->newGameRenderer, HARD_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->hardDifficultyButtonPressedTexture), 	newNewGameWindow->newGameRenderer, HARD_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->expertDifficultyButtonTexture), 	newNewGameWindow->newGameRenderer, EXPERT_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->expertDifficultyButtonPressedTexture), 	newNewGameWindow->newGameRenderer, EXPERT_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->backButtonTexture), 	newNewGameWindow->newGameRenderer, BACK_NEW_GAME_WINDOW_TEXTURE_PATH);
	success &= LoadTexture(&(newNewGameWindow->backgroundTexture), 	newNewGameWindow->newGameRenderer, BACKGROUND_NEW_GAME_WINDOW_TEXTURE_PATH);
	
	if (!success) {
		NewGameWindowDestroy(newNewGameWindow);
		return NULL;
	}

	newNewGameWindow->gameMode = 1;
	newNewGameWindow->difficulty = 2;
	newNewGameWindow->userColor = 1;

	return newNewGameWindow;
}

void NewGameWindowDestroy(NewGameWindow* src) {
	if (src->backgroundTexture != NULL)
		SDL_DestroyTexture(src->backgroundTexture);
	if (src->startNewGameButtonTexture != NULL)
		SDL_DestroyTexture(src->startNewGameButtonTexture);
	if (src->whiteButtonTexture != NULL)
		SDL_DestroyTexture(src->whiteButtonTexture);
	if (src->blackButtonTexture != NULL)
		SDL_DestroyTexture(src->blackButtonTexture);
	if (src->onePlayerButtonTexture != NULL)
		SDL_DestroyTexture(src->onePlayerButtonTexture);
	if (src->twoPlayerButtonTexture != NULL)
		SDL_DestroyTexture(src->twoPlayerButtonTexture);
	if (src->noobDifficultyButtonTexture != NULL)
		SDL_DestroyTexture(src->noobDifficultyButtonTexture);
	if (src->easyDifficultyButtonTexture != NULL)
		SDL_DestroyTexture(src->easyDifficultyButtonTexture);
	if (src->moderateDifficultyButtonTexture != NULL)
		SDL_DestroyTexture(src->moderateDifficultyButtonTexture);
	if (src->hardDifficultyButtonTexture != NULL)
		SDL_DestroyTexture(src->hardDifficultyButtonTexture);
	if (src->expertDifficultyButtonTexture != NULL)
		SDL_DestroyTexture(src->expertDifficultyButtonTexture);
	if (src->backButtonTexture != NULL)
		SDL_DestroyTexture(src->backButtonTexture);
	if (src->newGameRenderer != NULL)
		SDL_DestroyRenderer(src->newGameRenderer);
	if (src->newGameWindow != NULL)
		SDL_DestroyWindow(src->newGameWindow);
	free(src);
}

void NewGameWindowDraw(NewGameWindow* src) {
	SDL_Rect startGameR = CreateSDLRectFromIntArray(startNewGameButtonNewGameWindowRectangle);
	SDL_Rect whiteR = CreateSDLRectFromIntArray(whiteUserColorButtonNewGameWindowRectangle);
	SDL_Rect blackR = CreateSDLRectFromIntArray(blackUserColorButtonNewGameWindowRectangle);
	SDL_Rect oneR = CreateSDLRectFromIntArray(onePlayerGameModeButtonNewGameWindowRectangle);
	SDL_Rect twoR = CreateSDLRectFromIntArray(twoPlayerGameModeButtonNewGameWindowRectangle);
	SDL_Rect noobR = CreateSDLRectFromIntArray(noobDifficultyModeNewGameWindowRectangle);
	SDL_Rect easyR = CreateSDLRectFromIntArray(easyDifficultyModeNewGameWindowRectangle);
	SDL_Rect moderateR = CreateSDLRectFromIntArray(modarateDifficultyModeNewGameWindowRectangle);
	SDL_Rect hardR = CreateSDLRectFromIntArray(hardDifficultyModeNewGameWindowRectangle);
	SDL_Rect expertR = CreateSDLRectFromIntArray(expertDifficultyModeNewGameWindowRectangle);
	SDL_Rect backR = CreateSDLRectFromIntArray(backButtonNewGameWindowRectangle);
	SDL_Rect backgroundR = CreateSDLRectFromIntArray(backgroundNewGameWindowRectangle);
	SDL_SetRenderDrawColor(src->newGameRenderer, 255, 255, 255, 255);

	
	SDL_RenderClear(src->newGameRenderer);
	if(src->gameMode == 1){
		SDL_RenderCopy(src->newGameRenderer, src->onePlayerButtonPressedTexture, NULL, &oneR);
		SDL_RenderCopy(src->newGameRenderer, src->twoPlayerButtonTexture, NULL, &twoR);
		
		if(src->userColor == 1){
			SDL_RenderCopy(src->newGameRenderer, src->whiteButtonPressedTexture, NULL, &whiteR);
			SDL_RenderCopy(src->newGameRenderer, src->blackButtonTexture, NULL, &blackR);
		}else{
			SDL_RenderCopy(src->newGameRenderer, src->whiteButtonTexture, NULL, &whiteR);
			SDL_RenderCopy(src->newGameRenderer, src->blackButtonPressedTexture, NULL, &blackR);
		}
		SDL_RenderCopy(src->newGameRenderer, src->noobDifficultyButtonTexture, NULL, &noobR);
		SDL_RenderCopy(src->newGameRenderer, src->easyDifficultyButtonTexture, NULL, &easyR);
		SDL_RenderCopy(src->newGameRenderer, src->moderateDifficultyButtonTexture, NULL, &moderateR);
		SDL_RenderCopy(src->newGameRenderer, src->hardDifficultyButtonTexture, NULL, &hardR);
		SDL_RenderCopy(src->newGameRenderer, src->expertDifficultyButtonTexture, NULL, &expertR);
	}else{
		SDL_RenderCopy(src->newGameRenderer, src->onePlayerButtonTexture, NULL, &oneR);
		SDL_RenderCopy(src->newGameRenderer, src->twoPlayerButtonPressedTexture, NULL, &twoR);
	}
	
	
	SDL_RenderCopy(src->newGameRenderer, src->startNewGameButtonTexture, NULL, &startGameR);
	SDL_RenderCopy(src->newGameRenderer, src->backButtonTexture, NULL, &backR);
	SDL_RenderCopy(src->newGameRenderer, src->backgroundTexture, NULL, &backgroundR);
	SDL_RenderPresent(src->newGameRenderer);
}

void NewGameWindowHide(NewGameWindow* src) {
	SDL_HideWindow(src->newGameWindow);
}

void NewGameWindowShow(NewGameWindow* src) {
	SDL_ShowWindow(src->newGameWindow);
}

EventStruct NewGameWindowHandleEvent(NewGameWindow* src, SDL_Event* event) {
	EventStruct eventStruct = { EmptyEvent,{0} };
	if (event == NULL) {
		return eventStruct;
	}

	
	switch (ClickWasOnMainWindow(event->button.x, event->button.y)) {
	case StartNewGameNewGameWindowButtonElement:
		eventStruct.eventType = StartGameButtonNewGameWindowClickEvent;
		eventStruct.eventArgument[0] = src->gameMode;
		eventStruct.eventArgument[1] = src->difficulty;
		eventStruct.eventArgument[2] = src->userColor;
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
		eventStruct.eventType = BackButtonNewGameWindowClickEvent;
		break;
	default:
		break;
	}
	return eventStruct;
}
