#include "GuiManager.h"

GuiManager* GuiManagerCreate() {
	GuiManager* newGuiManager = (GuiManager*) malloc(sizeof(GuiManager));
	if (newGuiManager == NULL) {
		printf("malloc: Error\n");
		return NULL;
	}

	newGuiManager->mainWindow = MainWindowCreate();
	if (newGuiManager->mainWindow == NULL) {
		free(newGuiManager);
		return NULL;
	}
	newGuiManager->gameWindow = NULL;
	newGuiManager->newGameWindow = NULL;
	newGuiManager->loadWindow = NULL;
	newGuiManager->currentState = MainWindowState;
	newGuiManager->lastState = MainWindowState;

	GuiManagerShowCurrentWindow(newGuiManager);
	return newGuiManager;
}

void GuiManagerHideCurrentWindow(GuiManager* src) {
	switch (src->currentState) {
	case MainWindowState:
		MainWindowHide(src->mainWindow);
		break;
	case GameWindowState:
		GameWindowHide(src->gameWindow);
		break;
	case NewGameWindowState:
		NewGameWindowHide(src->newGameWindow);
		break;
	case LoadWindowState:
		LoadWindowHide(src->loadWindow);
		break;
	}
}

void GuiManagerShowCurrentWindow(GuiManager* src) {
	switch (src->currentState) {
	case MainWindowState:
		MainWindowShow(src->mainWindow);
		break;
	case GameWindowState:
		GameWindowShow(src->gameWindow);
		break;
	case NewGameWindowState:
		NewGameWindowShow(src->newGameWindow);
		break;
	case LoadWindowState:
		LoadWindowShow(src->loadWindow);
		break;
	}
}

void GuiManagerDestroy(GuiManager* src) {
	if (src->gameWindow != NULL)
		GameWindowDestroy(src->gameWindow);
	if (src->mainWindow != NULL)
		MainWindowDestroy(src->mainWindow);
	if (src->loadWindow != NULL)
		LoadWindowDestroy(src->loadWindow);
	if (src->newGameWindow != NULL)
		NewGameWindowDestroy(src->newGameWindow);
	free(src);
}

void GuiManagerDraw(GuiManager* src) {
	switch (src->currentState) {
	case MainWindowState:
		MainWindowDraw(src->mainWindow);
		break;
	case GameWindowState:
		GameWindowDraw(src->gameWindow);
		break;
	case NewGameWindowState:
		NewGameWindowDraw(src->newGameWindow);
		break;
	case LoadWindowState:
		LoadWindowDraw(src->loadWindow);
		break;
	}
}

EventStruct GuiManagerShowNewGameWindow(GuiManager* src) {
	EventStruct eventStruct = { EmptyEvent, { 0 } };
	GuiManagerHideCurrentWindow(src);

	if (src->newGameWindow != NULL)
		NewGameWindowDestroy(src->newGameWindow);

	src->newGameWindow = NewGameWindowCreate();
	if (src->newGameWindow == NULL) {
		eventStruct.eventType = QuitEvent;
	} else {
		src->lastState = src->currentState;
		src->currentState = NewGameWindowState;
		GuiManagerShowCurrentWindow(src);
	}
	return eventStruct;
}

EventStruct GuiManagerShowLoadGameWindow(GuiManager* src) {
	EventStruct eventStruct = { EmptyEvent, { 0 } };
	GuiManagerHideCurrentWindow(src);

	if (src->loadWindow != NULL)
		LoadWindowDestroy(src->loadWindow);

	src->loadWindow = LoadWindowCreate();
	if (src->loadWindow == NULL) {
		eventStruct.eventType = QuitEvent;
	} else {
		src->lastState = src->currentState;
		src->currentState = LoadWindowState;
		GuiManagerShowCurrentWindow(src);
	}
	return eventStruct;
}

EventStruct GuiManagerShowMainGameWindow(GuiManager* src) {
	EventStruct eventStruct = { EmptyEvent, { 0 } };
	GuiManagerHideCurrentWindow(src);

	if (src->mainWindow != NULL)
		MainWindowDestroy(src->mainWindow);

	src->mainWindow = MainWindowCreate();
	if (src->mainWindow == NULL) {
		eventStruct.eventType = QuitEvent;
	} else {
		src->lastState = src->currentState;
		src->currentState = MainWindowState;
		GuiManagerShowCurrentWindow(src);
	}
	return eventStruct;
}

void GuiManagerBackButtonHandler(GuiManager* src) {
	GuiManagerHideCurrentWindow(src);
	src->currentState = src->lastState;
	GuiManagerShowCurrentWindow(src);
}

EventStruct GuiManagerStratGame(GuiManager* src, char gameMode,
		char gameDifficulty, char player1Color) {
	EventStruct eventStruct = { EmptyEvent, { 0 } };
	GuiManagerHideCurrentWindow(src);

	if (src->gameWindow != NULL)
		GameWindowDestroy(src->gameWindow);

	src->gameWindow = GameWindowCreate(gameMode, player1Color, gameDifficulty);
	if (src->gameWindow == NULL) {
		eventStruct.eventType = QuitEvent;
	} else {
		src->lastState = src->currentState;
		src->currentState = GameWindowState;
		GuiManagerShowCurrentWindow(src);
	}
	return eventStruct;
}

EventStruct GuiManagerLoadGameFromFile(GuiManager* src, char loadSlotSelected) {
	EventStruct eventStruct = { EmptyEvent, { 0 } };
	GuiManagerHideCurrentWindow(src);

	if (src->gameWindow != NULL)
		GameWindowDestroy(src->gameWindow);

	src->gameWindow = GameWindowLoad(loadSlotSelected);
	if (src->gameWindow == NULL) {
		eventStruct.eventType = QuitEvent;
	} else {
		src->lastState = src->currentState;
		src->currentState = GameWindowState;
		GuiManagerShowCurrentWindow(src);
	}
	return eventStruct;
}

EventStruct GuiManagerInternalEventHandler(GuiManager* src, EventStruct event) {
	EventStruct eventStruct = { EmptyEvent, { 0 } };
	switch (event.eventType) {
	case NewGameButtonMainWindowClickEvent:
		return GuiManagerShowNewGameWindow(src);
	case LoadGameButtonMainWindowClickEvent:
	case LoadGameButtonGameWindowClickEvent:
		return GuiManagerShowLoadGameWindow(src);
	case GoToMainWindowButtonGameWindowClickEvent:
		return GuiManagerShowMainGameWindow(src);
	case BackButtonLoadWindowClickEvent:
	case BackButtonNewGameWindowClickEvent:
		GuiManagerBackButtonHandler(src);
		return eventStruct;
	case StartGameButtonNewGameWindowClickEvent:
		return GuiManagerStratGame(src, event.eventArgument[0],
				event.eventArgument[1], event.eventArgument[2]);
	case GameLoadOptionLoadWindowClickEvent:
		return GuiManagerLoadGameFromFile(src, event.eventArgument[0]);
	case QuitButtonGameWindowClickEvent:
	case QuitButtonMainWindowClickEvent:
	case QuitEvent:
		eventStruct.eventType = QuitEvent;
		return eventStruct;
	default:
		return eventStruct;
	}
}

EventStruct GuiManagerHandleEvent(GuiManager* src, SDL_Event* event) {
	EventStruct eventStruct = { EmptyEvent, { 0 } };
	if (event == NULL) {
		return eventStruct;
	}
	if (EventIsExitEvent(event)) {
		eventStruct.eventType = QuitEvent;
		return eventStruct;
	}

	if ((event->type == SDL_MOUSEBUTTONUP && event->button.button
			== SDL_BUTTON_LEFT) || src->currentState == GameWindowState) {
		switch (src->currentState) {
		case MainWindowState:
			eventStruct = MainWindowHandleEvent(src->mainWindow, event);
			break;
		case GameWindowState:
			eventStruct = GameWindowHandleEvent(src->gameWindow, event);
			break;
		case NewGameWindowState:
			eventStruct = NewGameWindowHandleEvent(src->newGameWindow, event);
			break;
		case LoadWindowState:
			eventStruct = LoadWindowHandleEvent(src->loadWindow, event);
			break;
		}
	}
	return GuiManagerInternalEventHandler(src, eventStruct);
}
