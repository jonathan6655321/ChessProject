#include "NewGameWindow.h"
// the new game windows element locations:
static int onePlayerGameModeButtonNewGameWindowRectangle[4] = {120, 280, 50, 150};
static int twoPlayerGameModeButtonNewGameWindowRectangle[4] = {120, 280, 200, 300};
static int whiteUserColorButtonNewGameWindowRectangle[4] = {150, 250, 50, 150};
static int blackUserColorButtonNewGameWindowRectangle[4] = {150, 250, 200, 300};
static int noobDifficultyModeNewGameWindowRectangle[4] = {120, 280, 50, 100};
static int easyDifficultyModeNewGameWindowRectangle[4] = {120, 280, 110, 160};
static int modarateDifficultyModeNewGameWindowRectangle[4] = {120, 280, 170, 230};
static int hardDifficultyModeNewGameWindowRectangle[4] = {120, 280, 240, 290};
static int expertDifficultyModeNewGameWindowRectangle[4] = {120, 280, 300, 350};
static int backButtonNewGameWindowRectangle[4] = {50, 175, 380, 430};
static int startNewGameButtonNewGameWindowRectangle[4] = {225, 350, 380, 430};
static int backgroundNewGameWindowRectangle[4] = {0, 400, 0, 450};

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

    newNewGameWindow->newGameRenderer = SDL_CreateRenderer(
            newNewGameWindow->newGameWindow, -1, SDL_RENDERER_ACCELERATED);
    // Check that the window renerer was created
    if (newNewGameWindow->newGameRenderer == NULL) {
        NewGameWindowDestroy(newNewGameWindow);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }

    int success = 1;
    success &= LoadTexture(&(newNewGameWindow->startNewGameButtonTexture),
                           newNewGameWindow->newGameRenderer,
                           START_NEW_GAME_NEW_GAME_WINDOW_TEXTURE_PATH);
    success &= LoadTexture(&(newNewGameWindow->nextButtonTexture),
                           newNewGameWindow->newGameRenderer,
                           NEXT_NEW_GAME_WINDOW_TEXTURE_PATH);
    success &= LoadTexture(&(newNewGameWindow->whiteButtonTexture),
                           newNewGameWindow->newGameRenderer,
                           WHITE_NEW_GAME_WINDOW_TEXTURE_PATH);
    success &= LoadTexture(&(newNewGameWindow->whiteButtonPressedTexture),
                           newNewGameWindow->newGameRenderer,
                           WHITE_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
    success &= LoadTexture(&(newNewGameWindow->blackButtonTexture),
                           newNewGameWindow->newGameRenderer,
                           BLACK_NEW_GAME_WINDOW_TEXTURE_PATH);
    success &= LoadTexture(&(newNewGameWindow->blackButtonPressedTexture),
                           newNewGameWindow->newGameRenderer,
                           BLACK_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
    success &= LoadTexture(&(newNewGameWindow->onePlayerButtonTexture),
                           newNewGameWindow->newGameRenderer,
                           ONE_PLAYER_NEW_GAME_WINDOW_TEXTURE_PATH);
    success &= LoadTexture(&(newNewGameWindow->onePlayerButtonPressedTexture),
                           newNewGameWindow->newGameRenderer,
                           ONE_PLAYER_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
    success &= LoadTexture(&(newNewGameWindow->twoPlayerButtonTexture),
                           newNewGameWindow->newGameRenderer,
                           TWO_PLAYER_NEW_GAME_WINDOW_TEXTURE_PATH);
    success &= LoadTexture(&(newNewGameWindow->twoPlayerButtonPressedTexture),
                           newNewGameWindow->newGameRenderer,
                           TWO_PLAYER_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
    success &= LoadTexture(&(newNewGameWindow->noobDifficultyButtonTexture),
                           newNewGameWindow->newGameRenderer,
                           NOOB_NEW_GAME_WINDOW_TEXTURE_PATH);
    success &= LoadTexture(
            &(newNewGameWindow->noobDifficultyButtonPressedTexture),
            newNewGameWindow->newGameRenderer,
            NOOB_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
    success &= LoadTexture(&(newNewGameWindow->easyDifficultyButtonTexture),
                           newNewGameWindow->newGameRenderer,
                           EASY_NEW_GAME_WINDOW_TEXTURE_PATH);
    success &= LoadTexture(
            &(newNewGameWindow->easyDifficultyButtonPressedTexture),
            newNewGameWindow->newGameRenderer,
            EASY_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
    success &= LoadTexture(
            &(newNewGameWindow->moderateDifficultyButtonTexture),
            newNewGameWindow->newGameRenderer,
            MODERATE_NEW_GAME_WINDOW_TEXTURE_PATH);
    success &= LoadTexture(
            &(newNewGameWindow->moderateDifficultyButtonPressedTexture),
            newNewGameWindow->newGameRenderer,
            MODERATE_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
    success &= LoadTexture(&(newNewGameWindow->hardDifficultyButtonTexture),
                           newNewGameWindow->newGameRenderer,
                           HARD_NEW_GAME_WINDOW_TEXTURE_PATH);
    success &= LoadTexture(
            &(newNewGameWindow->hardDifficultyButtonPressedTexture),
            newNewGameWindow->newGameRenderer,
            HARD_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
    success &= LoadTexture(&(newNewGameWindow->expertDifficultyButtonTexture),
                           newNewGameWindow->newGameRenderer,
                           EXPERT_NEW_GAME_WINDOW_TEXTURE_PATH);
    success &= LoadTexture(
            &(newNewGameWindow->expertDifficultyButtonPressedTexture),
            newNewGameWindow->newGameRenderer,
            EXPERT_NEW_GAME_WINDOW_PRESSED_TEXTURE_PATH);
    success &= LoadTexture(&(newNewGameWindow->backButtonTexture),
                           newNewGameWindow->newGameRenderer,
                           BACK_NEW_GAME_WINDOW_TEXTURE_PATH);
    success &= LoadTexture(
            &(newNewGameWindow->backgroundTextureChoosingGameMode),
            newNewGameWindow->newGameRenderer,
            BACKGROUND_GAME_MODE_NEW_GAME_WINDOW_TEXTURE_PATH);
    success &= LoadTexture(
            &(newNewGameWindow->backgroundTextureChoosingDifficulty),
            newNewGameWindow->newGameRenderer,
            BACKGROUND_DIFFICULTY_NEW_GAME_WINDOW_TEXTURE_PATH);
    success &= LoadTexture(
            &(newNewGameWindow->backgroundTextureChoosingUserColor),
            newNewGameWindow->newGameRenderer,
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
    if (src->backgroundTextureChoosingGameMode != NULL)
        SDL_DestroyTexture(src->backgroundTextureChoosingGameMode);
    if (src->backgroundTextureChoosingDifficulty != NULL)
        SDL_DestroyTexture(src->backgroundTextureChoosingDifficulty);
    if (src->backgroundTextureChoosingUserColor != NULL)
        SDL_DestroyTexture(src->backgroundTextureChoosingUserColor);
    if (src->nextButtonTexture != NULL)
        SDL_DestroyTexture(src->nextButtonTexture);
    if (src->startNewGameButtonTexture != NULL)
        SDL_DestroyTexture(src->startNewGameButtonTexture);
    if (src->whiteButtonTexture != NULL)
        SDL_DestroyTexture(src->whiteButtonTexture);
    if (src->whiteButtonPressedTexture != NULL)
        SDL_DestroyTexture(src->whiteButtonPressedTexture);
    if (src->blackButtonTexture != NULL)
        SDL_DestroyTexture(src->blackButtonTexture);
    if (src->blackButtonPressedTexture != NULL)
        SDL_DestroyTexture(src->blackButtonPressedTexture);
    if (src->onePlayerButtonTexture != NULL)
        SDL_DestroyTexture(src->onePlayerButtonTexture);
    if (src->onePlayerButtonPressedTexture != NULL)
        SDL_DestroyTexture(src->onePlayerButtonPressedTexture);
    if (src->twoPlayerButtonTexture != NULL)
        SDL_DestroyTexture(src->twoPlayerButtonTexture);
    if (src->twoPlayerButtonPressedTexture != NULL)
        SDL_DestroyTexture(src->twoPlayerButtonPressedTexture);
    if (src->noobDifficultyButtonTexture != NULL)
        SDL_DestroyTexture(src->noobDifficultyButtonTexture);
    if (src->noobDifficultyButtonPressedTexture != NULL)
        SDL_DestroyTexture(src->noobDifficultyButtonPressedTexture);
    if (src->easyDifficultyButtonTexture != NULL)
        SDL_DestroyTexture(src->easyDifficultyButtonTexture);
    if (src->easyDifficultyButtonPressedTexture != NULL)
        SDL_DestroyTexture(src->easyDifficultyButtonPressedTexture);
    if (src->moderateDifficultyButtonTexture != NULL)
        SDL_DestroyTexture(src->moderateDifficultyButtonTexture);
    if (src->moderateDifficultyButtonPressedTexture != NULL)
        SDL_DestroyTexture(src->moderateDifficultyButtonPressedTexture);
    if (src->hardDifficultyButtonTexture != NULL)
        SDL_DestroyTexture(src->hardDifficultyButtonTexture);
    if (src->hardDifficultyButtonPressedTexture != NULL)
        SDL_DestroyTexture(src->hardDifficultyButtonPressedTexture);
    if (src->expertDifficultyButtonTexture != NULL)
        SDL_DestroyTexture(src->expertDifficultyButtonTexture);
    if (src->expertDifficultyButtonPressedTexture != NULL)
        SDL_DestroyTexture(src->expertDifficultyButtonPressedTexture);
    if (src->backButtonTexture != NULL)
        SDL_DestroyTexture(src->backButtonTexture);
    if (src->backButtonPressedTexture != NULL)
        SDL_DestroyTexture(src->backButtonPressedTexture);
    if (src->newGameRenderer != NULL)
        SDL_DestroyRenderer(src->newGameRenderer);
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

    SDL_RenderCopy(src->newGameRenderer,
                   src->backgroundTextureChoosingDifficulty, NULL, &backgroundR);
    if (src->difficulty != 1) {
        SDL_RenderCopy(src->newGameRenderer, src->noobDifficultyButtonTexture,
                       NULL, &noobR);
    } else {
        SDL_RenderCopy(src->newGameRenderer,
                       src->noobDifficultyButtonPressedTexture, NULL, &noobR);
    }
    if (src->difficulty != 2) {
        SDL_RenderCopy(src->newGameRenderer, src->easyDifficultyButtonTexture,
                       NULL, &easyR);
    } else {
        SDL_RenderCopy(src->newGameRenderer,
                       src->easyDifficultyButtonPressedTexture, NULL, &easyR);
    }
    if (src->difficulty != 3) {
        SDL_RenderCopy(src->newGameRenderer,
                       src->moderateDifficultyButtonTexture, NULL, &moderateR);
    } else {
        SDL_RenderCopy(src->newGameRenderer,
                       src->moderateDifficultyButtonPressedTexture, NULL, &moderateR);
    }
    if (src->difficulty != 4) {
        SDL_RenderCopy(src->newGameRenderer, src->hardDifficultyButtonTexture,
                       NULL, &hardR);
    } else {
        SDL_RenderCopy(src->newGameRenderer,
                       src->hardDifficultyButtonPressedTexture, NULL, &hardR);
    }
    if (src->difficulty != 5) {
        SDL_RenderCopy(src->newGameRenderer,
                       src->expertDifficultyButtonTexture, NULL, &expertR);
    } else {
        SDL_RenderCopy(src->newGameRenderer,
                       src->expertDifficultyButtonPressedTexture, NULL, &expertR);
    }
    SDL_RenderCopy(src->newGameRenderer, src->nextButtonTexture, NULL, &nextR);
    SDL_RenderCopy(src->newGameRenderer, src->backButtonTexture, NULL, &backR);
    SDL_RenderPresent(src->newGameRenderer);
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
    SDL_RenderCopy(src->newGameRenderer,
                   src->backgroundTextureChoosingGameMode, NULL, &backgroundR);
    if (src->gameMode == 1) {
        SDL_RenderCopy(src->newGameRenderer,
                       src->onePlayerButtonPressedTexture, NULL, &oneR);
        SDL_RenderCopy(src->newGameRenderer, src->twoPlayerButtonTexture, NULL,
                       &twoR);
        SDL_RenderCopy(src->newGameRenderer, src->nextButtonTexture, NULL,
                       &startGameNextR);
    } else {
        SDL_RenderCopy(src->newGameRenderer, src->onePlayerButtonTexture, NULL,
                       &oneR);
        SDL_RenderCopy(src->newGameRenderer,
                       src->twoPlayerButtonPressedTexture, NULL, &twoR);
        SDL_RenderCopy(src->newGameRenderer, src->startNewGameButtonTexture,
                       NULL, &startGameNextR);
    }
    SDL_RenderCopy(src->newGameRenderer, src->backButtonTexture, NULL, &backR);
    SDL_RenderPresent(src->newGameRenderer);
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
    SDL_RenderCopy(src->newGameRenderer,
                   src->backgroundTextureChoosingUserColor, NULL, &backgroundR);
    if (src->userColor == 1) {
        SDL_RenderCopy(src->newGameRenderer, src->whiteButtonPressedTexture,
                       NULL, &whiteR);
        SDL_RenderCopy(src->newGameRenderer, src->blackButtonTexture, NULL,
                       &blackR);
    } else {
        SDL_RenderCopy(src->newGameRenderer, src->whiteButtonTexture, NULL,
                       &whiteR);
        SDL_RenderCopy(src->newGameRenderer, src->blackButtonPressedTexture,
                       NULL, &blackR);
    }
    SDL_RenderCopy(src->newGameRenderer, src->startNewGameButtonTexture, NULL,
                   &startGameR);
    SDL_RenderCopy(src->newGameRenderer, src->backButtonTexture, NULL, &backR);
}

void NewGameWindowDraw(NewGameWindow *src) {
    SDL_SetRenderDrawColor(src->newGameRenderer, 255, 255, 255, 255);
    SDL_RenderClear(src->newGameRenderer);
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
    SDL_RenderPresent(src->newGameRenderer);
}

void NewGameWindowHide(NewGameWindow *src) {
    SDL_HideWindow(src->newGameWindow);
}

void NewGameWindowShow(NewGameWindow *src) {
    SDL_ShowWindow(src->newGameWindow);
}

EventStruct NewGameWindowHandleEvent(NewGameWindow *src, SDL_Event *event) {
    EventStruct eventStruct = {EmptyEvent, {0}};
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
