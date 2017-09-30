#ifndef EVENTS_H_
#define EVENTS_H_

/*!
 *	All events type that can occurs in the game.
 */
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
} EventType;

/*!
 * Event struct represent an event that happened in the game, with possible arguments.
 */
typedef struct {
	EventType eventType;
	char eventArgument[3];
} EventStruct;

#endif
