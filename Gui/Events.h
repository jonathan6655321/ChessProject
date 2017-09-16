#ifndef EVENTS_H_
#define EVENTS_H_

typedef enum {
	NewGameButtonMainWindowClickEvent,
	LoadGameButtonMainWindowClickEvent,
	QuitButtonMainWindowClickEvent,
	
	BoardPositionButtonGameWindowClickEvent,
	UndoButtonGameWindowClickEvent,
	SaveGameButtonGameWindowClickEvent,
	LoadGameButtonGameWindowClickEvent,
	RestartGameButtonGameWindowClickEvent,
	GoToMainWindowButtonGameWindowClickEvent,
	QuitButtonGameWindowClickEvent,
	
	GameLoadOptionLoadWindowClickEvent,
	BackButtonLoadWindowClickEvent,
	
	GameModeButtonNewGameWindowClickEvent,
	DifficultyModeButtonNewGameWindowClickEvent,
	BackButtonNewGameWindowClickEvent,
	StartGameButtonNewGameWindowClickEvent,
	
	QuitEvent,
	EmptyEvent
} EventType

typedef struct {
	EventType eventType;
	char eventArgument[3];
} EventStruct;

#endif
