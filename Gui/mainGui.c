#include <SDL.h>
#include <SDL_video.h>
#include <stdio.h>
#include "GuiManager.h"


int main(int argc, char** argv) {
	//Init the SDL pakage.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { //SDL2 INIT
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}

	// Create the main instance
	GuiManager* guiManager = GuiManagerCreate();
	if (guiManager == NULL) {
		SDL_Quit();
		return 0;
	}

	// While event is not QuitEvent, keep handling event and drawing the game.
	SDL_Event event;
	while (1) {
		SDL_WaitEvent(&event);
		if (GuiManagerHandleEvent(guiManager, &event).eventType == QuitEvent) {
			break;
		}
		GuiManagerDraw(guiManager);
	}

	// End gui manager and quit game.
	GuiManagerDestroy(guiManager);
	SDL_Quit();
	return 0;
}

