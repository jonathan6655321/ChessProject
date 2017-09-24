////
//// Created by Jonathan on 7/18/2017.
////
#include <stdlib.h>
#include "CommandLineGame.h"
#include "Gui/mainGui.h"
#include <string.h>

int main(int argc, char **argv) {
	if (argc == 2 && strcmp("-g", argv[1]) == 0) {
		MainGuiLoop();
	} else {
		commandLineGameLoop();
	}

	return 0;
}
